#include "include/crosshair.hpp"

Crosshair::Crosshair(QChart* qchart,
                     QCandlestickSeries* qseries,
                     std::vector<TimeSeries>* seriesSet) :
    x_line(new QGraphicsLineItem(qchart)),
    y_line(new QGraphicsLineItem(qchart)),
    x_text(new QGraphicsTextItem(qchart)),
    y_text(new QGraphicsTextItem(qchart)),
    series(qseries),
    chart(qchart)
{
    seriesVec = seriesSet;

    QPen pen_line_x;
    pen_line_x.setStyle(Qt::DashLine);
    pen_line_x.setBrush(Qt::gray);
    x_line->setPen(pen_line_x);

    QPen pen_line_y;
    pen_line_y.setStyle(Qt::DashLine);
    pen_line_y.setBrush(Qt::gray);
    y_line->setPen(pen_line_y);
    
    x_text->setZValue(11);
    x_text->setDefaultTextColor(Qt::white);

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

    QString yText = QString("%1").arg(chart->mapToValue(pos).y());
    y_text->setHtml(QString("<div style='background-color: #3C5568;'>") + yText + "</div>");
    y_text->setPos(chart->plotArea().right(), pos.y() - y_text->boundingRect().height() / 2.0);

    int timeShift = chart->mapToValue(pos).x() + 0.5;

    if (timeShift < seriesVec->size() && timeShift >= 0)
    {
        double currTimestamp = seriesVec->at((seriesVec->size() - 1) - timeShift).timestamp;

        QString xText = QDateTime::fromSecsSinceEpoch(currTimestamp).toString("dd MMM yyyy, ddd");
        x_text->setHtml(QString("<div style='background-color: #3C5568;'>") + xText + "</div>");
        x_text->setPos(pos.x() - x_text->boundingRect().width() / 2.0, chart->plotArea().bottom());

        x_text->show();
        ohlc.PrintData(seriesVec->at((seriesVec->size() - 1) - timeShift));
    }
    else
        ohlc.hide();

    if (chart->plotArea().contains(pos))
    {
        x_line->show();
        y_line->show();
        y_text->show();
        cursor.setShape(Qt::CrossCursor);
        chart->setCursor(cursor);
    }
    else
    {
        x_line->hide();
        y_line->hide();
        x_text->hide();
        y_text->hide();
        ohlc.hide();
        cursor.setShape(Qt::ArrowCursor);
        chart->setCursor(cursor);
    }
}