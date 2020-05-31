class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> answer;

        for (int i = 0; i < nums.size() - 1; i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    answer.push_back(i);
                    answer.push_back(j);
                    return answer;
                }
            }
        }

        return answer;
    }
};

/* hash twice */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num_map;

        for (int index = 0; index < nums.size(); index++) {
            num_map[nums[index]] = index;   
            //  If 4 + 4 = 8; the second 4 will overwrite the first 4 !
            //  BUT you will search vector nums again ! This can make you get the right answer !
        }

        for (int i = 0; i < nums.size(); i++) {
            int another = target - nums[i];
            if (num_map.count(another) && num_map[another] != i) {  // you have to make sure they are not the same element.
                return vector<int> {i, num_map[another]};
            }
        }

        return vector<int> {-1};
    }
};

/* hash once */
/**
 * 在进行迭代并将元素插入到表中的同时，我们还会 回过头来 检查表中是否已经存在当前元素所
 * 对应的目标元素。如果它存在，那我们已经找到了对应解，并立即将其返回。
*/
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num_map;

        for (int i = 0; i < nums.size(); i++) {
            int another = target - nums[i];
            if (num_map.find(another) != num_map.end()) {
                return vector<int> {i, num_map[another]};
            }
            num_map[nums[i]] = i;
        }

        return vector<int> {-1};
    }
};