class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0)
            return false;

        int y = matrix.size();
        int x = matrix[0].size();

        int left = 0, right = x * y - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int curr = matrix[mid / x][mid % x];
            if (curr == target) {
                return true;

            } else if (curr > target) {
                right = mid - 1;

            } else {
                left = mid + 1;
            }   
        }   // end of while
        
        return false;
    }
};
