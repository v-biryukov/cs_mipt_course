#include <iostream>
using namespace std;


// Конечный автомат (Finite State Machine - FSM)
// Простейшая реализация на основе перечисляемого типа

enum class DoorState 
{
    Open, Closed, Locked
};


class DoorStateMachine
{
private:
    DoorState state;

public:

    DoorStateMachine()
    {
        state = DoorState::Closed;
    }

    void open()
    {
        if (state == DoorState::Closed)
            state = DoorState::Open;
    }

    void close()
    {
        if (state == DoorState::Open)
            state = DoorState::Closed;
    }

    void lock()
    {
        if (state == DoorState::Closed)
            state = DoorState::Locked;
    }

    void unlock()
    {
        if (state == DoorState::Locked)
            state = DoorState::Closed;
    }

    void printState()
    {
        switch (state)
        {
            case DoorState::Open:
                cout << "It's open!" << endl;
                break;
            case DoorState::Closed:
                cout << "It's closed!" << endl;
                break;
            case DoorState::Locked:
                cout << "It's locked!" << endl;
        }
    }
};


int main()
{
    DoorStateMachine fsm;
    fsm.printState();
    fsm.open();
    fsm.open();
    fsm.printState();
    fsm.close();
    fsm.lock();
    fsm.printState();
}

/* Задание:
    Создайте аналогичный конечный автомат для персонажа компьютерной игры.
    Состояния:
        Idle, Running, Jumping, Sliding (скользит по полу), Hooked (зацепился за уступ), Dead
    Действия:
        jump, startRunning, stop (переход в Idle), startSliding, hook, attacked 

        Схему автомата можно посмотреть в файле hero_fsm.png
*/