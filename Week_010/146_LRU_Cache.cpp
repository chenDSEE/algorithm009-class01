// STL version
class LRUCache {
private:
    // store value and it's order(by list's order); store key to erase key in map
    // key -> value
    list<pair<int, int>> val_list;

    // find value by key in O(1), stort iterator to remove ONE in O(1)
    unordered_map<int, list<pair<int, int>>::iterator> val_map;

    // to record list's size
    int max_size;

public:
    LRUCache(int capacity) : max_size(capacity) { }
    
    int get(int key) {
        if (val_map.find(key) == val_map.end())
            return -1;

        // update list order
        pair<int, int> kv = *val_map[key];  // this hold node should move to val_lis.begin()

        val_list.erase(val_map[key]);
        val_list.push_front(kv);

        val_map[key] = val_list.begin();

        return kv.second;
    }
    
    // if key in list ==> update order
    // else ==> insert into list
    //     if list == size  ==> remove least recently use
    //     else ==> insert directly
    void put(int key, int value) {
        if (val_map.find(key) == val_map.end()) {
            if (val_list.size() >= max_size) {
                val_map.erase(val_list.back().first);
                val_list.pop_back();
            }

        } else {
            val_list.erase(val_map[key]);
        }

        val_list.push_front(make_pair(key, value));
        val_map[key] = val_list.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// pointer version

