#include "include/ohlcTable.hpp"

OHLCTable::OHLCTable()
{
	ohlcInfo = new QWidget;
	ohlcLayout = new QVBoxLayout(ohlcInfo);

	ohlcInfo->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint);	
	
	time = new QLabel();
	time->setAlignment(Qt::AlignCenter);
	time->setFixedHeight(25);
	time->setStyleSheet("color: #A6BED4;"
						 "font-size: 14px;"
						 "background-color: #334656;"
						 "border-radius: 3px;"
						 "font-weight: bold;");

	open = new QLabel();
	open->setAlignment(Qt::AlignRight);
	o = new QLabel("open: ");

	open_value = new QFormLayout;
	open_value->addRow(o, open);

	high = new QLabel();
	high->setAlignment(Qt::AlignRight);
	h = new QLabel("high: ");

	high_value = new QFormLayout;
	high_value->addRow(h, high);

	low = new QLabel();
	low->setAlignment(Qt::AlignRight);
	l = new QLabel("low: ");

	low_value = new QFormLayout;
	low_value->addRow(l, low);

	close = new QLabel();
	close->setAlignment(Qt::AlignRight);
	c = new QLabel("close: ");

	close_value = new QFormLayout;
	close_value->addRow(c, close);

	change = new QLabel();
	change->setAlignment(Qt::AlignRight);
	cha = new QLabel("change: ");

	change_value = new QFormLayout;
	change_value->addRow(cha, change);

	o->setStyleSheet("color: #A6BED4; font-size: 14px");
	open->setStyleSheet("font-weight: bold; color: #A6BED4; font-size: 14px;");

	h->setStyleSheet("color: #A6BED4; font-size: 14px");
	high->setStyleSheet("font-weight: bold; color: #A6BED4; font-size: 14px;");

	l->setStyleSheet("color: #A6BED4; font-size: 14px");
	low->setStyleSheet("font-weight: bold; color: #A6BED4; font-size: 14px;");

	c->setStyleSheet("color: #A6BED4; font-size: 14px");
	close->setStyleSheet("font-weight: bold; color: #A6BED4; font-size: 14px;");

	cha->setStyleSheet("color: #A6BED4; font-size: 14px");

	ohlcLayout->addWidget(time);
	ohlcLayout->addLayout(open_value);
	ohlcLayout->addLayout(high_value);
	ohlcLayout->addLayout(low_value);
	ohlcLayout->addLayout(close_value);
	ohlcLayout->addLayout(change_value);

	ohlcInfo->setFixedSize(150, 175);
	ohlcInfo->setStyleSheet("background-color: #243441");
}

void OHLCTable::PrintData(TimeSeries set)
{
	QPoint globalCursorPos = QCursor::pos();
	ohlcInfo->move(globalCursorPos.x() - 180, globalCursorPos.y() - 205);

	ohlcInfo->raise();
	ohlcInfo->show();

	QString str_open = QString::number(set.open) + " $";
	QString str_high = QString::number(set.high) + " $";
	QString str_low = QString::number(set.low) + " $";
	QString str_close = QString::number(set.close) + " $";
	QString str_change = EstimateChange(set.open, set.close);

	time->setText(QDateTime::fromSecsSinceEpoch(set.timestamp).toString("dd MMM yyyy, ddd"));
	open->setText(str_open);
	high->setText(str_high);
	low->setText(str_low);
	close->setText(str_close);
	change->setText(str_change);
}

QString OHLCTable::EstimateChange(double open, double close)
{
	double dchange = close - open;

	bool flag = false;
	if (dchange < 0)
		change->setStyleSheet("font-weight: bold; color: #F57282; font-size: 14px;");
	else if (dchange > 0) 
	{
		change->setStyleSheet("font-weight: bold; color: #33C58D; font-size: 14px;");
		flag = true;
	}
	else
	{
		change->setStyleSheet("font-weight: bold; color: #A6BED4; font-size: 14px;");
		return "0 %"; 
	}

	dchange /= open;
	dchange *= 100;

	dchange = std::ceil(dchange * 100.0) / 100.0;

	if (flag)
		return '+' + QString::number(dchange) + " %";

	return QString::number(dchange) + " %";
}

void OHLCTable::hide()
{
    ohlcInfo->hide();
}