#ifndef QUEUE_H
#define QUEUE_H

#include <memory>
#include <iterator>

template<typename T, typename Allocator = std::pmr::polymorphic_allocator<T>>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        
        template<typename... Args> // принимает любое кол-во аргументов любого типа
        Node(Args&&... args) : data(std::forward<Args>(args)...), next(nullptr) {}
        // Args&& - универсальная ссылка, std::forward<Args>(args)... - сохраняет категорию значения (lvalue/rvalue), ... - разворачивает пакет
    };

    using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>; // rebind_alloc - перепривязывает алокатор к типу node
    
    Node* head;
    Node* tail;
    NodeAllocator allocator;

public:
    // Итератор
    class iterator {
    private:
        Node* current;

    public:
        // тип-трейты, чтобы STL (стандартная библиотека шаблонов) знала, как работать с итератором
        using value_type = T; // тип эоементов
        using reference = T&; // тип ссылки на элемент
        using pointer = T*; // тип указателя на элемент
        using difference_type = std::ptrdiff_t; // тип для разности итераторов
        using iterator_category = std::forward_iterator_tag; // категория - однонаправленный
 
        iterator(Node* node = nullptr) : current(node) {} // по умолчанию nullptr

        reference operator*() const { return current->data; } // возвращает ссылку на данные
        pointer operator->() const { return &current->data; } // возвращает указатель на данные

        iterator& operator++() { //префиксный инкремент
            if (current) current = current->next;
            return *this;
        }

        iterator operator++(int) { //постфиксный инкремент (переходим у следующему node, но возвращает старое значение)
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return current != other.current; }
    };

    Queue() : head(nullptr), tail(nullptr) {}
    explicit Queue(const Allocator& alloc) : head(nullptr), tail(nullptr), allocator(alloc) {} // explicit запрещает неявное преобразование (100 элементов или байтов?)

    ~Queue() {
        while (!empty()) {
            pop();
        }
    }

    // запрещаем копирование и присваивание для простоты управления памяти
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    template<typename... Args>
    void emplace(Args&&... args) {
        // 1. выделяем память под одтн Node
        Node* new_node = std::allocator_traits<NodeAllocator>::allocate(allocator, 1);
        try {
            // создаём объект в выделенной памяти c data
            std::allocator_traits<NodeAllocator>::construct(allocator, new_node, std::forward<Args>(args)...); // construct - создаёт объект в сырой памяти, используя мой аллокатор 
        } catch (...) {
            // если не получается, deallocate выделенной памяти 
            std::allocator_traits<NodeAllocator>::deallocate(allocator, new_node, 1);
            throw;
        }

        if (!tail) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    void push(const T& value) {
        emplace(value);
    }

    void push(T&& value) { // для rvalue перемещения
        emplace(std::move(value));
    }

    void pop() {
        if (!head) return;
        
        Node* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        
        std::allocator_traits<NodeAllocator>::destroy(allocator, temp); // вызывает деструктор 
        std::allocator_traits<NodeAllocator>::deallocate(allocator, temp, 1); // освобождает память
    } 

    T& front() { return head->data; } // для константных объектов
    const T& front() const { return head->data; } // для неконстантный объектов

    bool empty() const { return head == nullptr; }

    // итераторы
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
};

#endif