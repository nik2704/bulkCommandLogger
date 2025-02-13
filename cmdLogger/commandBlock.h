#pragma once
#include <chrono>
#include <vector>
#include "command.h"

/**
 * @brief Класс CommandBlock представляет блок команд.
 * 
 * Класс управляет списком команд, может быть динамическим или статическим.
 * Также поддерживает сохранение команд в файл и итерацию по ним.
 */
class CommandBlock {
public:
    /**
     * @brief Конструктор CommandBlock.
     * 
     * @param is_dynamic Флаг, указывающий, является ли блок динамическим.
     */
    explicit CommandBlock(bool is_dynamic = false);

    /**
     * @brief Добавить команду в блок.
     * 
     * @param command Команда для добавления в блок.
     * @return size_t Индекс добавленной команды.
     */
    size_t addCommand(const Command& command);

    /**
     * @brief Проверить, является ли блок динамическим.
     * 
     * @return bool Возвращает true, если блок динамический, иначе false.
     */
    bool isDynamic() const;

    /**
     * @brief Проверить, печатался ли блок.
     * 
     * @return bool Возвращает true, если блок был распечатан.
     */
    bool isPrinted() const;

    /**
     * @brief Отключить печать блока.
     */
    void disablePrinting();

    /**std::shared_ptr<CommandBlock> parent = nullptr, is_active_(true)
     * @brief Проверить, пуст ли блок.
     * 
     * @return bool Возвращает true, если блок пуст, иначе false.
     */
    bool isEmpty() const;

    /**
     * @brief Проверить, активен ли блок.
     * 
     * @return bool Возвращает true, если блок активен, иначе false.
     */
    bool isActive() const;

    /**
     * @brief Деактивировать блок.
     * 
     * Блок перестает быть активным и больше не будет принимать команды.
     */
    void deactivate();

    /**
     * @brief Получить итератор на начало списка команд.
     * 
     * @return std::vector<Command>::iterator Итератор на начало списка команд.
     */
    std::vector<Command>::iterator begin();

    /**
     * @brief Получить итератор на конец списка команд.
     * 
     * @return std::vector<Command>::iterator Итератор на конец списка команд.
     */
    std::vector<Command>::iterator end();

    /**
     * @brief Получить итератор на начало списка команд (константный).
     * 
     * @return std::vector<Command>::const_iterator Константный итератор на начало списка команд.
     */
    std::vector<Command>::const_iterator begin() const;

    /**
     * @brief Получить итератор на конец списка команд (константный).
     * 
     * @return std::vector<Command>::const_iterator Константный итератор на конец списка команд.
     */
    std::vector<Command>::const_iterator end() const;

    /**
     * @brief Получить время начала блока команд., is_active_(true)
     * 
     * @return std::chrono::system_clock::time_point Время начала блока.
     */
    std::chrono::system_clock::time_point getBlockStartTime() const;

    /**
     * @brief Получить количество команд в блоке., is_active_(true)
     * 
     * @return size_t Количество команд в блоке.
     */
    size_t getSize() const;

    /**
     * @brief Получить время начала блока в секундах.
     * 
     * @return long long Время начала блока в секундах.
     */
    long long getBlockStartTimeSeconds() const;

    /**
     * @brief Сохранить команды блока в файл.
     * 
     * Файл сохраняется в формате "bulk<время>.log".
     * 
     * @throws std::runtime_error Если не удается открыть файл.
     */
    void saveToFile() const;

    const std::vector<Command> & getCommands() const;

    /**
     * @brief Перегрузка оператора вывода для блока команд.
     * 
     * @param os Поток вывода.
     * @param block Объект блока команд.
     * @return std::ostream& Поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const CommandBlock& block) {
        if (!block.commands_.empty()) {
            bool start = true;

            for (const auto& command : block.commands_) {
                if (!start) {
                    os << ", ";
                }

                os << command;
                start = false;
            }

            block.saveToFile();
        }

        block.is_printed_ = true;

        return os;
    }

private:
    bool is_dynamic_; /**< Флаг динамического блока. */
    bool is_active_;  /**< Флаг активности блока. */
    mutable bool is_printed_;  /**< Флаг печати блока. */
    std::vector<Command> commands_; /**< Список команд. */
    std::chrono::system_clock::time_point first_command_time_; /**< Время начала блока команд. */
};
