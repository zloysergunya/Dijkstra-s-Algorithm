#include <QPainter>
#include <QGraphicsItem>
#include <QAbstractButton>
#include <QtMath>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myline.h"
#include "m_road.h"
#include "myline_line.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //объявляем графическую сцену

    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    //счетчик нажатий
    quantity_click = 0;
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //конектим кнопку
    coord = new QPoint[2];//создаем локальные координаты для двух выбранных вершин

    m_road *quash = new m_road;//область памяти под всплывающее окно
    connect(ui->pushButton, &QAbstractButton::clicked, this, &MainWindow::Graph_See);//конектим кнопку вывода
    connect(quash, &m_road::vozvrat_znahenie_vesa, this, &MainWindow::form_arr_mass);//конекти формирование масс и линеей
    connect(this, &MainWindow::Create_line, quash, &m_road::Window_qweschen);//конектим само всплывающее окно по нажатию на круги
    connect(quash, &m_road::no_quantity, this, &MainWindow::no_quantity);//конектим сброс счетчика при нажатии кнопки "отмена"
    connect(ui->pushButton_2, &QAbstractButton::clicked, this, &MainWindow::logic_alg_dix);//конект кнопки "считать с алгоритмом дийкстры"
    connect(ui->pushButton_3, &QAbstractButton::clicked, this, &MainWindow::Delete_graph);//конектим удаление графа
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::Graph_See(){
    //считываем с окна вводо количество кругов
    QString count = ui->lineEdit->text();
    //количество кругов в интеджер
    quantity_peaks = (count).toInt();
    //инициализируем массив весов
    matrix = new int* [quantity_peaks];

    for(int i = 0; i < quantity_peaks; i++){
        matrix[i] = new int[quantity_peaks];
    }

    for(int i = 0; i < quantity_peaks; i++){
        for(int j = 0; j < quantity_peaks; j++){
            matrix[i][j] = 0;
        }
    }

    //счетчик повторов
    double count_t = (count).toDouble();
    //период повтора печатанья
    double period = 2*M_PI/count_t;
    //массив кругов
    elips = new MyLine*[quantity_peaks];
    //массив ребер
    line = new MyLine_Line* [quantity_peaks*quantity_peaks];
    //инициализация массива посещенных точек
    visited_peaks = new int[quantity_peaks];
    //счетчик
    int i = 0;

    //цикл создания
    for(double p = 0; (p < 2*M_PI) && (2*M_PI - p > 0.00001); p += period, i++){//работает до 2пи и пока точночть не меньше 1стотысячной
        elips[i] = new MyLine(50 * log2(quantity_peaks) * cos(p), 50 * log2(quantity_peaks) * sin(p), quantity_peaks, i + 1);//попробывать использовать не количество а период
        connect(this, &MainWindow::SetMax, elips[i], &MyLine::SetMax);
        emit SetMax(quantity_peaks);
        scene->addItem(elips[i]);
        connect(elips[i], &MyLine::signal_push, this, &MainWindow::push_graph);
    }
}

//считываем клики и отдаем сигнал на всплывающее окно запросов
void MainWindow::push_graph(double p1, double p2, int n){
    coord[quantity_click] = QPoint(p1, p2);//записываем координаты кликов и по ним строим линию
    number_elips[quantity_click] = n;//еще записываем номера элипсов которые выбрали
    ++quantity_click;
    if(quantity_click % 2 == 0){
        emit Create_line(number_elips[0], number_elips[1]);
    }
}

//заполняем наш массив весов и чертим линию
void MainWindow::form_arr_mass(int n1, int n2, int mass){
    if (mass != 0 && n1 != n2) {
        matrix[n1 - 1][n2 - 1] = mass;
        matrix[n2 - 1][n1 - 1] = mass;
        line[quantity_line] = new MyLine_Line(QLineF(coord[0], coord[1]), n1, n2, mass);//создаем линию и записываем в массив линий
        scene->addItem(line[quantity_line]);//добавляем линию на рабочее графическое поле
        quantity_line++;
        quantity_click = 0;
    }
    else {
        QMessageBox::warning(this, "Ошибка!", "Старайтесь не создавать петель и 0 весов!");
    }
}

//обнуляем счетчик кликов при "отмена"
void MainWindow::no_quantity(){
    quantity_click = 0;
}

// Здесь находится вся логика программы (опционально изменяется)
void MainWindow::logic_alg_dix(){
    QString start_point = ui->lineEdit_2->text();
    start = start_point.toInt() - 1;

    //инициализация массива весов вершин
    min_distance = new int[quantity_peaks];
    visited = new bool[quantity_peaks];
    for(int i = 0; i < quantity_peaks; i++){
        min_distance[i] = INT_MAX;
        visited[i] = false;
    }
    min_distance[start] = 0;

    int count, index = 0, i;

    for (count = 0; count < quantity_peaks - 1; count++) {
            int min = INT_MAX;
            for (i = 0; i < quantity_peaks; i++)
                if (!visited[i] && min_distance[i] <= min) {
                    min = min_distance[i]; index = i;
                }

            visited[index] = true;
            for (i = 0; i < quantity_peaks; i++)
                if (!visited[i] && matrix[index][i] && min_distance[index] != INT_MAX &&
                    min_distance[index] + matrix[index][i] < min_distance[i])
                    min_distance[i] = min_distance[index] + matrix[index][i];
        }

    way_back();
}

// Здесь находим обратный путь но только один
void MainWindow::way_back(){
    QString end_point = ui->lineEdit_4->text();
    end = (end_point).toInt() - 1;
    visited_peaks[0] = end + 1; // начальный элемент - конечная вершина
    int previous = 1; // индекс предыдущей вершины
    int weight = min_distance[end]; // вес конечной вершины

    while (end != start) { // пока не дошли до начальной вершины
        for (int i = 0; i < quantity_peaks; i++) {
            if (matrix[end][i] != 0) { // если связь есть
                int temp = weight - matrix[end][i]; // определяем вес пути из предыдущей вершины
                if (temp == min_distance[i]) {  // если вес совпал с рассчитанным, значит из этой вершины и был переход
                    weight = temp; // сохраняем новый вес
                    end = i;       // сохраняем предыдущую вершину
                    visited_peaks[previous] = i + 1; // и записываем ее в массив
                    previous++;
                }
            }
        }
    }

//циферный вывод пути
    QString shag;
    for (int i = previous - 1; i >= 0; i--) {
        shag += QString::number(visited_peaks[i]) + " ";
        sum_step = min_distance[visited_peaks[i] - 1];
        }
    ui->lineEdit_3->setText(shag);

    QMessageBox::warning(this, "Сумма пути", "Расстояние от старта до финиша = " + QString::number(sum_step));

    for (int i = previous - 1; i >=0; i--){
        QGraphicsLineItem *reline = new QGraphicsLineItem;
        reline->setPen(QPen(Qt::black, 2));
        for(int j = 0; j < quantity_line; j++){
            if ((line[j]->Get_number_ellips1() == visited_peaks[i] &&
                    line[j]->Get_number_ellips2() == visited_peaks[i-1])
                    || (line[j]->Get_number_ellips1() == visited_peaks[i-1] &&
                        line[j]->Get_number_ellips2() == visited_peaks[i])){
               reline->setLine(line[j]->GetLine());
               scene->addItem(reline);
            }
        }
    }
}

//удаляем рабочее поле и заного рисуем его но пустым создаем заодно обнуляем все глобальные счетчики
void MainWindow::Delete_graph(){
    delete scene;
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    quantity_line = 0;
    quantity_click = 0;
}
