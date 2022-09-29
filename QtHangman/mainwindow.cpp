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

    this->ui->label_errorWrongFile->setHidden(true);
    this->ui->label_errorGuessTwice->setHidden(true);


    this->m_lay = new QHBoxLayout(this->ui->widget_labels);
    this->ui->widget_labels->setLayout(m_lay);

    this->ui->lineEdit_guess->setFixedWidth(30);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeError(QString msg,QLabel *location){
    location->setText(msg);
    location->setStyleSheet("border: 1px solid red;");
    location->setHidden(false);

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
        this->ui->label_errorWrongFile->setHidden(true);
    }
    else{
        this->writeError("Only use txt files",this->ui->label_errorWrongFile);
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

void MainWindow::on_pushButton_guess_clicked(){
    QList<QChar> guessesList;
    QString guessString = this->ui->lineEdit_guess->text();
    QChar guessC = guessString[0];

    if(guessesList.length() == 0){
        guessesList.append(guessC);
    }

    switch(checkGuess(guessC,guessesList)){
        case 0:
            writeError("Guessed this letter already",this->ui->label_errorGuessTwice);
            break;
        case 1:
            break;

    }
}

int MainWindow::checkGuess(QChar guessC, QList<QChar>guessesList){
    if(guessesList.length()> 1){
        for(QChar c : guessesList){
            QD << "lol";
            if(c == guessC){
                return 0;}
        }
    }

    for(int i = 0; i < this->m_choosenWord.length();i++){
        if(c == this->m_choosenWord[i]){
                QD << c;
        }
    }

}



