#include <iostream>
#include <thread>
#include <chrono>
#include <vector>


template <typename Unit = std::chrono::microseconds, typename Clock = std::chrono::high_resolution_clock>
class Timer {
    typename Clock::time_point mTick{Clock::now()};

public:

    void tick() 
    {
        mTick = Clock::now();
    }

    std::chrono::milliseconds::rep tock() 
    {
        auto time = std::chrono::duration_cast<Unit>(Clock::now() - mTick).count();
        return time;
    }

    void print() 
    {
        auto time = tock();
        std::cout << "Time difference = " << time << std::endl; 
    }
};

// Как зависит скорость работы от величины step?

const int n = 10;
const int iterations = 10'000'000;
const int step = 1;

std::vector<int> elems(n * step, 0);

int main()
{
    Timer<std::chrono::microseconds> t;

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < iterations; ++j) 
        {
            elems[step * i] += 1;
        }
    }

    t.print();



    t.tick();

    std::vector<std::thread> threads(n);

    for (int i = 0; i < n; ++i)
    {
        threads[i] = std::thread([i]()
        {
            for (int j = 0; j < iterations; ++j) 
            {
                elems[step * i] += 1;
            }
        });
    }


    for (int i = 0; i < n; ++i)
        threads[i].join();

    t.print();
}