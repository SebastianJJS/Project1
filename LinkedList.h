LinkedList.h

@@ -0,0 +1,392 @@
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class LinkedList {
public:
    class Node {
    public:
        T data;
        Node* next;
        Node* prev;

        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };

private:
    Node* head;
    Node* tail;
    int nodeCount;

public:
    LinkedList() : head(nullptr), tail(nullptr), nodeCount(0) {}

    ~LinkedList() {
        clear();
    }

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), nodeCount(0) {
        Node* current = other.head;
        while (current != nullptr) {
            AddTail(current->data);
            current = current->next;
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();

            Node* current = other.head;
            while (current != nullptr) {
                AddTail(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    bool operator==(const LinkedList& other) const {
        if (nodeCount != other.nodeCount) {
            return false;
        }
        Node* current1 = head;
        Node* current2 = other.head;
        while (current1 != nullptr) {
            if (current1->data != current2->data) {
                return false;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
        return current1 == nullptr && current2 == nullptr;
    }

    T& operator[](int index) {
        return GetNode(index)->data;
    }

    const T& operator[](int index) const {
        return GetNode(index)->data;
    }

    void AddHead(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        nodeCount++;
    }

    void AddTail(const T& value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        nodeCount++;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        nodeCount = 0;
    }

    void AddNodesHead(const T* values, int count) {
        for (int i = count - 1; i >= 0; --i) {
            AddHead(values[i]);
        }
    }

    void AddNodesTail(const T* values, int count) {
        for (int i = 0; i < count; ++i) {
            AddTail(values[i]);
        }
    }

    int NodeCount() const {
        return nodeCount;
    }

    void PrintForward() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void PrintReverse() const {
        Node* current = tail;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }

    T GetHeadData() const {
        if (head != nullptr) {
            return head->data;
        }
        throw std::runtime_error("Empty list");
    }

    Node* GetNode(int index) {
        if (index < 0 || index >= nodeCount) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    const Node* GetNode(int index) const {
        if (index < 0 || index >= nodeCount) {
            throw std::out_of_range("Index out of range");
        }
        const Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    Node* Find(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    const Node* Find(const T& value) const {
        const Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    int FindNumberNodes(const T& value) {
        Node* current = head;
        int count = 0;
        while (current != nullptr) {
            if (current->data == value) {
                count++;
            }
            current = current->next;
        }
        return count;
    }


    void FindAll(const T& value) {
        Node* current = head;
        int count = 0;
        while (current != nullptr) {
            if (current->data == value) {
                count++;
                std::cout << "Node #" << count << ":\n";
                std::cout << "Value: " << current->data << std::endl;

                std::cout << "Prev value: ";
                if (current->prev != nullptr) {
                    std::cout << current->prev->data;
                } else {
                    std::cout << "nullptr";
                }

                std::cout << "\nNext value: ";
                if (current->next != nullptr) {
                    std::cout << current->next->data;
                } else {
                    std::cout << "nullptr";
                }
                std::cout << std::endl;
            }
            current = current->next;
        }
    }

    void InsertBefore(Node* node, const T& value) {
        if (!node) return;
        Node* newNode = new Node(value);
        newNode->next = node;
        newNode->prev = node->prev;

        if (node->prev) {
            node->prev->next = newNode;
        } else {
            head = newNode;
        }
        node->prev = newNode;
        nodeCount++;
    }

    void InsertAfter(Node* node, const T& value) {
        if (!node) return;
        Node* newNode = new Node(value);
        newNode->prev = node;
        newNode->next = node->next;

        if (node->next) {
            node->next->prev = newNode;
        } else {
            tail = newNode;
        }
        node->next = newNode;
        nodeCount++;
    }

    void InsertAt(const T& value, int index) {
        if (index < 0 || index > nodeCount) {
            throw std::out_of_range("Index out pyhof range");
        }
        if (index == 0) {
            AddHead(value);
            return;
        }
        if (index == nodeCount) {
            AddTail(value);
            return;
        }
        Node* current = GetNode(index);
        InsertBefore(current, value);
    }

    bool RemoveHead() {
        if (head == nullptr) return false;

        Node* toDelete = head;
        head = head->next;
        delete toDelete;
        nodeCount--;

        if (nodeCount == 0) tail = nullptr;

        return true;
    }

    bool RemoveTail() {
        if (tail == nullptr) return false;

        if (head == tail) {
            delete tail;
            head = tail = nullptr;
        } else {
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        nodeCount--;

        return true;
    }

    bool RemoveAt(int index) {
        if (index < 0 || index >= nodeCount) return false;

        if (index == 0) return RemoveHead();

        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node* toDelete = current->next;
        current->next = toDelete->next;
        if (toDelete == tail) tail = current;
        delete toDelete;
        nodeCount--;

        return true;
    }

    int Remove(const T& value) {
        int removedCount = 0;
        Node* current = head;
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->data == value) {
                Node* toDelete = current;
                if (prev != nullptr) prev->next = current->next;
                else head = current->next;

                if (current == tail) tail = prev;
                current = current->next;

                delete toDelete;
                nodeCount--;
                removedCount++;
            } else {
                prev = current;
                current = current->next;
            }
        }
        return removedCount;
    }

    void Clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = tail = nullptr;
        nodeCount = 0;
    }

    void PrintForwardRecursive(Node* node) const {
        if (node == nullptr) return;
        std::cout << node->data << std::endl;
        PrintForwardRecursive(node->next);
    }

    void PrintReverseRecursive(Node* node) const {
        if (node == nullptr) return;
        std::cout << node->data << std::endl;
        PrintReverseRecursive(node->prev);
    }

    T* Head() const {
        return head ? &head->data : nullptr;
    }

    T* Tail() const {
        return tail ? &tail->data : nullptr;
    }
};

#endif
