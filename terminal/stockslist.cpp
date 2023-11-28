#include "include/stockslist.hpp"

StockList::StockList()
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    // hides title bar
    setTitleBarWidget(new QWidget);    

    QWidget* container = new QWidget;
    setWidget(container);

    container->setStyleSheet("background-color: red");

    QVBoxLayout* layout = new QVBoxLayout(container);
}

QDockWidget* StockList::operator()()
{
    return this;
}
