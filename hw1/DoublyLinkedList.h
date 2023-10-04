#include <iostream>
#include <vector>

struct Node {
    Node *next;
    Node *previous;
    int data;

    Node() : data(0), next(nullptr), previous(nullptr) {}

    Node(Node *next, Node *prev, int data) : next(next), previous(prev), data(data) {}

    explicit Node(int value) : data(value), next(nullptr), previous(nullptr) {}
};

class DoublyLinkedList {
public:
    Node *head;
    Node *tail;

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    DoublyLinkedList(const DoublyLinkedList &other) {
        if (other.head == nullptr) {
            head = nullptr;
            tail = nullptr;
            return;
        }

        head = new Node(other.head->data);
        Node *current = head;
        auto temp = other.head;
        temp = temp->next;

        while (temp != nullptr) {
            Node *newNode = new Node(temp->data);
            current->next = newNode;
            current = current->next;
            temp = temp->next;
        }

        tail = current;
    }

    explicit DoublyLinkedList(std::vector<int> &array) {
        if (array.empty()) {
            head = nullptr;
            tail = nullptr;
            return;
        } else if (array.size() == 1) {
            Node *newNode = new Node(array[0]);
            head = newNode;
            tail = head;
            return;
        }

        head = new Node(array.front());
        Node *current = head;

        for (int i = 1; i < array.size(); i++) {
            Node *newNode = new Node(array[i]);
            current->next = newNode;
            current = current->next;
        }

        tail = current;
    }

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    static void LinkAfter(Node *target, Node *after) {
        auto target_next = target->next;
        target->next = after;
        after->next = target_next;
        after->previous = target;
        target_next->previous = after;
    }

    void pushBack(int data) {
        auto newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            tail = head;
            return;
        }

        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
    }

    void pushFront(int data) {
        auto newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            tail = head;
            return;
        }

        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }

    static void insert(Node *target, int data) {
        if (target == nullptr || target->next == nullptr) {
            throw std::runtime_error("Wrong position for insertion!");
        }
        auto after = new Node(data);
        auto target_next = target->next;
        target->next = after;
        after->next = target_next;
        after->previous = target;
        target_next->previous = after;
    }

    void popFront() {
        if (head == nullptr) {
            throw std::runtime_error("Deletion error!");
        }
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->previous = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
    }

    void popBack() {
        if (head == nullptr) {
            throw std::runtime_error("Deletion error!”");
        }
        Node *temp = tail;
        tail = tail->previous;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
    }

    void pop(Node *node) {
        if(node == nullptr) {
            throw std::runtime_error("Wrong position for deletion!");
        }

        bool flag = false;
        Node* current = head;
        while (current != nullptr) {
            if (node == current) {
                flag = true;
            }
            current = current->next;
        }

        if (!flag) {
            throw std::runtime_error("Wrong position for deletion!");
        }

        if (node == tail) {
            popBack();
            return;
        } else if (node == head) {
            popFront();
            return;
        }
        node->previous->next = node->next;
        node->next->previous = node->previous;
        node->previous = nullptr;
        node->next = nullptr;
        delete node;
    }

    void erase() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    void reverse() {
        Node* current = head;
        Node* temp = nullptr;

        while (current != nullptr) {
            Node* next = current->next;
            current->next = temp;
            temp = current;
            current = next;
        }

        temp = head;
        head = tail;
        tail = temp;
    }

    void removeDuplicates() {

    }

    void replace(int oldElem, int newElem) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == oldElem) {
                current->data = newElem;
            }
            current = current->next;
        }
    }
};
