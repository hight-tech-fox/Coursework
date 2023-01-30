/*В системе двусторонних дорог найти путь из города A в город B с минимальной величиной P+S, 
где S – сумма длин дорог, а P – сумма пошлин за проезд по ним.*/

#pragma once
#ifndef HEADER_H
#define HEADER_H
int const Infinity = 100000;
int** Emptiness(int** r, int n);
int Isolation(int** ed, int n, int A, int B);
int* DeikstraWay(int* sh, int** ed, int n);
int* SameWay(int** ed, int* sh, int n, int A, int B, int* v);
int** Summa(int** rw, int** rd, int** ed, int n);
#endif HEADER_H
