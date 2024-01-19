#ifndef CROSSHAIR_HPP_
#define CROSSHAIR_HPP_

#include <QWidget>
#include <QChart>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QCursor>
#include <QCandlestickSeries>
#include <QCandlestickSet>
#include <QDateTime>

#include <vector>

#include "timeseries.hpp"

class Crosshair
{
private:
	QGraphicsLineItem* x_line;
	QGraphicsLineItem* y_line;
	QGraphicsTextItem* x_text;
	QGraphicsTextItem* y_text;

	QChart* chart;
	QCandlestickSeries* series;
	std::vector<TimeSeries>* seriesVec;

	QCursor cursor;

	QWidget* ohlc;

public:
	Crosshair(	QChart*,
				QCandlestickSeries*,
				std::vector<TimeSeries>*,
				QWidget*);

	~Crosshair() = default;

	void UpdatePosition(QPointF);

};

#endif /* CROSSHAIR_HPP_ */