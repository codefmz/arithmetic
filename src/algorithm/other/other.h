#pragma once

#include "iostream"
#include "map"
#include "set"
#include "vector"
#include "DataStruct/priorityQueue.h"

using namespace std;
namespace OtherQue
{
	/**
	* @brief  :打印中间是空的菱形
	* @author :fmw
	* @date   :
	**/
	void printDimand(int n);


	int getLongestDunum();



	void memmoveByMe(void* p1, const void* p2, size_t len);

	void memCpy(void* p1, const void* p2, size_t len);


	void strCpy(char* dest, const char* src);
	void testStrCpy();


	/*
	* 选择问题， 找出 n 个数中 k 个最大值
	*/
	vector<int> getNMax(vector<int>& arr, size_t n);
	/*
	* 使用选择排序， 后续使用插入的方法,但是还是会排序
	*/
	vector<int> getNMax_2(vector<int>& arr, size_t n);
	int getNMax_3(vector<int>& arr, size_t n);


	/*
	* 求解 最大子序列和
	* 方法一: 3 重for循环, 2重for循环 O(n^3)
	*/
	int getMaxSubSum_1(const vector<int>& a);

	/*
	* 方法二: 一重遍历 O(n)
	*/
	int getMaxSubSum_2(const vector<int>& a);

	/*
	* 方法三: 分治 O(nlogn)
	*/
	int getMaxSubSum_3(const vector<int>& a);
	int getMaxSubSumHelp(const vector<int>& a, int left, int right);


	double myPow(double x, int n);
}

namespace OtherTest
{
    void test_getNMax();

    void test_getMaxSubSum();

    void test_getPow();
}
