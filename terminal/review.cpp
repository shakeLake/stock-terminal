#include "include/review.hpp"

Review::Review()
{
	setFeatures(QDockWidget::NoDockWidgetFeatures);

	setWindowTitle("Review");				
	setStyleSheet("QDockWidget {color: #B9CCDB; font-weight: bold; font-size: 12px}");

	QWidget* container = new QWidget;
	setWidget(container);

	container->setStyleSheet("background-color: #1E2C38");

	QVBoxLayout* layout = new QVBoxLayout(container);

	// candle
	QCandlestickSeries* Series = new QCandlestickSeries;
	Series->setName("Name");
	Series->setIncreasingColor(QColor(Qt::green));
	Series->setDecreasingColor(QColor(Qt::red));

	QStringList categories;

	/*
									 ****
		std::string company_ticker = AAPL.json; 
	*/
	JsonParser p;
	std::vector<TimeSeries> ohlc = std::move(p.ReadTimeSeries("fl1.json"));
	
	for (auto& item : ohlc)
	{
		std::cout << item.timestamp << std::endl;
		QCandlestickSet *set = new QCandlestickSet((int)item.timestamp);
		set->setOpen(item.open);
		set->setHigh(item.high);
		set->setLow(item.low);
		set->setClose(item.close);

		if (set) 
		{
			Series->append(set);
			categories << QDateTime::fromMSecsSinceEpoch(set->timestamp()).toString("dd");
		}
	}

	// chart
	auto chart = new QChart;
	chart->addSeries(Series);
	chart->setTitle("Name Test");
	chart->setAnimationOptions(QChart::SeriesAnimations);

	chart->createDefaultAxes();

	auto axisX = qobject_cast<QBarCategoryAxis*>(chart->axes(Qt::Horizontal).at(0));
	axisX->setCategories(categories);

	auto axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).at(0));
	axisY->setMax(axisY->max() * 1.01);
	axisY->setMin(axisY->min() * 0.99);

	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	// createDefaultChartView(chart);

	QChartView* chartView = new QChartView(chart);
	layout->addWidget(chartView);
}

QDockWidget* Review::operator()()
{
	return this;
}
