#ifndef STOCKFORM_HPP_
#define STOCKFORM_HPP_

#include <QLabel>
#include <QString>

class StockForm : public QLabel
{
// private:
    // std::unordered_map<std::string, QLabel*> stock_storage;

public:
    StockForm() = default;
    ~StockForm() = default;

    void SetLabelDesignToolBar(QLabel*, std::string);

    // QLabel* operator()(std::string);

};

#endif /* STOCKFORM_HPP_ */