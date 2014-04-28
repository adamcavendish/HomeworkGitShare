#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <random>
#include <QBrush>
#include <QDebug>

#include <array>

class Drawer : public QWidget
{
    Q_OBJECT
public:
    explicit Drawer(QWidget *parent = 0);

    void paintEvent(QPaintEvent * event);

public slots:

public:
    const static int mc_red_count = 10;
    const static int mc_yellow_count = 40;
    const static int mc_green_count = 27;

    QList<QRect> m_reds;
    QList<QRect> m_yellows;
    QList<QRect> m_greens;

    bool m_ry_link[mc_red_count][mc_yellow_count];
    bool m_rg_link[mc_red_count][mc_green_count];
    bool m_yg_link[mc_yellow_count][mc_green_count];

    std::random_device rd;
    std::default_random_engine eng;
    std::uniform_int_distribution<int> m_rand_red;
    std::uniform_int_distribution<int> m_rand_yellow;
    std::uniform_int_distribution<int> m_rand_green;

    int r1, y1;
    int r2, g2;
    int y3, g3;

    int paintcounter;
};

#endif // DRAWER_HPP
