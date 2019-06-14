#include "myline.h"
#include "mainwindow.h"
#include "QtMath"

MyLine::MyLine(QObject *parent) : QObject(parent),  QGraphicsItem() {}

MyLine::~MyLine() {}

//возвращаемый сигнал по клику мышкой
void MyLine::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit signal_push(point_x + 22.5/log2(points), point_y + 22.5/log2(points), schetchik_i);//возвращаем значения центра
    QGraphicsItem::mousePressEvent(event);
}

QRectF MyLine::boundingRect() const { //возвращаем текущее положение фигуры
    return QRectF(point_x,point_y,55/log2(points), 55/log2(points));
}

void MyLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(QPen(Qt::black,1));//устанавливаем палку-рисовалку на черный цвет
    painter->setBrush(QBrush(Qt::black));//устанавливаем заливку
    painter->drawEllipse(point_x, point_y , 55/log2(points), 55/log2(points));//рисуем круг

    painter->setFont(QFont("Calibri", 12));//устанавливаем шрифт
    painter->drawText(point_x , point_y, QString::number(schetchik_i));//преобразование счетчика в текст

    Q_UNUSED(option);//отключаем опции
    Q_UNUSED(widget);//отключаем доп виджиты
}
//получаем из главного экрана количество точек
void MyLine::SetMax(int m){
    max = m;
}
