class MinStack {
private:
    stack<int> data_stack;
    stack<int> min_stack;

public:
    /** initialize your data structure here. */
    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int x) {
        data_stack.push(x);
        if (x < min_stack.top()) {
            min_stack.push(x);

        } else {
            min_stack.push(min_stack.top());
        }
    }
    
    void pop() {
        if (!data_stack.empty()) {
            data_stack.pop();
            min_stack.pop();
        }
    }
    
    int top() {
        return data_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */


class MinStack {
private:
    /* first for data, second for min_number */
    stack<pair<int, int>> min_stack;

public:
    /** initialize your data structure here. */    
    void push(int x) {
        int min;
        if (min_stack.empty()) {
            min = x;
        } else {
            min = std::min(min_stack.top().second, x);
        }

        min_stack.push({x, min});
    }
    
    void pop() {
        if (!min_stack.empty())
            min_stack.pop();
    }
    
    int top() {
        if (!min_stack.empty())
            return min_stack.top().first;
        
        return INT_MIN;
    }
    
    int getMin() {
        if (!min_stack.empty())
            return min_stack.top().second;
        
        return INT_MIN;        
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */



