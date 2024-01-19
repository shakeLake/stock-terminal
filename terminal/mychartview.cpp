#include "include/mychartview.hpp"

MyChartView::MyChartView(QChart* qchart,
						 QCandlestickSeries* qseries,
						 std::vector<TimeSeries>* seriesSet,
						 QWidget* qohlc) :
	QChartView(qchart),
	crosshair(new Crosshair(qchart, qseries, seriesSet, qohlc))
{
}

void MyChartView::mouseMoveEvent(QMouseEvent* event)
{
	crosshair->UpdatePosition(event->position());
	QChartView::mouseMoveEvent(event);
}

void MyChartView::wheelEvent(QWheelEvent* event)
{
	chart()->zoomReset();

	mFactor *= event->angleDelta().y() > 0 ? 0.5 : 2;

	QRectF rect = chart()->plotArea();
	QPointF c = chart()->plotArea().center();
	rect.setWidth(mFactor * rect.width());
	rect.moveCenter(c);
	chart()->zoomIn(rect);

	QChartView::wheelEvent(event);
}

MyChartView::~MyChartView()
{
	delete crosshair;
}