#ifndef MYLINE_LINE_H
#define MYLINE_LINE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class MyLine_Line : public QObject , public QGraphicsItem
{
    Q_OBJECT

public:
    explicit MyLine_Line(QObject *parent = nullptr);
    MyLine_Line(QLineF c, int p1, int p2, int mass){
        line = c;
        my_ellips_1 = p1;
        my_ellips_2 = p2;
        schetchik_i = mass;
    }
    ~MyLine_Line();
    QLineF GetLine();
    int Get_number_ellips1();
    int Get_number_ellips2();

signals:


public slots:


private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QLineF line;
    double point_x;
    double point_y;
    int schetchik_i;
    int my_ellips_1;
    int my_ellips_2;
};

#endif // MYLINE_LINE_H
