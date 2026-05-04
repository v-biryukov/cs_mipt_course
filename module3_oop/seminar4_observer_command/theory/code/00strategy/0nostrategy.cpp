#include <iostream>
#include <vector>

class SortingManager
{
private:
    std::vector<int>& mData;

public:
    SortingManager(std::vector<int>& data) : mData(data) {}

    void addElement(int x)
    {
        mData.push_back(x);
    }

    void bubbleSort()
    {
        for (size_t j = 0; j < mData.size(); ++j)
        {
            for (size_t i = 0; i < mData.size() - 1 - j; i += 1)
            {
                if (mData[i] > mData[i + 1])
                {
                    int temp = mData[i];
                    mData[i] = mData[i + 1];
                    mData[i + 1] = temp;
                }
            }
        }
    }

    void selectionSort()
    {
        for (size_t j = 0; j < mData.size(); ++j)
        {
            size_t min_index = j;
            for (size_t i = j + 1; i < mData.size(); ++i)
            {
                if (mData[i] < mData[min_index])
                    min_index = i;
            }

            int temp = mData[j];
            mData[j] = mData[min_index];
            mData[min_index] = temp;
        }
    }


    void quickSort()
    {
        quickSortHelper(0, mData.size() - 1);
    }

private:
    size_t partition(size_t begin, size_t end)
    {
        int pivot = mData[end];
        size_t i = begin;
        for (size_t j = begin; j < end; ++j)
        {
            if (mData[j] <= pivot)
            {
                int temp = mData[i];
                mData[i] = mData[j];
                mData[j] = temp;
                i++;
            }
        }
        int temp = mData[i];
        mData[i] = mData[end];
        mData[end] = temp;
        return i;
    }



    void quickSortHelper(size_t begin, size_t end)
    {
        std::cout << begin << " " << end << std::endl;
        if (begin < end)
        {
            size_t p = partition(begin, end);
            quickSortHelper(begin, p - 1);
            quickSortHelper(p + 1, end);
        }
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
    sm.quickSort();
    print(numbers);

    sm.addElement(40);
    sm.bubbleSort();
    print(numbers);

    sm.addElement(50);
    sm.selectionSort();
    print(numbers);
}