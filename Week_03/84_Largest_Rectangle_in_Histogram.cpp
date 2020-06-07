class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<pair<int, int>> max_stack;
        max_stack.push(pair<int, int> {-1, -1}); // first for position, second for data
        int max_area = 0;

        for (int i = 0; i < heights.size(); i++) {
            while (max_stack.top().second != -1 && heights[i] <= max_stack.top().second) {
                pair<int, int> data = max_stack.top();
                max_stack.pop();
                int area = data.second * (i - max_stack.top().first - 1);
                max_area = max(area, max_area);
            } // end of while (heights[i] < max_stack.top().second)

            max_stack.push(pair<int, int> {i, heights[i]});
        }

        while (max_stack.top().second > -1) {
            pair<int, int> data = max_stack.top();
            max_stack.pop();
            int area = data.second * (heights.size() - max_stack.top().first - 1);
            max_area = max(area, max_area);
        }

        return max_area;
    }
};

/**
 * S = H * W
 * 
 * 每一个棒子都能够用他们自身的高度来画一条横线形成一个矩形面积，所以以每一个棒子的高度作为 H 计算一次面积是不可避免的,
 * 你可以优化的是，怎么快速找到作为 H 的这一个棒子的最大宽度是什么？
 * 
 * 最基础的方式就是，枚举每一根棒子，然后分别向左向右扩散，寻找左右边界。但是你会发现，左右边界的寻找过程中是重复的！
 * 由于左右边界的判定标准是会根据当前棒子的自身高度发生改变(所以这个是相对的)，你就不能采用 排序 的方式，事先拍好所有
 * 棒子的高度顺序进行优化
 * 
 * 但是，当下一个棒子比上一个棒子矮的时候，前面的所有棒子的右边界就已经确定了（所有外层 for-loop 除了遍历所有棒子的功能之外，
 * 还在不断的寻找有边界）。这时候，你就可以把前面的棒子清掉，计算出相应的面积。
 * 当然，这时候仅仅是找到了可以作为有边界的某一跟棒子，而左边界还是不确定了，那么这时候，我们就要去看看左边界是什么？
 * 
 * 左边界其实就已经在 stack 里面了，只要当前棒子的高度小于 stack.top() 的高度，你都可以视为，这个 top 的棒子找到了右边界了。
 * 又由于，这个 stack 在存入的时候，就已经让 下一层 小于 上一层，所有，左边界自然也就立马出来了
 * 
 * 综上，有了左右边界，又有了高度，当前面积也就出来了
 * 
 * 
 * 这个解法的巧妙之处在于：
 * 1. 充分观察每一个棒子的面积是怎么计算的，发现问题的重点在于，怎么快速找到左右边界（毕竟高度就是自己的高度）
 * 2. stack 的设计也是极其巧妙的，当当前棒子大于 top 的话push，小于的话 pop，这样就相当于确保了下一层就是左边界
 *    这样的动态维护 stack，可以快速找到左边界（当你遇上一个比你更小的时候，他就已经取代了你，成为接下来的棒子的左边界了）
 *    stack 的这种 暂定里程碑\当前里程碑 的思想很值得借鉴，将里程碑动态的进行维护在 stack 里面！
 * 
*/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int max_area = 0;
        stack<int> min_stack;
        min_stack.push(-1);
        for (int index = 0; index < heights.size(); index++) {
            while (min_stack.top() != -1 && heights[index] <= heights[min_stack.top()]) {
                int H = heights[min_stack.top()];
                min_stack.pop();
                int L = index - min_stack.top() - 1;
                int area = H * L;
                max_area = max(max_area, area);
            }

            min_stack.push(index);
        }

        while (min_stack.top() != -1) {
            int H = heights[min_stack.top()];
            min_stack.pop();
            int L = heights.size() - min_stack.top() - 1;
            int area = H * L;
            max_area = max(max_area, area);
        }
        return max_area;
    }
};