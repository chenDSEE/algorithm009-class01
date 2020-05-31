class Solution {
private:
    vector<int> data;
public:
    int nthUglyNumber(int n) {
        if (data.size() >= n) {
            return data[n];
        }

        int cnt = 0;
        int target = 0;
        while (cnt != n) {
            target++;
            int tmp = target;

            while (tmp % 5 == 0) {
                tmp /= 5;
            }

            while (tmp % 3 == 0) {
                tmp /= 3;
            }

            while (tmp % 2 == 0) {
                tmp /= 2;
            }

            if (tmp == 1) {
                cnt++;
                data.push_back(target);
            }
        }

        return target;
    }
};

/**
 * 既然一个个去找是很慢的，毕竟你一个个累加的去找（很多不符合的，白费力气），然后每一个还要去检查是不是满足条件，
 * 这种 主动生成 然后进行判断的方式自然是浪费了很多时间（生成不符合要求的数，并对其进行遍历检查）
 *
 * 那样的话，为了不直接生成丑数呢？
 * 直接生成出是丑数的数字，剩下费时间的事情也就是怎么生成到 n 个丑数了
 * 既然告诉了你，丑数的构成，那我们直接那最最小的丑数生成新的丑数就完事了
 *
 * 怎么生成丑数？2 * 2，2 * 3, 2 * 5, 它们必然是丑数
 */


/**
 * 0. 为什么要用堆？
 *    不然你怎么在动态生成的过程中最迅速的拿到最小的那个丑数？
 *
 * 1. 为什么要用最小堆？
 *    因为只有从最小的丑数，乘上 2，3，5 才能够确保生成出来的是丑数，而且要把新丑数放进堆里面，
 *    以便下次找到新的材料生成新的丑数。
 *    而且用完了 top 元素之后，别忘了把它扔掉，新生成的丑数已经继承了它的意志，就不需要它本人了。
 * 
 * 2. 为什么还要引入 set ？
 *    因为你没办法控制生成绝对不重复的新丑数，所以需要 set 来进行去重处理
 */
class Solution {
private:
    vector<int> data;
public:
    int nthUglyNumber(int n) {
        set<long> num_set;
        priority_queue<long, vector<long>, greater<long>> pq;
        long answer = 0;

        num_set.insert(1);
        pq.push(1);
        for (int i = 1; i <= n; i++) {
            long num = pq.top();
            if (num_set.count(num * 2) == 0) {
                num_set.insert(num * 2);
                pq.push(num * 2);
            }

            if (num_set.count(num * 3) == 0) {
                num_set.insert(num * 3);
                pq.push(num * 3);
            }

            if (num_set.count(num * 5) == 0) {
                num_set.insert(num * 5);
                pq.push(num * 5);
            }

            answer = pq.top();
            pq.pop();
        } 

        return answer;
    }
};