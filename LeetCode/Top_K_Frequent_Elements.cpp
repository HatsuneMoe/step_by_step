#include <queue>
#include <vector>
#include <iostream>
#include <unordered_map>

using std::priority_queue;
using std::unordered_map;
using std::vector;
using std::greater;
using std::pair;



class Solution {
public:
    struct PriorityCompare
    {
        bool operator()(pair<int, int> _a,pair<int, int> _b)
        {
            return _a.second > _b.second;
        }
    };

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> hash_table;
        priority_queue<pair<int, int>, vector<pair<int, int>>, PriorityCompare> heap;
        vector<int> res;
        for (auto &i:nums)
            hash_table[i]++;
        for (auto &j:hash_table){
            heap.push(j);
            if (heap.size() > k) heap.pop();
        }
        while (!heap.empty()) {
            res.push_back(heap.top().first);
            heap.pop();
        }
        return res;
    }
};

int main()
{
    Solution A;
    vector<int> _list = {1,2};
    for (auto &i : A.topKFrequent(_list, 2))
        std::cout << i << std::endl;
    return 0;
}