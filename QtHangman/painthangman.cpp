#include "painthangman.h"

paintHangman::paintHangman(QWidget *parent)
    : QWidget{parent}
{

}


void paintHangman::paintEvent(QPaintEvent *ev){
    QPainter p(this);
    QPen pen(Qt::black,5);
    p.setPen(pen);

    //p.drawLine();
}
