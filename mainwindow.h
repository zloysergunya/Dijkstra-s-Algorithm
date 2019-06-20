#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPainter>
#include "myline.h"
#include "myline_line.h"
#include <QPoint>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

    void gragh_create();
    void Create_line(int p1, int p2);
    void Pain_line(int p);
    void SetMax(int max);
    void Repaint_signal(int ell1, int ell2);

private slots:

    void Graph_See();
    void push_graph(double p1, double p2, int n);

public slots:

    void form_arr_mass(int n1, int n2, int mass);
    void no_quantity();
    void logic_alg_dix();
    void Delete_graph();

protected:

    int quantity_peaks;//количество вершин

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;//рабочее пространство для рисования
    MyLine **elips;//массив точек
    MyLine_Line **line;
    QPoint *coord;//массив координат элипсов которые выбранны в данный момент

    int quantity_click;//счетчик кликов (2)
    int quantity_line = 0;//ычетчик под количество линий
    int number_elips[2];//массив содержащий 2 номер элипса которые в данный момент участвуют в соединении
    int **matrix;//массив содержащий массы ребер
    int *min_distance;//массив весов вершин
    bool *visited;//массив постоянных меток
    int *visited_peaks;//посещенные вершины
    int start; // старт
    int end;
    int sum_step = 0;

    void way_back();
};

#endif // MAINWINDOW_H
