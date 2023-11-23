#ifndef API_HPP_
#define API_HPP_

class APICall
{
private:
    std::string api_key;

public:
    APICall() = delete;

    APICall(std::string& /*api key*/);
    ~APICall() = default;

    std::string& TIME_SERIES_INTRADAY(std::string& /*symbol*/, 
                                     std::string& /*interval*/);

    std::string& TIME_SERIES_DAILY(std::string& /*symbol*/);

};

#endif /* API_HPP_ */