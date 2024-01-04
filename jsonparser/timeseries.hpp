#ifndef TIMESERIES_HPP_
#define TIMESERIES_HPP_

#include <string>

class TimeSeries
{
public:
    std::string timestamp;
    double open;
    double high;
    double low;
    double close;
    double volume;

private:
    TimeSeries() = default;
    ~TimeSeries() = default;

};

#endif /* TIMESERIES_HPP_ */