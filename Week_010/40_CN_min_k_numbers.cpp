class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        priority_queue<int> pq;
        for (int i : arr) {
            pq.push(i);

            while (pq.size() > k) {
                pq.pop();
            }
        }

        vector<int> answer;
        while (!pq.empty()) {
            answer.push_back(pq.top());
            pq.pop();
        }

        return answer;
    }
};

/* CN 官方题解 */
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int>vec(k, 0);
        if (k == 0) return vec; // 排除 0 的情况
        priority_queue<int>Q;
        for (int i = 0; i < k; ++i) Q.push(arr[i]);
        for (int i = k; i < (int)arr.size(); ++i) { // 这种方式，提前自行维护 heap，也算是可以加速，但是让整个
            if (Q.top() > arr[i]) {
                Q.pop();
                Q.push(arr[i]);
            }
        }
        for (int i = 0; i < k; ++i) {
            vec[i] = Q.top();
            Q.pop();
        }
        return vec;
    }
};