/**
 * 为什么要用最小堆？ 因为节省了维护堆所需要的时间
 * 1. 首先，堆，只能够 pop 根节点，这也就意味着，用最小堆的话，当超过了 k 个元素在堆里面，你可以很快的把最菜的那个踢掉；
 *    但是用最大堆的话，你只能把所有元素的频率都保存起来，不是不行，但是随着元素的增加，你用在维护堆上面的时间就会越来越多；
 *    既然小的频率我们是不要的，那还不如直接扔掉的好
 * 
 */

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> KF_map; // nums[i], F
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;  // F, nums[i]

        for (int i : nums) {
            KF_map[i]++;
        }

        for (auto kv : KF_map) {
            pq.push({kv.second, kv.first});
            if (pq.size() > k)
                pq.pop();
        }

        vector<int> answer;
        while (!pq.empty()) {
            answer.push_back(pq.top().second);
            pq.pop();
        }

        return answer;
    }
};