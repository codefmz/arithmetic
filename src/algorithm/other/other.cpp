#include "other.h"
#include <exception>
#include "iostream"
#include <algorithm>
void OtherQue::printDimand(int n)
{
	if ((n <= 0) && (n % 2 != 1)) {
		cout << "输入值有误，请输入一个正的奇数！" << endl;
		return;
	}

	for (size_t i = 0; i < n; i++) {
		if (i <= n / 2) {
			for (int j = 0; j < n; j++) {
				if (j < n / 2 - i) {
					cout << " ";
				} else if (j > n / 2 + i) {
					cout << " ";
				} else {
					if ((j == n / 2 - i) || j == (n / 2 + i)) {
						cout << "*";
					} else {
						cout << " ";
					}

				}
			}
		}
		else
		{
			for (int j = 0; j < n; j++)
			{
				if (j < i - n / 2)
				{
					cout << " ";
				}
				else if (j >= 3 * n / 2 - i)
				{
					cout << " ";
				}
				else
				{
					if (j == (i - n / 2) || (j == 3 * n / 2 - i - 1))
					{
						cout << "*";
					}
					else
					{
						cout << " ";
					}

				}
			}

		}
		cout << endl;
	}
}



void OtherQue::memmoveByMe(void* p1, const void* p2, size_t len)
{
	char* dest = static_cast<char*>(p1);
	const char* src = static_cast<const char*>(p2);
	if (dest <= src)
	{
		while (len != 0)
		{
			*dest++ = *src++;
		}
	}
	else
	{
		dest += len;
		src += len;
		while (len != 0)
		{
			*dest-- = *src--;
		}
	}
}

void OtherQue::memCpy(void* p1, const void* p2, size_t len)
{
	char* dest = static_cast<char*>(p1);
	const char* src = static_cast<const char*>(p2);
	if (src + len <= dest || dest <= src - len)
	{
		while (len != 0)
		{
			*dest-- = *src--;
		}
	}
	else
	{
		throw std::runtime_error("dest and src have same zone!");
	}
}

void OtherQue::strCpy(char* dest, const char* src)
{
	if (!dest || !src)
	{
		throw std::runtime_error(" dest or src is nullptr");
		return;
	}
	const char* srcBegin = src, * destBegin = dest;
	while (*src++ != '\0')
	{
		if (*dest++ == '\0')
		{
			throw std::runtime_error("dest is shorter then src!");
		}
	}
	if (src < destBegin || dest < srcBegin)
	{
		while (*src != '\0')
		{
			*dest++ = *src++;
		}
		*dest = *src;
	}
	else
	{
		throw runtime_error("原地址与目标地址存在重合区间！");
	}
}

void OtherQue::testStrCpy()
{
	char* chs = new char[10]{ "abcdefghi" };
	char* dest = new char[8];
	strCpy(dest, chs);
	cout << "dest = " << dest << endl;
}

vector<int> OtherQue::getNMax(vector<int>& arr, size_t n)
{
	vector<int> vctInt;
	if (n > arr.size())
	{
		throw runtime_error("n > arr.szie()!");
		return vctInt;
	}
	vctInt.reserve(n);
	size_t len = arr.size();
	//方式一，冒泡排序
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = len; j != i + 1; --j)
		{
			if (arr[j - 1] > arr[j - 2])
			{
				std::swap(arr[j - 1], arr[j - 2]);
			}
		}
	}
	vctInt.assign(arr.begin(), arr.begin() + n);
	return vctInt;
}

vector<int> OtherQue::getNMax_2(vector<int>& arr, size_t n)
{
	vector<int> vctInt;
	vector<int>::size_type len = arr.size();
	if (n > len)
	{
		throw runtime_error("n > arr.szie()!");
		return vctInt;
	}
	vctInt.reserve(n);
	vctInt.assign(arr.begin(), arr.begin() + n);
	sort(vctInt.begin(), vctInt.end(), [](auto i1, auto i2) {
		return i1 > i2;
		});
	for (size_t j = n; j < len; ++j)
	{
		size_t i = n - 1;
		if (vctInt[i] < arr[j])
		{
			vctInt[i] = arr[j];
			while (i > 0 && vctInt[i] > vctInt[i - 1])
			{
				std::swap(vctInt[i], vctInt[i - 1]);
				--i;
			}
		}
	}
	return vctInt;
}

int OtherQue::getNMax_3(vector<int>& arr, size_t n)
{
	vector<int> tvct(n + 1);
	for (size_t i = 0; i < n; i++)
	{
		tvct[i + 1] = arr[i];
	}
	BinaryHeap<int> bh(tvct);

	for (size_t i = n; i < arr.size(); i++)
	{
		if (bh.findMin() < arr[i])
		{
			bh.deleteMin();
			bh.insert(arr[i]);
		}
	}
	return bh.findMin();
}

int OtherQue::getMaxSubSum_1(const vector<int>& a)
{
	int max = 0;
	int begin = 0, end = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		int sum_2 = 0;
		for (int j = i; j < a.size(); ++j)
		{
			//int sum = 0;
			//for (int k = i; k <= j; ++k) //这一层的for循环其实可以省掉，应为 可以直接由上一次的结果直接计算得到
			//{
			//	sum += a[k];
			//}
			sum_2 += a[j];
			if (max < sum_2)
			{
				max = sum_2;
				begin = i;
				end = j;
			}
		}
	}
	return max;
}

int OtherQue::getMaxSubSum_2(const vector<int>& a)
{
	int maxSum = 0, thisSum = 0;
	int begin = 0, end = 0;
	for (int i = 0; i < a.size(); i++)
	{
		thisSum += a[i];
		if (thisSum > maxSum)
		{
			maxSum = thisSum;
			end = i;
		}
		else if (thisSum < 0)
		{
			thisSum = 0;
			begin = i + 1;
		}
	}
	return maxSum;
}

int OtherQue::getMaxSubSum_3(const vector<int>& a)
{
	int ret = getMaxSubSumHelp(a, 0, a.size() - 1);
	return ret;
}

int OtherQue::getMaxSubSumHelp(const vector<int>& a, int left, int right)
{
	if (right <= left)
	{
		return a[left] > 0 ? a[left] : 0;
	}
	int centor = (left + right) / 2;
	int leftMax = getMaxSubSumHelp(a, left, centor - 1);
	int rightMax = getMaxSubSumHelp(a, centor + 1, right);
	int centorLeftMax = 0, centorLeftSum = 0;
	for (int i = centor; i >= left; --i)
	{
		centorLeftSum += a[i];
		if (centorLeftMax < centorLeftSum)
		{
			centorLeftMax = centorLeftSum;
		}
	}
	int centorRightMax = 0, centorRightSum = 0;
	for (int i = centor + 1; i <= right; ++i)
	{
		centorRightSum += a[i];
		if (centorRightMax < centorRightSum)
		{
			centorRightMax = centorRightSum;
		}
	}
	return max({ leftMax, rightMax, centorLeftMax + centorRightMax });
}


double OtherQue::myPow(double x, int n)
{
	if (n == 0)
	{
		return 1;
	}
	else if (n > 0)
	{
		if (n % 2 == 0)
		{
			return myPow(x * x, n / 2);
		}
		else
		{
			return myPow(x * x, n / 2) * x;
		}
	}
	else
	{
		if (n == -1)
		{
			return 1 / x;
		}
		else if (n % 2 == 0)
		{
			return myPow(x * x, n / 2);
		}
		else
		{
			return myPow(x * x, n / 2) * 1 / x;
		}
	}
}

int OtherQue::getLongestDunum()
{
	size_t len = 0;
	cin >> len;
	map<size_t, set<size_t>> blocks;
	for (size_t i = 0; i < len; i++)
	{
		size_t num = 0;
		cin >> num;
		blocks[num].insert(i);
	}
	size_t distance = 0;
	for (auto& i : blocks)
	{
		if (i.second.size() > 1)
		{
			distance = max(distance, *--i.second.end() - *i.second.begin());
		}
	}
	return distance ? distance : -1;
}

void OtherTest::test_getNMax()
{
	vector<int> arr{ 1,6,7,9,-1,-10,8, 7,8,11 ,12,10 };
	cout << OtherQue::getNMax_3(arr, 4) << endl;
	//auto retVct = OtherQue::getNMax(arr, 3);
	//for_each(retVct.begin(), retVct.end(), [](auto z) {
	//	cout << z << endl;
	//	});


	//auto retVct2 = OtherQue::getNMax_2(arr, 3);
	//for_each(retVct2.begin(), retVct2.end(), [](auto z) {
	//	cout << z << endl;
	//	});
}

void OtherTest::test_getMaxSubSum()
{
	vector<int> vct{ 2, -1, -2,11,-4,13,-5,7,-2 };
	OtherQue::getMaxSubSum_3(vct);
}

void OtherTest::test_getPow()
{
	cout << OtherQue::myPow(34.00515, -3) << endl;
}
