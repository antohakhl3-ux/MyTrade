#include "MoexClient.hpp"
#include <iostream>

int main() {
    std::cout << "Starting MyTrade Backend..." << std::endl;
    MoexClient client;
    std::string jsonData = client.fetchHistory("SBER");
        if (!jsonData.empty()) {
            std::cout << "Success! Received " << jsonData.length() << " bytes from MOEX." << std::endl;
            std::cout << "Preview: " << jsonData.substr(0, 200) << "..." << std::endl;
        }
        else{
            std::cout << "Failed to fetch data." << std::endl;
        }
    return 0;
}
