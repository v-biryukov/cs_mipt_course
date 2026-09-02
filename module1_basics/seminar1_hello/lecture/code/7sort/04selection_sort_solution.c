/*
    На каждом подмассиве [j, n)   (j меняется от 0 до n - 1)

        -   ищем индекс минимального элемента
        
        -   меняем  j-й  элемент и минимальный на этом подмассиве
*/



#include <stdio.h>

int main()
{
    int n;
    scanf("%i", &n);

    int a[1000];
    for (int i = 0; i < n; ++i)
    {
        scanf("%i", &a[i]);
    }


    for (int j = 0; j < n; ++j)
    {
        int min_index = j;
        for (int i = j + 1; i < n; ++i)
        {
            if (a[i] < a[min_index])
                min_index = i;
        }

        int temp = a[j];
        a[j] = a[min_index];
        a[min_index] = temp;
    }



    for (int i = 0; i < n; ++i)
        printf("%i ", a[i]);
    printf("\n");

}


/*
    Задача:

        Измените эту сортировку так, чтобы она сортировала на по возрастанию, а по убыванию.
*/
