#ifndef _SORT_H
#define _SORT_H

#include <algorithm>
#include <functional>
#include <ctime>
#include <iostream>

using namespace std;

void bubble(int arr[], size_t len);

void select(int* arr, size_t len);

void insert(int* arr, size_t len);

void shell(int* arr, size_t len);

/* 快排，选择第一个节点为基准节点 */
void quick(int* arr, size_t len);

void quickHelp(int* arr, int left, int right);

/* 快排，选择第一个中间节点为基准节点 */
void quick2(int* arr, size_t len);

void quickHelp2(int* arr, size_t left, size_t right);

/* 快排，第一个、中间、最后一个节点联合选为基准节点 */
void quick3(int* arr, size_t len);

void quickHelp3(int* arr, size_t left, size_t right);

int median3(int* arr, size_t left, size_t right);

void merge(int* arr, size_t len);

void mergeHelp(int* arr, size_t left, size_t right, int* temp);

void radix(int* arr, size_t len);

void heap(int* arr, size_t len);

void heapHelp(int* arr, size_t n, size_t len);

typedef void (*Fun)(int arr[], size_t len);

void sort(int arr[], size_t len, Fun f);

#endif