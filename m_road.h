#ifndef M_ROAD_H
#define M_ROAD_H

#include <QDialog>

namespace Ui {
class m_road;
}

class m_road : public QDialog
{
    Q_OBJECT

public:
    explicit m_road(QWidget *parent = nullptr);
    ~m_road();


private:
    Ui::m_road *ui;

    int point1;
    int point2;

public slots:

    void Window_qweschen(int n1, int n2);
    void vozvrat_ok();
    void vozvrat_no();

signals:

    void vozvrat_znahenie_vesa(int n1,int n2,int mass);
    void no_quantity();

};

#endif // M_ROAD_H
