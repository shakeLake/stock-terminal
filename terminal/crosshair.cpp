#include "include/crosshair.hpp"

Crosshair::Crosshair(QChart* qchart) :
    x_line(new QGraphicsLineItem(qchart)),
    y_line(new QGraphicsLineItem(qchart)),
    chart(qchart)
{
    QPen pen_line_x;
    pen_line_x.setStyle(Qt::DashLine);
    pen_line_x.setBrush(Qt::gray);

    x_line->setPen(pen_line_x);

    QPen pen_line_y;
    pen_line_y.setStyle(Qt::DashLine);
    pen_line_y.setBrush(Qt::gray);

    y_line->setPen(pen_line_y);
}

void Crosshair::UpdatePosition(QPointF pos)
{
    QLineF xLine(pos.x(), chart->plotArea().top(),
                 pos.x(), chart->plotArea().bottom());

    QLineF yLine(chart->plotArea().left(), pos.y(),
                 chart->plotArea().right(), pos.y());

    x_line->setLine(xLine);
    y_line->setLine(yLine);

    if (chart->plotArea().contains(pos))
    {
        x_line->show();
        y_line->show();
        cursor.setShape(Qt::CrossCursor);
        chart->setCursor(cursor);
    }
    else
    {
        x_line->hide();
        y_line->hide();
        cursor.setShape(Qt::ArrowCursor);
        chart->setCursor(cursor);
    }
}