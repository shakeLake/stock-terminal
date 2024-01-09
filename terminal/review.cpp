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

	ohlcInfo = new QWidget;
	ohlcLayout = new QVBoxLayout(ohlcInfo);

	ohlcInfo->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint);	
	
	open = new QLabel();
	high = new QLabel();
	low = new QLabel();
	close = new QLabel();

	ohlcLayout->addWidget(open);
	ohlcLayout->addWidget(high);
	ohlcLayout->addWidget(low);
	ohlcLayout->addWidget(close);

	ohlcInfo->setFixedSize(140, 140);

	CandleSeriesInit();

	GetOHLC();
	
	CandlestickSetInit();

	ChartInit();

	chartView = new MyChartView(chart);
	layout->addWidget(chartView);
}

void Review::CandleSeriesInit()
{
	// candle
	series = new QCandlestickSeries;
	series->setIncreasingColor(QColor(Qt::green));
	series->setDecreasingColor(QColor(Qt::red));
	series->setBodyOutlineVisible(false);

	// show candle data
	QObject::connect(series, SIGNAL(hovered(bool, QCandlestickSet*)), this, SLOT(PrintData(bool, QCandlestickSet*)));
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
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->setBackgroundBrush(QBrush(QColor("#1E2C38")));
	chart->setTitleBrush(QBrush(QColor("white")));

	chart->createDefaultAxes();

	auto axisX = qobject_cast<QBarCategoryAxis*>(chart->axes(Qt::Horizontal).at(0));
	axisX->setCategories(categories);

	auto axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).at(0));
	// axisY->setMax(axisY->max() * 1.01);
	// axisY->setMin(axisY->min() * 0.99);

	axisX->setGridLineVisible(false);
	axisY->setGridLineVisible(false);

	chart->legend()->setVisible(false);
}

void Review::PrintData(bool status, QCandlestickSet* set)
{
	QPoint globalCursorPos = QCursor::pos();
	ohlcInfo->move(globalCursorPos.x() - 180, globalCursorPos.y() - 180);

	ohlcInfo->show();

	open->setText(QString::fromStdString(std::to_string(set->open())));
	high->setText(QString::fromStdString(std::to_string(set->high())));
	low->setText(QString::fromStdString(std::to_string(set->low())));
	close->setText(QString::fromStdString(std::to_string(set->close())));
}

QDockWidget* Review::operator()()
{
	return this;
}
