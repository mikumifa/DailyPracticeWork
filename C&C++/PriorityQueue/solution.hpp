
#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include <stdexcept>
#include "node.hpp"
template<typename T>
class PriorityQueue {
private:
    Node<T> *head_;
    Node<T> *tail_;
public:

    PriorityQueue() : head_(nullptr), tail_(nullptr) {}

    PriorityQueue(const PriorityQueue<T> &rhs) = delete;

    PriorityQueue<T> &operator=(const PriorityQueue<T> &rhs) = delete;

// 析构函数
    ~PriorityQueue() {
        Node<T> *p = head_;
        while (p != nullptr) {
            Node<T> *tmp = p;
            p = p->next;
            delete tmp;
        }
        head_ = nullptr;
        tail_ = nullptr;
    }
    void Enqueue(const T& data) {
        Node<T> *newNode = new  Node<T>(data);

        if (head_ == nullptr) {
            head_ = newNode;
            tail_ = newNode;
            return;
        }

        Node<T> *p = head_;
        Node<T> *prev = nullptr;
        while (p != nullptr && p->data < data) {
            prev = p;
            p = p->next;
        }
        if (p == head_) {
            newNode->next = head_;
            head_ = newNode;
        } else if (p == nullptr) {
            tail_->next = newNode;
            tail_ = newNode;
        } else {
            prev->next = newNode;
            newNode->next = p;
        }
    }
    T Dequeue() {
        if (head_ == nullptr) {
            throw std::runtime_error("the Dequeue() is nullptr");
        }

        T data = head_->data;
        Node<T> *p = head_;
        head_ = head_->next;
        delete p;

        if (head_ == nullptr) {
            tail_ = nullptr;
        }

        return data;
    }
};

#endif
