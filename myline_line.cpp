#include "myline_line.h"

MyLine_Line::MyLine_Line(QObject *parent) : QObject(parent), QGraphicsItem () {}

MyLine_Line::~MyLine_Line() {}

//возвращаем текущее положение линии(обязательная функция так как paint чистая виртуальная)
QRectF MyLine_Line::boundingRect() const {
    return QRectF(line.p1().rx(), line.p1().ry(), line.p2().rx(), line.p2().ry());
}
//рисуем линию и цыфирки над ней
void MyLine_Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(QPen(Qt::black,2));//устанавливаем палку-рисовалку на черный цвет
    painter->drawLine(line);
    painter->setFont(QFont("Calibri", 11));//устанавливаем шрифт
    painter->setPen(QPen(Qt::blue, 2));
    painter->drawText((line.p1().rx() - 10) + (line.p2().rx() - line.p1().rx())/2,
                      line.p1().ry() + (line.p2().ry() - line.p1().ry())/2,
                      QString::number(schetchik_i));//преобразование счетчика в текст
    Q_UNUSED(option);//отключаем опции
    Q_UNUSED(widget);//отключаем доп виджиты
}
//возвращаем положение линии (все дальше методы для того чтобы сделать кривую раскраску пути)
QLineF MyLine_Line::GetLine(){
    return line;
}

int MyLine_Line::Get_number_ellips1(){
    return my_ellips_1;
}

int MyLine_Line::Get_number_ellips2(){
    return my_ellips_2;
}
