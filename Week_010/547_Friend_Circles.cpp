/**
 * 并查集为什么要用数组？
 * 因为要通过 me，迅速地找到 me 的 boss，并通过 me 来进行 boss 的刷新。
 * 随机访问，那自然是 数组 啦
 */

// 极速版本：path compassion + balance sub tree
class union_set {
private:
    int cnt;
    vector<int> parent_record; // 记录 me 的 parent 是谁？
    vector<int> sub_size;      // 分支的重量，作为 merge 时候，boss 节点的判断
public:
    union_set(int n) : cnt(n), parent_record(n), sub_size(n, 1) { 
        for (int me = 0; me < cnt; me++) {
            parent_record[me] = me;
        }
    }

    int get_size() {
        return cnt;
    }

    int find_final_parent(int me) {
        while (parent_record[me] != me) {
            // path compression（我直接跟随我老大的老大）
            // 我压缩到我老大那一层也没有任何效果，本来就是跟随老大
            // 跟随老大的老大，就把原本的老大跳过了
            //     if (原本的老大自己就是终极 Boss)
            //         没关系，你新的老大还是你旧的老大，因为是用 parent_record[your_boss] 来更新的
            //     else
            //         太好了，直接掠过你老大不检查，毕竟旧老大上面还有老大
            //
            // NOTE: 为什么路径压缩做在 find 里？
            // 因为 find 会遍历，顺手呗，而且做在 find，能够每一次都进行充分的压缩，
            // 第一次 find，会压缩，但不一定是最优化的，但是你后面又 find 了，那我就再次顺手压缩，不停往复
            // 终有一天会变成最优化的
            parent_record[me] = parent_record[parent_record[me]];   
            me = parent_record[me];
        }   // end of while

        return me;
    }

    bool is_connected(int one, int another) {
        int parent_one = find_final_parent(one);
        int parent_another = find_final_parent(another);
        return parent_one == parent_another;
    }

    void merge_union(int one, int another) {
        int parent_one = find_final_parent(one);
        int parent_another = find_final_parent(another);
        if (parent_one == parent_another) {
            return ;
        }

        // 分支少的，接到 分支多的上面
        // 分支越多，那样需要压缩的量就比较多，而且 "可能" 深度更深
        if (sub_size[parent_one] > sub_size[parent_another]) {
            parent_record[parent_another] = parent_one;
            sub_size[parent_one] += sub_size[parent_another];

        } else {
            parent_record[parent_one] = parent_another;
            sub_size[parent_another] += sub_size[parent_one];
        }

        cnt--;
    }

};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        union_set circle_union(M.size());

        for (int x = 0; x < M.size(); x++) {
            for (int y = 0; y < M[x].size(); y++) {
                if (M[x][y] == 1)
                    circle_union.merge_union(x, y);
            }
        }

        return circle_union.get_size();
    }
};


// heap version
class union_set {
private:
    int  num;
    int *sub_size;
    int *parent_record;
public:

    union_set(int n) : num(n) {
        parent_record = new int[n];
        sub_size = new int[n];
        for (int i = 0; i < num; i++) {
            parent_record[i] = i;
            sub_size[i] = 1;
        }
    }

    ~union_set(){
        delete [] parent_record;
        delete [] sub_size;
    }

    void merge_union(int one, int two) {
        int root_one = find_final_parent(one);
        int root_two = find_final_parent(two);
        if (root_one == root_two)
            return ;

        if (sub_size[root_one] > sub_size[root_two]) {
            parent_record[root_two] = root_one;
            sub_size[root_one] += sub_size[root_two];

        } else {
            parent_record[root_one] = root_two;
            sub_size[root_two] += sub_size[root_one]; 
        }

        num--;
    }

    int find_final_parent(int me) {
        while (parent_record[me] != me) {
            parent_record[me] = parent_record[parent_record[me]];
            me = parent_record[me];
        }

        return me;
    }

    int get_size() {
        return num;
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        union_set circle_union(M.size());

        for (int x = 0; x < M.size(); x++) {
            for (int y = 0; y < M[x].size(); y++) {
                if (M[x][y] == 1)
                    circle_union.merge_union(x, y);
            }
        }

        return circle_union.get_size();
    }
};