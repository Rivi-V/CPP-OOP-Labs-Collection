#pragma once

// Предварительные объявления
class Dragon;
class Elf;
class KnightErrant;

class Visitor {
public:
    virtual ~Visitor() = default;
    
    virtual bool visit(Dragon* dragon) = 0;
    virtual bool visit(Elf* elf) = 0;
    virtual bool visit(KnightErrant* knight) = 0;
};