#ifndef MYLINE_H
#define MYLINE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class MyLine : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MyLine(QObject *parent = nullptr);
    MyLine(double point_1, double point_2, int pointsi , int i){
        point_x = point_1;
        point_y = point_2;
        points = pointsi;
        schetchik_i = i;
    }
    ~MyLine();


signals:

    void signal_push(double p1, double p2, int n);

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:

    void SetMax(int m);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    double point_x;
    double point_y;
    int points;
    int schetchik_i;
    int max;
};

#endif // MYLINE_H
