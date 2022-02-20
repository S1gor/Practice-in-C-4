#include <iostream>
#include <math.h>
#include <limits.h>

const int MAX = 100;

int askUserFillMatrix()
{
	int choise;
	do {
		printf("�������:\n1 - ��������� �� txt\n2 - ��������� �� bin\n3 - �������� �����\n4 - �������� ������������\n�����:");
		scanf_s("%d", &choise);
	} while (choise > 4 || choise < 1);
	return choise;
}

int scanMatrixSize(const char name[], int sizeMax)
{
	int size;
	do {
		printf("������� ���������� %s [0;%d]\n", name, sizeMax);
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
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j] = (rand() % (100 + 100 + 1) - 100);
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

void minSumSupDiag(float matrix[MAX][MAX], int rows)
{
	float sum = 0, minsum = INT_MAX;

	for (int i = 0; i < rows; i++)
	{
		sum = 0;
		for (int j = i; j >= 0; --j)
			sum += fabs(matrix[i - j][j]);
		if (sum < minsum)
			minsum = sum;
		//printf("%3.1f\n", sum);
	}
	for (int j = 1; j < rows; j++)
	{
		sum = 0;
		for (int i = j; i < rows; ++i)
			sum += fabs(matrix[i][rows - 1 - (i - j)]);
		if (sum < minsum)
			minsum = sum;
		//printf("%3.1f\n", sum);
	}
	printf("%3.1f\n", minsum);
}

	




int main()
{
	/*�) ���������� ����� ��������� � ��� ��������, ������� �� �������� ������������� ���������(�������� � ���� �������);
	�) ���������� ������� ����� ���� ������� ��������� ����������, ������������ �������� ��������� �������(�������� � ���� ���������).*/
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
		rows = scanMatrixSize("�����", MAX);
		cols = scanMatrixSize("��������", MAX);
		fillMatrixRandomInt(matrix, rows, cols);
		break;
	case 4:
		srand(time(0));
		rows = scanMatrixSize("�����", MAX);
		cols = scanMatrixSize("��������", MAX);
		fillMatrixRandomFloat(matrix, rows, cols);
		break;
	}
	outputArrToScreen(matrix, rows, cols);
	
	printf("\n");
	// �)C���� ��������� � ������������� ��������.
	float* p = sumPositivElem(matrix, rows, cols);
	for (int i = 0; i < cols; i++)						
		if (p[i] != -107374176.0)						
			printf("%3.1f\n", p[i]);
	// �)������� ����� ���� ������� ��������� ����������, ������������ �������� ��������� �������.
	minSumSupDiag(matrix, rows);




	return 0;
}