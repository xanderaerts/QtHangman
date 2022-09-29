#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qdebug.h"
#include "QRandomGenerator"

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
    ui->label_fileName->setHidden(true);

    this->m_lay = new QHBoxLayout(this->ui->widget_labels);
    this->ui->widget_labels->setLayout(m_lay);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Start_clicked()
{
    this->ui->groupBox_gameScreen->setVisible(true);
    this->ui->groupBox_startScreen->setVisible(false);

    this->readWords();
    this->chooseWord();
    QD << this->m_choosenWord;
    this->drawLabels();
}

void MainWindow::on_pushButton_chooseFile_clicked()
{
    this->m_file_path = QFileDialog::getOpenFileName();
    QString msg = "Choosen file: " + m_file_path;

    this->ui->label_fileName->setText(msg);
    this->ui->label_fileName->setHidden(false);

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


void MainWindow::readWords(){
   QFile f(this->m_file_path);

   if(!f.open(QIODevice::ReadOnly)){
       qFatal("Could not open the file");
   }

   QTextStream in(&f);
   while(!in.atEnd()){
       QString line = in.readLine();
       this->m_words.append(line);
   }
   f.close();
}

void MainWindow::chooseWord(){
    quint32 rint = QRandomGenerator::global()->bounded(0,this->m_words.length());
    this->m_choosenWord = this->m_words[rint];
}

void MainWindow::drawLabels(){


    for(int i = 0; i<this->m_choosenWord.length();i++){
        QLabel *l = new QLabel("__");
        this->labelsList.append(l);
        this->m_lay->addWidget(l);

    }
}
