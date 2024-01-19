#ifndef OHLCTABLE_HPP_
#define OHLCTABLE_HPP_

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>

class OHLCTable
{
private:
	// ohlc info
	QWidget* ohlcInfo;
	QVBoxLayout* ohlcLayout;

	QLabel* time;
	QLabel* open;
	QLabel* high;
	QLabel* low;
	QLabel* close;
	QLabel* change;

	QLabel* o;
	QLabel* h;
	QLabel* l;
	QLabel* c;
	QLabel* cha;

	QFormLayout* open_value;
	QFormLayout* high_value;
	QFormLayout* low_value;
	QFormLayout* close_value;
	QFormLayout* change_value;

private:
	void PrintData(TimeSeries);
    QString EstimateChange(double open, double close)

public:
    OHLCTable();
    ~OHLCTable();

};

#endif /* OHLCTABLE_HPP_ */