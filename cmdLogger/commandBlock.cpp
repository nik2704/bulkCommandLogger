#include <chrono>
#include <fstream>
#include <vector>
#include "command.h"
#include "commandBlock.h"

CommandBlock::CommandBlock(bool is_dynamic) : is_dynamic_(is_dynamic), is_active_(true), is_printed_(false) {}

size_t CommandBlock::addCommand(const Command& command) {
    commands_.push_back(command);

    if (commands_.size() == 1) {
        first_command_time_ = std::chrono::system_clock::now();
    }

    return commands_.size() - 1;
}

bool CommandBlock::isDynamic() const {
    return is_dynamic_;
}

bool CommandBlock::isEmpty() const {
    return commands_.empty();
}

bool CommandBlock::isActive() const {
    return is_active_;
}

bool CommandBlock::isPrinted() const {
    return is_printed_;
}

void CommandBlock::disablePrinting() {
    is_printed_ = true;
}


void CommandBlock::deactivate() {
    is_active_ = false;
}

std::vector<Command>::iterator CommandBlock::begin() {
    return commands_.begin();
}

std::vector<Command>::iterator CommandBlock::end() {
    return commands_.end();
}

std::vector<Command>::const_iterator CommandBlock::begin() const {
    return commands_.begin();
}

std::vector<Command>::const_iterator CommandBlock::end() const {
    return commands_.cend();
}

std::chrono::system_clock::time_point CommandBlock::getBlockStartTime() const {
    return first_command_time_;
}

size_t CommandBlock::getSize() const {
    return commands_.size();
}

const std::vector<Command> & CommandBlock::getCommands() const {
    return commands_;
}


long long CommandBlock::getBlockStartTimeSeconds() const {
    return std::chrono::duration_cast<std::chrono::seconds>(first_command_time_.time_since_epoch()).count();
}

void CommandBlock::saveToFile() const {
    std::string filename = "bulk" + std::to_string(getBlockStartTimeSeconds()) + ".log";

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    for (const auto& command : commands_) {
        file << command << std::endl;
    }
}
