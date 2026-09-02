#include <stdio.h>

int main()
{
	FILE* file = fopen("special_numbers.txt", "r");
	int N;
	int array[20001];
	fscanf(file, "%d", &N);
	for (int i = 0; i < N; i++)
		fscanf(file, "%d", &array[i]);

	for (int i = 20001-100; i < 20001; i++)
		printf("%d\n", array[i]);

}