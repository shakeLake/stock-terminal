#ifndef MYCHARTVIEW_HPP_
#define MYCHARTVIEW_HPP_

#include <QChartView>
#include <QChart>

#include "crosshair.hpp"

class MyChartView : public QChartView
{
private:
    Crosshair* crosshair;

public:
    MyChartView(QChart*);
    ~MyChartView();

    void mouseMoveEvent(QMouseEvent*) override;
};

#endif /* MYCHARTVIEW_HPP_ */