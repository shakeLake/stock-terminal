#ifndef TOOLBAR_HPP_
#define TOOLBAR_HPP_

#include <QToolBar>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include "stockform.hpp"

class ToolBar : public QToolBar
{
private:
	// label design
	StockForm design;

	// GOLD, AAPL, S&P, Nasdaq, NVIDIA, AMZN, TSLA, GOOG, USD/BTC,
	// MSFT, META, Brent
	QHBoxLayout* main_layout;
	QWidget* main_widget;

	// tickers
	std::unordered_map<std::string, QLabel*> stuff;

private:
	QWidget* GetTicker(std::string /* ticker */);
	void UpdatePrice(std::string /* price */);

public:
	ToolBar();
	~ToolBar() = default;

	QToolBar* operator()();

};

#endif /* TOOLBAR_HPP_ */