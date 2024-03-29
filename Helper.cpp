﻿/*В системе двусторонних дорог найти путь из города A в город B с минимальной величиной P+S, 
где S – сумма длин дорог, а P – сумма пошлин за проезд по ним.*/

#include "Header.h"
#include <iostream>
#include <locale.h>
#include <algorithm>
#include <fstream> //библиотека для работы со строками
using namespace std;

int** Emptiness(int** r, int n) //функция зануления массива 
{
	int i, j; //итераторы создаем
	for (i = 0; i < n; i++)
	{
		r[i][i] = 0; //заполняем диагональные элементы нулями
		for (j = i + 1; j < n; j++)
		{
			r[i][j] = 0;
			r[j][i] = r[i][j]; //симметрично* заполняем нулями
		}
	}
	return r;
}

int** Summa(int** pr, int** wr, int** ed, int n) //создаем матрицу суммы P+S (длина дороги + пошлина за проезд по ней)
{
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			ed[i][j] = pr[i][j] + wr[i][j];
		}
	}
	return ed;
}
int Isolation(int** ed, int n, int A, int B) //проверка A и B на изолированность 
{
	int* check = new int[n]; //создаем указатель на новый одномерный массив размера n
	int i, j, ctrl = 1; //создаем итераторы и переменную определитель изолированности (0 - изолированы, 1 - нет)
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			check[i] += ed[i][j]; //записываем в ячейку сумму элементов матрицы смежности по строке
		}
		if (check[i] == 0 && (i == B || i == A)) //если сумма элементов = 0 (из A или B нет дороги ни в один город) или их индексы совпадают (значит, это 1 город)
		{
			ctrl = 0;
		}
	}
	return ctrl;
}
int* DeikstraWay(int* sh, int** ed, int n) //поиск кратчайшего пути, алгоритм Дейкстры
{
	int i, j; //создаем итераторы
	int* v = new int[n]; //Заводим массив для хранения посещенных городов, 1 - посещен, 0 - нет
	for (i = 0; i < n; i++)
		v[i] = 0;
	int close, shortway; //Заводим локальные переменные отвечающие за индекс ближайшего города, кратчайшую дорогу
	do {
		close = Infinity;
		shortway = Infinity;
		for (i = 0; i < n; i++)
		{
			if ((v[i] == 0) && (sh[i] < shortway)) // Проверяем, посещена ли вершина, и является ли текущий путь до нее кратчайшим
			{
				shortway = sh[i]; //eсли да, то обновляем данные
				close = i;
			}
		}
		if (close != Infinity)
		{
			for (i = 0; i < n; i++) //проверяем, является ли новый короткий путь до города, кратчайшим. Сравниваем с предыдущим значением. 
			{
				if (ed[close][i] > 0)
				{
					if (shortway + ed[close][i] < sh[i])
					{
						sh[i] = shortway + ed[close][i];
					}
				}
			}
			v[close] = 1;
		}
	} while (close < Infinity); //пока индекс ближайшего города меньше бесконечности
	return sh;
}
int* SameWay(int** ed, int* sh, int n, int A, int B, int* v)   //восстановление пути
{
	v[0] = B; // начинаем поиск с конца
	int k = 1;
	int length = sh[B]; // Расстояние до города В
	for (int e = 1; e < n; e++) {
		v[e] = Infinity;
	}
	while (B != A) // Пока не вернулись в первый город
	{
		for (int i = 0; i < n; i++) // просматриваем все города на наличия связи
			if (ed[i][B] != 0)
			{
				if (length - ed[i][B] == sh[i])// определяем длину пути из предыдыдущего города, если длина совпала с полученной, то переход был отсюда
				{
					length -= ed[i][B];
					B = i;
					v[k] = i;
					k++;
				}
			}
	}
	return v; //массив, состоящий из индексов городов в обратном порядке посещения
}

