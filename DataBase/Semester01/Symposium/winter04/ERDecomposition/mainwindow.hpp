#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <QPen>
#include <QRect>
#include <QList>

// STL
#include <random>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paint(QPaintEvent * event);

private slots:
    void on_sb1_red_valueChanged(int arg1);

    void on_sb1_yellow_valueChanged(int arg1);

    void on_sb2_red_valueChanged(int arg1);

    void on_sb2_green_valueChanged(int arg1);

    void on_sb3_yellow_valueChanged(int arg1);

    void on_sb3_green_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
