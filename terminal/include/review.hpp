#ifndef REVIEW_HPP_
#define REVIEW_HPP_

#include <QDockWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

#include <QChart>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QCandlestickSeries>
#include <QCandlestickSet>
#include <QDateTime>

#include "../../jsonparser/parser.hpp"
#include "mychartview.hpp"

class Review : public QDockWidget
{
	Q_OBJECT

private:
	std::string rev_ticker;

	QCandlestickSeries* series;
	std::vector<TimeSeries> ohlc;
	QStringList categories;
	QChart* chart;

	MyChartView* chartView;

	// ohlc info
	QWidget* ohlcInfo;
	QVBoxLayout* ohlcLayout;
	QLabel* open;
	QLabel* high;
	QLabel* low;
	QLabel* close;

private:
	void CandleSeriesInit();
	void GetOHLC();
	void CandlestickSetInit();
	void ChartInit();

private slots:
	void PrintData(bool, QCandlestickSet*);

public:
	Review(std::string /* ticker */);
	~Review() = default;

	QDockWidget* operator()();

};

#endif /* REVIEW_HPP_ */