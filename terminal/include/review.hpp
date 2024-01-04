#ifndef REVIEW_HPP_
#define REVIEW_HPP_

#include <QDockWidget>
#include <QVBoxLayout>
#include <QWidget>

#include <QChart>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QCandlestickSeries>
#include <QCandlestickSet>
#include <QDateTime>

#include "../../jsonparser/parser.hpp"

class Review : public QDockWidget
{
	Q_OBJECT
public:
	Review();
	~Review() = default;

	QDockWidget* operator()();

};

#endif /* REVIEW_HPP_ */