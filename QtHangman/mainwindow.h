#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QFileDialog>
#include <QHBoxLayout>

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

    QString m_file_path;
    QList<QString> m_words;
    QString m_choosenWord;
    QList<QChar> guessesList;



    QHBoxLayout *m_lay;
    QList<QLabel*> labelsList;


private slots:
    void on_pushButton_Start_clicked();

    void on_pushButton_chooseFile_clicked();

    void on_pushButton_guess_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
