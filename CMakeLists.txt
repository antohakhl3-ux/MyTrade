cmake_minimum_required(VERSION 3.10)
project(MyTradeBackend)

# Устанавливаем стандарт C++17 (нужен для нормальной работы)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем флаги для отладки (очень важно для обучения!)
# -Wall -Wextra показывают все предупреждения, -g добавляет отладочную инфу для gdb
add_compile_options(-Wall -Wextra -g)

# Создаем исполняемый файл my_trade из файла src/main.cpp
add_executable(my_trade src/main.cpp)