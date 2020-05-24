class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] == 9) {
                digits[i] = 0;

            } else {
                digits[i]++;
                return digits;
            }
        }

        digits[0] = 1;
        digits.push_back(0);
        return digits;
    }
};


class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int is_add = true;
        for (int i = digits.size() - 1; is_add && i >= 0; i--) {
            int new_num = digits[i] + 1;
            is_add = new_num / 10;
            digits[i] = new_num % 10;

            if (i == 0 && is_add) {
                digits.insert(digits.begin(), 1);
                is_add = false;
            }
        }
        
        return digits;
    }
};