#pragma once
#include <string>

// Структура для хранения текущих данных по акции
struct TickerData {
    std::string ticker;      // "SBER"
    std::string shortName;   // "Сбербанк"
    double lastPrice;        // 292.8 (LAST)
    double openPrice;        // 290.89 (OPEN)
    double highPrice;        // 294.71 (HIGH)
    double lowPrice;         // 289.05 (LOW)
    long long volume;        // 20901302 (VOLTODAY)
};