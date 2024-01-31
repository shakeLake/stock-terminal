#include "include/mychartview.hpp"

MyChartView::MyChartView(QChart* qchart,
						 QCandlestickSeries* qseries,
						 std::vector<TimeSeries>* seriesSet) :
	QChartView(qchart),
	crosshair(new Crosshair(qchart, qseries, seriesSet))
{
	setDragMode(QGraphicsView::ScrollHandDrag);
	setInteractive(false);

	axisX = qobject_cast<QBarCategoryAxis*>(chart()->axes(Qt::Horizontal).at(0));
	seriesVec = seriesSet;

	rightMax = 0;
	wheelMinPoint = 30;

	axisX->setMin(QDateTime::fromSecsSinceEpoch(seriesVec->at(wheelMinPoint).timestamp).toString("dd\nMMM\nyyyy"));
	axisX->setMax(QDateTime::fromSecsSinceEpoch(seriesVec->back().timestamp).toString("dd\nMMM\nyyyy"));
}

void MyChartView::mouseMoveEvent(QMouseEvent* event)
{
	if (isPressed)
	{
		if (trajectory.x() < event->position().x())
		{
			if (wheelMinPoint < seriesVec->size() - 1 && rightMax < seriesVec->size() - 1)
			{
				wheelMinPoint += 1; 
				rightMax += 1;

				if (wheelMinPoint >= 0 
					|| wheelMinPoint < seriesVec->size() 
					|| rightMax >= 0 
					|| rightMax < seriesVec->size())
				{
					axisX->setMin(QDateTime::fromSecsSinceEpoch(seriesVec->at(wheelMinPoint).timestamp).toString("dd MMM yyyy"));
					axisX->setMax(QDateTime::fromSecsSinceEpoch(seriesVec->at(rightMax).timestamp).toString("dd MMM yyyy"));
				}

				trajectory = event->position();
			}
		}
		else
		{
			if (wheelMinPoint > 0 && rightMax > 0)
			{
				wheelMinPoint -= 1; 
				rightMax -= 1;

				if (wheelMinPoint >= 0 
					|| wheelMinPoint < seriesVec->size() 
					|| rightMax >= 0 
					|| rightMax < seriesVec->size())
				{
					axisX->setMin(QDateTime::fromSecsSinceEpoch(seriesVec->at(wheelMinPoint).timestamp).toString("dd MMM yyyy"));
					axisX->setMax(QDateTime::fromSecsSinceEpoch(seriesVec->at(rightMax).timestamp).toString("dd MMM yyyy"));
				}

				trajectory = event->position();
			}
		}
	}
	else
		crosshair->UpdatePosition(event->position());
}

void MyChartView::wheelEvent(QWheelEvent* event)
{
	if (event->angleDelta().y() < 0)
	{
		if (wheelMinPoint < seriesVec->size() - 31)
		{
			wheelMinPoint += 30;
			axisX->setMin(QDateTime::fromSecsSinceEpoch(seriesVec->at(wheelMinPoint).timestamp).toString("dd MMM yyyy"));
		}
	}
	else
	{
		if (wheelMinPoint > 31)
		{
			wheelMinPoint -= 30;
			axisX->setMin(QDateTime::fromSecsSinceEpoch(seriesVec->at(wheelMinPoint).timestamp).toString("dd MMM yyyy"));
		}
	}
}

void MyChartView::mousePressEvent(QMouseEvent* event)
{
	crosshair->HideEverything();

	cursor.setShape(Qt::ClosedHandCursor);
	chart()->setCursor(cursor);

	isPressed = true;
	trajectory = event->position();

	QChartView::mousePressEvent(event);
}

void MyChartView::mouseReleaseEvent(QMouseEvent* event)
{
	cursor.setShape(Qt::ArrowCursor);
	chart()->setCursor(cursor);

	isPressed = false;
	QChartView::mouseReleaseEvent(event);
}

MyChartView::~MyChartView()
{
	delete crosshair;
}