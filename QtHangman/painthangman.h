#ifndef PAINTHANGMAN_H
#define PAINTHANGMAN_H

#include <QWidget>
#include <QPainter>

class paintHangman : public QWidget
{
    Q_OBJECT
public:
    explicit paintHangman(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent*);

signals:

};

#endif // PAINTHANGMAN_H
