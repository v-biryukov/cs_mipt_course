#include <iostream>

using namespace std;

// Так как класс DoorState ссылается на DoorStateMachine,
// а класс DoorStateMachine на DoorState, то скомпилировать предыдущий 
// файл не получилось

// Чтобы это избежать, используем предварительное объявление (forward declaration)
// Объявим то, что у нас есть такие классы
class DoorState;
class DoorStateMachine;

class DoorState
{
public:
    virtual void open(DoorStateMachine* sm) = 0;
    virtual void close(DoorStateMachine* sm) = 0;
    virtual void lock(DoorStateMachine* sm) = 0;
    virtual void unlock(DoorStateMachine* sm) = 0;
    virtual void print() = 0;
    virtual ~DoorState() {};
};

class Open : public DoorState
{
    void open(DoorStateMachine* sm) {}
    void close(DoorStateMachine* sm);
    void lock(DoorStateMachine* sm) {}
    void unlock(DoorStateMachine* sm) {}
    void print();
};

class Closed : public DoorState
{
    void open(DoorStateMachine* sm);
    void close(DoorStateMachine* sm) {}
    void lock(DoorStateMachine* sm);
    void unlock(DoorStateMachine* sm) {}
    void print();
};

class Locked : public DoorState
{
    void open(DoorStateMachine* sm) {}
    void close(DoorStateMachine* sm) {}
    void lock(DoorStateMachine* sm) {}
    void unlock(DoorStateMachine* sm);
    void print();
};


class DoorStateMachine
{
private:
    DoorState* state;

public:
    DoorStateMachine()
    {
        state = new Closed();
    }

    void setState(DoorState* newState)
    {
        delete state;
        state = newState;
    }

    void open() 
    {
        state->open(this);
    }
    void close()
    {
        state->close(this);
    }
    void lock()
    {
        state->lock(this);
    }
    void unlock()
    {
        state->unlock(this);
    }

    void printState()
    {
        state->print();
    }

    ~DoorStateMachine()
    {
        delete state;
    }
};


void Open::close(DoorStateMachine* sm)
{
    sm->setState(new Closed());
}

void Open::print()
{
    cout << "It's open!" << endl;
}

void Closed::open(DoorStateMachine* sm)
{
    sm->setState(new Open());
}

void Closed::lock(DoorStateMachine* sm)
{
    sm->setState(new Locked());
}

void Closed::print()
{
    cout << "It's closed!" << endl;
}

void Locked::unlock(DoorStateMachine* sm) 
{
    sm->setState(new Closed());
}
void Locked::print()
{
    cout << "It's locked!" << endl;
}


int main()
{
    DoorStateMachine sm;
    // В начале дверь закрыта (Closed)
    sm.printState();

    // Откроем её
    sm.open();
    sm.printState();

    // Попытаемся открыть ещё, состояние от этого не должно поменяться
    sm.open();
    sm.open();
    sm.printState();

    // Попытаемся запереть на ключ открытую дверь (ничего не получится)
    sm.lock();
    sm.printState();

    // Много разных операций, приводящие к тому, что дверь будет заперта на ключ
    sm.close();
    sm.lock();
    sm.unlock();
    sm.open();
    sm.close();
    sm.close();
    sm.lock();
    sm.printState();
}

/* 
    Задание:

        Создайте аналогичный конечный автомат для персонажа компьютерной игры.

        Состояния:
            Idle (просто стоит), Running, Falling(падает, например, после прыжка), 
            Hooked (зацепился за уступ), Dead

        Действия:
            startRunning: Если игрок в Idle
                            то перейти в Running
                            Например, если игрок нажал на клавиши Влево/Вправо
    
            stoprunning: Если игрок в Running
                            то перейти в Idle
                            Например, если игрок отпустил клавиши Влево/Вправо
    
            startFalling: Если игрок в Idle или Running или Hooked
                            то перейти в Falling
                            Например, если игрок прыгнул или сошел с обрыва
    
            hitGround:    Если игрок в Falling,
                            то перейти в Idle
    
            hook:          Если игрок в Falling,
                            то перейти в Hooked
    
            attacked:      Если игрок не в Dead,
                            то перейти в Dead
    
            Схему автомата можно посмотреть в файле hero_fsm.png
*/