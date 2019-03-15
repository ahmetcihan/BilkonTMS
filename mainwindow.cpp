#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    remote  = new RemoteConnection(8945,this);

    remote->setTarget("192.168.1.177");

    QTimer::singleShot(1000,this,SLOT(start_comm()));
    connect(remote,SIGNAL(periodic_response_handler(QByteArray)),this,SLOT(periodic_response_handler(QByteArray)));
    init_THEME();

    initilize_plot();
    ui->label_communication->setText("No communication");

    connect(ui->pushButton_tare_ch2,SIGNAL(clicked()),this,SLOT(tare_ch2()));
    connect(ui->pushButton_tare_ch3,SIGNAL(clicked()),this,SLOT(tare_ch3()));
    connect(ui->pushButton_tare_ch4,SIGNAL(clicked()),this,SLOT(tare_ch4()));
    connect(ui->pushButton_start_test,SIGNAL(clicked()),this,SLOT(start_test()));
    connect(ui->pushButton_stop_motor,SIGNAL(clicked()),this,SLOT(stop_test()));
    connect(ui->pushButton_pause_test,SIGNAL(clicked()),this,SLOT(pause_test()));
    connect(ui->pushButton_refresh,SIGNAL(clicked()),this,SLOT(refresh_test()));

    connect(ui->pushButton_read_from_device,SIGNAL(clicked()),this,SLOT(read_parameters_from_the_device()));
    connect(ui->pushButton_write_to_device,SIGNAL(clicked()),this,SLOT(write_parameters_to_the_device()));

    connect(this, SIGNAL(test_value_tracker(QString)),this, SLOT(test_value_handler(QString)));

}
void MainWindow::read_parameters_from_the_device(void){
    static u8 tmp = 0;
    switch(tmp){
    case 0:
        remote->get("param.pace_rate");
        QTimer::singleShot(100,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 1:
        remote->get("param.start_speed");
        QTimer::singleShot(100,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 2:
        remote->get("param.max_load");
        QTimer::singleShot(100,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 3:
        remote->get("param.failure_treshold");
        QTimer::singleShot(100,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 4:
        remote->get("param.zero_suppression");
        QTimer::singleShot(100,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 5:
        remote->get("param.break_percentage");
        QTimer::singleShot(100,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 6:
        remote->get("param.dp.load");
        QTimer::singleShot(100,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 7:
        remote->get("param.dp.ch2");
        QTimer::singleShot(100,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 8:
        remote->get("param.dp.ch3");
        QTimer::singleShot(100,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 9:
        remote->get("param.dp.ch4");
        QTimer::singleShot(100,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 10:
        remote->get("param.dp.stress");
        QTimer::singleShot(100,this,SLOT(read_parameters_from_the_device()));
        tmp++;
        break;
    case 11:
        remote->get("test.type");
        tmp = 0;
        break;
    }

}
void MainWindow::write_parameters_to_the_device(void){

}

void MainWindow::test_value_handler(QString val){
    if(real_time.status == "Test is STOPPED"){
        ui->pushButton_start_test->setStyleSheet("min-width: 50px; min-height: 50px;"
                                                    "border-image: url(:sari_start.png);"
                                                    "border-width: 0px ;");
        ui->pushButton_pause_test->setStyleSheet("min-width: 50px; min-height: 50px;"
                                                    "border-image: url(:sari_pause-silver.png);"
                                                    "border-width: 0px ;");
        ui->pushButton_stop_motor->setStyleSheet("min-width: 50px; min-height: 50px;"
                                                    "border-image: url(:sari_stop-silver.png);"
                                                    "border-width: 0px ;");
        ui->pushButton_refresh->hide();

    }
    else if(real_time.status == "Test is RUNNING"){
        ui->pushButton_start_test->setStyleSheet("min-width: 50px; min-height: 50px;"
                                                    "border-image: url(:sari_start-silver.png);"
                                                    "border-width: 0px ;");
        ui->pushButton_pause_test->setStyleSheet("min-width: 50px; min-height: 50px;"
                                                    "border-image: url(:sari_pause.png);"
                                                    "border-width: 0px ;");
        ui->pushButton_stop_motor->setStyleSheet("min-width: 50px; min-height: 50px;"
                                                    "border-image: url(:sari_stop.png);"
                                                    "border-width: 0px ;");
        ui->pushButton_refresh->hide();
    }
    else if(real_time.status == "Test is PAUSED"){
        ui->pushButton_start_test->setStyleSheet("min-width: 50px; min-height: 50px;"
                                                    "border-image: url(:sari_start.png);"
                                                    "border-width: 0px ;");
        ui->pushButton_pause_test->setStyleSheet("min-width: 50px; min-height: 50px;"
                                                    "border-image: url(:sari_pause.png);"
                                                    "border-width: 0px ;");
        ui->pushButton_stop_motor->setStyleSheet("min-width: 50px; min-height: 50px;"
                                                    "border-image: url(:sari_stop.png);"
                                                    "border-width: 0px ;");
        ui->pushButton_refresh->hide();
    }
    else if(real_time.status == "Test is FINISHED"){
        ui->pushButton_pause_test->setStyleSheet("min-width: 50px; min-height: 50px;"
                                                    "border-image: url(:sari_pause-silver.png);"
                                                    "border-width: 0px ;");
        ui->pushButton_stop_motor->setStyleSheet("min-width: 50px; min-height: 50px;"
                                                    "border-image: url(:sari_stop-silver.png);"
                                                    "border-width: 0px ;");
        ui->pushButton_refresh->setStyleSheet("min-width: 50px; min-height: 50px;"
                                                    "border-image: url(:sari_refresh.png);"
                                                    "border-width: 0px ;");
        ui->pushButton_refresh->show();
    }
    else {

    }
}
void MainWindow::tare_ch2(void){
    remote->set("main.tare.ch2", "1");
}
void MainWindow::tare_ch3(void){
    remote->set("main.tare.ch3", "1");
}
void MainWindow::tare_ch4(void){
    remote->set("main.tare.ch4", "1");
}
void MainWindow::start_test(void){
    remote->set("main.start_test", "1");
}
void MainWindow::stop_test(void){
    remote->set("main.stop_test", "1");
}
void MainWindow::pause_test(void){
    remote->set("main.pause_test", "1");
}
void MainWindow::refresh_test(void){
    remote->set("main.refresh", "1");
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

        my_resp._integer = ((unsigned char)datagram[15] + ((unsigned char)datagram[16] << 8) + ((unsigned char)datagram[17] << 16) + ((unsigned char)datagram[18] << 24));
        real_time.load = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[20] + ((unsigned char)datagram[21] << 8) + ((unsigned char)datagram[22] << 16) + ((unsigned char)datagram[23] << 24));
        real_time.ch2 = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[25] + ((unsigned char)datagram[26] << 8) + ((unsigned char)datagram[27] << 16) + ((unsigned char)datagram[28] << 24));
        real_time.ch3 = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[30] + ((unsigned char)datagram[31] << 8) + ((unsigned char)datagram[32] << 16) + ((unsigned char)datagram[33] << 24));
        real_time.ch4 = my_resp._float;

        my_resp._integer = ((unsigned char)datagram[35] + ((unsigned char)datagram[36] << 8) + ((unsigned char)datagram[37] << 16) + ((unsigned char)datagram[38] << 24));
        real_time.stress = my_resp._float;

        ui->label_current_test_no->setText(QString("Test No : ") + QString::number(real_time.test_no,10));
        ui->label_test_status->setText(real_time.status);
        ui->label_area->setText(QString("Area : ") + QString::number(real_time.area,'f',3));
        ui->label_main_load->setText(QString::number(real_time.load,'f',3));
        ui->label_main_stress->setText(QString::number(real_time.stress,'f',3));
        ui->label_main_ch2->setText(QString::number(real_time.ch2,'f',3));
        ui->label_main_ch3->setText(QString::number(real_time.ch3,'f',3));
        ui->label_main_ch4->setText(QString::number(real_time.ch4,'f',3));
        plot_graph();
        emit test_value_tracker(real_time.status);
    }
    else{
        ui->label_communication->setText("No communication");
        qDebug() << "başka veri";
        qDebug() << datagram;

        QString str = datagram;
        QString first_section = str.section(":",0,0);
        QString second_section = str.section(":",1,1);
        QString third_section = str.section(":",2,2);

        if(first_section == "get"){
            if(second_section == "param.pace_rate"){
                ui->doubleSpinBox_pace_rate->setValue(third_section.toDouble());
                ui->doubleSpinBox_pace_rate_mpa->setValue(1000*(double)third_section.toDouble()/(double)real_time.area);
            }
            else if(second_section == "param.start_speed"){
                ui->spinBox_start_speed_percentage->setValue(third_section.toInt());
            }
            else if(second_section == "param.max_load"){
                ui->doubleSpinBox_max_load->setValue(third_section.toDouble());
            }
            else if(second_section == "param.failure_treshold"){
                ui->doubleSpinBox_load_treshold->setValue(third_section.toDouble());
            }
            else if(second_section == "param.zero_suppression"){
                ui->doubleSpinBox_zero_suppression->setValue(third_section.toDouble());
            }
            else if(second_section == "param.break_percentage"){
                ui->spinBox_break_percentage->setValue(third_section.toInt());
            }
            else if(second_section == "param.dp.load"){
                ui->spinBox_dp_load->setValue(third_section.toInt());
            }
            else if(second_section == "param.dp.ch2"){
                ui->spinBox_dp_ch2->setValue(third_section.toInt());
            }
            else if(second_section == "param.dp.ch3"){
                ui->spinBox_dp_ch3->setValue(third_section.toInt());
            }
            else if(second_section == "param.dp.ch4"){
                ui->spinBox_dp_ch4->setValue(third_section.toInt());
            }
            else if(second_section == "param.dp.stress"){
                ui->spinBox_dp_stress->setValue(third_section.toInt());
            }
            else if(second_section == "test.type"){
                if(third_section.toInt() == 0){
                    ui->radioButton_compression->setChecked(true);
                }
                else if(third_section.toInt() == 1){
                    ui->radioButton_flexural->setChecked(true);
                }
                else if(third_section.toInt() == 2){
                    ui->radioButton_split_tensile->setChecked(true);
                }
            }
        }
        else if(first_section == "set"){
            qDebug() << "inside set";
        }
        else{
            qDebug() << "inside nothing";
        }

        //qDebug() << "section 0 0" << dene.section(":",0,0) << "section 1 1" << dene.section(":",1,1) << "section 2 2" << dene.section(":",2,2);
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}
