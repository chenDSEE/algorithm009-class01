```python
# Python
def BFS(graph, start, end):
    visited = set()  # 更多的是为了图之类的，避免重复遍历
	
    queue = [] # 必备，正是这玩意实现了，暂时记录下一层的待访问节点
	queue.append([start]) # 将初始能够访问的节点加入队列中
    
	while queue: 
        curr_level_size = queue.size() # 通过这种方式
		node = queue.pop() 	# 因为该节点已经访问过了，所以就从 wait_queue中删除
		visited.add(node)  # 更多的是为了图之类的，避免重复遍历
        
		process(node) 
		
        # 看看是不是新的节点能够加入 等待队列 中
        nodes = generate_related_nodes(node) 
		if nodes_can_use:
        	queue.push(nodes)	# 能够加入 queue 里面进行排队等待的，都是能够作为下一个起点的中间状态
		
	# other processing work 
	...
    
# 515 作为 C++ 的模板可能比较标准，基因那题也是

```



```c++
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        queue<pair<TreeNode *, int>> wait_queue;    // node -- level
        vector<int> answer;

        if (root)
            wait_queue.push({root, 0});

        while (!wait_queue.empty()) {
            TreeNode *curr_node = wait_queue.front().first;
            int curr_level = wait_queue.front().second;
            wait_queue.pop();

            if (answer.size() <= curr_level)    // pay attention for this line !
                answer.push_back(INT_MIN);

            if (curr_node->val > answer[curr_level])
                answer[curr_level] = curr_node->val;

            if (curr_node->left)
                wait_queue.push({curr_node->left, curr_level + 1});	
            if (curr_node->right)
                wait_queue.push({curr_node->right, curr_level + 1});

        }   // end of while

        return answer;
    }
};

```





```c++
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> answer;

        queue<TreeNode*> wait_queue;
        if (root)
            wait_queue.push(root);

        while(!wait_queue.empty()) {
            int levelSize = wait_queue.size();	// this line
            int levelMax = INT_MIN;
            for(int i = 0; i < levelSize; i++) {	
                TreeNode* curNode = wait_queue.front(); // and this line, 这两行实现了，知道单层 queue 有多少的需要进行遍历，更好的控制了进入 wait_queue 跟离开的情况，使过程更为可控
                wait_queue.pop();
                levelMax = max(curNode->val, levelMax);

                if(curNode->left) 
                    wait_queue.push(curNode->left);
                if(curNode->right) 
                    wait_queue.push(curNode->right);
            }
            answer.push_back(levelMax);
        }
        return answer;
    }
};
```





## DFS

```python
visited = set() 

def dfs(node, visited):
    if node in visited: # terminator
    	# already visited 
    	return 
    	
	visited.add(node) 
	
	# process current node here. 
	...
	for next_node in node.children(): 
		if next_node not in visited: 
			dfs(next_node, visited)
            
            
            
# recusion
def DFS(self, tree): 
	if tree.root is None: 
		return [] 
    
	visited, stack = [], [tree.root]
    
	while stack: 			# 注意，这里要反向填装
		node = stack.pop()  # 能加入 stack 轮候等待的，都是能够作为下一个起点的中间状态
		visited.add(node)
        
		process (node) 
        
		nodes = generate_related_nodes(node) 
		stack.push(nodes) 
        
	# other processing work 
	...
```



## 二分查找

```python
# Python
left, right = 0, len(array) - 1 
while left <= right: 
	  mid = (left + right) / 2 
	  if array[mid] == target: 
		    # find the target!! 
		    break or return result 
	  elif array[mid] < target: 
		    left = mid + 1 
	  else: 
		    right = mid - 1
```



```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left <= right) {
            int mid = (left + right) >> 1;
            if (target == nums[mid])
                return mid;

            if (nums[mid] >= nums[left]) {  // 先判断在那一截上面
                // 在根据对应截的单调性，看看 target 在不在这一截中，再决定左右边界的移动方案
                if (target >= nums[left] && target < nums[mid]) 
                    right = mid - 1;
                else
                    left = mid + 1;

            } else {
                if (target > nums[mid] && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;

            }

        }   // end of while

        return -1;
    }
};
```



## 寻找旋转数组旋转点

```c++
#include <vector>
#include <iostream>

int
find_point(std::vector<int> &test_case)
{
    int left = 0, right = test_case.size() - 1;
    int target = 0;
    while (left < right) {
        int mid = (left + right) >> 1;
        if (test_case[mid] > test_case[mid + 1])
            return mid;

        if (test_case[mid] >= test_case[left])
            left = mid + 1;
        else
            right = mid - 1;

    } // end of while

    return left;
}

int main()
{
    std::vector<int> test_case;
//    test_case.emplace_back(4);
//    test_case.emplace_back(5);
//    test_case.emplace_back(6);
//    test_case.emplace_back(7);
//    test_case.emplace_back(0);
//    test_case.emplace_back(1);
//    test_case.emplace_back(2);

    test_case.emplace_back(3);
    test_case.emplace_back(1);

    std::cout << find_point(test_case) << std::endl;
    return 0;
}
```

