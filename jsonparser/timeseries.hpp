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

public:
    TimeSeries() = default;

    TimeSeries(const TimeSeries& t)
    {
        timestamp = t.timestamp;
        open = t.open; 
        high = t.high;
        low = t.low;
        close = t.close;
        volume = t.volume;
    }

    ~TimeSeries() = default;

};

#endif /* TIMESERIES_HPP_ */