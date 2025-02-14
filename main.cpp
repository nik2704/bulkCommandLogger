
#include <iostream>
#include <string>
#include "./cmdReader/commandReader.h"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Ошибка: укажите размер блока команд.\n";
        return 1;
    }

    try {
        size_t block_size = std::stoul(argv[1]);

        CommandReader commandReader(block_size);
        commandReader.execute();
    } catch (const std::exception& e) {
        std::cerr << "Некорректный размер блока: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}