cmake_minimum_required(VERSION 2.8.0)
project(player_movement)

# Найдём библиотеку SFML в системе
find_package(SFML 2.5 REQUIRED graphics window system)

# Создадим исполняемый файл по имени player_movement из исходных файлов
add_executable(player_movement src/main.cpp src/player.cpp src/player_states.cpp)

# Укажем, что нужно использовать стандарт C++20
target_compile_features(player_movement PRIVATE cxx_std_20)

# Подключим библиотеку SFML к нашему проекту
target_link_libraries(player_movement PRIVATE sfml-graphics sfml-system sfml-window)
