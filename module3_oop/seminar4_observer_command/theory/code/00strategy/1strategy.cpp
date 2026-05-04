/*
    Использование стратегии позволяет добавлять новые алгоритмы сортировки без изменения
    самого класса SortingManager.
*/


#include <iostream>
#include <vector>

class SortingAlgorithm
{
public:

    virtual void execute(std::vector<int>& data) = 0;
    virtual ~SortingAlgorithm() {}
};


class BubbleSort : public SortingAlgorithm
{
public:
    void execute(std::vector<int>& data) override
    {
        for (size_t j = 0; j < data.size(); ++j)
        {
            for (size_t i = 0; i < data.size() - 1 - j; i += 1)
            {
                if (data[i] > data[i + 1])
                {
                    int temp = data[i];
                    data[i] = data[i + 1];
                    data[i + 1] = temp;
                }
            }
        }
    }
};


class SelectionSort : public SortingAlgorithm
{
public:
    void execute(std::vector<int>& data) override
    {
        for (size_t j = 0; j < data.size(); ++j)
        {
            size_t min_index = j;
            for (size_t i = j + 1; i < data.size(); ++i)
            {
                if (data[i] < data[min_index])
                    min_index = i;
            }

            int temp = data[j];
            data[j] = data[min_index];
            data[min_index] = temp;
        }
    }

};



class QuickSort : public SortingAlgorithm
{
public:
    void execute(std::vector<int>& data) override
    {
        quickSortHelper(data, 0, data.size() - 1);
    }

private:
    size_t partition(std::vector<int>& data, size_t begin, size_t end)
    {
        int pivot = data[end];
        size_t i = begin;
        for (size_t j = begin; j < end; ++j)
        {
            if (data[j] <= pivot)
            {
                int temp = data[i];
                data[i] = data[j];
                data[j] = temp;
                i++;
            }
        }
        int temp = data[i];
        data[i] = data[end];
        data[end] = temp;
        return i;
    }

    void quickSortHelper(std::vector<int>& data, size_t begin, size_t end)
    {
        if (begin < end)
        {
            size_t p = partition(data, begin, end);
            quickSortHelper(data, begin, p - 1);
            quickSortHelper(data, p + 1, end);
        }
    }
};



class SortingManager
{
private:
    std::vector<int>& mData;

    SortingAlgorithm* mpAlgorithm {};


public:
    SortingManager(std::vector<int>& data) : mData(data) 
    {
        mpAlgorithm = new BubbleSort;
    }

    void addElement(int x)
    {
        mData.push_back(x);
    }

    void setAlgorithm(SortingAlgorithm* p)
    {
        delete mpAlgorithm;
        mpAlgorithm = p;
    }

    void sort()
    {
        mpAlgorithm->execute(mData);
    }

    ~SortingManager()
    {
        delete mpAlgorithm;
    }
};


void print(const std::vector<int>& numbers)
{
    for (auto x : numbers)
        std::cout << x << " ";
    std::cout << std::endl;
}



int main()
{
    std::vector<int> numbers {70, 10, 80, 60, 30, 20, 90};
    print(numbers);

    SortingManager sm {numbers};
    sm.setAlgorithm(new BubbleSort);
    sm.sort();
    print(numbers);

    sm.addElement(40);
    sm.setAlgorithm(new SelectionSort);
    sm.sort();
    print(numbers);

    sm.addElement(50);
    sm.setAlgorithm(new QuickSort);
    sm.sort();
    print(numbers);
}