#ifndef CROSSHAIR_HPP_
#define CROSSHAIR_HPP_

#include <QChart>
#include <QGraphicsLineItem>
#include <QCursor>

class Crosshair
{
private:
	QGraphicsLineItem* x_line;
	QGraphicsLineItem* y_line;
	QChart* chart;

	QCursor cursor;

public:
	Crosshair(QChart*);
	~Crosshair() = default;

	void UpdatePosition(QPointF);

};

#endif /* CROSSHAIR_HPP_ */