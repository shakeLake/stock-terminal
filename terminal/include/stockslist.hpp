#ifndef STOCKLIST_HPP_
#define STOCKLIST_HPP_

#include <QApplication>
#include <QScreen>

#include <QDockWidget>
#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QCheckBox>
#include <QLabel>
#include <QStringList>
#include <QHeaderView>
#include <QPushButton>

#include <QVBoxLayout>

class StockList : public QDockWidget
{
private:
	QWidget* main_widget;
	QVBoxLayout* main_layout;

	// search
	QLineEdit* search;

	// list
	QWidget* table_widget;
	QTableWidget* table;
	QStringList ctable_name;

	// proceed
	QWidget* proceed_widget;
	QHBoxLayout* proceed_layout;
	QPushButton* proceed;

private:
	void GetSearchBar();
	void GetStockList();
	QWidget* StockCheckBox(std::string);
	void GetProceedMenu();

public:
	StockList();
	~StockList() = default;

	QDockWidget* operator()();

};

#endif /* STOCKLIST_HPP_ */