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
	o = new QLabel("open: ");

	open_value = new QFormLayout;
	open_value->addRow(o, open);

	high = new QLabel();
	h = new QLabel("high:  ");

	high_value = new QFormLayout;
	high_value->addRow(h, high);

	low = new QLabel();
	l = new QLabel("low: ");

	low_value = new QFormLayout;
	low_value->addRow(l, low);

	close = new QLabel();
	c = new QLabel("close: ");

	close_value = new QFormLayout;
	low_value->addRow(c, close);

	o->setStyleSheet("color: gray; font-size: 14px");
	open->setStyleSheet("font-weight: bold");

	h->setStyleSheet("color: gray; font-size: 14px");
	high->setStyleSheet("font-weight: bold");

	l->setStyleSheet("color: gray; font-size: 14px");
	low->setStyleSheet("font-weight: bold");

	c->setStyleSheet("color: gray; font-size: 14px");
	close->setStyleSheet("font-weight: bold");

	ohlcLayout->addLayout(open_value);
	ohlcLayout->addLayout(high_value);
	ohlcLayout->addLayout(low_value);
	ohlcLayout->addLayout(close_value);

	ohlcInfo->setFixedSize(140, 100);
	ohlcInfo->setStyleSheet("background-color: white");

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
	ohlcInfo->move(globalCursorPos.x() - 170, globalCursorPos.y() - 130);

	ohlcInfo->raise();
	ohlcInfo->show();

	QString str_open = QString::number(set->open()) + " $";
	QString str_high = QString::number(set->high()) + " $";
	QString str_low = QString::number(set->low()) + " $";
	QString str_close = QString::number(set->close()) + " $";

	open->setText(str_open);
	high->setText(str_high);
	low->setText(str_low);
	close->setText(str_close);
}

QDockWidget* Review::operator()()
{
	return this;
}
