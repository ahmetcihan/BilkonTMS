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
        double encoder;
    };
    struct _real_time real_time;


public slots:
    void start_comm(void);
    void read_parameter(void);
    void periodic_response_handler(QByteArray datagram);
    void set_gradient(int val);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
