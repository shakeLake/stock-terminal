#ifndef STOCKLIST_HPP_
#define STOCKLIST_HPP_

#include <iostream>

#include <QApplication>
#include <QScreen>

#include <QDockWidget>
#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QCheckBox>
#include <QLabel>
#include <QStringList>
#include <QPushButton>

#include <QVBoxLayout>
#include <QHeaderView>

#include <QFile>

#include <unordered_map>

#include "completer.hpp"

class StockList : public QDockWidget
{
	Q_OBJECT
private:
	QWidget* main_widget;
	QVBoxLayout* main_layout;

	// search
	QLineEdit* search;
	QCompleter* completer;
	std::unordered_map<std::string, int> taken;
	int cellPointer = 0;

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

private slots:
	void TakeFromLineEdit();

public:
	StockList();
	~StockList() = default;

	QDockWidget* operator()();

};

#endif /* STOCKLIST_HPP_ */