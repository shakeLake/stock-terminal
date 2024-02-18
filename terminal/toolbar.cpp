#include "include/toolbar.hpp"

ToolBar::ToolBar()
{
	setMovable(false);

	main_widget = new QWidget;
	addWidget(main_widget);

	main_layout = new QHBoxLayout(main_widget);
	main_layout->setSpacing(40);

	stuff["AAPL"]   = new QLabel("-1");
	stuff["NVIDIA"] = new QLabel("-1"); 
	stuff["AMZN"]   = new QLabel("-1"); 
	stuff["TSLA"]   = new QLabel("-1"); 
	stuff["GOOG"]   = new QLabel("-1"); 
	stuff["MSFT"]   = new QLabel("-1");
	stuff["META"]   = new QLabel("-1");
	stuff["AMD"]   = new QLabel("-1"); 
	stuff["NFLX"]   = new QLabel("-1"); 
	stuff["INTC"]   = new QLabel("-1");
	stuff["COIN"]   = new QLabel("-1");
	stuff["ARM"]   = new QLabel("-1");
	stuff["KO"]   = new QLabel("-1");

	// Call this first
	// UpdatePrice();

	main_layout->addWidget(GetTicker("AAPL"));
	main_layout->addWidget(GetTicker("NVIDIA"));
	main_layout->addWidget(GetTicker("AMZN"));
	main_layout->addWidget(GetTicker("TSLA"));
	main_layout->addWidget(GetTicker("GOOG"));
	main_layout->addWidget(GetTicker("MSFT"));
	main_layout->addWidget(GetTicker("META"));
	main_layout->addWidget(GetTicker("AMD"));
	main_layout->addWidget(GetTicker("NFLX"));
	main_layout->addWidget(GetTicker("INTC"));
	main_layout->addWidget(GetTicker("COIN"));
	main_layout->addWidget(GetTicker("ARM"));
	main_layout->addWidget(GetTicker("KO"));

	QPropertyAnimation *animation = new QPropertyAnimation(main_widget, "pos");
    animation->setDuration(10000);

    animation->setStartValue(QPoint(main_widget->x(), main_widget->y()));
    animation->setEndValue(QPoint(main_widget->x() + 150, main_widget->y()));

    animation->start();
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
	GET request("AAPL", "STOCK_PRICE");
	GET request("NVIDIA", "STOCK_PRICE");
	GET request("AMZN", "STOCK_PRICE");
	GET request("TSLA", "STOCK_PRICE");
	GET request("GOOG", "STOCK_PRICE");
	GET request("MSFT", "STOCK_PRICE");
	GET request("META", "STOCK_PRICE");
	GET request("AMD", "STOCK_PRICE");
	GET request("NFLX", "STOCK_PRICE");
	GET request("INTC", "STOCK_PRICE");
	GET request("COIN", "STOCK_PRICE");
	GET request("ARM", "STOCK_PRICE");
	GET request("KO", "STOCK_PRICE");
}

QToolBar* ToolBar::operator()()
{
	return this;
}