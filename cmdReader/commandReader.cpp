#include <iostream>
#include <string>
#include "../cmdLogger/commandBlockQueue.h"
#include "commandReader.h"


CommandReader::CommandReader(size_t block_size) : block_size_(block_size), currentBlockIndex_(0), level_(0) {
    if (block_size_ == 0) {
        throw std::invalid_argument("Размер блока команд должен быть больше 0");
    }
}

void CommandReader::execute() {
    while (true) {
        CommandBlockQueue cmdQueue;

        for (size_t i = 0; i < block_size_; ++i) {
            if (!readCommand(0, cmdQueue)) {
                break;
            }
        }
        
        cmdQueue.logCommandQueue();
    }
}

bool CommandReader::readCommand(std::size_t level, CommandBlockQueue & cmdQueue) {
    std::string line;
    std::getline(std::cin, line);

    if (line.empty() || (line == "}")) {
        cmdQueue.closeBlock(line.empty(), level);
        return false;
    }

    if (line == "{") {
        cmdQueue.openBlock(true);

        while (readCommand(level + 1, cmdQueue)) { }
    } else {
        cmdQueue.addCommand(line, level);
    } 


    return true;
}
