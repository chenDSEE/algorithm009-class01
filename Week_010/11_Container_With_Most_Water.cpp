class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_area = 0;
        int area = 0;
        for (int i = 0; i < height.size(); i++) {
            for (int j = i + 1; j < height.size(); j++) {
                area = (j - i) * (height[i] < height[j] ? height[i] : height[j]);
                max_area = max_area > area ? max_area : area;
            }
        }
        return max_area;
    }
};



/**
 * Hide Hint:
 * 1. The aim is to maximize the area formed between the vertical lines. 
 *    The area of any container is calculated using the shorter line as length 
 *    and the distance between the lines as the width of the rectangle.
 *          Area = length of shorter vertical line * distance between lines
 *    We can definitely get the maximum width container as the outermost lines 
 *    have the maximum distance between them. However, this container might not 
 *    be the maximum in size as one of the vertical lines of this container could 
 *    be really short. 
 * 2. Start with the maximum width container and go to a shorter width container 
 *    if there is a vertical line longer than the current containers shorter line. 
 *    This way we are compromising on the width but we are looking forward to a 
 *    longer length container.
 */

class Solution {
public:
    int maxArea(vector<int>& height) {
        int area = 0, max_area = 0, min_heigh = 0;
        for (int left = 0, right = height.size() - 1; left < right; ) {
            min_heigh = height[left] < height[right] ? height[left++] : height[right--];
            area = (right - left + 1) * min_heigh;
            if (max_area < area)
                max_area = area;
        }
        return max_area;
    }
};

/**
 * Good explanation
 * 1. Start by evaluating the widest container, using the first and the last line. 
 *    All other possible containers are less wide, so to hold more water, they need 
 *    to be higher. Thus, after evaluating that widest container, skip lines at both 
 *    ends that don't support a higher height. Then evaluate that new container we 
 *    arrived at. Repeat until there are no more possible containers left.
 * 2. 你要留意一下：为什么要用两个指针？为什么要交替移动？
 *    一个指针是用来记录当前最大值，那自然是让另一个指针来寻找下一个更大的高度啦
 *    而且一定要左右交替！问题是让我们容积最大，而不是最大高度，更高的高度并不代表面积更大的，
 *    你仍然要检查实际容积大小！
*/


/**
 * S = W * H
 * 
 * 1. 为什么最开始的方案要用两层循环？
 *    因为 W，H 都是没有规律的，没有任何的单调性可言，所以只能扫描全部 W 跟 H 的组合，
 *    然后找出最大的 S。
 * 
 * 2. 为什么 W 的单调性能减去一层循环？
 *    因为发现了规律。首先，我们的枚举方式，仅仅枚举没有任何单调规律的 H，而在循环的
 *    过程中，W 是单调减小的，这也就是为什么能够减少一层循环的主要原因
 * 
*/