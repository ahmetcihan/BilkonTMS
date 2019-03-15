#include "mainwindow.h"
#include "ui_mainwindow.h"

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
