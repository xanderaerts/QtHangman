#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QFileDialog>
#include <QHBoxLayout>
#include <painthangman.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readWords();
    void chooseWord();
    void drawLabels();
    int checkGuess(QChar);
    void writeError(QString msg,QLabel *location);
    void endGame(bool);
    void resetGame();

    QString m_file_path;
    QList<QString> m_words;
    QString m_choosenWord;
    QList<QChar> guessesList;
    QList<QLabel*> labelsList;
    int correctGuesses=0;
    PaintHangman *ph;



    QHBoxLayout *m_lay;
    QHBoxLayout *m_lay2;



private slots:
    void on_pushButton_Start_clicked();

    void on_pushButton_chooseFile_clicked();

    void on_pushButton_guess_clicked();

    void on_pushButton_restart_clicked();

    void on_pushButton_exit_clicked();

    void on_lineEdit_guess_returnPressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
