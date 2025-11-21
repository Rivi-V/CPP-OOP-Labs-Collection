#include <gtest/gtest.h>
#include "fixed_block_memory_resource.h"
#include "queue.h"

// Тесты для FixedBlockMemoryResource
TEST(FixedBlockMemoryResourceTest, BasicAllocation) {
    FixedBlockMemoryResource memory_resource(1024);
    
    void* ptr1 = memory_resource.allocate(100, 1);
    void* ptr2 = memory_resource.allocate(200, 1);
    
    ASSERT_NE(ptr1, nullptr);
    ASSERT_NE(ptr2, nullptr);
    ASSERT_NE(ptr1, ptr2);
    
    memory_resource.deallocate(ptr1, 100, 1);
    memory_resource.deallocate(ptr2, 200, 1);
}

TEST(FixedBlockMemoryResourceTest, MemoryReuseSimple) {
    FixedBlockMemoryResource memory_resource(512);
    
    void* ptr1 = memory_resource.allocate(100, 1);
    ASSERT_NE(ptr1, nullptr);
    memory_resource.deallocate(ptr1, 100, 1);
    
    void* ptr2 = memory_resource.allocate(100, 1);
    ASSERT_NE(ptr2, nullptr);
    memory_resource.deallocate(ptr2, 100, 1);
}

TEST(FixedBlockMemoryResourceTest, OutOfMemory) {
    FixedBlockMemoryResource memory_resource(100);
    
    void* ptr1 = memory_resource.allocate(80, 1);
    ASSERT_NE(ptr1, nullptr);
    
    // Должно бросить исключение при нехватке памяти
    // Сохраняем результат allocate чтобы избежать warning
    ASSERT_THROW({
        void* ptr = memory_resource.allocate(50, 1);
        (void)ptr; // явно используем переменную
    }, std::bad_alloc);
    
    memory_resource.deallocate(ptr1, 80, 1);
}

TEST(FixedBlockMemoryResourceTest, MultipleAllocationsDeallocations) {
    FixedBlockMemoryResource memory_resource(1024);
    
    std::vector<void*> pointers;
    for (int i = 0; i < 10; ++i) {
        void* ptr = memory_resource.allocate(50, 1);
        pointers.push_back(ptr);
    }
    
    // Освобождаем в случайном порядке
    memory_resource.deallocate(pointers[2], 50, 1);
    memory_resource.deallocate(pointers[7], 50, 1);
    memory_resource.deallocate(pointers[0], 50, 1);
    
    // Должны быть able to allocate again
    void* new_ptr = memory_resource.allocate(50, 1);
    ASSERT_NE(new_ptr, nullptr);
    
    memory_resource.deallocate(new_ptr, 50, 1);
    for (int i = 1; i < 10; ++i) {
        if (i != 0 && i != 2 && i != 7) {
            memory_resource.deallocate(pointers[i], 50, 1);
        }
    }
}

// Тесты для Queue с простыми типами
TEST(QueueTest, DefaultConstructor) {
    Queue<int> queue;
    ASSERT_TRUE(queue.empty());
}

TEST(QueueTest, PushAndFront) {
    Queue<int> queue;
    queue.push(42);
    
    ASSERT_FALSE(queue.empty());
    ASSERT_EQ(queue.front(), 42);
}

TEST(QueueTest, PushPop) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    
    ASSERT_EQ(queue.front(), 1);
    queue.pop();
    
    ASSERT_EQ(queue.front(), 2);
    queue.pop();
    
    ASSERT_EQ(queue.front(), 3);
    queue.pop();
    
    ASSERT_TRUE(queue.empty());
}

TEST(QueueTest, Emplace) {
    Queue<std::pair<int, int>> queue;
    queue.emplace(1, 2);
    queue.emplace(3, 4);
    
    ASSERT_EQ(queue.front().first, 1);
    ASSERT_EQ(queue.front().second, 2);
    queue.pop();
    
    ASSERT_EQ(queue.front().first, 3);
    ASSERT_EQ(queue.front().second, 4);
}

TEST(QueueTest, Iterator) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    
    int sum = 0;
    int count = 0;
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        sum += *it;
        count++;
    }
    
    ASSERT_EQ(sum, 6);
    ASSERT_EQ(count, 3);
}

TEST(QueueTest, RangeBasedFor) {
    Queue<int> queue;
    queue.push(10);
    queue.push(20);
    queue.push(30);
    
    int sum = 0;
    for (const auto& item : queue) {
        sum += item;
    }
    
    ASSERT_EQ(sum, 60);
}

TEST(QueueTest, MoveSemantics) {
    Queue<std::unique_ptr<int>> queue;
    queue.push(std::make_unique<int>(42));
    queue.push(std::make_unique<int>(84));
    
    ASSERT_EQ(*queue.front(), 42);
    queue.pop();
    ASSERT_EQ(*queue.front(), 84);
}

// Тесты со сложными типами
struct TestStruct {
    std::string name;
    int value;
    double data;
    
    TestStruct(const std::string& n, int v, double d) : name(n), value(v), data(d) {}
    
    bool operator==(const TestStruct& other) const {
        return name == other.name && value == other.value && data == other.data;
    }
};

TEST(QueueTest, ComplexType) {
    Queue<TestStruct> queue;
    queue.emplace("first", 1, 1.1);
    queue.emplace("second", 2, 2.2);
    queue.emplace("third", 3, 3.3);
    
    ASSERT_EQ(queue.front(), TestStruct("first", 1, 1.1));
    queue.pop();
    ASSERT_EQ(queue.front(), TestStruct("second", 2, 2.2));
}

// Интеграционные тесты: Queue с FixedBlockMemoryResource
TEST(IntegrationTest, QueueWithCustomAllocator) {
    FixedBlockMemoryResource memory_resource(2048);
    std::pmr::polymorphic_allocator<int> allocator(&memory_resource);
    
    Queue<int, std::pmr::polymorphic_allocator<int>> queue(allocator);
    
    for (int i = 0; i < 100; ++i) {
        queue.push(i);
    }
    
    int expected = 0;
    while (!queue.empty()) {
        ASSERT_EQ(queue.front(), expected++);
        queue.pop();
    }
}

TEST(IntegrationTest, ComplexTypeWithCustomAllocator) {
    FixedBlockMemoryResource memory_resource(4096);
    std::pmr::polymorphic_allocator<TestStruct> allocator(&memory_resource);
    
    Queue<TestStruct, std::pmr::polymorphic_allocator<TestStruct>> queue(allocator);
    
    for (int i = 0; i < 50; ++i) {
        queue.emplace("Item" + std::to_string(i), i, i * 1.5);
    }
    
    int count = 0;
    for (const auto& item : queue) {
        ASSERT_EQ(item.name, "Item" + std::to_string(count));
        ASSERT_EQ(item.value, count);
        ASSERT_EQ(item.data, count * 1.5);
        count++;
    }
    
    ASSERT_EQ(count, 50);
}

TEST(IntegrationTest, MemoryReuseInQueue) {
    FixedBlockMemoryResource memory_resource(1024);
    std::pmr::polymorphic_allocator<int> allocator(&memory_resource);
    
    Queue<int, std::pmr::polymorphic_allocator<int>> queue(allocator);
    
    // Заполняем и очищаем очередь несколько раз
    for (int cycle = 0; cycle < 5; ++cycle) {
        for (int i = 0; i < 10; ++i) {
            queue.push(i);
        }
        
        for (int i = 0; i < 10; ++i) {
            ASSERT_EQ(queue.front(), i);
            queue.pop();
        }
        
        ASSERT_TRUE(queue.empty());
    }
}

// Тесты на граничные случаи
TEST(EdgeCaseTest, EmptyQueueOperations) {
    Queue<int> queue;
    
    ASSERT_TRUE(queue.empty());
    // front() на пустой очереди - неопределенное поведение, но мы не тестируем это
    
    // pop() на пустой очереди должна работать без падения
    // (в нашей реализации это безопасно)
    queue.pop();
    ASSERT_TRUE(queue.empty());
}

TEST(EdgeCaseTest, SingleElementQueue) {
    Queue<int> queue;
    queue.push(42);
    
    ASSERT_FALSE(queue.empty());
    ASSERT_EQ(queue.front(), 42);
    
    queue.pop();
    ASSERT_TRUE(queue.empty());
}

TEST(EdgeCaseTest, IteratorOnEmptyQueue) {
    Queue<int> queue;
    
    auto begin = queue.begin();
    auto end = queue.end();
    
    ASSERT_EQ(begin, end);
}

TEST(EdgeCaseTest, LargeNumberOfElements) {
    FixedBlockMemoryResource memory_resource(65536); // 64KB
    std::pmr::polymorphic_allocator<int> allocator(&memory_resource);
    
    Queue<int, std::pmr::polymorphic_allocator<int>> queue(allocator);
    
    const int N = 1000;
    for (int i = 0; i < N; ++i) {
        queue.push(i);
    }
    
    int count = 0;
    for (const auto& item : queue) {
        ASSERT_EQ(item, count++);
    }
    
    ASSERT_EQ(count, N);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}