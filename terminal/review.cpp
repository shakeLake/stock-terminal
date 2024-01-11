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
	
	time = new QLabel();
	time->setAlignment(Qt::AlignCenter);
	time->setFixedHeight(25);
	time->setStyleSheet("color: #A6BED4;"
						 "font-size: 14px;"
						 "background-color: #334656;"
						 "border-radius: 3px;"
						 "font-weight: bold;");

	open = new QLabel();
	open->setAlignment(Qt::AlignRight);
	o = new QLabel("open: ");

	open_value = new QFormLayout;
	open_value->addRow(o, open);

	high = new QLabel();
	high->setAlignment(Qt::AlignRight);
	h = new QLabel("high: ");

	high_value = new QFormLayout;
	high_value->addRow(h, high);

	low = new QLabel();
	low->setAlignment(Qt::AlignRight);
	l = new QLabel("low: ");

	low_value = new QFormLayout;
	low_value->addRow(l, low);

	close = new QLabel();
	close->setAlignment(Qt::AlignRight);
	c = new QLabel("close: ");

	close_value = new QFormLayout;
	close_value->addRow(c, close);

	change = new QLabel();
	change->setAlignment(Qt::AlignRight);
	cha = new QLabel("change: ");

	change_value = new QFormLayout;
	change_value->addRow(cha, change);

	o->setStyleSheet("color: #A6BED4; font-size: 14px");
	open->setStyleSheet("font-weight: bold; color: #A6BED4; font-size: 14px;");

	h->setStyleSheet("color: #A6BED4; font-size: 14px");
	high->setStyleSheet("font-weight: bold; color: #A6BED4; font-size: 14px;");

	l->setStyleSheet("color: #A6BED4; font-size: 14px");
	low->setStyleSheet("font-weight: bold; color: #A6BED4; font-size: 14px;");

	c->setStyleSheet("color: #A6BED4; font-size: 14px");
	close->setStyleSheet("font-weight: bold; color: #A6BED4; font-size: 14px;");

	cha->setStyleSheet("color: #A6BED4; font-size: 14px");

	ohlcLayout->addWidget(time);
	ohlcLayout->addLayout(open_value);
	ohlcLayout->addLayout(high_value);
	ohlcLayout->addLayout(low_value);
	ohlcLayout->addLayout(close_value);
	ohlcLayout->addLayout(change_value);

	ohlcInfo->setFixedSize(150, 175);
	ohlcInfo->setStyleSheet("background-color: #243441");

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

	axisX->setGridLineColor(QColor("#17232D"));
	axisY->setGridLineColor(QColor("#17232D"));

	chart->legend()->setVisible(false);
}

QString Review::EstimateChange(double open, double close)
{
	double dchange = close - open;

	if (dchange < 0)
		change->setStyleSheet("font-weight: bold; color: #F57282; font-size: 14px;");
	else 
		change->setStyleSheet("font-weight: bold; color: #33C58D; font-size: 14px;");

	dchange /= open;
	dchange *= 100;

	dchange = std::ceil(dchange * 100.0) / 100.0;

	return QString::number(dchange) + " %";
}

void Review::PrintData(bool status, QCandlestickSet* set)
{
	QPoint globalCursorPos = QCursor::pos();
	ohlcInfo->move(globalCursorPos.x() - 165, globalCursorPos.y() - 165);

	ohlcInfo->raise();
	ohlcInfo->show();

	QString str_open = QString::number(set->open()) + " $";
	QString str_high = QString::number(set->high()) + " $";
	QString str_low = QString::number(set->low()) + " $";
	QString str_close = QString::number(set->close()) + " $";
	QString str_change = EstimateChange(set->open(), set->close());

	time->setText(QDateTime::fromSecsSinceEpoch(set->timestamp()).toString("dd MMM yyyy, ddd"));
	open->setText(str_open);
	high->setText(str_high);
	low->setText(str_low);
	close->setText(str_close);
	change->setText(str_change);
}

QDockWidget* Review::operator()()
{
	return this;
}
