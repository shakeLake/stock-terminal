#include "include/stockform.hpp"

// QLabel* StockForm::operator()(std::string ticker)
// {
//	 if (stock_storage.find(ticker) != stock_storage.end())
//		 return stock_storage[ticker];

//	 stock_storage[ticker] = new QLabel(ticker);

//	 return stock_storage[ticker];
// }

void StockForm::SetLabelDesignToolBar(QLabel* label, std::string ticker)
{
	label->setText(QString::fromStdString(ticker));

	label->setStyleSheet("color: white");

	label->repaint();
}