class MyCircularDeque {
private:
    vector<int> data;
    int front;
    int rear;
    int cnt;

public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) : data(k), front(0), rear(0), cnt(0) { }
    
    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if (cnt == data.size())
            return false;

        front = (front + data.size() - 1) % data.size();
        data[front] = value;
        cnt++;
        return true;
    }
    
    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if (cnt == data.size())
            return false;

        data[rear] = value;
        rear = (rear + 1) % data.size();
        cnt++;
        return true;
    }
    
    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if (cnt == 0)
            return false;

        front = (front + 1) % data.size();
        cnt--;
        return true;
    }
    
    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if (cnt == 0)
            return false;

        rear = (rear + data.size() - 1) % data.size();
        cnt--;
        return true;
    }
    
    /** Get the front item from the deque. */
    int getFront() {
        if (isEmpty())
            return -1;
            
        return data[front];
    }
    
    /** Get the last item from the deque. */
    int getRear() {
        if (isEmpty())
            return -1;

        return data[(rear + data.size() - 1) % data.size()];
    }
    
    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        if (cnt == 0)
            return true;

        return false;
    }
    
    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        if (cnt == data.size())
            return true;

        return false;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */


// 还有一种 额外多申请一个空白坑位 的做法，可以作为补充。不需要使用到 cnt， 如下：

// 判别队列为空的条件是：front == rear;
// 判别队列为满的条件是：(rear + 1) % capacity == front;。可以这样理解，当 rear 循环到数组的前面，要从后面追上 front，还差一格的时候，判定队列为满。

// 这里巧妙的地方在于，这个空白的多余坑位是会跟着 rear 一起走的 ！所以在 front % data.szie() 的时候，其实也同时
// 把这个多余的坑位给跳过去了

class MyCircularDeque {
private:
    vector<int> data;
    int front;
    int rear;

public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) : data(k + 1), front(0), rear(0) { }
    
    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if (isFull())
            return false;
        
        front = (front + data.size() - 1) % data.size();
        data[front] = value;
        return true;
    }
    
    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if (isFull())
            return false;

        data[rear] = value;
        rear = (rear + 1) % data.size();
        return true;
    }
    
    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if (isEmpty())
            return false;
        
        front = (front + 1) % data.size();
        return true;
    }
    
    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if (isEmpty())
            return false;

        rear = (rear + data.size() - 1) % data.size();
        return true;
    }
    
    /** Get the front item from the deque. */
    int getFront() {
        if (isEmpty())
            return -1;

        return data[front];
    }
    
    /** Get the last item from the deque. */
    int getRear() {
        if (isEmpty())
            return -1;

        return data[(rear + data.size() - 1) % data.size()];
    }
    
    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return front == rear;
    }
    
    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return (rear + 1) % data.size() == front;
    }
};


