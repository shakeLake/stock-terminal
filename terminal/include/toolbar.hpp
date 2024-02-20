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

#include "stockform.hpp"

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
	QVector<QString> prices;

	// animation
	QPropertyAnimation* animation;
	QScrollBar* scrollBar;

private:
	void StockAnimation();

	void AddTickers();
	QWidget* GetTicker(std::string /* ticker */);
	void UpdatePrice();
	void GetPrices();

private slots:
	void RestartStockAnimation();
	void FakeCircle();

public:
	ToolBar();
	~ToolBar() = default;

	QToolBar* operator()();

};

#endif /* TOOLBAR_HPP_ */