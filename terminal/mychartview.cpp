#include "include/mychartview.hpp"

MyChartView::MyChartView(QChart* qchart,
						 QCandlestickSeries* qseries,
						 std::vector<TimeSeries>* seriesSet) :
	QChartView(qchart),
	crosshair(new Crosshair(qchart, qseries, seriesSet))
{
}

void MyChartView::mouseMoveEvent(QMouseEvent* event)
{
	if (isPressed)
		chart()->scroll((trajectory.x() - event->position().x()),  0);
	else
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

void MyChartView::mousePressEvent(QMouseEvent* event)
{
	isPressed = true;
	trajectory = event->position();
	crosshair->HideEverything();

	QChartView::mousePressEvent(event);
}

void MyChartView::mouseReleaseEvent(QMouseEvent* event)
{
	isPressed = false;
	QChartView::mouseReleaseEvent(event);
}

MyChartView::~MyChartView()
{
	delete crosshair;
}