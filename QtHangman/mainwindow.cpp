#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_title->setAlignment(Qt::AlignCenter);   //Aligning label text to center
    QFont f("Arial",40);        //Setting the default font size to 50
    QFontMetrics fm(f);
    ui->label_title->setFont(f);

    ui->groupBox_gameScreen->setVisible(false);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Start_clicked()
{
    this->ui->groupBox_gameScreen->setVisible(true);
    this->ui->groupBox_startScreen->setVisible(false);
}

