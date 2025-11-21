#include "fixed_block_memory_resource.h"
#include <stdexcept>
#include <algorithm>

FixedBlockMemoryResource::FixedBlockMemoryResource(size_t size) 
    : buffer(size), total_size(size), used_size(0) {
    free_blocks.push_back({buffer.data(), size});
}

FixedBlockMemoryResource::~FixedBlockMemoryResource() {
    // Автоматически очищается с уничтожением buffer
}

void* FixedBlockMemoryResource::find_free_block(size_t size) {
    for (auto it = free_blocks.begin(); it != free_blocks.end(); ++it) {
        if (it->size >= size) { // блок больше или равен необходимому
            void* result = it->ptr; // запоминаем указатель на начало блока, который будем возвращать
            if (it->size > size) {
                // Отрезаем от свободного блока необходимую часть памяти
                it->ptr = static_cast<char*>(it->ptr) + size; // перемещаем указатель на начало блока памяти
                it->size -= size; // уменьшаем размер
            } else {
                // Удаляем полностью использованный блок
                free_blocks.erase(it);
            }
            return result;
        }
    }
    return nullptr;
}

void* FixedBlockMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    if (bytes == 0) return nullptr;

    void* ptr = find_free_block(bytes);
    if (!ptr) {
        throw std::bad_alloc();
    }

    allocated_blocks[ptr] = bytes;
    used_size += bytes;
    return ptr;
}

void FixedBlockMemoryResource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    (void)bytes; // не используется, но нужен для сигнатуры
    (void)alignment; 
    if (!p) return;

    auto it = allocated_blocks.find(p); // ищем по указателю нужный блок
    if (it != allocated_blocks.end()) { // если не совпадает с концом вектора (т.е. если у нас ни остался изначально выделенный один кусок памяти)
        size_t allocated_size = it->second; // обратиться к значению ячейки с помощью итератора it (которая в map хранит выделенный объём памяти)
        allocated_blocks.erase(it); // удаляем запись из map
        
        free_blocks.push_back({p, allocated_size});
        used_size -= allocated_size;
    }
}

bool FixedBlockMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}