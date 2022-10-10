#include "painthangman.h"
#include "QDebug"

#define QD qDebug() << __FILE__ << __LINE__

PaintHangman::PaintHangman(QWidget *parent)
    : QWidget{parent}
{

}


void PaintHangman::paintEvent(QPaintEvent *ev){
    QPainter p(this);
    QPen pen(Qt::black,5);
    p.setPen(pen);

    switch(this->hangmanState){
        case 10:
            p.drawLine(250,250,300,320);
            [[fallthrough]];
        case 9:
            p.drawLine(250,250,200,320);
            [[fallthrough]];
        case 8:
            p.drawLine(250,180,300,230);
            [[fallthrough]];
        case 7:
            p.drawLine(250,180,200,230);
            [[fallthrough]];
        case 6:
            p.drawLine(250,170,250,250);
            [[fallthrough]];
        case 5:
            p.drawLine(245,145,255,145);
            p.drawEllipse(235,125,10,10);
            p.drawEllipse(255,125,10,10);
            p.drawEllipse(225,110,50,50);
            [[fallthrough]];
        case 4:
            p.drawLine(250,20,250,100);
            [[fallthrough]];
        case 3:
            p.drawLine(20,20,250,20);
            [[fallthrough]];
        case 2:
            p.drawLine(20,400,20,20);
            [[fallthrough]];
        case 1:
            p.drawLine(10,400,500,400);
    }
}
