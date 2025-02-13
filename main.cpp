
#include <iostream>
#include <string>
#include "./cmdReader/commandReader.h"


int main(int argc, char* argv[]) {
    // Проверка на наличие аргумента командной строки для размера блока команд
    if (argc < 2) {
        std::cerr << "Ошибка: укажите размер блока команд.\n";
        return 1; // Завершаем программу с кодом ошибки
    }

    try {
        // Преобразуем строковый аргумент в число
        size_t block_size = std::stoul(argv[1]);

        // Создаем объект для обработки команд с заданным размером блока
        CommandReader commandReader(block_size);
        commandReader.execute();
    } catch (const std::exception& e) {
        // Обработка ошибок при некорректном размере блока команд
        std::cerr << "Некорректный размер блока: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}