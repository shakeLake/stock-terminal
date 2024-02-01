#ifndef REVIEW_HPP_
#define REVIEW_HPP_

#include <QDockWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QWidget>
#include <QLabel>

#include <QChart>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QCandlestickSeries>
#include <QCandlestickSet>
#include <QDateTime>
#include <QFont>

#include <cmath>

#include "../../jsonparser/parser.hpp"
#include "mychartview.hpp"
#include "rescrollbar.hpp"

class Review : public QDockWidget
{
	Q_OBJECT

private:
	QLabel* infoData;

	QWidget* container;
	QVBoxLayout* layout;

	std::string rev_ticker;

	QCandlestickSeries* series;
	std::vector<TimeSeries> ohlc;
	QStringList categories;
	QChart* chart;

	QBarCategoryAxis* axisX;
	QValueAxis* axisY;

	MyChartView* chartView;

private:
	void CandleSeriesInit();
	void GetOHLC();
	void CandlestickSetInit();
	void ChartInit();

public:
	Review();
	~Review() = default;

	void ReviewStart(std::string /*ticker*/);

	QDockWidget* operator()();

};

#endif /* REVIEW_HPP_ */