// DFS version(not mine)
class Solution {
    public int minimumTotal(List<List<Integer>> triangle) {
        return  dfs(triangle, 0, 0);
    }

    private int dfs(List<List<Integer>> triangle, int i, int j) {
        if (i == triangle.size()) {
            return 0;
        }
        return Math.min(dfs(triangle, i + 1, j), dfs(triangle, i + 1, j + 1)) + triangle.get(i).get(j);
    }
}
// DFS 记忆优化
class Solution {
    Integer[][] memo;
    public int minimumTotal(List<List<Integer>> triangle) {
        memo = new Integer[triangle.size()][triangle.size()];
        return  dfs(triangle, 0, 0);
    }

    private int dfs(List<List<Integer>> triangle, int i, int j) {
        if (i == triangle.size()) {
            return 0;
        }
        if (memo[i][j] != null) {
            return memo[i][j];
        }
        return memo[i][j] = Math.min(dfs(triangle, i + 1, j), dfs(triangle, i + 1, j + 1)) + triangle.get(i).get(j);
    }
}

// python example
# O(n*n/2) space, top-down 
def minimumTotal1(self, triangle):
    if not triangle:
        return 
    res = [[0 for i in xrange(len(row))] for row in triangle]
    res[0][0] = triangle[0][0]
    for i in xrange(1, len(triangle)):
        for j in xrange(len(triangle[i])):
            if j == 0:
                res[i][j] = res[i-1][j] + triangle[i][j]
            elif j == len(triangle[i])-1:
                res[i][j] = res[i-1][j-1] + triangle[i][j]
            else:
                res[i][j] = min(res[i-1][j-1], res[i-1][j]) + triangle[i][j]
    return min(res[-1])
    
# Modify the original triangle, top-down
def minimumTotal2(self, triangle):
    if not triangle:
        return 
    for i in xrange(1, len(triangle)):
        for j in xrange(len(triangle[i])):
            if j == 0:
                triangle[i][j] += triangle[i-1][j]
            elif j == len(triangle[i])-1:
                triangle[i][j] += triangle[i-1][j-1]
            else:
                triangle[i][j] += min(triangle[i-1][j-1], triangle[i-1][j])
    return min(triangle[-1])
    
# Modify the original triangle, bottom-up
def minimumTotal3(self, triangle):
    if not triangle:
        return 
    for i in xrange(len(triangle)-2, -1, -1):
        for j in xrange(len(triangle[i])):
            triangle[i][j] += min(triangle[i+1][j], triangle[i+1][j+1])
    return triangle[0][0]

# bottom-up, O(n) space
def minimumTotal(self, triangle):
    if not triangle:
        return 
    res = triangle[-1]
    for i in xrange(len(triangle)-2, -1, -1):
        for j in xrange(len(triangle[i])):
            res[j] = min(res[j], res[j+1]) + triangle[i][j]
    return res[0]


/* DP version */
/**
 * 无论是自底向上，还是自顶向下的方式都是能够完成这道题目的。
 * 之所以可以，是因为每一个 DP_status 记录的都是：能够到达当前节点的最小耗费。
 * 无论你怎么走，走过了多少步，都是会把影响遗留下来的。
 * 由于每一个可能走到的地方，都会记录下对应的最优 dp_status，所以你不用担心可能有跳跃性太大的组合被忽略!
 * 因为是 每一个 可能走到的地方，都 会记录下对应的最优 dp_status !
 * 因为是 每一个 可能走到的地方，都 会记录下对应的最优 dp_status !
 * 因为是 每一个 可能走到的地方，都 会记录下对应的最优 dp_status !
 */
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if (triangle.size() == 0) {
            return 0;
        }

        // 从头开始递推，积累历史影响
        for (int row = 1; row < triangle.size() - 1; row++) {
            for (int col = 0; col < triangle[row].size(); col++) {
                // 有选择性的继承全部历史影响
                triangle[row][col] += min(triangle[row + 1][col], triangle[row + 1][col + 1]);
            }
        }

        return triangle[0][0];
    }
};