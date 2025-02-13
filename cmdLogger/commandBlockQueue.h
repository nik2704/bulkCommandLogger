#pragma once
#include <algorithm>
#include <optional>
#include <queue>
#include <vector>
#include "commandBlock.h"


/**#include <algorithm>
 * @brief Класс CommandBlockQueue представляет очередь блоков команд.
 * 
 */
class CommandBlockQueue {
public:
    using iterator = std::deque<CommandBlock>::iterator; /**< Тип итератора для блока команд. */
    using const_iterator = std::deque<CommandBlock>::const_iterator; /**< Тип константного итератора для блока команд. */

    // CommandBlockQueue() : level_(0) { };
    /**
     * @brief Оператор присваивания удален.
     * 
     */
    CommandBlockQueue& operator=(const CommandBlockQueue&) = delete;

//---------------------------------

    void addCommand(const std::string& command_text, std::size_t level);

    void openBlock(bool isDynamic);

    void closeBlock(bool disable_printing, std::size_t level);

    void logCommandQueue();

    std::size_t Size() const;

//------------------------------


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
    friend std::ostream& operator<<(std::ostream& os, const CommandBlockQueue& queue) {
        for (auto it = queue.begin(); it < queue.end(); ++it) {
            // os << "Level:" << queue.level_ << ", Active:" << (*it).isActive() << ", Printed:" << (*it).isPrinted() << ", Dynamic:" << (*it).isDynamic() << ": ";

            // if (!(*it).isEmpty()) {
                bool start = true;

                for (const auto& command : (*it).getCommands()) {
                    if (!start) {
                        os << ", ";
                    }

                    os << command;
                    start = false;
                }

                std::cout << std::endl;
            // }

        }

        os << std::endl;
        
        return os;
    }

private:
    // std::size_t level_;
    std::deque<CommandBlock> blocks_; /**< Очередь блоков команд. */

    template <typename Predicate>
    std::optional<std::size_t> findBlockIndex(Predicate predicate) const {
        auto it = std::find_if(blocks_.begin(), blocks_.end(), predicate);

        if (it != blocks_.end()) {
            return std::distance(blocks_.begin(), it);
        }

        return std::nullopt;
    }

    void logDynamicBlocks();
    void logBlocks(std::size_t index);
};

