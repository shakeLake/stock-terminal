#include "include/crosshair.hpp"

Crosshair::Crosshair(QChart* qchart) :
    x_line(new QGraphicsLineItem(qchart)),
    y_line(new QGraphicsLineItem(qchart)),
    // x_text(new QGraphicsTextItem(qchart)),
    y_text(new QGraphicsTextItem(qchart)),
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
    
    // x_text->setZValue(11);
    // x_text->setDefaultTextColor(Qt::white);

    y_text->setZValue(11);
    y_text->setDefaultTextColor(Qt::white);
}

void Crosshair::UpdatePosition(QPointF pos)
{
    QLineF xLine(pos.x(), chart->plotArea().top(),
                 pos.x(), chart->plotArea().bottom());

    QLineF yLine(chart->plotArea().left(), pos.y(),
                 chart->plotArea().right(), pos.y());

    x_line->setLine(xLine);
    y_line->setLine(yLine);

    // QString xText = QString::number(static_cast<int>(chart->mapToValue(pos).x()));
    // x_text->setHtml(QString("<div style='background-color: #3C5568;'>") + xText + "</div>");
    // x_text->setPos(pos.x() - x_text->boundingRect().width() / 2.0, chart->plotArea().bottom());

    QString yText = QString("%1").arg(chart->mapToValue(pos).y());
    y_text->setHtml(QString("<div style='background-color: #3C5568;'>") + yText + "</div>");
    y_text->setPos(chart->plotArea().left() / 8.0, pos.y() - y_text->boundingRect().height() / 2.0);

    if (chart->plotArea().contains(pos))
    {
        x_line->show();
        y_line->show();
        // x_text->show();
        y_text->show();
        cursor.setShape(Qt::CrossCursor);
        chart->setCursor(cursor);
    }
    else
    {
        x_line->hide();
        y_line->hide();
        // x_text->hide();
        y_text->hide();
        cursor.setShape(Qt::ArrowCursor);
        chart->setCursor(cursor);
    }
}