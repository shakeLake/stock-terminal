#ifndef API_HPP_
#define API_HPP_

#include <string>

class APICall
{
private:
    std::string apiKey;

public:
    APICall(std::string /*api*/);

    APICall() = delete;
    ~APICall() = default;

    // Core Stock API
    std::string TIME_SERIES_INTRADAY(std::string /*symbol*/, 
                                      std::string /*interval*/);

    std::string TIME_SERIES_DAILY(std::string /*symbol*/);

    // Alpha Intelligence
    std::string NEWS_SENTIMENT(std::string /*ticker*/);

};

#endif /* API_HPP_ */