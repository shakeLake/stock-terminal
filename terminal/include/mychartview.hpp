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

private:
    void mouseMoveEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent*) override;

public:
    MyChartView(QChart*,
                QCandlestickSeries*,
                std::vector<TimeSeries>*,
                QWidget*);

    ~MyChartView();

};

#endif /* MYCHARTVIEW_HPP_ */