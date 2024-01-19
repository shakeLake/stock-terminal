#include "include/rescrollbar.hpp"

MyScrollBar::MyScrollBar(QChart* qchart) :
    QScrollBar(Qt::Horizontal),
    chart(qchart)
{
}

void MyScrollBar::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y() < 0)
        chart->scroll(200, 0);
    else
        chart->scroll(-200, 0);
}