#ifndef FIXED_BLOCK_MEMORY_RESOURCE_H
#define FIXED_BLOCK_MEMORY_RESOURCE_H

#include <memory_resource> // для работы с polymorphic memory resources
#include <vector>
#include <map>
#include <cstddef> // библиотека для типов и макросов связанных с размерами памяти

class FixedBlockMemoryResource : public std::pmr::memory_resource { // ::pmr - базовый класс для создания своих менеджеров памяти
private:
    std::vector<char> buffer; // область памяти, которая выделяется при создании, и откуда потом выделяются кусочки памяти (по 1 байту)
    std::map<void*, size_t> allocated_blocks; // словарь: ключ - адрес выделенного блока, size_t - значение размер блока в байтах
    size_t total_size;
    size_t used_size;

    struct FreeBlock {
        void* ptr;
        size_t size;
    };
    std::vector<FreeBlock> free_blocks; // список свободных блоков для переиспользования

    void* find_free_block(size_t size);

public:
    explicit FixedBlockMemoryResource(size_t size); // explicit - Запрещает неявное преобразование типов
    ~FixedBlockMemoryResource();

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

#endif