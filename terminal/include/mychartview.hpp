#ifndef MYCHARTVIEW_HPP_
#define MYCHARTVIEW_HPP_

#include <QChartView>
#include <QChart>
#include <QWidget>
#include <QCandlestickSeries>

#include "crosshair.hpp"

class MyChartView : public QChartView
{
private:
    Crosshair* crosshair;

    // zoom
	double mFactor = 1.0;

    // drag and move
    bool isPressed = false;
    QPointF trajectory;

private:
    void mouseMoveEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

public:
    MyChartView(QChart*,
                QCandlestickSeries*,
                std::vector<TimeSeries>*);

    ~MyChartView();

};

#endif /* MYCHARTVIEW_HPP_ */