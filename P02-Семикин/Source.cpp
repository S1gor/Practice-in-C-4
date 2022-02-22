#include <iostream>
#include <math.h>
#include <limits.h>

const int MAX = 100;

int askUserFillMatrix()
{
	int choise;
	do {
		printf("Введите:\n1 - заполнить из txt\n2 - заполнить из bin\n3 - рандомно целые\n4 - рандомно вещественные\nВыбор:");
		scanf_s("%d", &choise);
	} while (choise > 4 || choise < 1);
	return choise;
}

int askUserAction()
{
	int choise;
	do {
		printf("Введите:\n1 - Определить сумму элементов в тех столбцах, которые не содержат отрицательных элементов.\n");
		printf("2 - Определить минимум среди сумм модулей элементов диагоналей, параллельных побочной диагонали матрицы(Матрица должна быть квадратной).\n");
		printf("3 - Упорядочить строки матрицы по убыванию количества разных элементов в каждой строке.\n");
		printf("4 - Найти номер первой из строк, не содержащей ни одного положительного элемента.\nВыбор:");
		scanf_s("%d", &choise);
		printf("\n\n");
	} while (choise > 4 || choise < 1);
	return choise;
}

int scanMatrixSize(const char name[], int sizeMax)
{
	int size;
	do {
		printf("Введите количество %s [0;%d]\n", name, sizeMax);
		scanf_s("%d", &size);
	} while (size<0 || size>sizeMax);
	return size;
}

void fillMatrixFromFile(float matrix[MAX][MAX], int& rows, int& cols, const char filename[])
{
	FILE* f;
	if (fopen_s(&f, filename, "r") != 0)
		exit(1);

	fscanf_s(f, "%d %d\n", &rows, &cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			fscanf_s(f, "%f", &matrix[i][j]);
	fclose(f);
}

void fillMatrixFromBinFile(float matrix[MAX][MAX], int& rows, int& cols, const char filename[])
{
	FILE* f;
	if (fopen_s(&f, filename, "rt") != 0)
		exit(1);

	fread(&rows, sizeof(int), 1, f);
	fread(&cols, sizeof(int), 1, f);

	for (int i = 0; i < rows; i++)
		fread(&matrix[i], sizeof(float), cols, f);
	fclose(f);
}

void fillMatrixRandomInt(float matrix[MAX][MAX], int rows, int cols)
{
	int a, b;
	printf("Введите диапозон рандомных чисел:\nот:"); scanf_s("%d", &a);
	printf("до:"); scanf_s("%d", &b);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j] = (rand() % (b - a + 1) + a);
}

void fillMatrixRandomFloat(float matrix[MAX][MAX], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j] = (rand() % 2001 - 1000.0) / 10;
}

void outputArrToScreen(float matrix[MAX][MAX], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			printf("%6.1f ", matrix[i][j]);
		printf("\n");
	}
}

float* sumPositivElem(float matrix[MAX][MAX], int rows, int cols)
{
	int n = 0;
	float mas[50];
	for (int i = 0; i < cols; i++)
	{
		int counter = 0;
		float sum = 0;
		for (int j = 0; j < rows; j++)
		{
			if (matrix[j][i] >= 0)
				sum += matrix[j][i];
			else
				counter++;
		}
		if (counter == 0)
		{
			mas[n] = sum;
			n++;
		}
	}
	return mas;
}

void minSumSupDiag(float matrix[MAX][MAX], int rows, int cols)
{
	if (rows == cols)
	{
		float sum = 0, minsum = INT_MAX;

		for (int i = 0; i < rows; i++)
		{
			sum = 0;
			for (int j = i; j >= 0; j--)
				sum += fabs(matrix[i - j][j]);
			if (sum < minsum)
				minsum = sum;
		}
		for (int j = 1; j < rows; j++)
		{
			sum = 0;
			for (int i = j; i < rows; i++)
				sum += fabs(matrix[i][rows - 1 - (i - j)]);
			if (sum < minsum)
				minsum = sum;
		}
		printf("%3.1f\n", minsum);
	}
	else
		printf("Матрица не квадратная!");
}

void sortRows(float matrix[MAX][MAX], int rows, int cols)
{
	float mas[MAX], min[MAX];
	int s = 0;
	for (int k = 0; k < rows; k++)
	{
		int counter = 0, counter2 = INT_MAX;

		for (int i = 0; i < cols; i++)
			mas[i] = matrix[k][i];
			
		for (int j = 0; j < cols - 1; j++)
			for (int i = 0; i < cols - 1 - j; i++)
				if (mas[i] < mas[i + 1])
				{
					float tmp = mas[i];
					mas[i] = mas[i + 1];
					mas[i + 1] = tmp;
				}
		
		for (int i = 0; i < cols; i++)
			printf("%5.1f  ", mas[i]);

		for (int i = 0; i < cols; i++)
			if (mas[i] == mas[i + 1])
				counter++;
		printf("\tКоличество повторов - %d\n", counter);
		/*if (counter2 < counter)
		{
			for (s; s < cols; s++)
			{
				min[s] = mas[s];
				printf("%3.1f ", min[s]);
			}
		}

		counter2 = counter;
		s += cols;*/
	}
}

int numberFirstRowsNoPosElem(float matrix[MAX][MAX], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		int counter = 0;
		for (int j = 0; j < cols; j++)
		{
			if (matrix[i][j] <= 0)
				counter++;
			else
				break;
		}
		if (counter == cols)
			return i;
	}
}

int main()
{
	/*а) Определить сумму элементов в тех столбцах, которые не содержат отрицательных элементов(оформить в виде функции);
	б) Определить минимум среди сумм модулей элементов диагоналей, параллельных побочной диагонали матрицы(оформить в виде процедуры).
	в) Упорядочить строки матрицы по убыванию количества разных элементов в каждой строке(оформить в виде процедуры);
	г) Найти номер первой из строк, не содержащей ни одного положительного элемента(оформить в виде функции).*/
	system("chcp 1251");

	float matrix[MAX][MAX];
	int rows, cols;
	char filename[] = "1.txt";
	char filenameBin[] = "2.bin";
	
	switch (askUserFillMatrix())
	{
	case 1:
		fillMatrixFromFile(matrix, rows, cols, filename);
		break;
	case 2:
		fillMatrixFromBinFile(matrix, rows, cols, filenameBin);
		break;
	case 3:
		srand(time(0));
		rows = scanMatrixSize("рядов", MAX);
		cols = scanMatrixSize("столбцов", MAX);
		fillMatrixRandomInt(matrix, rows, cols);
		break;
	case 4:
		srand(time(0));
		rows = scanMatrixSize("рядов", MAX);
		cols = scanMatrixSize("столбцов", MAX);
		fillMatrixRandomFloat(matrix, rows, cols);
		break;
	}
	outputArrToScreen(matrix, rows, cols);
	printf("\n");
	
	switch (askUserAction())
	{
	case 1:	// а)Cумма элементов в положительных столбцах.
	{
		printf("Cумма элементов в столбцах, которые не содержат отрицательных элементов:\n");
		float* p = sumPositivElem(matrix, rows, cols);
		for (int i = 0; i < cols; i++)
			if (p[i] != -107374176.0)
				printf("%3.1f\n", p[i]);
		break;
	}
	case 2: // б)Минимум среди сумм модулей элементов диагоналей, параллельных побочной диагонали матрицы.
	{
		printf("Минимум среди сумм модулей элементов диагоналей, параллельных побочной диагонали матрицы:\n");
		minSumSupDiag(matrix, rows, cols);
		break;
	}
	case 3: //в)Упорядочить строки матрицы по убыванию количества разных элементов в каждой строке.
	{
		printf("Упорядочить строки матрицы по убыванию количества разных элементов в каждой строке:\n");
		sortRows(matrix, rows, cols);
		
		break;
	}
	case 4:
	{
		printf("Номер первой из строк, не содержащей ни одного положительного элемента:\n");
		int number = numberFirstRowsNoPosElem(matrix, rows, cols) + 1;
		if (number > cols)
			printf("Нет такой строки!");
		else
			printf("№%d", number);
		break;
	}
	}
	printf("\n");

	return 0;
}