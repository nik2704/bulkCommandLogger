#pragma once
#include <iostream>
#include <string>
#include "../cmdLogger/commandBlockQueue.h"


/**
 * @brief Класс CommandReader отвечает за чтение и выполнение команд в блоках.
 */
class CommandReader {
public:
    /**
     * @brief Конструктор класса CommandReader.
     * 
     * @param block_size Размер блока команд.
     * @throws std::invalid_argument Если размер блока команд равен 0.
     */
    CommandReader(size_t block_size);

    // Запрещаем копирование и присваивание
    CommandReader(const CommandReader&) = delete;CommandBlockQueue cmdQueue_;
    CommandReader& operator=(const CommandReader&) = delete;

    /**
     * @brief Выполнить чтение команд и их выполнение.
     */
    void execute();

private:
    /**
     * @brief Прочитать одну команду и добавить ее в блок.
     * 
     * Читает одну строку из ввода, анализирует ее и добавляет команду в текущий блок.
     * Если команда представляет собой начало нового блока или завершение блока, это также обрабатывается.
     * 
     * @param isDynamic Флаг, указывающий, является ли команда динамической.
     * @param startIteration Флаг, указывающий начало нового цикла.
     * @return bool Возвращает true, если команда была успешно прочитана и обработана, иначе false.
     */
    bool readCommand(std::size_t level, CommandBlockQueue & cmdQueue);


    size_t block_size_; /**< Размер блока команд. */
    size_t currentBlockIndex_; /**< Индекс текущего блока команд. */
    // CommandManager commandManager_; /**< Менеджер команд для обработки и логирования команд. */
    size_t level_;
};
