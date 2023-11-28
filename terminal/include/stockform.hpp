#ifndef STOCKFORM_HPP_
#define STOCKFORM_HPP_

#include <QLabel>

class StockForm : public QLabel
{
private:
    std::unordered_map<std::string, QLabel*> stock_storage;

private:
    void SetLabelDesign(QLable*, std::string);

public:
    StockForm() = default;
    ~StockForm() = default;

    QLabel* operator()(std::string);

};

#endif /* STOCKFORM_HPP_ */