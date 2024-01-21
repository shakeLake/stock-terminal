#include "include/review.hpp"

Review::Review(std::string ticker)
{
	setFeatures(QDockWidget::NoDockWidgetFeatures);

	setWindowTitle("Review");				
	setStyleSheet("QDockWidget {color: #B9CCDB; font-weight: bold; font-size: 12px}");

	QWidget* container = new QWidget;
	setWidget(container);

	container->setStyleSheet("background-color: #1E2C38");

	QVBoxLayout* layout = new QVBoxLayout(container);

	rev_ticker = ticker;

	CandleSeriesInit();

	GetOHLC();
	
	CandlestickSetInit();

	ChartInit();

	chartView = new MyChartView(chart, series, &ohlc);
	layout->addWidget(chartView);
}

void Review::CandleSeriesInit()
{
	// candle
	series = new QCandlestickSeries;
	series->setIncreasingColor(QColor(Qt::green));
	series->setDecreasingColor(QColor(Qt::red));
	series->setBodyOutlineVisible(false);
}

void Review::GetOHLC()
{
	JsonParser p;
	ohlc = std::move(p.ReadTimeSeries(rev_ticker)); // change to ticker
}

void Review::CandlestickSetInit()
{
	for (auto item = ohlc.end() - 1; item != ohlc.begin(); --item)
	{
		QCandlestickSet* set = new QCandlestickSet(item->timestamp);
		set->setOpen(item->open);
		set->setHigh(item->high);
		set->setLow(item->low);
		set->setClose(item->close);

		series->append(set);
		categories << QDateTime::fromSecsSinceEpoch(set->timestamp()).toString("dd");
	}
}

void Review::ChartInit()
{
	// chart
	chart = new QChart;
	chart->addSeries(series);
	chart->setAnimationOptions(QChart::NoAnimation);
	chart->setBackgroundBrush(QBrush(QColor("#1E2C38")));
	chart->setTitleBrush(QBrush(QColor("white")));
	chart->setDropShadowEnabled(false);

	QBarCategoryAxis* axisX = new QBarCategoryAxis();
	axisX->setCategories(categories);
	chart->addAxis(axisX, Qt::AlignBottom);

	QValueAxis* axisY = new QValueAxis;
	chart->addAxis(axisY, Qt::AlignRight);

	series->attachAxis(axisX);
	series->attachAxis(axisY);

	axisX->setGridLineColor(QColor("#17232D"));
	axisY->setGridLineColor(QColor("#17232D"));

	chart->legend()->setVisible(false);
}

QDockWidget* Review::operator()()
{
	return this;
}