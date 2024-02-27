#include "include/toolbar.hpp"

ToolBar::ToolBar()
{
	setMovable(false);

	main_widget = new QWidget;
	addWidget(main_widget);

	main_layout = new QHBoxLayout(main_widget);

	AddTickers();

	ReadPrices();

	scrollArea = new QScrollArea;

	scrollArea->setFrameShape( QFrame::NoFrame );
	scrollArea->setWidgetResizable( true );
	scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff ); 
	scrollArea->setWidget(stockLayoutWidget);

	main_layout->addWidget(scrollArea);

	scrollBar = scrollArea->horizontalScrollBar();
	animation = new QPropertyAnimation(scrollBar, "sliderPosition");

	Loading();
}

void ToolBar::StartAnimation()
{
	endPoint = {scrollBar->maximum(), false};
	startPoint = scrollBar->minimum();
	StockAnimation();
}

void ToolBar::Loading()
{
	QTimer::singleShot(1000, this, &ToolBar::StartAnimation);
}

void ToolBar::StockAnimation()
{
	connect(animation, &QPropertyAnimation::finished, this, &ToolBar::RestartStockAnimation);

	animation->setDuration(10000);
    animation->setStartValue(startPoint);
    animation->setEndValue(endPoint.first);

	// qDebug() << startPoint << ' ' << endPoint.first;

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void ToolBar::RestartStockAnimation()
{
	animation = new QPropertyAnimation(scrollBar, "sliderPosition");

	if (endPoint.second == false)
	{
		startPoint = endPoint.first;
		endPoint.first = scrollBar->minimum();
		endPoint.second = true;
	}
	else
	{
		startPoint = endPoint.first;
		endPoint.first = scrollBar->maximum(); 
		endPoint.second = false;
	}

	StockAnimation();
}

void ToolBar::AddTickers()
{
	stockLayoutWidget = new QWidget;
	stockLayout = new QHBoxLayout(stockLayoutWidget);
	stockLayout->setSpacing(30);
}

QWidget* ToolBar::GetTicker(std::string ticker)
{
	QWidget* tick = new QWidget;

	QWidget* nameLayoutWidget = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout(tick);

	// icon
	QPushButton* tickicon = new QPushButton;
	std::string path = ":/Resources/logo/";
	path += ticker + ".png";

	tickicon->setIcon(QIcon(QString::fromStdString(path)));
	tickicon->setStyleSheet("border: none");
	tickicon->setIconSize(QSize(20, 40));
	
	// Name
	QLabel* ticker_name = new QLabel(QString::fromStdString(ticker) + ' ');
	ticker_name->setStyleSheet("font: 14px;"
							   "color: white");

	tick->setStyleSheet("background-color: #273E4E;"
						"border-radius: 5px;"
						"height: 20px;");

	layout->addWidget(tickicon);
	layout->addWidget(ticker_name);

	// Price
	stuff[ticker]->setStyleSheet("font: 14px;"
								 "color: white;"
								 "font-weight: bold");

	layout->addWidget(stuff[ticker]);

	return tick;
}

std::pair<std::string, QString> ToolBar::TakeTickerAndPrice(QString& line)
{
	QString ticker;
	QString price;

	int i;
	for (i = 0; i < line.size(); ++i)
	{
		if (line[i] == ' ')
			break;

		ticker += line[i];
	}

	for (i += 1; i < line.size(); ++i)
		price += line[i];

	// qDebug() << ticker << price;

	return std::make_pair(ticker.toStdString(), price);
}

void ToolBar::ReadPrices()
{
	QFile file("prices");

	if(file.open(QFile::ReadOnly | QFile::Text))
	{
		while(!file.atEnd())
		{
			QString buf = file.readLine();
			buf.removeLast();

			prices << TakeTickerAndPrice(buf);
		}

		// qDebug() << prices.size();

		if (prices.size() == 13)
			UpdatePrice();
		else
			GetPrices();
	}
	else
		qDebug() << file.errorString() << file.error();

	file.close();
}

void ToolBar::GetPrices()
{
	if (MoreThanOneFlag == true)
		return;

	MoreThanOneFlag = true;

	qDebug() << "Request";

	// GET request_1("AAPL", "STOCK_PRICE");
	// GET request_2("NVDA", "STOCK_PRICE");
	// GET request_3("AMZN", "STOCK_PRICE");
	// GET request_4("TSLA", "STOCK_PRICE");
	// GET request_5("GOOG", "STOCK_PRICE");
	// GET request_6("MSFT", "STOCK_PRICE");
	// GET request_7("META", "STOCK_PRICE");
	// GET request_8("AMD", "STOCK_PRICE");
	// GET request_9("NFLX", "STOCK_PRICE");
	// GET request_10("INTC", "STOCK_PRICE");
	// GET request_11("COIN", "STOCK_PRICE");
	// GET request_12("ARM", "STOCK_PRICE");
	// GET request_13("KO", "STOCK_PRICE");

	// std::ofstream fl("prices");

	// fl << "AAPL 1\n";
	// fl << "NVDA 2\n";
	// fl << "AMZN 3\n";
	// fl << "TSLA 3\n";
	// fl << "GOOG 4\n";
	// fl << "MSFT 5\n";
	// fl << "META 6\n";
	// fl << "AMD 7\n";
	// fl << "NFLX 8\n";
	// fl << "INTC 9\n";
	// fl << "COIN 10\n";
	// fl << "ARM 11\n";
	// fl << "KO 12\n";

	// fl.close();

	ReadPrices();
}

void ToolBar::UpdatePrice()
{
	for (auto [key, value] : prices)
	{
		stuff[key] = new QLabel(value);
		stockLayout->addWidget(GetTicker(key));
	}
}

QToolBar* ToolBar::operator()()
{
	return this;
}