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
#include "ohlcTable.hpp"

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

	OHLCTable ohlc;

	QCursor cursor;

public:
	Crosshair(	QChart*,
				QCandlestickSeries*,
				std::vector<TimeSeries>*);

	~Crosshair() = default;

	void UpdatePosition(QPointF);
	void HideEverything();

};

#endif /* CROSSHAIR_HPP_ */