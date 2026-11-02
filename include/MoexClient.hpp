#pragma once
#include <string>

class MoexClient{
public:
    MoexClient();
    ~MoexClient();

    std::string fetchHistory(const std::string& ticker);
};
