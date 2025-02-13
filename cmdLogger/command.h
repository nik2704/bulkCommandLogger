#pragma once
#include <iostream>
#include <string>

/**
 * @brief Класс Command - команда.
 * 
 * Строковое представление команды и предоставляет методы
 * для доступа к содержимому команды и вывода её на экран.
 */
class Command {
public:
    /**
     * @brief Конструктор Command.
     * 
     * @param content Текст команды.
     */
    explicit Command(const std::string& content);

    /**
     * @brief Конструктор копирования.
     * 
     * @param other Другой объект команды.
     */
    Command(const Command& other);

    /**
     * @brief Получить содержимое команды.
     * 
     * Возвращает строку, содержащую текст команды.
     * 
     * @return const std::string& Содержимое команды.
     */
    const std::string& GetContent();

    /**
     * @brief Перегрузка оператора вывода для команды.
     * 
     * @param os Поток вывода.
     * @param cmd Объект команды.
     * @return std::ostream& Поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const Command& cmd) {
        os << cmd.content_;
        return os;
    }

private:
    std::string content_; /**< Текст команды. */
};
