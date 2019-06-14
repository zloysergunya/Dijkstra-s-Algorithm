#include "m_road.h"
#include "ui_m_road.h"
#include "mainwindow.h"
#include <QAbstractButton>

m_road::m_road(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::m_road) {
    ui->setupUi(this);
    //конектим кнопки "ок" и "отмена" на ввод данных
    connect(ui->pushButton, &QAbstractButton::clicked, this, &m_road::vozvrat_ok);
    connect(ui->pushButton_2, &QAbstractButton::clicked, this, &m_road::vozvrat_no);
    //конектим кнопки все те же на закрытие самого окошка
    connect(ui->pushButton, &QAbstractButton::clicked, this, &QAbstractButton::close);
    connect(ui->pushButton_2, &QAbstractButton::clicked, this, &QAbstractButton::close);
}

m_road::~m_road() {
    delete ui;
}
//рисуем лэйбл о точках которые хотим соединить
//и открываем окно рабочее
void m_road::Window_qweschen(int n1, int n2){

    point1 = n1;
    point2 = n2;

    ui->label->setText("Введите расстояние между " + QString::number(n1) + " и " + QString::number(n2));

    show();
    exec();
}
//возвращаем значение что ввели в поле и передаем сигнал на обнуление строки чтобы не оставались прошлые значения
void m_road::vozvrat_ok(){
    emit vozvrat_znahenie_vesa(point1, point2,(ui->lineEdit->text()).toInt());
    ui->lineEdit->setText("");
}
//возвращаем сигнал отмены и так же обнуляем поля для удаления мусора
void m_road::vozvrat_no(){
    emit no_quantity();
    ui->lineEdit->setText("");
}
