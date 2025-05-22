#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// Node structure for linked list implementations
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

// Custom Stack Implementation
template <typename T>
class CustomStack {
private:
    Node<T>* topNode;
    int stackSize;
    
public:
    CustomStack() : topNode(nullptr), stackSize(0) {}
    
    ~CustomStack() {
        while (!isEmpty()) {
            pop();
        }
    }
    
    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = topNode;
        topNode = newNode;
        stackSize++;
    }
    
    void pop() {
        if (isEmpty()) {
            cout << "Stack underflow!\n";
            return;
        }
        Node<T>* temp = topNode;
        topNode = topNode->next;
        delete temp;
        stackSize--;
    }
    
    T top() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty!");
        }
        return topNode->data;
    }
    
    bool isEmpty() {
        return topNode == nullptr;
    }
    
    int size() {
        return stackSize;
    }
    
    void display() {
        Node<T>* current = topNode;
        cout << "Stack (top to bottom): ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// Custom Queue Implementation
template <typename T>
class CustomQueue {
private:
    Node<T>* frontNode;
    Node<T>* rearNode;
    int queueSize;
    
public:
    CustomQueue() : frontNode(nullptr), rearNode(nullptr), queueSize(0) {}
    
    ~CustomQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        queueSize++;
    }
    
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue underflow!\n";
            return;
        }
        Node<T>* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
        queueSize--;
    }
    
    T front() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty!");
        }
        return frontNode->data;
    }
    
    T rear() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty!");
        }
        return rearNode->data;
    }
    
    bool isEmpty() {
        return frontNode == nullptr;
    }
    
    int size() {
        return queueSize;
    }
    
    void display() {
        Node<T>* current = frontNode;
        cout << "Queue (front to rear): ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// Enhanced Linked List Implementation
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int listSize;
    
public:
    LinkedList() : head(nullptr), listSize(0) {}
    
    ~LinkedList() {
        clear();
    }
    
    void insertAtBeginning(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        listSize++;
    }
    
    void insertAtEnd(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        listSize++;
    }
    
    bool deleteNode(T value) {
        if (head == nullptr) return false;
        
        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            listSize--;
            return true;
        }
        
        Node<T>* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }
        
        if (current->next != nullptr) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
            listSize--;
            return true;
        }
        
        return false;
    }
    
    bool search(T value) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        listSize = 0;
    }
    
    void display() {
        Node<T>* current = head;
        cout << "Linked List: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    int size() {
        return listSize;
    }
};

// Demonstration Functions
void demonstrateCustomStack() {
    cout << "\n=== CUSTOM STACK IMPLEMENTATION ===\n";
    CustomStack<int> myStack;
    
    cout << "Pushing elements 5, 10, 15...\n";
    myStack.push(5);
    myStack.push(10);
    myStack.push(15);
    myStack.display();
    
    cout << "Top element: " << myStack.top() << endl;
    cout << "Stack size: " << myStack.size() << endl;
    
    cout << "Popping two elements...\n";
    myStack.pop();
    myStack.pop();
    myStack.display();
    
    cout << "Is stack empty? " << (myStack.isEmpty() ? "Yes" : "No") << endl;
}

void demonstrateCustomQueue() {
    cout << "\n=== CUSTOM QUEUE IMPLEMENTATION ===\n";
    CustomQueue<string> myQueue;
    
    cout << "Enqueuing names...\n";
    myQueue.enqueue("Alice");
    myQueue.enqueue("Bob");
    myQueue.enqueue("Charlie");
    myQueue.display();
    
    cout << "Front: " << myQueue.front() << ", Rear: " << myQueue.rear() << endl;
    cout << "Queue size: " << myQueue.size() << endl;
    
    cout << "Dequeuing two elements...\n";
    myQueue.dequeue();
    myQueue.dequeue();
    myQueue.display();
    
    cout << "Is queue empty? " << (myQueue.isEmpty() ? "Yes" : "No") << endl;
}

void demonstrateEnhancedLinkedList() {
    cout << "\n=== ENHANCED LINKED LIST IMPLEMENTATION ===\n";
    LinkedList<double> myList;
    
    cout << "Inserting at beginning and end...\n";
    myList.insertAtBeginning(3.14);
    myList.insertAtEnd(2.71);
    myList.insertAtBeginning(1.61);
    myList.insertAtEnd(9.81);
    myList.display();
    
    cout << "Searching for 2.71: " << (myList.search(2.71) ? "Found" : "Not found") << endl;
    cout << "Searching for 5.0: " << (myList.search(5.0) ? "Found" : "Not found" << endl;
    
    cout << "Deleting 3.14...\n";
    myList.deleteNode(3.14);
    myList.display();
    
    cout << "Current size: " << myList.size() << endl;
    
    cout << "Clearing the list...\n";
    myList.clear();
    cout << "Size after clearing: " << myList.size() << endl;
}

void demonstrateSTLStackQueue() {
    cout << "\n=== STL STACK AND QUEUE DEMONSTRATION ===\n";
    
    // STL Stack
    stack<int> stlStack;
    cout << "STL Stack operations:\n";
    stlStack.push(100);
    stlStack.push(200);
    stlStack.push(300);
    cout << "Top: " << stlStack.top() << ", Size: " << stlStack.size() << endl;
    stlStack.pop();
    cout << "After pop, Top: " << stlStack.top() << endl;
    
    // STL Queue
    queue<char> stlQueue;
    cout << "\nSTL Queue operations:\n";
    stlQueue.push('A');
    stlQueue.push('B');
    stlQueue.push('C');
    cout << "Front: " << stlQueue.front() << ", Back: " << stlQueue.back() 
         << ", Size: " << stlQueue.size() << endl;
    stlQueue.pop();
    cout << "After dequeue, Front: " << stlQueue.front() << endl;
}

int main() {
    // Demonstrate all implementations
    demonstrateCustomStack();
    demonstrateCustomQueue();
    demonstrateEnhancedLinkedList();
    demonstrateSTLStackQueue();
    
    return 0;
}