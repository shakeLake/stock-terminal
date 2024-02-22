#include "include/toolbar.hpp"

ToolBar::ToolBar()
{
	setMovable(false);

	main_widget = new QWidget;
	addWidget(main_widget);

	main_layout = new QHBoxLayout(main_widget);

	GetPrices();

	AddTickers();

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

	// animation->setLoopCount(-1);
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

	stockLayout->addWidget(GetTicker("AAPL"));
	stockLayout->addWidget(GetTicker("NVDA"));
	stockLayout->addWidget(GetTicker("AMZN"));
	stockLayout->addWidget(GetTicker("TSLA"));
	stockLayout->addWidget(GetTicker("GOOG"));
	stockLayout->addWidget(GetTicker("MSFT"));
	stockLayout->addWidget(GetTicker("META"));
	stockLayout->addWidget(GetTicker("AMD"));
	stockLayout->addWidget(GetTicker("NFLX"));
	stockLayout->addWidget(GetTicker("INTC"));
	stockLayout->addWidget(GetTicker("COIN"));
	stockLayout->addWidget(GetTicker("ARM"));
	stockLayout->addWidget(GetTicker("KO"));
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

void ToolBar::ReadPrices()
{
	QFile file("prices");

	if(file.open(QFile::ReadOnly | QFile::Text))
	{
		while(!file.atEnd())
		{
			prices << file.readLine();
			prices.back().removeLast();
		}

		if (prices.size() == 13)
			UpdatePrice();
	}
	else
		qDebug() << file.errorString() << file.error();
}

void ToolBar::GetPrices()
{
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

	ReadPrices();
}

void ToolBar::UpdatePrice()
{
	stuff["AAPL"]   = new QLabel(prices[0]);
	stuff["NVDA"] = new QLabel(prices[1]); 
	stuff["AMZN"]   = new QLabel(prices[2]); 
	stuff["TSLA"]   = new QLabel(prices[3]); 
	stuff["GOOG"]   = new QLabel(prices[4]); 
	stuff["MSFT"]   = new QLabel(prices[5]);
	stuff["META"]   = new QLabel(prices[6]);
	stuff["AMD"]    = new QLabel(prices[7]); 
	stuff["NFLX"]   = new QLabel(prices[8]); 
	stuff["INTC"]   = new QLabel(prices[9]);
	stuff["COIN"]   = new QLabel(prices[10]);
	stuff["ARM"]    = new QLabel(prices[11]);
	stuff["KO"]     = new QLabel(prices[12]);
}

QToolBar* ToolBar::operator()()
{
	return this;
}