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

	QScrollBar* scrollBar = scrollArea->horizontalScrollBar();
	QPropertyAnimation *animation = new QPropertyAnimation(scrollBar, "sliderPosition");

    animation->setStartValue(scrollBar->sliderPosition());
    animation->setEndValue(scrollBar->sliderPosition() + 10);

    animation->start(QAbstractAnimation::DeleteWhenStopped);

	main_layout->addWidget(scrollArea);
}

void ToolBar::AddTickers()
{
	stockLayoutWidget = new QWidget;
	stockLayout = new QHBoxLayout(stockLayoutWidget);
	stockLayout->setSpacing(40);

	stockLayout->addWidget(GetTicker("AAPL"));
	stockLayout->addWidget(GetTicker("NVIDIA"));
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
						"height: 20px");

	layout->addWidget(tickicon);
	layout->addWidget(ticker_name);

	// Price
	stuff[ticker]->setStyleSheet("font: 14px;"
								 "color: white;"
								 "font-weight: bold");

	layout->addWidget(stuff[ticker]);

	return tick;
}

void ToolBar::GetPrices()
{
	// GET request("AAPL", "STOCK_PRICE");
	// GET request("NVIDIA", "STOCK_PRICE");
	// GET request("AMZN", "STOCK_PRICE");
	// GET request("TSLA", "STOCK_PRICE");
	// GET request("GOOG", "STOCK_PRICE");
	// GET request("MSFT", "STOCK_PRICE");
	// GET request("META", "STOCK_PRICE");
	// GET request("AMD", "STOCK_PRICE");
	// GET request("NFLX", "STOCK_PRICE");
	// GET request("INTC", "STOCK_PRICE");
	// GET request("COIN", "STOCK_PRICE");
	// GET request("ARM", "STOCK_PRICE");
	// GET request("KO", "STOCK_PRICE");

	QFile file("prices");

	if(file.open(QFile::ReadOnly | QFile::Text))
	{
		while(!file.atEnd())
			prices << file.readLine();

		if (prices.size() == 13)
			UpdatePrice();
		else
			qDebug() << "Not enough error\n";
	}
	else
		qDebug() << file.errorString() << file.error();
}

void ToolBar::UpdatePrice()
{
	stuff["AAPL"]   = new QLabel(prices[0]);
	stuff["NVIDIA"] = new QLabel(prices[1]); 
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