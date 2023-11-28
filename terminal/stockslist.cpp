#include "include/stockslist.hpp"

StockList::StockList()
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    QWidget* container = new QWidget;
    setWidget(container);

    QVBoxLayout* layout = new QVBoxLayout(container);
    search = new QLineEdit;
    search->setFixedSize(50, 100);

    test = new QLabel("test");

    layout->addWidget(search);
    layout->addWidget(test);
}

QDockWidget* StockList::operator()()
{
    return this;
}
