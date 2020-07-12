// 极度不优雅的方式 ！！！

unordered_map<int, int> record; // arr2[index] -> index of array_2

bool cmp(int num1, int num2) {
    if (record.count(num1) == 1 && record.count(num2) == 1) { // arr1 中比较的两个数字都在 arr2 里面，按他们在 arr2 中的相对位置进行排序
        return record[num1] < record[num2];

    } else if (record.count(num1) == 1) {  // 只有前面的数字在 arr2 中出现，则把后面的数字排在后面
        return true;

    } else if (record.count(num2) == 1) {  // 只有后面的数字在 arr2 中出现，则把前面的数字排在后面
        return false;

    } else {    // 两个数字都不在 arr2 中出现
        return num1 < num2;
    }
}

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        init_hash_map(arr2);
        std::sort(arr1.begin(), arr1.end(), cmp);
        return arr1;
    }

    void init_hash_map(const vector<int> &nums) {
        record.clear();
        for (int index = 0; index < nums.size(); index++) {
            record[nums[index]] = index;
        }
    }

};