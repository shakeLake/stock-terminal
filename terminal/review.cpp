#include "include/review.hpp"

Review::Review()
{
	setFeatures(QDockWidget::NoDockWidgetFeatures);

	setWindowTitle("Review");				
	setStyleSheet("QDockWidget {color: #B9CCDB; font-weight: bold; font-size: 12px}");

	container = new QWidget;
	setWidget(container);

	container->setStyleSheet("background-color: #1E2C38");

	layout = new QVBoxLayout(container);

	infoData = new QLabel("No Data");
	infoData->setStyleSheet("font-size: 48px; color: #152029");
	infoData->setAlignment(Qt::AlignCenter);

	layout->addWidget(infoData);
}

// current day ohlc
std::vector<double> Review::ReviewStart(std::string ticker)
{
	infoData->setVisible(false);

	rev_ticker = "TIME_SERIES_";
	rev_ticker += ticker + ".json";

	categories = new QStringList;

	CandleSeriesInit();

	GetOHLC();
	
	CandlestickSetInit();

	ChartInit();

	chartView = new MyChartView(chart, series, &ohlc);
	layout->addWidget(chartView);

	return {ohlc[0].open, ohlc[0].high, ohlc[0].low, ohlc[0].close, ohlc[0].volume};
}

void Review::ReviewReset()
{
	layout->removeWidget(chartView);

	delete axisX;
	delete axisY;
	delete categories;
	delete series;
	delete chart;
	delete chartView;
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
	ohlc = std::move(p.ReadTimeSeries(rev_ticker));
}

void Review::CandlestickSetInit()
{
	for (auto item = ohlc.end(); item != ohlc.begin(); --item)
	{
		QCandlestickSet* set = new QCandlestickSet(item->timestamp);
		set->setOpen(item->open);
		set->setHigh(item->high);
		set->setLow(item->low);
		set->setClose(item->close);

		series->append(set);
		categories->push_back(QDateTime::fromSecsSinceEpoch(set->timestamp()).toString("dd MMM yyyy"));
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

	axisX = new QBarCategoryAxis();
	axisX->setCategories(*categories);
	QFont sansFont("Helvetica", 5);
	axisX->setLabelsFont(sansFont);

	axisY = new QValueAxis;

	chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignRight);

	series->attachAxis(axisX);
	series->attachAxis(axisY);

	chart->legend()->setVisible(false);

	axisX->setGridLineColor(QColor("#17232D"));
	axisY->setGridLineColor(QColor("#17232D"));
}

QDockWidget* Review::operator()()
{
	return this;
}