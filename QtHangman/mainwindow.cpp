#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qdebug.h"

#define QD qDebug() << __FILE__ << __LINE__

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_title->setAlignment(Qt::AlignCenter);
    QFont f("Arial",40);
    ui->label_title->setFont(f);

    ui->groupBox_gameScreen->setVisible(false);
    ui->pushButton_Start->setVisible(false);
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

void MainWindow::on_pushButton_chooseFile_clicked()
{
    this->m_file_path = QFileDialog::getOpenFileName();
    QString msg = "Choosen file: " + m_file_path;
    this->ui->label_fileName->setText(msg);

    QFileInfo fi(m_file_path);

    QString ext = fi.completeSuffix();

    if(ext == "txt"){
        this->ui->pushButton_Start->setVisible(true);

        this->ui->label_errorMsg->setVisible(false);
    }
    else{
        this->ui->label_errorMsg->setText("Only use txt files.");
        this->ui->label_errorMsg->setStyleSheet("border: 1px solid red;");
    }
}

