#pragma once
/*
* 力扣刷题
*/
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <deque>
#include <queue>
#include <list>
#include <functional>
#include <algorithm>
#include "iostream"
#include <tuple>
#include <DataStruct/disjSet.h>
using namespace std;

namespace HASHTABLE
{
	//力扣第 3 题
	int lengthOfLongestSubstring(string s);

	//力扣第 12 题
	string intToRoman(int num);

	//力扣第 13 题
	int romanToInt(string s);

	//力扣第 17 题
	vector<string> letterCombinations(string digits);

	//力扣第 30 题
	vector<int> findSubstring(string s, vector<string>& words);
	void testFindSubstring();
}

namespace HEAP
{
	//力扣第 703 
	class KthLargest {
	public:
		KthLargest(int k, vector<int>& nums) {
			kth = k;
			currentSize = nums.size() > k ? k : nums.size();
			array.resize(k + 1);
			for (int i = 0; i < k && i < nums.size(); ++i)
			{
				array[i + 1] = nums[i];
			}
			buildHeap();
			for (size_t i = k; i < nums.size(); ++i)
			{
				add(nums[i]);
			}
		}

		int add(int val)
		{
			if (currentSize < kth)
			{
				array[++currentSize] = val;
				int hole = currentSize;
				for (; hole > 1 && val < array[hole / 2]; hole /= 2)
				{
					array[hole] = move(array[hole / 2]);
				}
				array[hole] = val;
				return array[1];
			}
			if (array[1] < val)
			{
				array[1] = val;
				percolateDown(1);
			}
			return array[1];
		}
	private:
		vector<int> array;
		int currentSize;
		int kth;

		void buildHeap()
		{
			for (int hole = currentSize / 2; hole > 0; --hole)
			{
				percolateDown(hole);
			}
		}
		void percolateDown(int hole)
		{
			auto temp = move(array[hole]);
			while (2 * hole <= currentSize)
			{
				size_t child = 2 * hole;
				if (child + 1 <= currentSize && array[child] > array[child + 1])
				{
					++child;
				}
				if (temp > array[child])
				{
					array[hole] = array[child];
					hole = child;
				}
				else
				{
					break;
				}
			}
			array[hole] = move(temp);
		}
	};


}


namespace SORT
{
	//力扣第 15 题
	vector<vector<int>> threeSum(vector<int>& nums);
	int binarySearchNum(vector<int>& nums, int left, int right, int dNum);
	vector<vector<int>> threeSum2(vector<int>& nums);

	//力扣第 16 题
	int threeSumClosest(vector<int>& nums, int target);

	//力扣第 18 题
	vector<vector<int>> fourSum(vector<int>& nums, int target);
	void testFourSum();


	//力扣第 26 题
	int removeDuplicates(vector<int>& nums);
}


//#include <stack>
namespace LIST
{
	struct ListNode
	{
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}
	};

	//力扣第 2 题
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
	void testAddTwoNumbers();

	//力扣第 19 题
	ListNode* removeNthFromEnd(ListNode* head, int n);

	//力扣第 21 题
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2);

	//力扣第 24 题
	ListNode* swapPairs(ListNode* head);

	//力扣第 25 题
	ListNode* reverseKGroup(ListNode* head, int k);
	ListNode* reverse(ListNode* head, ListNode* end);
	void testReverseKGroup();
}


namespace ARRAY
{
	//力扣第 4 题
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);
	int getKth(vector<int>& nums1, int b1, int e1, vector<int>& nums2, int b2, int e2, int k);
}

namespace STRING
{
	//力扣第 5 题
	string longestPalindrome(string s);

	//力扣第 6 题
	string convert(string s, int numRows);

	//力扣第 8 题
	int myAtoi(string s);
	void testMyAtoi();

	//力扣第 9 题
	bool isPalindrome(int x);
}

namespace STACK
{
	int reverse(int x);

	bool isValid(string s);
	void testIsValid();

	//力扣第 14 题
	string longestCommonPrefix(vector<string>& strs);
}

namespace GRAPH
{
	// 力扣第 207 题  拓扑排序
	bool canFinish(int numCourses, vector<vector<int>>& prerequisites);
	vector<vector<int>> buildGraph(int numCourses, const vector<vector<int>>& prerequisites);
	bool hasCycle(const vector<vector<int>>& graph, vector<int>& visit, int num);

	//力扣第 210 题  拓扑排序
	vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites);
}

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};



class Node {

public:
	int val;
	vector<Node*> neighbors;
	Node() {
		val = 0;
		neighbors = vector<Node*>();
	}
	Node(int _val) {
		val = _val;
		neighbors = vector<Node*>();
	}
	Node(int _val, vector<Node*> _neighbors) {
		val = _val;
		neighbors = _neighbors;
	}
};


namespace ALGORITHM
{
	// 广度优先遍历
	vector<vector<int>> levelOrder(TreeNode* root);
	//力扣第 133 题
	Node* cloneGraph(Node* node);
	void testcloneGraph();

	//力扣第 787 题 dijstra 算法
	struct State
	{
		int id;
		int distFromStart;
		int costnodes;
		State(int id, int distFromStart, int costnodes)
		{
			this->id = id;
			this->distFromStart = distFromStart;
			this->costnodes = costnodes;
		}
	};
	struct cmp
	{
		bool operator()(State a, State b)
		{
			return a.distFromStart > b.distFromStart;
		}
	};

	int dijkstra(int start, int end, int k, vector<vector<pair<int, int>>> graph);

	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k);

	//力扣第 743 题 dijstra 算法
	int networkDelayTime(vector<vector<int>>& times, int n, int k);
	struct Vertex
	{
		int id;
		bool isKnown;
		int costTime;
	};

	//力扣第 1334 题 dijstra 算法
	int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold);

	//力扣第 882 题 dijstra 算法
	int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n);


	//力扣第 1584 题 最短路径算法
	// prim 算法
	int minCostConnectPoints(vector<vector<int>>& points);
	//kurskal 算法
	int minCostConnectPoints2(vector<vector<int>>& points);
	struct Edge
	{
		int len;
		int start;
		int end;
		Edge(int _len, int _start, int _end) :len(_len), start(_start), end(_end) {};
	};

	//力扣第 94 题 深度优先算法
	vector<int> inorderTraversal(TreeNode* root);
	void dfs(TreeNode* node, vector<int>& ans);
	void testInorderTraversal();

	//力扣第 98 题 深度优先算法
	bool isValidBST(TreeNode* root);
	void testisValidBST();

	//力扣第98 题 深度优先算法
	void recoverTree(TreeNode* root);
	void testRecoverTree();


	//力扣第 11 题 贪心算法
	int maxArea(vector<int>& height);

	//力扣第 55 题 贪心算法
	bool canJump(vector<int>& nums);
	void testCanJump();

	//力扣第 122 题 贪心算法
	int maxProfit2(vector<int>& prices);
	void testMaxProfit();

	//力扣第 44 题 
	bool isMatch(string s, string p);
	void testIsMathc();

	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}

	};

	//力扣第 23 题 分治算法
	ListNode* mergeKLists(vector<ListNode*>& lists);
	ListNode* divideMerge(vector<ListNode*>& lists, int left, int right);
	void testMergeKLists();

	//力扣第 121 题 动态规划
	int maxProfit(vector<int>& prices);
	//力扣第 62 题 
	int uniquePaths(int m, int n);
	//力扣第 63 题
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid);
	//力扣第 64 题
	int minPathSum(vector<vector<int>>& grid);

	//力扣第 22 题
	vector<string> generateParenthesis(int n);
	void generate(vector<string>& res, string str, int leftCnt, int rightCnt, int n);
	void testGenerateParenthesis();


	class LRUCache {
	public:
		LRUCache(int capacity)
		{
			cap = capacity;
		}

		int get(int key)
		{
			auto iter = keyIterMap.find(key);
			if (iter != keyIterMap.end())
			{
				auto listIter = iter->second;
				int res = listIter->second;
				keyValList.splice(keyValList.begin(), keyValList, listIter);
				return res;
			}
			return -1;
		}

		void put(int key, int value)
		{
			auto iter = keyIterMap.find(key);
			if (iter != keyIterMap.end())
			{
				iter->second->second = value;
				keyValList.splice(keyValList.begin(), keyValList, iter->second);
			}
			else
			{
				if (keyValList.size() == cap)
				{
					auto endListIter = keyValList.end();
					int key = endListIter->first;
					keyValList.erase(endListIter);
					auto keyMapIter = keyIterMap.find(key);
					keyIterMap.erase(keyMapIter);
				}
				keyValList.emplace_front(key, value);
				keyIterMap.insert({ key, keyValList.begin() });
			}
		}
	private:
		list<pair<int, int>> keyValList;
		unordered_map<int, std::list<pair<int, int>>::iterator> keyIterMap;
		int cap;
	};

	struct PairComp
	{
		bool operator()(const pair<int, int>& pair1, const pair<int, int>& pair2)
		{
			return pair1.second < pair2.second;
		}
	};




	//力扣第 460 最近最不经常使用, 设置频率
	//1. 常数条
	struct LFUNode
	{
		int key = 0, value = 0, freq = 0;
		LFUNode(int _key, int _value, int _freq) :key(_key), value(_value), freq(_freq) {};
	};
	class LFUCache
	{
	private:
		unordered_map<int, list<LFUNode*>> freqNodeMap;
		unordered_map<int, list<LFUNode*>::iterator> keyIterMap;
		int cap;
		int smallestFreq;
	public:
		LFUCache(int capacity)
		{
			cap = capacity;
			smallestFreq = 1;
		}
		int get(int key)
		{
			auto iter = keyIterMap.find(key);
			if (iter != keyIterMap.end())
			{
				auto listIter = iter->second;
				LFUNode* node = *listIter;
				int res = node->value;
				++node->freq;
				freqNodeMap[node->freq].splice(freqNodeMap[node->freq].begin(), freqNodeMap[node->freq - 1], listIter);
				if (freqNodeMap[node->freq - 1].size() == 0 && smallestFreq == node->freq - 1)
				{
					++smallestFreq;
				}
				return res;
			}
			return -1;
		}
		void put(int key, int value)
		{
			auto iter = keyIterMap.find(key);
			if (iter != keyIterMap.end())
			{
				auto listIter = iter->second;
				LFUNode* node = *listIter;
				node->value = value;
				++node->freq;
				freqNodeMap[node->freq].splice(freqNodeMap[node->freq].begin(), freqNodeMap[node->freq - 1], listIter);
				if (freqNodeMap[node->freq - 1].size() == 0 && smallestFreq == node->freq - 1)
				{
					++smallestFreq;
				}
			}
			else
			{	//缓冲的数据个数等于容量
				if (keyIterMap.size() == cap)
				{
					LFUNode* node = *(--freqNodeMap[smallestFreq].end()); //最小次数的list 的最后一个node
					int key = node->key;
					freqNodeMap[smallestFreq].pop_back();
					auto iter = keyIterMap.find(key);
					keyIterMap.erase(iter);
				}
				smallestFreq = 1;
				freqNodeMap[1].emplace_front(new LFUNode(key, value, 1));
				keyIterMap[key] = freqNodeMap[1].begin();
			}
		}
	};
	void testLFUCache();
	//排序
	//力扣第 31 题
	void nextPermutation(vector<int>& nums);

	//力扣第 300 题， 动态规划
	int lengthOfLIS(vector<int>& nums);

	bool isValidSudoku(vector<vector<char>>& board);


	bool checkSubarraySum(vector<int>& nums, int k);

}


void recordError();


bool equalDisj(const pair<int, int>& p1, const pair<int, int>& p2);


int hashDisj(const pair<int, int>& p1);



int getNodeNum();

//
int getMettingRoom();//会议室问题

int getMettingRoom2(); //会议室问题变种，一个会议占据两个或两个以上的会议室, 任务混部

int getPerfectStepNum();

int logSystem(); //日志采集系统

void cityBuild(); // 城市修建

namespace MaxArea
{
	extern int row;
	extern int col;
	extern vector<pair<int, int>> direct;
	void caculateMaxArea();
	void  dfsArea(int i, int j, vector<vector<char>>& charVct, int& cnt, int& isSingle);
}

//最长共公子串
void maxSubStr();
//基站维修工程师
void baseMaintain();
void dfsBase(const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& path, int& ans);

//k 个相同子集
/* 判断是否可以将 nums 分成 k 个子集，每个子集的和相等 */
bool canPartitionKSubsets();

//通信误吗
int getMaxFreqSub();
//获取中间数
int getMiddleIndex();

int getNoName();


//迭代 + 回朔
//力扣第46题
vector<vector<int>> permute(vector<int>& nums);
void permute(vector<int>& nums, vector<vector<int>>& vcts, vector<bool>& isVisited, vector<int>& res);

//生成括号
void generateParentheses2(int n);
void generateParentheses2Help(vector<string>& ret, string& res, int n, int l, int r);

void reverseStr();


int calculate(string s);
