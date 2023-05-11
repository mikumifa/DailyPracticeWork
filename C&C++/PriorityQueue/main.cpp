#include <iostream>
#include <cassert>
#include <random>
#include "solution.hpp"
using namespace std;

template<typename T>
class PriorityQueueTest {
public:
    void runTests() {
        testEnqueueDequeue();
        testPriorityOrder();
        testRandom();
    }

private:
    void testRandom() {
        PriorityQueue<T> q;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        // Enqueue some random elements
        for (int i = 0; i < 1000; i++) {
            q.Enqueue(dis(gen));
        }

        T prev = q.Dequeue();
        try {
            while (true) {
                T current = q.Dequeue();
                assert(current >= prev);
                prev = current;
            }
        }
        catch (exception e) {

        }

    }
    void testEnqueueDequeue() {
        PriorityQueue<T> q;

        // Enqueue some elements
        q.Enqueue(3);
        q.Enqueue(1);
        q.Enqueue(4);


        // Dequeue the elements and check their order
        assert(q.Dequeue() == 1);
        assert(q.Dequeue() == 3);
        assert(q.Dequeue() == 4);

    }

    void testPriorityOrder() {
        PriorityQueue<T> q;

        // Enqueue some elements with different priorities
        q.Enqueue(1);
        q.Enqueue(4);
        q.Enqueue(2);
        q.Enqueue(4);
        q.Enqueue(3);


        // Dequeue the elements and check their order
        assert(q.Dequeue() == 1);
        assert(q.Dequeue() == 2);
        assert(q.Dequeue() == 3);
        assert(q.Dequeue() == 4);
        assert(q.Dequeue() == 4);

    }
};

int main() {
    PriorityQueueTest<int> test;
    test.runTests();

    cout << "All tests passed!" << endl;

    return 0;
}
