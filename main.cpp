#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <unordered_set>
#include <random>
#include <iterator>
#include <functional>
#include <stack>
#include <list>
#include <queue>
#include <iomanip>


#include "Sort.h"
using namespace std;
#if (defined _MSC_VER) && (defined _DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <cstdlib> 
#include <crtdbg.h>
#endif // defined (_MSC_VER && _DEBUG)
//合并区间
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.size() == 0 || intervals.size() == 1) return intervals;
    int u = 0, v = 0;
    vector<vector<int>> ans;
    std::sort(intervals.begin(), intervals.end());
    while (v < intervals.size()) {
        if (intervals[v][0] > intervals[u][1]) 
        {
            ans.emplace_back(intervals[u]);
            u = v;
        }
        else if (intervals[v][1] <= intervals[u][1]) 
                ++v;
             else {
                intervals[u][1] = intervals[v][1];
                ++v;
            }
        }
    ans.emplace_back(intervals[u]);
    return ans;
}

// Leetcode 1143 最长公共子序列 LCS
size_t longestCommonSubsequence(const string& text1, const string& text2) {
    string::size_type len1 = text1.length();
    string::size_type len2 = text2.length();
    vector<vector<size_t>> dp(len1 + 1, vector<size_t>(len2 + 1, 0));
    for (size_t i = 1; i < len1 + 1; i++) {
        for (size_t j = 1; j < len2 + 1; j++) {
            if (text1[i - 1] == text2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[len1][len2];
}
// Singleton without multi-thread safe options
class Singleton
{
public:
    static Singleton* getInstance()
    {
        // check if exists
        if (m_instance == nullptr)
        m_instance = new Singleton();
    return m_instance;
    }
private:
    static Singleton* m_instance;
    Singleton();
    Singleton(const Singleton& other);
};
Singleton* Singleton::m_instance = nullptr;

// multi-thread safe for C++11
template<typename T>
class goodSingleton {
public:
    static T& getInstance() {
        static T value;
        return value;
    }
    goodSingleton() = delete;
    goodSingleton(const goodSingleton&) = delete;
    ~goodSingleton() = delete;
    goodSingleton& operator=(const goodSingleton&) = delete;
};

int main()
{
#if (defined _MSC_VER) && (defined _DEBUG) 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define DBG_NEW new
#endif // defined (_MSC_VER && _DEBUG)
	
	return 0;
}
