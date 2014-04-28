#include "drawer.hpp"


Drawer::Drawer(QWidget *parent) :
    QWidget(parent),
    rd(),
    eng(rd()),
    m_rand_red(0, mc_red_count-1),
    m_rand_yellow(0, mc_yellow_count-1),
    m_rand_green(0, mc_green_count-1),
    r1(-1), y1(-1),
    r2(-1), g2(-1),
    y3(-1), g3(-1),
    paintcounter(0)
{
    int x, y;
    int sz;

    x = 10;
    y = 10;
    sz = 10;
    for(auto i = 0; i < mc_red_count; ++i) {
        m_reds.append(QRect(QPoint(x, y), QSize(sz, sz)));
        y += sz + 5;
    }//for

    x = 600;
    y = 10;
    for(auto i = 0; i < mc_yellow_count; ++i) {
        m_yellows.append(QRect(QPoint(x, y), QSize(sz, sz)));
        y += sz + 5;
    }//for

    x = 10;
    y = 600;
    for(auto i = 0; i < mc_green_count; ++i) {
        m_greens.append(QRect(QPoint(x, y), QSize(sz, sz)));
        x += sz + 5;
    }//for

    for(auto i = 0; i < mc_red_count; ++i) {
        for(auto j = 0; j < mc_yellow_count; ++j) {
            m_ry_link[i][j] = false;
        }//for
    }//for

    for(auto i = 0; i < mc_red_count; ++i) {
        for(auto j = 0; j < mc_green_count; ++j) {
            m_rg_link[i][j] = false;
        }//for
    }//for

    for(auto i = 0; i < mc_yellow_count; ++i) {
        for(auto j = 0; j < mc_green_count; ++j) {
            m_yg_link[i][j] = false;
        }//for
    }//for

    auto r_red = m_rand_red(eng);
    auto r_yellow = m_rand_yellow(eng);
    auto r_green = m_rand_green(eng);

    auto i1 = m_rand_red(eng);
    auto i2 = m_rand_yellow(eng);

    for(auto i = 0; i < i1*i2; ++i) {
        r_red = m_rand_red(eng);
        r_yellow = m_rand_yellow(eng);

        m_ry_link[r_red][r_yellow] = true;
    }//for

    i1 = m_rand_red(eng);
    i2 = m_rand_green(eng);
    for(auto i = 0; i < i1 * i2; ++i) {
        r_red = m_rand_red(eng);
        r_green = m_rand_green(eng);

        m_rg_link[r_red][r_green] = true;
    }//for

    i1 = m_rand_yellow(eng);
    i2 = m_rand_green(eng);
    for(auto i = 0; i < i1 * i2; ++i) {
        r_yellow = m_rand_yellow(eng);
        r_green = m_rand_green(eng);

        m_yg_link[r_yellow][r_green] = true;
    }//for
}

void Drawer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    ++paintcounter;

    QPainter p(this);
    QBrush br_red(Qt::red);
    QBrush br_yellow(Qt::yellow);
    QBrush br_green(Qt::green);

    //p.drawText(QRect(10, 300, 100, 350), QString("paint: %1").arg(paintcounter));

    p.setPen(Qt::black);
    p.setBrush(br_red);
    for(auto i = 0; i < mc_red_count; ++i) {
        p.drawRect(m_reds.at(i));
    }//for

    p.setPen(Qt::black);
    p.setBrush(br_yellow);
    for(auto i = 0; i < mc_yellow_count; ++i) {
        p.drawRect(m_yellows.at(i));
    }//for

    p.setPen(Qt::black);
    p.setBrush(br_green);
    for(auto i = 0; i < mc_green_count; ++i) {
        p.drawRect(m_greens.at(i));
    }//for



    {
        p.setPen(Qt::white);
        for(auto i = 0; i < mc_red_count; ++i) {
            for(auto j = 0; j < mc_yellow_count; ++j) {
                auto drawornot = m_ry_link[i][j];
                if(drawornot) {
                    p.drawLine(QLine(m_reds.at(i).topRight(), m_yellows.at(j).topLeft()));
                }//if
            }//for
        }//for

        p.setPen(Qt::white);
        for(auto i = 0; i < mc_red_count; ++i) {
            for(auto j = 0; j < mc_green_count; ++j) {
                auto drawornot = m_rg_link[i][j];
                if(drawornot) {
                    p.drawLine(QLine(m_reds.at(i).topRight(), m_greens.at(j).topLeft()));
                }//if
            }//for
        }//for

        p.setPen(Qt::white);
        for(auto i = 0; i < mc_yellow_count; ++i) {
            for(auto j = 0; j < mc_green_count; ++j) {
                auto drawornot = m_yg_link[i][j];
                if(drawornot) {
                    p.drawLine(QLine(m_yellows.at(i).topLeft(), m_greens.at(j).topLeft()));
                }//if
            }//for
        }//for
    }


    // red and yellow
    p.setPen(Qt::white);
    for(auto i = 0; i < mc_red_count; ++i) {
        bool flag = false;
        QPen lastpen1;

        if(i == r1 || i == r2) {
            lastpen1 = p.pen();
            p.setPen(Qt::red);
            flag = true;
        }

        for(auto j = 0; j < mc_yellow_count; ++j) {
            QPen lastpen2;

            if(j == y1 || j == y3) {
                lastpen2 = p.pen();
                p.setPen(Qt::red);
                flag = true;
            }

            auto drawornot = m_ry_link[i][j];
            if(flag && drawornot) {
                p.drawLine(QLine(m_reds.at(i).topRight(), m_yellows.at(j).topLeft()));
            }//if

            if(j == y1 || j == y3)
                p.setPen(lastpen2);
        }//for

        if(i == r1 || i == r2)
            p.setPen(lastpen1);
    }//for

    // red and green
    p.setPen(Qt::white);
    for(auto i = 0; i < mc_red_count; ++i) {
        bool flag = false;
        QPen lastpen1;

        if(i == r1 || i == r2) {
            lastpen1 = p.pen();
            p.setPen(Qt::red);
            flag = true;
        }

        for(auto j = 0; j < mc_green_count; ++j) {
            QPen lastpen2;
            if(j == g2 || j == g3) {
                lastpen2 = p.pen();
                p.setPen(Qt::red);
                flag = true;
            }

            auto drawornot = m_rg_link[i][j];
            if(flag && drawornot) {
                p.drawLine(QLine(m_reds.at(i).topRight(), m_greens.at(j).topLeft()));
            }//if

            if(j == g2 || j == g3)
                p.setPen(lastpen2);
        }//for

        if(i == r1 || i == r2)
            p.setPen(lastpen1);
    }//for

    // yellow and green
    p.setPen(Qt::white);
    for(auto i = 0; i < mc_yellow_count; ++i) {
        bool flag = false;
        QPen lastpen1;

        if(i == y1 || i == y3) {
            lastpen1 = p.pen();
            p.setPen(Qt::red);
            flag = true;
        }

        for(auto j = 0; j < mc_green_count; ++j) {
            QPen lastpen2;
            if(j == g2 || j == g3) {
                lastpen2 = p.pen();
                p.setPen(Qt::red);
                flag = true;
            }

            auto drawornot = m_yg_link[i][j];
            if(flag && drawornot) {
                p.drawLine(QLine(m_yellows.at(i).topLeft(), m_greens.at(j).topLeft()));
            }//if

            if(j == g2 || j == g3)
                p.setPen(lastpen2);
        }//for
        if(i == y1 || i == y3)
            p.setPen(lastpen1);
    }//for
}
