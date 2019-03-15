#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include <qcustomplot.h>
#include "remoteconnection.h"

typedef char s8;
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initilize_plot(void);
    void plot_graph(void);
    void init_THEME(void);

    RemoteConnection *remote;
    QCustomPlot *customPlot;
    QElapsedTimer graph_time;
    QString currentStyleSheet;
    u8 theme_index;

    struct _real_time{
        int test_no;
        QString status;
        double area;
        double load;
        double stress;
        double ch2;
        double ch3;
        double ch4;
    };
    struct _real_time real_time;
signals:
    void test_value_tracker(QString val);

public slots:
    void test_value_handler(QString val);
    void start_comm(void);
    void periodic_response_handler(QByteArray datagram);
    void set_gradient(int val);
    void tare_ch2(void);
    void tare_ch3(void);
    void tare_ch4(void);
    void start_test(void);
    void stop_test(void);
    void pause_test(void);
    void refresh_test(void);
    void read_parameters_from_the_device(void);
    void write_parameters_to_the_device(void);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
