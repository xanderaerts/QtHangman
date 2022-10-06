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

    this->ph = new PaintHangman();

    this->m_lay2 = new QHBoxLayout(this->ui->widget_hangman);

    this->ui->widget_hangman->setLayout(this->m_lay2);
    this->m_lay2->addWidget(ph);

    this->ui->widget_hangman->setFixedWidth(600);

    this->ui->stackedWidget->setCurrentIndex(0);
    this->ui->pushButton_Start->setVisible(false);

    this->ui->label_fileName->setHidden(true);
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
    this->ui->stackedWidget->setCurrentIndex(1);

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
        this->writeError("Only use .txt files",this->ui->label_errorWrongFile);
        this->ui->pushButton_Start->setVisible(false);
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

    bool doubleGuess = false;

    this->ui->label_errorGuessTwice->setHidden(true);

    QString guessString = this->ui->lineEdit_guess->text();
    QChar guessC = guessString[0];

    this->ui->lineEdit_guess->setText("");

   int guessChecked = checkGuess(guessC);
   if(guessChecked == -1){
       doubleGuess = true;
   }
   else{doubleGuess = false;}

   if(this->correctGuesses == this->m_choosenWord.length()){
       this->endGame(true);
   }
    if(guessChecked == 0 && !doubleGuess){
        this->ph->hangmanState++;
        this->ph->repaint();
        //QD << "twas fout";
    }

    if(this->ph->hangmanState == 10){
        this->endGame(false);
    }
}

int MainWindow::checkGuess(QChar guessC){
    bool correct = false;

    for(QChar c : this->guessesList){
        QD << "lol";
        if(c == guessC){
            writeError("Guessed this letter already",this->ui->label_errorGuessTwice);
            return -1;
        }
    }
    this->guessesList.append(guessC);

    for(int i = 0; i < this->m_choosenWord.length();i++){
        if(guessC == this->m_choosenWord[i]){
            this->labelsList[i]->setText(guessC);
            this->correctGuesses++;
            QD << this->correctGuesses;
            correct = true;

        }
    }

    if(correct){
        return 1;
    }

    return 0;
}

void MainWindow::endGame(bool status){

    this->ui->stackedWidget->setCurrentIndex(2);
    if(status){
        this->ui->label_endGame->setText("You won");
    }
    else{
        this->ui->label_endGame->setText("You lost");
    }
}

void MainWindow::on_pushButton_restart_clicked()
{
    this->resetGame();
    this->on_pushButton_Start_clicked();
}

void MainWindow::resetGame(){

    for(int i = 0;i<this->labelsList.length();i++){

    this->m_lay->removeWidget(this->labelsList[i]);
    delete this->labelsList[i];

    }

    this->labelsList.clear();
    this->guessesList.clear();
    this->correctGuesses = 0;
    this->m_choosenWord = "";
    this->ph->hangmanState = 0;

}

void MainWindow::on_pushButton_exit_clicked()
{
    QApplication::exit();
}


void MainWindow::on_lineEdit_guess_returnPressed()
{
    MainWindow::on_pushButton_guess_clicked();
}

