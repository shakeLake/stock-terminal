#ifndef TOOLBAR_HPP_
#define TOOLBAR_HPP_

#include <QToolBar>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QVector>
#include <QString>
#include <QFile>
#include <QPropertyAnimation>
#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>

#include "../../api/include/client.hpp"
#include "stockform.hpp"

using GET = Client;

class ToolBar : public QToolBar
{
private:
	// label design
	StockForm design;

	QScrollArea* scrollArea;
	QHBoxLayout* main_layout;
	QWidget* main_widget;

	// stock layout
	QWidget* stockLayoutWidget;
	QHBoxLayout* stockLayout;

	// tickers
	std::unordered_map<std::string, QLabel*> stuff;
	QVector<std::pair<std::string, QString>> prices;

	// animation
	QPropertyAnimation* animation;

	int startPoint;
	std::pair<int, bool> endPoint;

	QScrollBar* scrollBar;

	// read prices
	bool MoreThanOneFlag = false;

private:
	void StartAnimation();
	void StockAnimation();
	void Loading();

	void AddTickers();
	QWidget* GetTicker(std::string /* ticker */);

	void ReadPrices();
	void UpdatePrice();
	void GetPrices();

private slots:
	void RestartStockAnimation();

public:
	ToolBar();
	~ToolBar() = default;

	QToolBar* operator()();

};

#endif /* TOOLBAR_HPP_ */