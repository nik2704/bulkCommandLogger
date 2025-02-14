#include <optional>
#include <queue>
#include <iostream>
#include "commandBlock.h"
#include "commandBlockQueue.h"


void CommandBlockQueue::addCommand(const std::string& command_text, std::size_t level) {
    if (blocks_.empty() || !blocks_.back().isActive()) {
        openBlock(level > 0);
    }

    blocks_.back().addCommand(Command(command_text));
}

void CommandBlockQueue::openBlock(bool isDynamic) {
    if (!blocks_.empty() && !blocks_.back().isDynamic()) {
        logBlocks(blocks_.size() - 1);

        blocks_.back().deactivate();
    }

    blocks_.emplace_back(isDynamic);
}

void CommandBlockQueue::closeBlock(bool disable_printing, std::size_t level) {   
    if (!blocks_.empty()) {
        auto& block = blocks_.back();
        block.deactivate();

        if (disable_printing && block.isDynamic()) {
            block.disablePrinting();
        }

        if (block.isDynamic() && level == 1) {
            logDynamicBlocks();
        }
    }
}

void CommandBlockQueue::logDynamicBlocks() {
    if (auto index_opt = findBlockIndex([](const CommandBlock& block) { return block.isDynamic() && !block.isPrinted(); }); index_opt) {
        logBlocks(*index_opt);
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
    if (auto index_opt = findBlockIndex([](const CommandBlock& block) { return !block.isPrinted(); }); index_opt) {
        logBlocks(*index_opt);
    }
}

std::size_t CommandBlockQueue::Size() const {
    return blocks_.size();
}

CommandBlockQueue::iterator CommandBlockQueue::begin() { return blocks_.begin(); }
CommandBlockQueue::iterator CommandBlockQueue::end() { return blocks_.end(); }
CommandBlockQueue::const_iterator CommandBlockQueue::begin() const { return blocks_.begin(); }
CommandBlockQueue::const_iterator CommandBlockQueue::end() const { return blocks_.end(); }

template <typename Predicate>
std::optional<std::size_t> CommandBlockQueue::findBlockIndex(Predicate predicate) const {
    auto it = std::find_if(blocks_.begin(), blocks_.end(), predicate);
    return (it != blocks_.end()) ? std::optional<std::size_t>(std::distance(blocks_.begin(), it)) : std::nullopt;
}

std::ostream& operator<<(std::ostream& os, const CommandBlockQueue& queue) {
    for (const auto& block : queue.blocks_) {
        bool first = true;

        for (const auto& command : block.getCommands()) {
            if (!first) {
                os << ", ";
            }
            os << command;
            first = false;
        }

        os << std::endl;
    }

    return os;
}