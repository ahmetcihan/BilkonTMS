#include "mainwindow.h"
#include "ui_mainwindow.h"

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
