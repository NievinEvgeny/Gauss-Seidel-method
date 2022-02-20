#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define n 4 //разрядность матрицы
double e = 0.00000000001;

int converge(double ResPrev[n], double Res[n])
{
    for (int i = 0; i < n; i++)
    {
        if ((fabs(Res[i] - ResPrev[i])) >= e)
        {
            return 0;
        }
    }
    return 1;
}

void diagonal(double A[][n + 1], double B[n])
{
    double k;
    for (int i = 0; i < n; i++)
    {
        k = A[i][i];
        for (int j = 0; j < n; j++)
        {
            A[i][j] /= k;
        }
        B[i] /= k;
    }
}

void Calculation(double A[][n + 1], double B[n], double ResPrev[n], double Res[n])
{
    double Temp;

    for (int i = 0; i < n; i++)
    {
        Temp = 0;
        for (int j = 0; j < n; j++)
        {
            Temp += ResPrev[j] * A[i][j];
        }
        Res[i] = B[i] - Temp;
    }
}

int main()
{
    int i, j;

    double A[n][n + 1] /*Матрица*/, B[n] /*Правый столбец*/, Res[n] /*Результирующий массив*/, ResPrev[n];
    FILE* in;
    FILE* out;
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");

    if (in == NULL || out == NULL)
    {
        printf("ошибка открытия файла\n");
        return -1;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            fscanf(in, "%lf", &A[i][j]);
        }
        fscanf(in, "%lf", &B[i]);
    }

    for (i = 0; i < n; i++) //инициализация результирующего массива нулями
    {
        ResPrev[i] = 0;
        Res[i] = 0;
    }

    diagonal(A, B);

    for (i = 0; i < n; i++) //зануление главной диагонали
    {
        A[i][i] = 0;
    }
    while (1)
    {
        Calculation(A, B, ResPrev, Res);

        if (converge(ResPrev, Res) == 1)
        {
            for (i = 0; i < n; i++)
            {
                fprintf(out, "x%d = %10.16lf\n", i + 1, Res[i]);
            }
            return 1;
        }
        else
        {
            for (i = 0; i < n; i++)
            {
                ResPrev[i] = Res[i];
            }
        }
    }
}