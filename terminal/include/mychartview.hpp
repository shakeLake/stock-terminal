#ifndef MYCHARTVIEW_HPP_
#define MYCHARTVIEW_HPP_

#include <QChartView>
#include <QChart>
#include <QWidget>
#include <QCandlestickSeries>
#include <QScrollBar>
#include <QBarCategoryAxis>
#include <QDateTime>
#include <QCursor>

#include "crosshair.hpp"

class MyChartView : public QChartView
{
private:
    QCursor cursor;

    Crosshair* crosshair;

    // zoom
	double mFactor = 1.0;

    // drag and move
    bool isPressed = false;
    QPointF trajectory;
    QBarCategoryAxis* axisX;

    // wheel data
    int wheelMinPoint;
	std::vector<TimeSeries>* seriesVec;

    // move event
    int rightMax;
    
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