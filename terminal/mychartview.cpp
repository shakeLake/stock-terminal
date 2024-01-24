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
	{
		double delta = trajectory.x() - event->position().x();
		chart()->scroll(delta,  0);
		trajectory = event->position();

		crosshair->UpdatePosition(event->position());
	}
	else
		crosshair->UpdatePosition(event->position());

	// QChartView::mouseMoveEvent(event);
}

void MyChartView::wheelEvent(QWheelEvent* event)
{
	chart()->zoomReset();

	mFactor *= event->angleDelta().y() > 0 ? 0.5 : 2;

	QRectF rect = chart()->plotArea();
	double r = mapToScene(sceneRect().center().x() * 2, 0).x();
	rect.setWidth(mFactor * rect.width());
	rect.moveRight(r);
	chart()->zoomIn(rect);

	// QChartView::wheelEvent(event);
}

void MyChartView::mousePressEvent(QMouseEvent* event)
{
	isPressed = true;
	trajectory = event->position();
	// crosshair->HideEverything();

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