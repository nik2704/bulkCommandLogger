#include <iostream>
#include <string>
#include "command.h"

Command::Command(const std::string& content) : content_(content) {}

Command::Command(const Command& other) : content_(other.content_) {}

const std::string& Command::GetContent() {
    return content_;
}
