#include "include/toolbar.hpp"

ToolBar::ToolBar()
{
    setMovable(false);

    main_widget = new QWidget;
    addWidget(main_widget);

    main_layout = new QHBoxLayout(main_widget);

    stuff["GOLD"]   = new QLabel("-1");
    stuff["AAPL"]   = new QLabel("-1");
    stuff["SPX"]   = new QLabel("-1");
    stuff["Nasdaq"] = new QLabel("-1");
    stuff["NVIDIA"] = new QLabel("-1"); 
    stuff["AMZN"]   = new QLabel("-1"); 
    stuff["TSLA"]   = new QLabel("-1"); 
    stuff["GOOG"]   = new QLabel("-1"); 
    stuff["BTC"]    = new QLabel("-1");
    stuff["MSFT"]   = new QLabel("-1");
    stuff["META"]   = new QLabel("-1");
    stuff["Brent"]  = new QLabel("-1");

    // Call this first
    // UpdatePrice();

    main_layout->addWidget(GetTicker("GOLD"));
    main_layout->addWidget(new QLabel("  "));

    main_layout->addWidget(GetTicker("AAPL"));
    main_layout->addWidget(new QLabel("  "));

    main_layout->addWidget(GetTicker("SPX"));
    main_layout->addWidget(new QLabel("  "));

    main_layout->addWidget(GetTicker("Nasdaq"));
    main_layout->addWidget(new QLabel("  "));

    main_layout->addWidget(GetTicker("NVIDIA"));
    main_layout->addWidget(new QLabel("  "));

    main_layout->addWidget(GetTicker("AMZN"));
    main_layout->addWidget(new QLabel("  "));

    main_layout->addWidget(GetTicker("TSLA"));
    main_layout->addWidget(new QLabel("  "));

    main_layout->addWidget(GetTicker("GOOG"));
    main_layout->addWidget(new QLabel("  "));

    main_layout->addWidget(GetTicker("BTC"));
    main_layout->addWidget(new QLabel("  "));

    main_layout->addWidget(GetTicker("MSFT"));
    main_layout->addWidget(new QLabel("  "));

    main_layout->addWidget(GetTicker("META"));
    main_layout->addWidget(new QLabel("  "));

    main_layout->addWidget(GetTicker("Brent"));
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

QToolBar* ToolBar::operator()()
{
    return this;
}