#include <optional>
#include <queue>
#include <iostream>
#include "commandBlock.h"
#include "commandBlockQueue.h"


void CommandBlockQueue::addCommand(const std::string& command_text, std::size_t level) {
    Command command(command_text);

    if (Size() == 0 || !blocks_.back().isActive()) {
        openBlock(level > 0);
    }

    blocks_.back().addCommand(command);
}

void CommandBlockQueue::openBlock(bool isDynamic) {
    if (Size() > 0) {
        auto index = Size() - 1;

        if (!blocks_[index].isDynamic()) {
            logBlocks(index);
        }

        blocks_[index].deactivate();
    }

    blocks_.emplace_back(isDynamic);
}

void CommandBlockQueue::closeBlock(bool disable_printing, std::size_t level) {   
    if (Size() > 0) {
        auto & block = blocks_[Size() - 1];
        block.deactivate();

        if (disable_printing && block.isDynamic()) {
            block.disablePrinting();
        }

        if (block.isDynamic()) {
            // std::cout << "DYNAMIC, level=" << level_ << std::endl;

            if (level == 1) {
                logDynamicBlocks();
            }

            // --level_;
        }
    }
}

void CommandBlockQueue::logDynamicBlocks() {
    auto index_opt = findBlockIndex([](const CommandBlock& block) {
        return block.isDynamic() && !block.isPrinted();
    });

    if (index_opt.has_value()) {
        logBlocks(index_opt.value());
    }
}

void CommandBlockQueue::logBlocks(std::size_t index) {
    bool start = true;
    std::cout << "bulk: ";

    for (std::size_t i = index; i < Size(); ++i) {
        if (!blocks_[i].isPrinted()) {
            if (!start) {
                std::cout << ", ";
            }

            std::cout << blocks_[i];
            start = false;
        }
    }

    std::cout << std::endl;
}

void CommandBlockQueue::logCommandQueue() {
    auto index_opt = findBlockIndex([](const CommandBlock& block) {
        return !block.isPrinted();
    });

    if (index_opt.has_value()) {
        logBlocks(index_opt.value());
    }
}

std::size_t CommandBlockQueue::Size() const {
    return blocks_.size();
}

CommandBlockQueue::iterator CommandBlockQueue::begin() {
    return blocks_.begin();
}

CommandBlockQueue::iterator CommandBlockQueue::end() {
    return blocks_.end();
}

CommandBlockQueue::const_iterator CommandBlockQueue::begin() const {
    return blocks_.begin();
}

CommandBlockQueue::const_iterator CommandBlockQueue::end() const {
    return blocks_.end();
}
