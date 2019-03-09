#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    remote  = new RemoteConnection(8945,this);

    remote->setTarget("10.10.255.177");

    QTimer::singleShot(1000,this,SLOT(start_comm()));
    connect(ui->pushButton_read_parameter,SIGNAL(clicked()),this,SLOT(read_parameter()));
    connect(remote,SIGNAL(periodic_response_handler(QByteArray)),this,SLOT(periodic_response_handler(QByteArray)));
    init_THEME();

    initilize_plot();
    ui->label_communication->setText("No communication");
}
void MainWindow::init_THEME(void){
    theme_index = 4;

    ui->comboBox_theme->addItem(QStringLiteral("DEFAULT"));
    ui->comboBox_theme->addItem(QStringLiteral("SANDY"));
    ui->comboBox_theme->addItem(QStringLiteral("METAL"));
    ui->comboBox_theme->addItem(QStringLiteral("FIRE"));
    ui->comboBox_theme->addItem(QStringLiteral("BLACK"));
    ui->comboBox_theme->addItem(QStringLiteral("BLACK-FAST"));
    ui->comboBox_theme->addItem(QStringLiteral("DARK-ORANGE"));
    ui->comboBox_theme->addItem(QStringLiteral("COFFEE"));
    ui->comboBox_theme->addItem(QStringLiteral("PAGEFOLD"));
    ui->comboBox_theme->addItem(QStringLiteral("QDark"));
    ui->comboBox_theme->addItem(QStringLiteral("Denemeci"));
    ui->comboBox_theme->setCurrentIndex(theme_index);
    set_gradient(theme_index);

}

void MainWindow::set_gradient(int val){
    QFile file;

    switch(val){
    case 0:
        break;
    case 1:
        file.setFileName(":/qss/qmc-sandy/qmc.qss");
        break;
    case 2:
        file.setFileName(":/qss/qmc-metal/qmc.qss");
        break;
    case 3:
        file.setFileName(":/qss/qmc2-fire-0.8/qmc2-fire-0.8.qss");
        break;
    case 4:
        file.setFileName(":/qss/qmc2-black-0.10/qmc2-black-0.10.qss");
        break;
    case 5:
        file.setFileName(":/qss/qmc2-black-fast/qmc2-black-0.10.qss");
        break;
    case 6:
        file.setFileName(":/qss/darkOrange/darkOrange.qss");
        break;
    case 7:
        file.setFileName(":/qss/coffee/coffee.qss");
        break;
    case 8:
        file.setFileName(":/qss/pagefold/pagefold.qss");
        break;
    case 9:
        file.setFileName(":/qss/QDark/QDark.qss");
        break;
    case 10:
        file.setFileName(":/qss/denemeci/denemeci.qss");
        break;
    }
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);
    currentStyleSheet = styleSheet;

    theme_index = val;
    connect(this->ui->comboBox_theme,SIGNAL(currentIndexChanged(int)),this,SLOT(set_gradient(int)));
}
void MainWindow::initilize_plot(void){
    customPlot = new QCustomPlot(this->ui->plot_widget);

    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->setGeometry(0,0,ui->plot_widget->width(),ui->plot_widget->height());
    // give the axes some labels:
    customPlot->yAxis->setLabel("LOAD (kN)");
    customPlot->xAxis->setLabel("TIME (s)");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();
}
void MainWindow::plot_graph(void){
    static bool first_in = false;
    static unsigned int counter = 0;
    static double max_y = 0;
    static double min_y = 0;
    double x_axis,y_axis;

    if(first_in == false){
        first_in = true;
        graph_time.start();
        counter = 0;
    }
    x_axis = (double)graph_time.elapsed() / 1000;
    customPlot->xAxis->setRange(0,x_axis+1);

    y_axis = real_time.load;
    if(y_axis > max_y){
        max_y = y_axis;
    }
    if(y_axis < min_y){
        min_y = y_axis;
    }
    customPlot->yAxis->setRange(min_y-1,max_y+1);

    customPlot->graph(0)->addData(x_axis,y_axis);
    counter++;

    customPlot->replot();
}
void MainWindow::read_parameter(void){
    remote->get("param.pace_rate");
}

void MainWindow::start_comm(void){
    qDebug(__FUNCTION__);

    remote->set("device_settings.stream.enable", "1");

}
void MainWindow::periodic_response_handler(QByteArray datagram){
    union _my_resp{
        int _integer;
        float _float;
    };
    _my_resp my_resp;
    int start_stream = 0;
    int tmp = 0;

    start_stream = (unsigned char)datagram[0] + ((unsigned char)datagram[1] << 8) + ((unsigned char)datagram[2] << 16) + ((unsigned char)datagram[3] << 24);
    if(start_stream == 0x11223344){
        ui->label_communication->setText("Communication is established");

        real_time.test_no = (unsigned char)datagram[4] + ((unsigned char)datagram[5] << 8) + ((unsigned char)datagram[6] << 16) + ((unsigned char)datagram[7] << 24);

        tmp = (unsigned char)datagram[8] + ((unsigned char)datagram[9] << 8);
        if(tmp == 0){
            real_time.status = "Test is STOPPED";
        }
        else if(tmp == 1){
            real_time.status = "Test is RUNNING";
        }
        else if(tmp == 2){
            real_time.status = "Test is PAUSED";
        }
        else if(tmp == 3){
            real_time.status = "Test is FINISHED";
        }

        my_resp._integer = ((unsigned char)datagram[10] + ((unsigned char)datagram[11] << 8) + ((unsigned char)datagram[12] << 16) + ((unsigned char)datagram[13] << 24));
        real_time.area = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[14] + ((unsigned char)datagram[15] << 8) + ((unsigned char)datagram[16] << 16) + ((unsigned char)datagram[17] << 24));
        real_time.load = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[18] + ((unsigned char)datagram[19] << 8) + ((unsigned char)datagram[20] << 16) + ((unsigned char)datagram[21] << 24));
        real_time.stress = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[22] + ((unsigned char)datagram[23] << 8) + ((unsigned char)datagram[24] << 16) + ((unsigned char)datagram[25] << 24));
        real_time.ch2 = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[26] + ((unsigned char)datagram[27] << 8) + ((unsigned char)datagram[28] << 16) + ((unsigned char)datagram[29] << 24));
        real_time.ch3 = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[30] + ((unsigned char)datagram[31] << 8) + ((unsigned char)datagram[32] << 16) + ((unsigned char)datagram[33] << 24));
        real_time.ch4 = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[34] + ((unsigned char)datagram[35] << 8) + ((unsigned char)datagram[36] << 16) + ((unsigned char)datagram[37] << 24));
        real_time.encoder = my_resp._float;

        ui->label_current_test_no->setText(QString::number(real_time.test_no,10));
        ui->label_test_status->setText(real_time.status);
        ui->label_area->setText(QString::number(real_time.area,'f',3));
        ui->label_main_load->setText(QString::number(real_time.load,'f',3));
        ui->label_stress->setText(QString::number(real_time.stress,'f',3));
        ui->label_main_ch2->setText(QString::number(real_time.ch2,'f',3));
        ui->label_main_ch3->setText(QString::number(real_time.ch3,'f',3));
        ui->label_main_ch4->setText(QString::number(real_time.ch4,'f',3));
        ui->label_main_displacement->setText(QString::number(real_time.encoder,'f',3));
        plot_graph();
    }
    else{
        ui->label_communication->setText("No communication");
        qDebug() << "başka veri";
        qDebug() << datagram;
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}
