#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sb1_red->setMaximum(ui->widget->mc_red_count-1);
    ui->sb1_yellow->setMaximum(ui->widget->mc_yellow_count-1);

    ui->sb2_red->setMaximum(ui->widget->mc_red_count-1);
    ui->sb2_green->setMaximum(ui->widget->mc_green_count-1);

    ui->sb3_yellow->setMaximum(ui->widget->mc_yellow_count-1);
    ui->sb3_green->setMaximum(ui->widget->mc_green_count-1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paint(QPaintEvent *event)
{
    Q_UNUSED(event);
}


void MainWindow::on_sb1_red_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->sb2_red->setValue(-1);
    ui->sb2_green->setValue(-1);

    ui->sb3_yellow->setValue(-1);
    ui->sb3_green->setValue(-1);

    ui->widget->r1 = ui->sb1_red->value();
    ui->widget->y1 = ui->sb1_yellow->value();
    ui->widget->r2 = ui->sb2_red->value();
    ui->widget->g2 = ui->sb2_green->value();
    ui->widget->y3 = ui->sb3_yellow->value();
    ui->widget->g3 = ui->sb3_green->value();

    ui->widget->repaint();
}

void MainWindow::on_sb1_yellow_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->sb2_red->setValue(-1);
    ui->sb2_green->setValue(-1);

    ui->sb3_yellow->setValue(-1);
    ui->sb3_green->setValue(-1);

    ui->widget->r1 = ui->sb1_red->value();
    ui->widget->y1 = ui->sb1_yellow->value();
    ui->widget->r2 = ui->sb2_red->value();
    ui->widget->g2 = ui->sb2_green->value();
    ui->widget->y3 = ui->sb3_yellow->value();
    ui->widget->g3 = ui->sb3_green->value();

    ui->widget->repaint();
}

void MainWindow::on_sb2_red_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->sb1_red->setValue(-1);
    ui->sb1_yellow->setValue(-1);

    ui->sb3_yellow->setValue(-1);
    ui->sb3_green->setValue(-1);

    ui->widget->r1 = ui->sb1_red->value();
    ui->widget->y1 = ui->sb1_yellow->value();
    ui->widget->r2 = ui->sb2_red->value();
    ui->widget->g2 = ui->sb2_green->value();
    ui->widget->y3 = ui->sb3_yellow->value();
    ui->widget->g3 = ui->sb3_green->value();

    ui->widget->repaint();
}

void MainWindow::on_sb2_green_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->sb1_red->setValue(-1);
    ui->sb1_yellow->setValue(-1);

    ui->sb3_yellow->setValue(-1);
    ui->sb3_green->setValue(-1);

    ui->widget->r1 = ui->sb1_red->value();
    ui->widget->y1 = ui->sb1_yellow->value();
    ui->widget->r2 = ui->sb2_red->value();
    ui->widget->g2 = ui->sb2_green->value();
    ui->widget->y3 = ui->sb3_yellow->value();
    ui->widget->g3 = ui->sb3_green->value();

    ui->widget->repaint();
}

void MainWindow::on_sb3_yellow_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->sb2_red->setValue(-1);
    ui->sb2_green->setValue(-1);

    ui->sb1_red->setValue(-1);
    ui->sb1_yellow->setValue(-1);

    ui->widget->r1 = ui->sb1_red->value();
    ui->widget->y1 = ui->sb1_yellow->value();
    ui->widget->r2 = ui->sb2_red->value();
    ui->widget->g2 = ui->sb2_green->value();
    ui->widget->y3 = ui->sb3_yellow->value();
    ui->widget->g3 = ui->sb3_green->value();

    ui->widget->repaint();
}

void MainWindow::on_sb3_green_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->sb2_red->setValue(-1);
    ui->sb2_green->setValue(-1);

    ui->sb1_red->setValue(-1);
    ui->sb1_yellow->setValue(-1);

    ui->widget->r1 = ui->sb1_red->value();
    ui->widget->y1 = ui->sb1_yellow->value();
    ui->widget->r2 = ui->sb2_red->value();
    ui->widget->g2 = ui->sb2_green->value();
    ui->widget->y3 = ui->sb3_yellow->value();
    ui->widget->g3 = ui->sb3_green->value();

    ui->widget->repaint();
}
