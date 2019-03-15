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
MainWindow::~MainWindow()
{
    delete ui;
}
