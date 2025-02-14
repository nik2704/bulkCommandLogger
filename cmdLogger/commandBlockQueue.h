#pragma once
#include <algorithm>
#include <optional>
#include <queue>
#include <vector>
#include "commandBlock.h"


/**
 * @brief Класс CommandBlockQueue представляет очередь блоков команд.
 */
class CommandBlockQueue final {
public:
    using iterator = std::deque<CommandBlock>::iterator; /**< Тип итератора для блока команд. */
    using const_iterator = std::deque<CommandBlock>::const_iterator; /**< Тип константного итератора для блока команд. */

    /**
     * @brief Оператор присваивания удален.
     * 
     */
    CommandBlockQueue& operator=(const CommandBlockQueue&) = delete;

    /**
     * @brief Добавить команду в очередь.
     * 
     * @param command_text Текст команды.
     * @param level Уровень вложенности команды.
     */
    void addCommand(const std::string& command_text, std::size_t level);

    /**
     * @brief Открыть новый блок команд.
     * 
     * @param isDynamic Флаг, указывающий, является ли блок динамическим.
     */
    void openBlock(bool isDynamic);

    /**
     * @brief Закрыть текущий блок команд.
     * 
     * @param disable_printing Флаг, запрещающий вывод блока.
     * @param level Уровень вложенности команды.
     */
    void closeBlock(bool disable_printing, std::size_t level);

    /**
     * @brief Записать содержимое очереди в лог.
     */
    void logCommandQueue();

    /**
     * @brief Получить размер очереди блоков команд.
     * 
     * @return std::size_t Количество блоков в очереди.
     */
    std::size_t Size() const;

    /**
     * @brief Получить итератор на начало очереди блоков.
     * 
     * @return iterator Итератор на начало очереди блоков.
     */
    iterator begin();

    /**
     * @brief Получить итератор на конец очереди блоков.
     * 
     * @return iterator Итератор на конец очереди блоков.
     */
    iterator end();

    /**
     * @brief Получить константный итератор на начало очереди блоков.
     * 
     * @return const_iterator Константный итератор на начало очереди блоков.
     */
    const_iterator begin() const;

    /**
     * @brief Получить константный итератор на конец очереди блоков.
     * 
     * @return const_iterator Константный итератор на конец очереди блоков.
     */
    const_iterator end() const;

    /**
     * @brief Перегрузка операто#include <algorithm>ра вывода для очереди блоков.
     * 
     * @param os Поток вывода.
     * @param queue Объект очереди блоков команд.
     * @return std::ostream& Поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const CommandBlockQueue& queue);

private:
    std::deque<CommandBlock> blocks_; /**< Очередь блоков команд. */

    template <typename Predicate>
    std::optional<std::size_t> findBlockIndex(Predicate predicate) const;

    void logDynamicBlocks();
    void logBlocks(std::size_t index);
};

