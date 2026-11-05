#include "MoexClient.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <map>
#include <string>

using json = nlohmann::json;

// Функция для парсинга JSON в структуру
TickerData parseTickerData(const json& parsedData, const std::string& ticker) {
    TickerData result;
    result.ticker = ticker;

    // 1. Получаем доступ к блоку marketdata (там цены)
    const json& marketData = parsedData["marketdata"];
    
    // 2. Читаем колонки (это массив строк)
    // Чтобы не гадать, на каком месте "LAST", мы ищем его индекс
    std::map<std::string, int> columnIndexes;
    for (std::size_t i = 0; i < marketData["columns"].size(); ++i) {
        std::string colName = marketData["columns"][i];
        columnIndexes[colName] = i; // Запоминаем: "LAST" -> индекс 12
    }

    // 3. Берем данные (первая строка data[0])
    const json& row = marketData["data"][0];

    // 4. Вытаскиваем значения по именам колонок
    // Если колонки нет (nullptr), ставим 0.0
    if (columnIndexes.count("LAST")) {
        result.lastPrice = row[columnIndexes["LAST"]].is_null() ? 0.0 : row[columnIndexes["LAST"]].get<double>();
    }
    if (columnIndexes.count("OPEN")) {
        result.openPrice = row[columnIndexes["OPEN"]].is_null() ? 0.0 : row[columnIndexes["OPEN"]].get<double>();
    }
    if (columnIndexes.count("HIGH")) {
        result.highPrice = row[columnIndexes["HIGH"]].is_null() ? 0.0 : row[columnIndexes["HIGH"]].get<double>();
    }
    if (columnIndexes.count("LOW")) {
        result.lowPrice = row[columnIndexes["LOW"]].is_null() ? 0.0 : row[columnIndexes["LOW"]].get<double>();
    }
    if (columnIndexes.count("VOLTODAY")) {
        result.volume = row[columnIndexes["VOLTODAY"]].is_null() ? 0 : row[columnIndexes["VOLTODAY"]].get<long long>();
    }

    // 5. Достаем имя из блока securities
    const json& securities = parsedData["securities"];
    std::map<std::string, int> secIndexes;
    for (std::size_t i = 0; i < securities["columns"].size(); ++i) {
        secIndexes[securities["columns"][i]] = i;
    }
    if (secIndexes.count("SHORTNAME")) {
        result.shortName = securities["data"][0][secIndexes["SHORTNAME"]].get<std::string>();
    }

    return result;
}

int main() {
    std::cout << "Starting MyTrade Backend..." << std::endl;

    MoexClient client;

    std::string jsonData = client.fetchHistory("SBER");

    if (!jsonData.empty()) {
            std::cout << "Success! Received " << jsonData.length() << " bytes from MOEX." << std::endl;
            try{
                json parsedData = json::parse(jsonData);

                            // Парсим в структуру
                TickerData sber = parseTickerData(parsedData, "SBER");

            // Выводим красиво
                std::cout << "=== " << sber.shortName << " (" << sber.ticker << ") ===" << std::endl;
                std::cout << "Last Price: " << sber.lastPrice << " RUB" << std::endl;
                std::cout << "Open:       " << sber.openPrice << " RUB" << std::endl;
                std::cout << "High:       " << sber.highPrice << " RUB" << std::endl;
                std::cout << "Low:        " << sber.lowPrice << " RUB" << std::endl;
                std::cout << "Volume:     " << sber.volume << " shares" << std::endl;
            }
            catch (const json::parse_error& e){
                std::cerr << "JSON Parse Error" << e.what() << std::endl;
            }
        }
    else{
            std::cout << "Failed to fetch data." << std::endl;
        }
    return 0;
}
