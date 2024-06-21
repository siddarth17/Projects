#include <vector>
#include <stdexcept>
#include <iostream>


template <class T>
class MinHeap {
public:
    MinHeap(int d) : d(d) {}

    void add(T item, int priority) {
        data.push_back({item, priority});
        // Adjusting minheap by trickling up, keeping data at correct value
        trickleup(data.size() - 1);
    }

    const T& peek() const {
        if (data.empty()) {
            throw std::runtime_error("Empty Heap");
        }
        return data[0].item;
    }

    void remove() {
        if (isEmpty()) {
            throw std::runtime_error("Empty Heap");
        }
        std::swap(data[0], data.back());
        data.pop_back();
        if (!isEmpty()) {
            // Adjusting heap by trickling down so top value is at correct position to maintain minheap property
            trickledown(0);
        }
    }

    bool isEmpty() const {
        return data.empty();
    }


private:
    struct Node {
        T item;
        int priority;
        
        // Operator overloading for comparing variables, especially when there is a draw so can help recognise alphabetically smaller strings
        bool operator<(const Node& other) const {
            if(priority == other.priority) {
                return item < other.item;
            }
            return priority < other.priority;
        }

    };

    int d;
    std::vector<Node> data;

    void trickleup(int idx) {
        int parent;
        // Continously comparing parent and child values
        while (idx >= 0) {
            parent = (idx - 1) / d;
            if(data[idx] < data[parent]) {
                std::swap(data[idx], data[parent]);
                idx = parent;
            } 
            else {
                break; 
            }
        }
    }
    void trickledown(int idx) {
        int child;
        // Keeps comparing parent to minchild
        while (true) {
            child = minchild(idx);
            if (child == -1 || !(data[child] < data[idx])) {
                break;
            }
            std::swap(data[idx], data[child]);
            idx = child;
        }
    }

    int minchild(int idx) {
        size_t child;
        int minIndex = -1;
        int minPriority = 999999999;
        
        // Loops through and compares priorities
        for (int i = 1; i <= d; ++i) {
            child = d * idx + i;
            if (child < data.size() && data[child].priority < minPriority) {
                minPriority = data[child].priority;
                minIndex = child;
            }
        }
        return minIndex;
    }
};







