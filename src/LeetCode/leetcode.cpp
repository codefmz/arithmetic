#include <LeetCode/leetcode.h>
#include <algorithm>
int HASHTABLE::lengthOfLongestSubstring(string s)
{
	if (s.length() <= 1)
	{
		return s.length();
	}
	size_t index = 0;
	int len = 0;
	string subStr;
	size_t begin = 0, i = 0;
	for (; i < s.length(); ++i)
	{
		size_t fIndex = subStr.find(s[i]);
		if (fIndex != string::npos)
		{
			if (len < i - begin)
			{
				len = i - begin;
			}
			begin += fIndex + 1;
			subStr.erase(subStr.begin(), subStr.begin() + fIndex + 1);
		}
		subStr.push_back(s[i]);
	}
	if (begin != i - 1)
	{
		if (len < i - begin)
		{
			len = i - begin;
		}
	}
	return len;
}


string HASHTABLE::intToRoman(int num)
{
	if (num >= 1000)
		return "M" + intToRoman(num - 1000);
	else if (num >= 900)
		return "CM" + intToRoman(num - 900);
	else if (num >= 500)
		return "D" + intToRoman(num - 500);
	else if (num >= 400)
		return "CD" + intToRoman(num - 400);
	else if (num >= 100)
		return "C" + intToRoman(num - 100);
	else if (num >= 90)
		return "XC" + intToRoman(num - 90);
	else if (num >= 50)
		return "L" + intToRoman(num - 50);
	else if (num >= 40)
		return "XL" + intToRoman(num - 40);
	else if (num >= 10)
		return "X" + intToRoman(num - 10);
	else if (num >= 9)
		return "IX" + intToRoman(num - 9);
	else if (num >= 5)
		return "V" + intToRoman(num - 5);
	else if (num >= 4)
		return "IV" + intToRoman(num - 4);
	else if (num >= 1)
		return "I" + intToRoman(num - 1);
	else
		return "";
}

int HASHTABLE::romanToInt(string s)
{
	unordered_map<char, int> ci_map;
	ci_map['I'] = 1;
	ci_map['V'] = 5;
	ci_map['X'] = 10;
	ci_map['L'] = 50;
	ci_map['C'] = 100;
	ci_map['D'] = 500;
	ci_map['M'] = 1000;
	if (s.length() < 2)
	{
		return s.empty() ? 0 : ci_map[s[0]];
	}
	int value = 0, ret = 0;
	int i = s.length() - 1;
	for (; i >= 0; --i)
	{
		if (ci_map[s[i]] < value)
		{
			ret -= ci_map[s[i]];
		}
		else
		{
			ret += ci_map[s[i]];
			value = ci_map[s[i]];
		}
	}
	return ret;
}

vector<string> HASHTABLE::letterCombinations(string digits)
{
	vector<string> ret;
	unordered_map<char, string> is_umap;
	is_umap['2'] = "abc";
	is_umap['3'] = "def";
	is_umap['4'] = "ghi";
	is_umap['5'] = "jkl";
	is_umap['6'] = "mno";
	is_umap['7'] = "pqrs";
	is_umap['8'] = "tuv";
	is_umap['9'] = "wxyz";
	int index = 0;
	for (char c : digits)
	{
		auto temp = ret;
		int index2 = 0;
		for (char ic : is_umap[c])
		{
			if (index == 0)
			{
				ret.emplace_back(1, ic);
			}
			else if (index2 == 0)
			{
				for (auto& s : ret)
				{
					s += ic;
				}
				++index2;
			}
			else
			{
				for (auto& s : temp)
				{
					ret.push_back(s + ic);
				}
			}
		}
		++index;
	}
	return ret;
}

vector<int> HASHTABLE::findSubstring(string s, vector<string>& words)
{
	vector<int> ret;
	unordered_map<string, int> wordsMap;
	for (auto& word : words)
	{
		wordsMap[word] = -1;
	}
	int wordLen = words[0].length(), wordCnt = words.size();
	int index = 0, sLen = s.length();
	while (index < sLen)
	{
		int tIndex = index, cnt = 0;
		while (cnt < wordCnt)
		{
			//没有找到 字符串 str
			string str = s.substr(tIndex, wordLen);
			if (wordsMap.find(str) == wordsMap.end())
			{
				++index;
				break;
			}
			else if (wordsMap[str] < index || wordsMap[str] == tIndex)
			{
				wordsMap[str] = tIndex;
				tIndex += wordLen;
				++cnt;
			}
			else
			{
				index = tIndex;
				break;
			}
		}
		if (cnt == wordCnt)
		{
			ret.push_back(index);
			index += wordLen;
		}
		cnt = 0;
	}
	return ret;
}

void HASHTABLE::testFindSubstring()
{

	vector<string> words{ "foo","bar","the" };
	string s = "barfoofoobarthefoobarman";
	findSubstring(s, words);
}

vector<vector<int>> SORT::threeSum(vector<int>& nums)
{
	vector<vector<int>> ret;
	sort(nums.begin(), nums.end());
	auto posIndexIter = find_if(nums.begin(), nums.end(), [](auto it) {
		return it > 0;
		});
	auto maxIter1 = (posIndexIter > nums.end() - 2) ? nums.end() - 2 : posIndexIter;
	for (auto iter1 = nums.begin(); iter1 < maxIter1; ++iter1)
	{
		if (iter1 - nums.begin() > 0 && *iter1 == *(iter1 - 1))
		{
			continue;
		}
		for (auto iter2 = iter1 + 1; iter2 < nums.end() - 1; ++iter2)
		{
			if (iter2 - 1 != iter1 && *iter2 == *(iter2 - 1))
			{
				continue;
			}
			int res = binarySearchNum(nums, iter2 - nums.begin() + 1, nums.size() - 1, -*iter1 - *iter2);
			if (res != -1)
			{
				ret.emplace_back(vector<int>{*iter1, * iter2, nums[res]});
			}
		}
	}
	return ret;
}

int SORT::binarySearchNum(vector<int>& nums, int left, int right, int dNum)
{
	int ret;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (dNum < nums[mid])
		{
			right = mid - 1;
		}
		else if (dNum > nums[mid])
		{
			left = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

vector<vector<int>> SORT::threeSum2(vector<int>& nums)
{
	vector<vector<int>> ret;
	vector<int> res(3);
	sort(nums.begin(), nums.end());
	for (auto iter1 = nums.begin(); iter1 < nums.end() - 2; ++iter1)
	{
		if (*iter1 > 0)
		{
			break;
		}
		if (iter1 - nums.begin() > 0 && *iter1 == *(iter1 - 1))
		{
			continue;
		}
		auto iter2 = iter1 + 1;
		auto iter3 = nums.end() - 1;
		while (iter2 < iter3)
		{
			if (*iter1 + *iter2 + *iter3 > 0)
			{
				iter3--;
			}
			else if (*iter1 + *iter2 + *iter3 < 0)
			{
				iter2++;
			}
			else
			{
				res.clear();
				res.push_back(*iter1);
				res.push_back(*iter2);
				res.push_back(*iter3);
				ret.push_back(res);
				++iter2;
				--iter3;
				while (*iter2 == *(iter2 - 1) && iter2 < iter3)
				{
					++iter2;
				}
				while (*iter3 == *(iter3 + 1) && iter2 < iter3)
				{
					--iter3;
				}
			}
		}
	}
	return ret;
}

int SORT::threeSumClosest(vector<int>& nums, int target)
{
	int ans = 0;
	sort(nums.begin(), nums.end());
	int mins = INT_MAX;
	for (auto iter1 = nums.begin(); iter1 < nums.end() - 2; ++iter1)
	{
		auto iter2 = iter1 + 1;
		auto iter3 = nums.end() - 1;
		while (iter2 < iter3)
		{
			int sum = *iter1 + *iter2 + *iter3;
			if (sum < target)
			{
				++iter2;
			}
			else if (sum >= target)
			{
				--iter3;
			}
			if (abs(sum - target) < mins)
			{
				mins = abs(sum - target);
				ans = sum;
			}
		}
	}
	return ans;
}

vector<vector<int>> SORT::fourSum(vector<int>& nums, int target)
{
	vector<vector<int>> ret;
	sort(nums.begin(), nums.end());
	for (auto iter1 = nums.begin(); iter1 < nums.end() - 3; ++iter1)
	{
		if (iter1 - nums.begin() > 0 && *iter1 == *(iter1 - 1))
		{
			continue;
		}
		for (auto iter2 = iter1 + 1; iter2 < nums.end() - 2; ++iter2)
		{
			if (iter2 > iter1 + 1 && *iter2 == *(iter2 - 1))
			{
				continue;
			}
			auto iter3 = iter2 + 1, iter4 = nums.end() - 1;

			while (iter3 < iter4)
			{
				long sum = *iter1 + *iter2 + *iter3 + *iter4;
				if (sum < target)
				{
					++iter3;
				}
				else if (sum > target)
				{
					--iter4;
				}
				else
				{
					ret.push_back({ *iter1,*iter2,*iter3,*iter4 });
					++iter3;
					--iter4;
					while (iter3 < iter4 && *iter3 == *(iter3 - 1))
					{
						++iter3;
					}
					while (iter3 < iter4 && *iter4 == *(iter4 - 1))
					{
						--iter4;
					}
				}
			}
		}
	}
	return ret;
}

void SORT::testFourSum()
{
	vector<int> vct{ 1,1,1,1 };
	fourSum(vct, 0);
}

int SORT::removeDuplicates(vector<int>& nums)
{
	size_t index = 0, len = nums.size();
	for (size_t i = 1; i < len; ++i)
	{
		if (nums[index] != nums[i])
		{
			nums[++index] = nums[i];
		}
	}
	return index - 1;
}



LIST::ListNode* LIST::addTwoNumbers(ListNode* l1, ListNode* l2)
{
	ListNode* head = nullptr, * head2 = head;
	int jw = 0;
	int index = 0;
	while (l1 || l2)
	{
		int num1 = 0;
		if (l1)
		{
			num1 = l1->val;
			l1 = l1->next;
		}
		int num2 = 0;
		if (l2)
		{
			num2 = l2->val;
			l2 = l2->next;
		}
		int sum = num1 + num2;
		if (jw)
		{
			++sum;
			jw = 0;
		}
		if (sum > 9)
		{
			jw = 1;
			sum %= 10;
		}
		auto tNode = new ListNode(sum);
		if (head)
		{
			head->next = tNode;
			head = head->next;
		}
		else
		{
			head = tNode;
			head2 = head;
		}
		++index;
	}
	if (jw)
	{
		auto tNode = new ListNode(1);
		if (head)
		{
			head->next = tNode;
		}
		else
		{
			head = tNode;
			head2 = head;
		}
	}
	return head2;
}

void LIST::testAddTwoNumbers()
{
	ListNode* t1 = new ListNode(2);
	t1->next = new ListNode(4);
	t1->next->next = new ListNode(9);


	ListNode* t2 = new ListNode(5);
	t2->next = new ListNode(6);
	t2->next->next = new ListNode(4);
	auto t3 = t2->next->next;
	t3->next = new ListNode(9);
	//t3->next->next = new ListNode(9);
	//auto t4 = t3->next->next;
	//t4->next = new ListNode(9);
	//t4->next->next = new ListNode(9);
	//auto t5 = t4->next->next;
	//t5->next = new ListNode(9);
	//t5->next->next = new ListNode(9);
	//t5->next->next->next = new ListNode(1);

	addTwoNumbers(t1, t2);
}

LIST::ListNode* LIST::removeNthFromEnd(ListNode* head, int n)
{
	ListNode tempNode(0, head);
	ListNode* left = &tempNode, * right = left;
	for (size_t i = 0; i < n; ++i)
	{
		if (right != nullptr)
		{
			right = right->next;
		}
	}
	while (right->next != nullptr)
	{
		right = right->next;
		left = left->next;
	}
	left->next = left->next->next;
	return tempNode.next;
}

LIST::ListNode* LIST::mergeTwoLists(ListNode* list1, ListNode* list2)
{
	ListNode temp, * head = &temp;
	while (list1 && list2)
	{
		if (list1->val < list2->val)
		{
			head->next = list1;
			list1 = list1->next;
		}
		else
		{
			head->next = list2;
			list2 = list2->next;
		}
		head = head->next;
	}
	head->next = list1 ? list1 : list2;
	return temp.next;
}

LIST::ListNode* LIST::swapPairs(ListNode* head)
{
	if (!head || !head->next)
	{
		return head;
	}
	ListNode* node = head->next;
	head->next = swapPairs(node->next);
	node->next = head;
	return node;
}

LIST::ListNode* LIST::reverseKGroup(ListNode* head, int k)
{
	ListNode* begin = head, * end;
	for (size_t i = 0; i < k - 1; ++i)
	{
		if (!head)
		{
			break;
		}
		head = head->next;
	}
	if (head)
	{
		end = head;
	}
	else  //不满足 k 个
	{
		return begin;
	}
	ListNode* node = end->next;
	reverse(begin, end);
	begin->next = reverseKGroup(node, k);
	return end;
}

LIST::ListNode* LIST::reverse(ListNode* head, ListNode* end)
{
	ListNode temp;
	while (true)
	{
		ListNode* node = temp.next;
		temp.next = head;
		ListNode* after = head->next;
		head->next = node;
		if (head == end)
		{
			break;
		}
		head = after;
	}
	return temp.next;
}

void LIST::testReverseKGroup()
{
	ListNode* node5 = new ListNode(5, nullptr);
	ListNode* node4 = new ListNode(4, node5);
	ListNode* node3 = new ListNode(3, node4);
	ListNode* node2 = new ListNode(2, node3);
	ListNode* node1 = new ListNode(1, node2);

	reverseKGroup(node1, 2);
}

double ARRAY::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
	int l1 = nums1.size(), l2 = nums2.size();
	int n = (l1 + l2 + 1) / 2, m = (l1 + l2 + 2) / 2;
	return (getKth(nums1, 0, l1 - 1, nums2, 0, l2 - 1, n) + getKth(nums1, 0, l1 - 1, nums2, 0, l2 - 1, m)) / 2.0;
}

int ARRAY::getKth(vector<int>& nums1, int b1, int e1, vector<int>& nums2, int b2, int e2, int k)
{
	int len1 = e1 - b1 + 1;
	int len2 = e2 - b2 + 1;
	if (len1 > len2)
	{
		return getKth(nums2, b2, e2, nums1, b1, e1, k);
	}
	if (len1 == 0)
	{
		return nums2[b2 + k - 1];
	}
	if (k == 1)
	{
		return min(nums1[b1], nums2[b2]);
	}
	int i = b1 + min(len1, k / 2) - 1;
	int j = b2 + min(len2, k / 2) - 1;
	if (nums1[i] > nums2[j])
	{
		return getKth(nums1, b1, e1, nums2, j + 1, e2, k - (j - b2 + 1));
	}
	else
	{
		return getKth(nums1, i + 1, e1, nums2, b2, e2, k - (i - b1 + 1));
	}
}

string STRING::longestPalindrome(string s)
{
	int l = 0, r = 0, maxLen = 0, start = 0, end = 0;
	for (size_t i = 1; i < s.size(); i++)
	{
		l = i - 1;
		r = i + 1;
		while (l >= 0 && s[l] == s[i])
		{
			--l;
		}
		while (r < s.size() && s[r] == s[i])
		{
			++r;
		}
		while (l >= 0 && r < s.size() && s[l] == s[r])
		{
			--l;
			++r;
		}
		if (maxLen < r - l - 1)
		{
			maxLen = r - l - 1;
			start = l + 1;
			end = r - 1;
		}
	}
	string ss;
	for (int i = start; i <= end; i++)
	{
		ss.push_back(s[i]);
	}
	return ss;
}

string STRING::convert(string s, int numRows)
{
	int len = s.length();
	if (numRows == 1)
	{
		return s;
	}
	int cicle = 2 * numRows - 2;
	vector<vector<char>> res(numRows);
	for (size_t i = 0; i < len; i++)
	{
		int temp = i % cicle;
		if (temp < numRows)
		{
			res[temp].push_back(s[i]);
		}
		else
		{
			res[cicle - temp].push_back(s[i]);
		}
	}
	string result;
	for (auto& vct : res)
	{
		for (auto i : vct)
		{
			result.push_back(i);
		}
	}
	return result;
}

int STRING::myAtoi(string s)
{
	string::size_type index = 0;
	size_t len = s.size();
	while (index < len && s[index] == ' ')
	{
		++index;
	}
	bool flag = false;
	if (index < len)
	{
		if (s[index] == '-')
		{
			flag = true;
			++index;
		}
		else if (s[index] == '+')
		{
			++index;
		}
	}
	int ans = 0;
	bool isOver = false;
	while (index < len)
	{
		if (s[index] < '0' || s[index] > '9')
		{
			break;
		}
		else
		{
			if (ans != 0 && (INT_MAX - 7) / ans <= 10)
			{
				if ((INT_MAX - 7) / ans == 10 && s[index] - '0' <= 7)
				{
					ans = ans * 10 + s[index] - '0';
				}
				else
				{
					ans = INT_MAX;
					isOver = true;
				}
				break;
			}
			else
			{
				ans = ans * 10 + s[index] - '0';
			}
		}
		++index;
	}
	if (flag)
	{
		if (isOver)
		{
			ans = -ans - 1;
		}
		else
		{
			ans = -ans;
		}
	}
	return ans;
}

void STRING::testMyAtoi()
{
	myAtoi("2147483646");

}

bool STRING::isPalindrome(int x)
{
	if (x < 0)
	{
		return false;
	}
	int res = 0, before = x;
	while (x > 0)
	{
		int temp = x % 10;
		res = 10 * res + temp;
		x /= 10;
	}
	if (res != before)
	{
		return false;
	}
	return true;
}

int STACK::reverse(int x)
{
	//假设没有 64 位的数值类型
	int ret = 0;
	while (x != 0)
	{
		if ((ret > 0 && INT_MAX / ret < 10) || (ret < -10 && INT_MIN / ret < 10))
		{
			return 0;
		}
		else
		{
			ret = ret * 10 + x % 10;
		}
		x /= 10;
	}
	return ret;
}

bool STACK::isValid(string s)
{
	stack<char> chStack;
	size_t len = s.length();
	for (size_t i = 0; i < len; ++i)
	{
		if (chStack.empty())
		{
			chStack.push(s[i]);
			continue;
		}
		char topCh = chStack.top();
		if ((topCh == '(' && s[i] == ')') || (topCh == '{' && s[i] == '}') || (topCh == '[' && s[i] == ']'))
		{
			chStack.pop();
		}
		else
		{
			chStack.push(s[i]);
		}
	}
	if (chStack.empty())
	{
		return true;
	}
	return false;
}

void STACK::testIsValid()
{
	isValid("()[]{}");
}

string STACK::longestCommonPrefix(vector<string>& strs)
{
	int len = strs.size();
	string ans = strs[0];
	for (size_t i = 1; i < len; ++i)
	{
		size_t index = 0, ansLen = ans.length();
		for (; index < ansLen; ++index)
		{
			if (strs[i][index] != ans[index])
			{
				break;
			}
		}
		if (index < ansLen)
		{
			ans = ans.substr(0, index - 1);
		}
	}
	return ans;
}

bool GRAPH::canFinish(int numCourses, vector<vector<int>>& prerequisites)
{
	vector<vector<int>> graphics = buildGraph(numCourses, prerequisites);
	vector<int> visit(numCourses, 0);
	for (size_t i = 0; i < numCourses; i++)
	{
		bool res = hasCycle(graphics, visit, i);
		if (res)
		{
			return true;
		}
	}
	return false;
}

vector<vector<int>> GRAPH::buildGraph(int numCourses, const vector<vector<int>>& prerequisites)
{
	vector<vector<int>> ret(numCourses);
	for (size_t i = 0; i < prerequisites.size(); i++)
	{
		ret[prerequisites[i][0]].push_back(prerequisites[i][1]);
	}
	return ret;
}

bool GRAPH::hasCycle(const vector<vector<int>>& graph, vector<int>& visit, int num)
{
	if (visit[num] == 0)
	{
		for (size_t i = 0; i < graph[num].size(); i++)
		{
			visit[num] = 2;
			bool res = hasCycle(graph, visit, graph[num][i]);
			if (res)
			{
				return true;
			}
		}
		visit[num] = 1;
	}
	else if (visit[num] == 1)
	{
		return false;
	}
	return true;
}

vector<int> GRAPH::findOrder(int numCourses, vector<vector<int>>& prerequisites)
{
	// 构建图， 保存图每个节点的 入度 
	vector<vector<int>> graph(numCourses);
	vector<int> degree(numCourses);
	vector<int> ret(numCourses);
	int counter = 0;
	for (size_t i = 0; i < prerequisites.size(); i++)
	{
		graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
		++degree[prerequisites[i][0]];
	}
	queue<int> di;
	for (size_t j = 0; j < numCourses; j++)
	{
		if (degree[j] == 0)
		{
			di.push(j);
		}
	}
	while (!di.empty())
	{
		int i = di.front();
		for (auto& x : graph[i])
		{
			--degree[x];
			if (degree[x] == 0)
			{
				di.push(x);
			}
		}
		ret[counter++] = i;
		di.pop();
	}
	if (counter != numCourses)
	{
		return vector<int>();
	}
	return ret;
}

vector<vector<int>> ALGORITHM::levelOrder(TreeNode* root)
{
	vector<vector<int>> ret;
	queue<TreeNode*> tque;
	if (root)
	{
		tque.push(root);
	}
	while (!tque.empty())
	{
		vector<int> temp;
		int size = tque.size();
		for (size_t i = 0; i < size; i++)
		{
			auto node = tque.front();
			tque.pop();
			temp.push_back(node->val);
			if (node->left)
			{
				tque.push(node->left);
			}
			if (node->right)
			{
				tque.push(node->right);
			}
		}
	}
	return ret;
}

Node* ALGORITHM::cloneGraph(Node* node)
{
	auto hashFun = [](Node* node)
	{
		return std::hash<int>{}(node->val);
	};

	auto equalFun = [](Node* node1, Node* node2)
	{
		return node1 == node2;
	};
	unordered_map<Node*, Node*, decltype(hashFun), decltype(equalFun)> nodeMap(10, hashFun, equalFun); //key  (old node) : value(new node)
	queue<Node*> nodeQueue;
	Node* head = new Node(node->val, node->neighbors);
	nodeQueue.push(node);
	nodeMap.insert({ node, head });
	while (!nodeQueue.empty())
	{
		int nodeSize = nodeQueue.size();
		for (size_t i = 0; i < nodeSize; ++i)
		{
			Node* curNode = nodeQueue.front();
			nodeQueue.pop();
			vector<Node*> curNeighborVct;
			for (auto& neighborNode : curNode->neighbors)
			{
				auto iter = nodeMap.find(neighborNode);
				if (iter == nodeMap.end())
				{
					Node* cloneNode = new Node(neighborNode->val, neighborNode->neighbors);
					nodeQueue.push(cloneNode);
					curNeighborVct.push_back(cloneNode);
					nodeMap.insert({ neighborNode, cloneNode });
				}
				else
				{
					curNeighborVct.push_back(iter->second);
				}
			}
			curNode->neighbors = curNeighborVct;
		}
	}
	return head;
}

void ALGORITHM::testcloneGraph()
{
	vector<vector<int>> adjList = { {2, 4},{1, 3 },{2, 4},{1, 3} };

	Node* node1 = new Node(1);
	Node* node2 = new Node(2);
	Node* node3 = new Node(3);
	Node* node4 = new Node(4);

	node1->neighbors = { node2, node4 };
	node2->neighbors = { node1,node3 };
	node3->neighbors = { node2, node4 };
	node4->neighbors = { node1,node3 };

	cloneGraph(node1);
}

int ALGORITHM::dijkstra(int start, int end, int k, vector<vector<pair<int, int>>> graph)
{
	vector<int> distTo(graph.size(), INT_MAX);
	vector<int> nodeNumTo(graph.size(), INT_MAX);
	distTo[start] = 0;
	nodeNumTo[start] = 1;
	// priority_queue<State,vector<State>,cmp> pq;
	priority_queue<State, vector<State>, function<bool(State, State)>> pq(
		[](State a, State b)
		{
			return a.distFromStart > b.distFromStart;
		});
	pq.push(State(start, 0, 1));
	while (!pq.empty())
	{
		State cur = pq.top();
		pq.pop();
		int curID = cur.id;
		int curDIS = cur.distFromStart;
		int curNum = cur.costnodes;
		if (curID == end)
		{
			return  distTo[end];
		}
		if (curNum == k)
		{
			continue;
		}
		for (auto neighbor : graph[curID])
		{
			int nextNodeID = neighbor.first;
			int costToNextNode = curDIS + neighbor.second;
			// 中转次数消耗 1
			int nextNodeNumFromSrc = curNum + 1;
			// 更新 dp table
			if (distTo[nextNodeID] > costToNextNode && nextNodeNumFromSrc <= k)
			{
				distTo[nextNodeID] = costToNextNode;
				nodeNumTo[nextNodeID] = nextNodeNumFromSrc;
			}
			//// 剪枝，如果中转次数更多，花费还更大，那必然不会是最短路径
			if (costToNextNode > distTo[nextNodeID] && nextNodeNumFromSrc > nodeNumTo[nextNodeID])
			{
				continue;
			}
			// if(nextNodeNumFromSrc>k) continue;
			// cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
			pq.push(State(nextNodeID, costToNextNode, nextNodeNumFromSrc));
		}
	}
	return -1;
}

int ALGORITHM::findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
{
	vector<vector<pair<int, int>>> graph(n);
	for (auto& flight : flights)
	{
		int from = flight[0];
		int to = flight[1];
		int price = flight[2];
		graph[from].push_back({ to, price });
	}

	// 启动 dijkstra 算法
	// 计算以 src 为起点在 k 次中转到达 dst 的最短路径
	k += 2;
	return dijkstra(src, dst, k, graph);
	// vector<int> res=dijkstra( src, k,graph);
	// return res[dst]==INT_MAX/2? -1: res[dst];
}

int ALGORITHM::networkDelayTime(vector<vector<int>>& times, int n, int k)
{
	vector<vector<pair<int, int>>> graph(n);
	for (auto& flight : times)
	{
		graph[flight[0] - 1].emplace_back(flight[1], flight[2]);
	}
	vector<Vertex> vvct(n);
	for (size_t i = 0; i < vvct.size(); ++i)
	{
		vvct[i].costTime = INT_MAX;
		vvct[i].isKnown = false;
		vvct[i].id = i + 1;
	}
	vvct[k - 1].costTime = 0;
	priority_queue<Vertex*, vector<Vertex*>, function<bool(const Vertex*, const Vertex*)>> pq(
		[](const Vertex* v1, const Vertex* v2)
		{
			return v1->costTime > v2->costTime;
		});
	pq.push(&vvct[k - 1]);
	while (!pq.empty())
	{
		auto vp = pq.top();
		pq.pop();
		vp->isKnown = true;
		int curId = vp->id;
		int curCost = vp->costTime;
		for (auto& w : graph[curId - 1])
		{
			int nextId = w.first;
			int nextCost = w.second;
			/*		if (!vvct[nextId - 1].isKnown)
					{*/
			if (curCost + nextCost < vvct[nextId - 1].costTime)
			{
				vvct[nextId - 1].costTime = curCost + nextCost;
				pq.push(&vvct[nextId - 1]);
			}
		}
	}
	int max = 0;
	for (auto& v : vvct)
	{
		if (v.costTime == INT_MAX)
		{
			return -1;
		}
		else if (v.costTime > max)
		{
			max = v.costTime;
		}
	}
	return max;
}

int ALGORITHM::findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold)
{
	vector<vector<pair<int, int>>> graph(n);
	for (auto& vct : edges)
	{
		graph[vct[0]].emplace_back(vct[1], vct[2]);
		graph[vct[1]].emplace_back(vct[0], vct[2]);
	}
	int ans = INT_MAX, index = 0;
	using Pair = pair<int, int>;
	for (size_t i = 0; i < n; i++)
	{
		vector<int> dis(n, INT_MAX);
		dis[i] = 0;
		priority_queue < Pair, vector< Pair>, function<bool(const Pair&, const Pair&)>> pq(
			[](const Pair& p1, const Pair& p2)
			{
				return p1.second > p2.second;
			});
		pq.emplace(i, 0);
		while (!pq.empty())
		{
			auto cur = pq.top();
			pq.pop();
			int curId = cur.first;
			int curDis = cur.second;
			for (auto& next : graph[curId])
			{
				int nextId = next.first;
				int nextDis = next.second;
				int wDis = nextDis + curDis;
				if (wDis <= distanceThreshold && wDis < dis[nextId])
				{
					dis[nextId] = wDis;
					pq.emplace(nextId, wDis);
				}
			}
		}
		int cnt = 0;
		for (size_t j = 0; j < n; ++j)
		{
			if (dis[j] != 0 && dis[j] != INT_MAX)
			{
				++cnt;
			}
		}
		if (cnt <= ans)
		{
			ans = cnt;
			index = i;
		}
	}
	return index;
}

int ALGORITHM::reachableNodes(vector<vector<int>>& edges, int maxMoves, int n)
{
	vector<vector<pair<int, int>>> graph(n);
	for (auto& vct : edges)
	{
		graph[vct[0]].emplace_back(vct[1], vct[2]);
		graph[vct[1]].emplace_back(vct[0], vct[2]);
	}
	using Pair = pair<int, int>;
	priority_queue<Pair, vector<Pair>, function<bool(const Pair& p1, const Pair& p2)>> pq([](const Pair& p1, const Pair& p2) {
		return p1.second > p2.second;
		});
	vector<int> dis(n, INT_MAX);
	dis[0] = 0;
	pq.emplace(0, 0);
	while (!pq.empty())
	{
		auto cur = pq.top();
		pq.pop();
		int curId = cur.first;
		int curDis = cur.second;
		for (auto& next : graph[curId])
		{
			int nextId = next.first;
			int nextDis = next.second;
			int wDis = curDis + nextDis;
			if (wDis < dis[nextId])
			{
				dis[nextId] = wDis;
				pq.emplace(nextId, wDis);
			}
		}
	}
	int ans = 0;
	for (auto& i : dis)
	{
		if (i <= maxMoves)
		{
			++ans;
		}
	}
	for (auto& e : edges)
	{
		int u = e[0], v = e[1], cnt = e[2];
		int a = max(maxMoves - dis[u], 0);
		int b = max(maxMoves - dis[v], 0);
		ans += min(a + b, cnt);
	}
	return ans;
}

int ALGORITHM::minCostConnectPoints(vector<vector<int>>& points)
{
	int len = points.size();
	vector<vector<int>> graph(len, vector<int>(len, 0));
	for (size_t i = 0; i < len; ++i)
	{
		for (size_t j = 0; j < len; ++j)
		{
			graph[i][j] = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
		}
	}
	vector<bool> isVisited(len, false);
	isVisited[0] = true;
	int sum = 0;
	vector<int> dis(len, INT_MAX);
	for (size_t i = 0; i < len; ++i)
	{
		dis[i] = graph[0][i];
	}
	for (size_t i = 0; i < len - 1; ++i)
	{
		int minId = 0, minDis = INT_MAX;
		for (size_t j = 0; j < len; ++j)
		{
			if (!isVisited[j] && dis[j] < minDis)
			{
				minId = j;
				minDis = dis[j];
			}
		}
		isVisited[minId] = true;
		sum += minDis;
		//更新节点
		for (size_t k = 0; k < len; ++k)
		{
			if (!isVisited[k] && graph[minId][k] < dis[k])
			{
				dis[k] = graph[minId][k];
			}
		}
	}
	return sum;

}

int ALGORITHM::minCostConnectPoints2(vector<vector<int>>& points)
{
	int n = points.size();
	vector<Edge> edges;
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = i + 1; j < n; ++j)
		{
			int dist = abs(points[j][0] - points[i][0]) + abs(points[j][1] - points[i][1]);
			edges.emplace_back(dist, i, j);
		}
	}
	sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
		return a.len < b.len;
		});
	int ret = 0, num = 1;
	DisjSet dsu(n);
	for (auto& edge : edges)
	{
		auto len = edge.len, x = edge.start, y = edge.end;
		if (dsu.unionSet(x, y))
		{
			ret += len;
			++num;
			if (num == n)
			{
				break;
			}
		}
	}

	return ret;
}

vector<int> ALGORITHM::inorderTraversal(TreeNode* root)
{
	vector<int> ret;
	stack<TreeNode*> nodeStack;
	while (root || !nodeStack.empty())
	{
		while (root)
		{
			nodeStack.push(root);
			root = root->left;
		}
		root = nodeStack.top();
		nodeStack.pop();
		ret.push_back(root->val);
		root = root->right;
	}
	return ret;
}

void ALGORITHM::dfs(TreeNode* node, vector<int>& ans)
{
	if (!node)
	{
		return;
	}
	ans.push_back(node->val);
	dfs(node->left, ans);
	dfs(node->right, ans);
}

void ALGORITHM::testInorderTraversal()
{
	TreeNode* f3l = new TreeNode(-2, nullptr, nullptr);
	TreeNode* f3r = new TreeNode(0, nullptr, nullptr);
	TreeNode* f2r = new TreeNode(-1, f3l, f3r);
	TreeNode* f2l = new TreeNode(-4, nullptr, nullptr);
	TreeNode* f2rr = new TreeNode(3, nullptr, nullptr);
	TreeNode* f1l = new TreeNode(-3, f2l, f2r);
	TreeNode* f1r = new TreeNode(2, nullptr, f2rr);
	TreeNode* root = new TreeNode(1, f1l, f1r);

	inorderTraversal(root);
}

bool ALGORITHM::isValidBST(TreeNode* root)
{
	vector<int> ret;
	stack<TreeNode*> nodeStack;
	while (root || !nodeStack.empty())
	{
		while (root)
		{
			nodeStack.push(root);
			root = root->left;
		}
		root = nodeStack.top();
		nodeStack.pop();
		ret.push_back(root->val);
		root = root->right;
	}
	for (size_t i = 0; i < ret.size() - 1; ++i)
	{
		if (ret[i] >= ret[i + 1])
		{
			return false;
		}
	}
	return true;
}





void ALGORITHM::testisValidBST()
{
	TreeNode* f2l = new TreeNode(3, nullptr, nullptr);
	TreeNode* f2r = new TreeNode(7, nullptr, nullptr);
	TreeNode* f1l = new TreeNode(4, nullptr, nullptr);
	TreeNode* f1r = new TreeNode(6, f2l, f2r);
	TreeNode* root = new TreeNode(5, f1l, f1r);

	isValidBST(root);
}

void ALGORITHM::recoverTree(TreeNode* root)
{
	stack<TreeNode*> stn;
	vector<TreeNode*> vctn;
	while (root || !stn.empty())
	{
		while (root)
		{
			stn.push(root);
			root = root->left;
		}
		root = stn.top();
		stn.pop();
		vctn.push_back(root);
		root = root->right;
	}
	int before = 0;
	for (size_t i = 0; i < vctn.size() - 1; ++i)
	{
		if (vctn[i]->val > vctn[i + 1]->val)
		{
			before = i;
			break;
		}
	}
	int min = vctn[before + 1]->val;
	int after = before + 1;
	for (int i = before + 2; i < vctn.size(); ++i)
	{
		if (min > vctn[i]->val)
		{
			after = i;
		}
	}
	int temp = vctn[before]->val;
	vctn[before]->val = vctn[after]->val;
	vctn[after]->val = temp;
}

void ALGORITHM::testRecoverTree()
{
	TreeNode* f2l = new TreeNode(2, nullptr, nullptr);
	TreeNode* f1l = new TreeNode(1, nullptr, nullptr);
	TreeNode* f1r = new TreeNode(4, f2l, nullptr);
	TreeNode* root = new TreeNode(3, f1l, f1r);
	recoverTree(root);
}

int ALGORITHM::maxArea(vector<int>& height)
{
	int left = 0, right = height.size() - 1, maxA = 0;
	while (left < right)
	{
		auto area = (right - left) * min(height[right], height[left]);
		maxA = area > maxA ? area : maxA;
		if (height[right] > height[left])
		{
			++left;
		}
		else
		{
			++right;
		}
	}
	return maxA;
}

bool ALGORITHM::canJump(vector<int>& nums)
{
	int cur = 0, before = 0, dest = nums.size() - 1;
	while (cur < dest)
	{
		int maxJump = nums[before] + before;
		for (int i = before + 1; i < cur; ++i)
		{
			int jump = nums[i] + i;
			if (jump > maxJump)
			{
				maxJump = jump;
			}
		}
		if (maxJump < cur)
		{
			return false;
		}
		else
		{
			before = cur;
			cur = maxJump;
		}
	}
	return true;
}

void ALGORITHM::testCanJump()
{
	vector<int> vct{ 3,2,1,0,4 };
	canJump(vct);
}

int ALGORITHM::maxProfit(vector<int>& prices)
{
	//int size = prices.size(), minPrices = INT_MAX, maxProfit = 0;
	//for (size_t i = 0; i < size; ++i)
	//{
	//	minPrices = min(minPrices, prices[i]);
	//	maxProfit = max(maxProfit, prices[i] - minPrices);
	//}
	//return maxProfit;

	//动态规划阶阶题
	int size = prices.size();
	vector<pair<int, int>> profit(size);
	profit[0] = { -prices[0], 0 };
	for (size_t i = 1; i < size; ++i)
	{
		profit[i].first = max(-prices[i], profit[i - 1].first);
		profit[i].second = max(profit[i - 1].second, prices[i] + profit[i].first);
	}
	return profit[size - 1].second;
}

int ALGORITHM::uniquePaths(int m, int n)
{
	vector<vector<int>> grid(m, vector<int>(n, 0));
	grid[0][0] = 1;
	for (size_t i = 0; i < m; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			if (i > 0 && j > 0)
			{
				grid[i][j] = grid[i - 1][j] + grid[i][j - 1];
			}
			else if (i > 0)
			{
				grid[i][j] = grid[i - 1][j];
			}
			else if (j > 0)
			{
				grid[i][j] = grid[i][j - 1];
			}
		}
	}
	return grid[m - 1][n - 1];
}

int ALGORITHM::uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
{
	int m = obstacleGrid.size(), n = obstacleGrid[0].size();
	if (obstacleGrid[0][0])
	{
		return 0;
	}
	vector<vector<int>> grid(m, vector<int>(n, 0));
	grid[0][0] = 1;
	for (size_t i = 0; i < m; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			if (obstacleGrid[i][j])
			{
				grid[i][j] == 0;
				continue;
			}
			if (i > 0 && j > 0)
			{
				grid[i][j] = grid[i - 1][j] + grid[i][j - 1];
			}
			else if (i > 0)
			{
				grid[i][j] = grid[i - 1][j];
			}
			else if (j > 0)
			{
				grid[i][j] = grid[i][j - 1];
			}
		}
	}
	return grid[m - 1][n - 1];
}

int ALGORITHM::minPathSum(vector<vector<int>>& grid)
{
	int m = grid.size(), n = grid[0].size();
	int col = 0, row = 0;
	for (size_t i = 0; i < m + n; ++i)
	{
		if (row < m - 1 && col < n - 1)
		{
			if (grid[row][col + 1] > grid[row + 1][col])
			{
				grid[row + 1][col] += grid[row][col];
				++row;
			}
			else
			{
				grid[row][col + 1] += grid[row][col];
				++col;
			}
		}
		else if (row == m - 1)
		{

		}

	}
	return grid[m - 1][n - 1];
}



vector<string> ALGORITHM::generateParenthesis(int n)
{
	vector<string> ret;
	generate(ret, "", 0, 0, n);
	return ret;
}

void ALGORITHM::generate(vector<string>& res, string str, int leftCnt, int rightCnt, int n)
{
	if (leftCnt > n || rightCnt > n)
	{
		return;
	}
	if (leftCnt == n && rightCnt == n)
	{
		res.push_back(str);
	}
	if (leftCnt >= rightCnt)
	{
		generate(res, str + "(", leftCnt + 1, rightCnt, n);
		generate(res, str + ")", leftCnt, rightCnt + 1, n);
	}
}

void ALGORITHM::testGenerateParenthesis()
{
	generateParenthesis(3);

}

void ALGORITHM::testLFUCache()
{
	LFUCache lfuCache(2);
	lfuCache.put(1, 1);
	lfuCache.put(2, 2);
	lfuCache.get(1);
	lfuCache.put(3, 3);
	lfuCache.get(2);
	lfuCache.get(3);
	lfuCache.put(4, 4);
	lfuCache.get(1);
	lfuCache.get(3);
	lfuCache.get(4);
}

void ALGORITHM::nextPermutation(vector<int>& nums)
{

}

int ALGORITHM::lengthOfLIS(vector<int>& nums)
{
	int len = nums.size();
	vector<int> maxSub(len, 0);
	maxSub[0] = 1;
	int maxSubLen = 1;
	for (size_t i = 1; i < len; ++i)
	{
		int max = 0;
		for (size_t j = 0; j < i; ++j)
		{
			if (nums[j] < nums[i] && maxSub[j] > max)
			{
				max = maxSub[j];
			}
		}
		maxSub[i] = max + 1;
		if (maxSubLen < maxSub[i])
		{
			maxSubLen = maxSub[i];
		}
	}
	return maxSubLen;
}

bool ALGORITHM::isValidSudoku(vector<vector<char>>& board)
{
	vector<vector<bool>> row(9, vector<bool>(10, false));
	vector<vector<bool>> column(9, vector<bool>(10, false));
	vector<vector<bool>> box(9, vector<bool>(10, false));

	for (size_t i = 0; i < 9; ++i)
	{
		for (size_t j = 0; j < 9; ++j)
		{
			if (board[i][j] == '.')
			{
				continue;
			}
			int value = board[i][j] - '0';
			if (row[i][value])
			{
				return false;
			}
			if (column[j][value])
			{
				return false;
			}
			if (box[j / 3 + (i / 3) * 3][value])
			{
				return false;
			}
			row[i][value] = true;
			column[j][value] = true;
			box[j / 3 + (i / 3) * 3][value] = true;
		}
	}
	return true;
}

bool ALGORITHM::checkSubarraySum(vector<int>& nums, int k)
{
	int len = nums.size();
	for (size_t i = 0; i < len; ++i)
	{
		int sum = nums[i];
		for (size_t j = i + 1; j < len; ++j)
		{
			sum += nums[j];
			if (sum % k == 0)
			{
				return true;
			}
		}
	}
	return false;
}

int ALGORITHM::maxProfit2(vector<int>& prices)
{
	int i = 0, profit = 0;
	size_t priceSize = prices.size();
	for (size_t i = 0; i < priceSize - 1; ++i)
	{
		if (prices[i] <= prices[i + 1])
		{
			profit += prices[i + 1] - prices[i];
		}
	}
	return profit;
}

void ALGORITHM::testMaxProfit()
{
	vector<int> vct{ 2,4,1 };
	maxProfit(vct);
}

bool ALGORITHM::isMatch(string s, string p)
{
	size_t pIndex = 0, sIndex = 0;
	size_t pTemp = 0, sTemp = 0;
	string::size_type sLen = s.length(), pLen = p.length();
	bool flag = false;
	while (pIndex < pLen && sIndex < sLen)
	{
		if (p[pIndex] == '?' || p[pIndex] == s[sIndex])
		{
			++pIndex;
			++sIndex;
		}
		else if (p[pIndex] == '*')
		{
			flag = true;
			sTemp = sIndex;
			pTemp = ++pIndex;
		}
		else if (flag)
		{
			++sIndex;
			pIndex = pTemp;
		}
		else
		{
			return false;
		}
	}

	if (pIndex == pLen)
	{
		if (sIndex < sLen)
		{
			return false;
		}
		return true;
	}
	else
	{
		for (size_t i = pIndex; i < pLen; ++i)
		{
			if (p[i] != '*')
			{
				return false;
			}
		}
		return true;
	}
}

void ALGORITHM::testIsMathc()
{
	isMatch("adceb", "*a*b");
}

ALGORITHM::ListNode* ALGORITHM::mergeKLists(vector<ListNode*>& lists)
{
	return divideMerge(lists, 0, lists.size() - 1);
}

ALGORITHM::ListNode* ALGORITHM::divideMerge(vector<ListNode*>& lists, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		ListNode* leftNode = divideMerge(lists, left, mid);
		ListNode* rightNode = divideMerge(lists, mid + 1, right);
		if (!(leftNode && rightNode))
		{
			return leftNode ? leftNode : rightNode;
		}
		ListNode head, * tail = &head;
		while (leftNode && rightNode)
		{
			if (leftNode->val > rightNode->val)
			{
				tail->next = rightNode;
				rightNode = rightNode->next;
			}
			else
			{
				tail->next = leftNode;
				leftNode = leftNode->next;
			}
			tail = tail->next;
		}
		tail->next = leftNode ? leftNode : rightNode;
		return head.next;
	}
	else if (left == right)
	{
		lists[left];
	}
	return nullptr;
}

void ALGORITHM::testMergeKLists()
{
	ListNode* a3 = new ListNode(5);
	ListNode* a2 = new ListNode(4, a3);
	ListNode* a1 = new ListNode(1, a2);

	ListNode* b1 = new ListNode(4);
	ListNode* b2 = new ListNode(3, b1);
	ListNode* b3 = new ListNode(1, b2);

	ListNode* c2 = new ListNode(6);
	ListNode* c1 = new ListNode(2, c2);

	vector<ListNode*> lists{ a1,b1,c1 };
	mergeKLists(lists);

}


struct RecordNode
{
	string s;
	int line;

	RecordNode(string _s, int _line) :s(_s), line(_line) {};
};

int hashRecordNode(const RecordNode& node)
{
	return std::hash<string>()(node.s) + std::hash<int>()(node.line);
}

bool equalRecordNode(const RecordNode& node1, const RecordNode& node2)
{
	return node1.line == node2.line && node1.s == node2.s;
}
void recordError()
{
	string s;
	int num;
	unordered_map<RecordNode, int, decltype(&hashRecordNode), decltype(&equalRecordNode)> reUm(10, &hashRecordNode, &equalRecordNode);
	list<RecordNode> slist;
	while (cin >> s >> num)
	{
		auto pos = s.find_last_of('\\', 0);
		s = s.substr(pos + 1, s.length());
		if (s.length() > 16)
		{
			s = s.substr(s.length() - 16, 16);
		}
		RecordNode recordNode(s, num);
		++reUm[recordNode];
		if (reUm[recordNode] == 1)
		{
			slist.push_back(recordNode);
		}
	}
	while (slist.size() > 16)
	{
		RecordNode key = *slist.begin();
		reUm.erase(key);
		slist.pop_front();
	}
	for (auto& p : reUm)
	{
		printf("%s %d %d\n", p.first.s, p.first.line, p.second);
	}
}

bool equalDisj(const pair<int, int>& p1, const pair<int, int>& p2)
{
	return p1.first == p2.first && p1.second == p2.second;
}

int hashDisj(const pair<int, int>& p1)
{
	return std::hash<int>()(p1.first) + std::hash<int>()(p1.second);
}

int getNodeNum()
{


	return 0;
}

int getMettingRoom()
{
	vector<vector<int>> timeInterval{ {0,20}, {5, 10},{15,20} };
	std::sort(timeInterval.begin(), timeInterval.end(), [](auto& vct1, auto vct2)
		{
			return vct1[0] < vct2[0];
		});
	priority_queue<int> endTimeDq;
	endTimeDq.push(timeInterval[0][1]);
	int len = timeInterval.size();
	for (size_t i = 1; i < len; ++i)
	{
		if (timeInterval[i][0] >= endTimeDq.top())
		{
			endTimeDq.pop();
		}
		endTimeDq.push(timeInterval[i][1]);
	}
	return endTimeDq.size();
}

int getMettingRoom2()
{
	vector<vector<int>> timeInterval{ {3,9,2}, {4, 7,3} };
	vector<pair<int, int>> timeInter;
	int n = timeInterval.size();
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < timeInterval[i][2]; ++j)
		{
			timeInter.emplace_back(timeInterval[i][0], timeInterval[i][1]);
		}
	}
	std::sort(timeInter.begin(), timeInter.end(), [](auto& p1, auto& p2)
		{
			return p1.first < p2.first;
		});
	priority_queue<int> endTimeDq;
	endTimeDq.push(timeInter[0].second);
	int len = timeInter.size();
	for (size_t i = 1; i < len; ++i)
	{
		if (timeInter[i].first >= endTimeDq.top())
		{
			endTimeDq.pop();
		}
		endTimeDq.push(timeInter[0].second);
	}

	return endTimeDq.size();
}

int getPerfectStepNum()
{

	string s;
	// 输入字符串
	cin >> s;
	// 创建一个无序映射，用于记录每个字符出现的次数
	unordered_map<char, int> counts;
	for (int i = 0; i < s.length(); i++) {
		char c = s[i];
		counts[c]++;
	}
	// 计算每个字符出现次数的平均值
	int avg = s.length() / 4;
	int total = 0;
	bool is_balanced = true;
	// 遍历每个字符，判断是否超过平均值
	for (auto& c : counts) {
		if (c.second > avg) {
			is_balanced = false;
			// 计算超出平均值的数量
			c.second -= avg;
			total += c.second;
		}
		else {
			c.second = 0;
		}
	}
	// 如果每个字符出现的次数都不超过平均值，则字符串已经平衡
	if (is_balanced) {
		cout << 0 << endl;
		return 0;
	}
	// 使用双指针法寻找最短的平衡子串
	int left = 0;
	int right = 0;
	int min_len = s.length() + 1;
	while (right < s.length()) {
		char rc = s[right];
		if (counts[rc] > 0) {
			total--;
		}
		counts[rc]--;
		while (total == 0) {
			min_len = min(min_len, right - left + 1);
			char lc = s[left];
			if (counts[lc] >= 0) {
				total++;
			}
			counts[lc]++;
			left++;
		}
		right++;
	}
	// 输出最短的平衡子串的长度
	cout << min_len << endl;
	return 0;
}

int logSystem()
{
	vector<int> logs{ 1, 98, 1 };
	int len = logs.size();
	int sum = 0;
	int f = 0;
	int res = 0;
	for (size_t i = 0; i < len; ++i)
	{
		if (logs[i] + sum <= 100)
		{
			f = f + logs[i] - sum;
			sum += logs[i];
		}
		else
		{
			f = f + logs[i] - sum - (logs[i] + sum - 100);
			if (res < f)
			{
				res = f;
			}
			break;
		}
		if (res < f)
		{
			res = f;
		}
	}
	return res;
}



struct CityEdge
{
	int startCity, endCity, cost;
	CityEdge(int _startCity, int _endCity, int _cost) :startCity(_startCity), endCity(_endCity), cost(_cost) {};
};

void cityBuild()
{
	int cityCount, needBuildCity, mustBuildCity;
	cin >> cityCount >> needBuildCity >> mustBuildCity;
	vector<CityEdge> edge;
	auto equalPair = [](const pair<int, int>& pair1, const pair<int, int>& pair2)
	{
		return pair1.first == pair2.first && pair1.second == pair2.second;
	};
	auto hashPair = [](const pair<int, int>& pair1)
	{
		return std::hash<int>()(pair1.first) + std::hash<int>()(pair1.second);
	};
	unordered_map<pair<int, int>, int, decltype(hashPair), decltype(equalPair)> cityCostMap(31, hashPair, equalPair);
	int start, end, cost;
	for (int i = 0; i < needBuildCity; ++i)
	{
		cin >> start >> end >> cost;
		edge.emplace_back(start, end, cost);
		cityCostMap[pair<int, int>(start, end)] = cost;
	}
	vector<pair<int, int>> mustBuildVct;
	int mustBuild = mustBuildCity;
	for (int i = 0; i < mustBuildCity; ++i)
	{
		cin >> start >> end;
		mustBuildVct.emplace_back(start, end);
	}
	std::sort(edge.begin(), edge.end(), [](const CityEdge& edge1, const CityEdge& edge2) {
		return edge1.cost < edge2.cost;
		});
	int res = 0;
	int alreadyConnectCity = 0;
	DisjSet disjSet(cityCount + 1);
	for (size_t i = 0; i < mustBuildCity; ++i)
	{
		if (disjSet.unionSet(mustBuildVct[i].first, mustBuildVct[i].second))
		{
			res += cityCostMap[mustBuildVct[i]];
			++alreadyConnectCity;
		}
		else
		{
			//res += 
		}
	}

	for (int i = 0; i < needBuildCity; ++i)
	{
		int startCity = edge[i].startCity;
		int endCity = edge[i].endCity;
		int cost = edge[i].cost;
		if (disjSet.unionSet(startCity, endCity))
		{
			res += cost;
			++alreadyConnectCity;
			if (alreadyConnectCity == cityCount - 1)
			{
				break;
			}
		}
	}
	if (alreadyConnectCity == cityCount - 1)
	{
		cout << res;
		return;
	}
	cout << -1;
	return;
}

void maxSubStr()
{
	string s1, s2;
	cin >> s1 >> s2;
	int len1 = s1.length(), len2 = s2.length();
	string res;
	int maxLen = 0;
	vector<vector<int>> dpVct(len1, vector<int>(len2, 0));
	for (size_t i = 0; i < len1; ++i)
	{
		if (s1[i] == s2[0])
		{
			dpVct[i][0] = 1;
		}
	}
	for (size_t i = 0; i < len2; ++i)
	{
		if (s1[0] == s2[i])
		{
			dpVct[0][i] = 1;
		}
	}
	if (s1[0] == s2[0])
	{
		maxLen = 1;
		res.push_back(s1[0]);
	}
	for (size_t i = 1; i < len1; ++i)
	{
		for (size_t j = 1; j < len2; ++j)
		{
			if (s1[i] == s2[j])
			{
				dpVct[i][j] = dpVct[i - 1][j - 1] + 1;
				if (dpVct[i][j] > maxLen)
				{
					maxLen = dpVct[i][j];
					res = s1.substr(i - maxLen + 1, maxLen);
				}
			}
			else
			{
				dpVct[i][j] = 0;
			}
		}
	}
	return;
}

void baseMaintain()
{
	vector<vector<int>> graph{
		{0,2,1},
		{1,0,2},
		{2,1,0}
	};
	vector<bool> visited(3, false);
	vector<int> path(3, -1);
	int ans = INT_MAX;
	dfsBase(graph, visited, path, ans);

}

void dfsBase(const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& path, int& ans)
{
	if (path.size() == 2)
	{
		//int dis = 
	}
	for (size_t i = 1; i < 3; ++i)
	{
		if (!visited[i])
		{
			path.push_back(i);
			visited[i] = true;
			dfsBase(graph, visited, path, ans);
			visited[false];
			path.pop_back();
		}
	}
}

#include <algorithm>
#include <numeric>
bool canPartitionKSubsets()
{
	vector<int> nums{ 3, 4, 1,2,2,3,5 };
	int k = 4;
	std::sort(nums.begin(), nums.end());
	int allSum = std::accumulate(nums.begin(), nums.end(), 0);
	int perSum = allSum / k; /* 每个子集的和 */
	sort(nums.begin(), nums.end());
	if (nums.back() > perSum)
	{
		/* 如果最大的元素大于每个子集的和，则无法分割成 k 个子集 */
		return(false);
	}
	int		n = nums.size();
	vector<bool>	dp(1 << n, false);    /* dp[i] 表示能否构成元素下标为 i 的子集 */
	vector<int>	curSum(1 << n, 0);    /* curSum[i] 表示元素下标为 i 的子集的和 */
	dp[0] = true;
	for (int i = 0; i < 1 << n; i++)
	{
		if (!dp[i])
		{
			continue;
		}
		for (int j = 0; j < n; j++)
		{
			if (curSum[i] + nums[j] > perSum)
			{
				/* 如果当前子集的和加上 nums[j] 大于每个子集的和，则跳过 */
				break;
			}
			if (((i >> j) & 1) == 0)
			{
				/* 如果 nums[j] 没有被使用过 */
				int next = i | (1 << j);
				if (!dp[next])
				{
					curSum[next] = (curSum[i] + nums[j]) % perSum;
					dp[next] = true;
				}
			}
		}
	}
	return(dp[(1 << n) - 1]); /* 返回是否能够构成所有元素的子集 */
}

struct NumNode
{
	int begin;
	int end;
	int freq;
	NumNode() {};
	NumNode(int _begin, int _end, int _freq) :begin(_begin), end(_end), freq(_freq) {};
};

int getMaxFreqSub()
{
	int num = 0;
	cin >> num;
	unordered_map<int, NumNode> umN;
	for (int i = 0; i < num; ++i)
	{
		int temp = 0;
		cin >> temp;
		if (umN.find(temp) != umN.end())
		{
			++umN[temp].freq;
			umN[temp].end = i;
		}
		else
		{
			umN.insert({ temp, NumNode(i,i,1) });
		}
	}

	int minLen = 0, maxFreq = 0;
	for (auto& iter : umN)
	{
		if (iter.second.freq > maxFreq)
		{
			maxFreq = iter.second.freq;
			minLen = iter.second.end - iter.second.begin + 1;
		}
		else if (iter.second.freq == maxFreq)
		{
			if (minLen >= iter.second.end - iter.second.begin + 1)
			{
				minLen = iter.second.end - iter.second.begin + 1;
			}
		}
	}
	return minLen;
}
#include <sstream>
int getMiddleIndex()
{
	vector<int> numVct;
	string input;
	getline(cin, input); // 读取输入
	istringstream iss(input);
	int num;
	while (iss >> num)
	{
		numVct.push_back(num); // 将输入转化为整数数组
	}

	int len = numVct.size();
	if (len == 1)
	{
		return 0;
	}
	int left = 0, right = len - 1;
	long leftAcc = numVct[0], rightAcc = numVct[len - 1];
	while (left < right)
	{
		if (leftAcc < rightAcc)
		{
			++left;
			leftAcc *= numVct[left];
		}
		else if (leftAcc > rightAcc)
		{
			--right;
			rightAcc *= numVct[right];
		}
		else
		{
			++left;
			--right;
			leftAcc *= numVct[left];
			rightAcc *= numVct[right];
		}
	}
	if (rightAcc == leftAcc)
	{
		return right;
	}
	return -1;
}

#include <sstream>
int getNoName()
{
	string newsPaperLine, anonymousLetterLine;
	getline(cin, newsPaperLine);
	getline(cin, anonymousLetterLine);
	vector<string> anonymousLetterVct;
	string::size_type start = 0, end = 0;
	while ((end = anonymousLetterLine.find(" ", start)) != string::npos)
	{
		string word = anonymousLetterLine.substr(start, end - start);
		start = end + 1;
		anonymousLetterVct.push_back(word);
	}
	anonymousLetterVct.push_back(anonymousLetterLine.substr(start));

	auto stringEqual = [](const string& str1, const string& str2)
	{
		int len = str1.length();
		if (len != str2.length())
		{
			return false;
		}
		unordered_map<char, int> charMap;
		for (auto& c : str1)
		{
			++charMap[c];
		}
		for (auto& c : str2)
		{
			auto iter = charMap.find(c);
			if (iter == charMap.end())
			{
				return false;
			}
			else
			{
				--charMap[c];
				if (charMap[c] == 0)
				{
					charMap.erase(iter);
				}
			}
		}
		return true;
	};
	//auto stringHahs = [](const string& str) {
	//	int hashVal = 0;
	//	for (auto& i : str)
	//	{
	//		hashVal += std::hash<char>()(i);
	//	}
	//};
	unordered_map<string, int, decltype(std::hash<string>()), decltype(stringEqual)> strMap(31, std::hash<string>(), stringEqual);
	start = 0, end = 0;
	while ((end = newsPaperLine.find(" ", start)) != string::npos)
	{
		string word = newsPaperLine.substr(start, end - start);
		start = end + 1;
		++strMap[word];
	}
	++strMap[newsPaperLine.substr(start)];
	for (auto& str : anonymousLetterVct)
	{
		auto iter = strMap.find(str);
		if (iter == strMap.end())
		{
			return false;
		}
		else
		{
			--strMap[str];
			if (strMap[str] == 0)
			{
				strMap.erase(iter);
			}
		}
	}
	return true;
}


int MaxArea::row;
int MaxArea::col;
vector<pair<int, int>> MaxArea::direct{ {1,0},{0,-1},{-1, 0},{0, 1} };
void MaxArea::caculateMaxArea()
{
	int col, row;
	cin >> row >> col;
	MaxArea::row = row;
	MaxArea::col = col;
	vector<vector<char>> charVct(row, vector<char>(col, 'X'));
	vector<vector<int>> resVct;
	char c;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cin >> c;
			charVct[i][j] = c;
		}
	}
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (i == 0 || i == row - 1 || j == 0 || j == col - 1)
			{
				int cnt = 0, isSingle = 0;
				dfsArea(i, j, charVct, cnt, isSingle);
				if (isSingle == 1)
				{
					if (resVct.empty())
					{
						vector<int> vec{ i, j, cnt };
						resVct.emplace_back(vec);
					}
					else if (cnt > resVct.front()[2])
					{
						if (resVct.size() > 0)
						{
							resVct.clear();
						}
						vector<int> vec{ i, j, cnt };
						resVct.emplace_back(vec);
					}
					else if (cnt == resVct.front()[2])
					{
						vector<int> vec{ i, j, cnt };
						resVct.emplace_back(vec);
					}
				}
			}

		}
	}
	if (resVct.size() == 0)
	{
		cout << "NULL";
	}
	else if (resVct.size() == 1)
	{
		cout << resVct[0][0] << " " << resVct[0][1] << " " << resVct[0][2];
	}
	else
	{
		cout << resVct[0][2];
	}
	return;
}

void MaxArea::dfsArea(int i, int j, vector<vector<char>>& charVct, int& cnt, int& isSingle)
{
	if (i < 0 || i >= row || j < 0 || j >= col || charVct[i][j] == 'X')
	{
		return;
	}
	if (isSingle < 2 && (i == 0 || i == row - 1 || j == 0 || j == col - 1))
	{
		if (charVct[i][j] == 'O')
		{
			++isSingle;
		}
	}
	charVct[i][j] = 'X';
	++cnt;
	for (auto& p : direct)
	{
		int nextCol = j + p.second;
		int nextRow = i + p.first;
		dfsArea(nextRow, nextCol, charVct, cnt, isSingle);
	}
	return;
}

vector<vector<int>> permute(vector<int>& nums)
{
	vector<int> res;
	int len = nums.size();
	vector<bool> isVisited(len, false);
	vector<vector<int>> vcts;
	permute(nums, vcts, isVisited, res);
	return vcts;
}

void permute(vector<int>& nums, vector<vector<int>>& vcts, vector<bool>& isVisited, vector<int>& res)
{
	int len = nums.size();
	if (res.size() == len)
	{
		vcts.push_back(res);
		return;
	}

	for (int i = 0; i < len; ++i)
	{
		if (!isVisited[i])
		{
			isVisited[i] = true;
			res.push_back(nums[i]);
			permute(nums, vcts, isVisited, res);
			isVisited[i] = false;
			res.erase(res.end() - 1);
		}
	}
}

void generateParentheses2(int n)
{
	vector<string> ret;
	string res;
	generateParentheses2Help(ret, res, 2, 0, 0);
	string s;

}

void reverseStr()
{
	string s = "a(bcdefghijkl(mno)p)q";
	int iLastIndexBegin = s.find('(');
	string res;
	for (size_t i = 0; i < iLastIndexBegin; ++i)
	{
		res.push_back(s[i]);
	}
	int iLastIndexEnd = s.find_last_of(')');
	stack<char> cStack;
	int len = s.size();
	string strTemp;
	for (int i = iLastIndexBegin; i <= iLastIndexEnd; ++i)
	{
		if (s[i] == ')')
		{
			strTemp = "";
			while (cStack.top() != '(')
			{
				strTemp.push_back(cStack.top());
				cStack.pop();
			}
			cStack.pop();
			if (i == iLastIndexEnd)
			{
				break;
			}
			for (int j = 0; j < strTemp.size(); ++j)
			{
				cStack.push(strTemp[j]);
			}
		}
		else
		{
			cStack.push(s[i]);
		}
	}
	res += strTemp;
	for (int k = iLastIndexEnd + 1; k < len; ++k)
	{
		res.push_back(s[k]);
	}
}

int calculate(string s)
{
	stack<int> cStack;
	int n = s.size();
	int num = 0;
	char sign = '+';
	for (int i = 0; i < n; ++i)
	{
		if (isdigit(s[i]))
		{
			num = num * 10 + s[i] - '0';
		}
		else if (s[i] != ' ')
		{
			switch (sign)
			{
			case '+':
				cStack.push(num);
				break;
			case '-':
				cStack.push(-num);
				break;
			case '*':
				cStack.top() *= num;
				break;
			case '/':
				cStack.top() /= num;
				break;
			}
			sign = s[i];
			num = 0;
		}
	}
	int ret = 0;
	while (!cStack.empty())
	{
		ret += cStack.top();
		cStack.pop();
	}
	return ret;
}

void generateParentheses2Help(vector<string>& ret, string& res, int n, int l, int r)
{
	if (res.size() == 2 * n)
	{
		ret.push_back(res);
		return;
	}
	if (l < n)
	{
		res.push_back('(');
		generateParentheses2Help(ret, res, n, ++l, r);
		--l;
		res.pop_back();

	}
	if (r < l)
	{
		res.push_back(')');
		generateParentheses2Help(ret, res, n, l, ++r);
		--r;
		res.pop_back();
	}
}
