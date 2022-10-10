#ifndef PAINTHANGMAN_H
#define PAINTHANGMAN_H

#include <QWidget>
#include <QPainter>

class PaintHangman : public QWidget
{
    Q_OBJECT
public:
    explicit PaintHangman(QWidget *parent = nullptr);
    int hangmanState = 0;

protected:
    void paintEvent(QPaintEvent*);

signals:

};

#endif // PAINTHANGMAN_H
