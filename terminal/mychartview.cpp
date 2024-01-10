#include "include/mychartview.hpp"

MyChartView::MyChartView(QChart* qchart) :
    QChartView(qchart),
    crosshair(new Crosshair(qchart))
{
}

void MyChartView::mouseMoveEvent(QMouseEvent* event)
{
    crosshair->UpdatePosition(event->position());
    QChartView::mouseMoveEvent(event);
}

MyChartView::~MyChartView()
{
    delete crosshair;
}