#pragma once
#include <string>

struct TickerData {
    std::string ticker;
    std::string shortName;
    double lastPrice;
    double openPrice;
    double highPrice;
    double lowPrice;
    long long volume;
};

class MoexClient{
public:
    MoexClient();
    ~MoexClient();

    std::string fetchHistory(const std::string& ticker);
};
