cmake_minimum_required(VERSION 3.10)
project(MyTradeBackend)
include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)
# Устанавливаем стандарт C++17 (нужен для нормальной работы)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем флаги для отладки (очень важно для обучения!)
# -Wall -Wextra показывают все предупреждения, -g добавляет отладочную инфу для gdb
add_compile_options(-Wall -Wextra -g)

find_package(CURL REQUIRED)

include_directories(include)

# Создаем исполняемый файл my_trade из файла src/main.cpp
add_executable(my_trade src/main.cpp src/MoexClient.cpp)

target_link_libraries(my_trade PRIVATE ${CURL_LIBRARIES} nlohmann_json::nlohmann_json)