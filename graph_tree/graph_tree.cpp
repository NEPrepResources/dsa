#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// ====================== TREE IMPLEMENTATIONS ======================

// Binary Tree Node
template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

// Binary Search Tree Implementation
template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;
    
    TreeNode<T>* insertHelper(TreeNode<T>* node, T value) {
        if (node == nullptr) {
            return new TreeNode<T>(value);
        }
        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        }
        return node;
    }
    
    TreeNode<T>* findMin(TreeNode<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    TreeNode<T>* deleteHelper(TreeNode<T>* node, T value) {
        if (node == nullptr) return nullptr;
        
        if (value < node->data) {
            node->left = deleteHelper(node->left, value);
        } else if (value > node->data) {
            node->right = deleteHelper(node->right, value);
        } else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                TreeNode<T>* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }
            
            // Node with two children
            TreeNode<T>* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteHelper(node->right, temp->data);
        }
        return node;
    }
    
    void inorderHelper(TreeNode<T>* node) {
        if (node == nullptr) return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }
    
    void preorderHelper(TreeNode<T>* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }
    
    void postorderHelper(TreeNode<T>* node) {
        if (node == nullptr) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->data << " ";
    }
    
    void levelOrderHelper(TreeNode<T>* node) {
        if (node == nullptr) return;
        
        queue<TreeNode<T>*> q;
        q.push(node);
        
        while (!q.empty()) {
            TreeNode<T>* current = q.front();
            q.pop();
            cout << current->data << " ";
            
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }
    
public:
    BinarySearchTree() : root(nullptr) {}
    
    void insert(T value) {
        root = insertHelper(root, value);
    }
    
    void remove(T value) {
        root = deleteHelper(root, value);
    }
    
    bool search(T value) {
        TreeNode<T>* current = root;
        while (current != nullptr) {
            if (value == current->data) {
                return true;
            } else if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }
    
    void inorderTraversal() {
        cout << "Inorder: ";
        inorderHelper(root);
        cout << endl;
    }
    
    void preorderTraversal() {
        cout << "Preorder: ";
        preorderHelper(root);
        cout << endl;
    }
    
    void postorderTraversal() {
        cout << "Postorder: ";
        postorderHelper(root);
        cout << endl;
    }
    
    void levelOrderTraversal() {
        cout << "Level Order: ";
        levelOrderHelper(root);
        cout << endl;
    }
};

// ====================== GRAPH IMPLEMENTATIONS ======================

// Graph implementation using adjacency list
class Graph {
private:
    unordered_map<int, vector<int>> adjList;
    bool isDirected;
    
public:
    Graph(bool directed = false) : isDirected(directed) {}
    
    void addVertex(int vertex) {
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = vector<int>();
        }
    }
    
    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        if (!isDirected) {
            adjList[dest].push_back(src);
        } else {
            // For directed graphs, make sure destination exists
            if (adjList.find(dest) == adjList.end()) {
                adjList[dest] = vector<int>();
            }
        }
    }
    
    void printGraph() {
        for (const auto& pair : adjList) {
            cout << "Vertex " << pair.first << " -> ";
            for (int neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
    
    void BFS(int startVertex) {
        unordered_set<int> visited;
        queue<int> q;
        
        q.push(startVertex);
        visited.insert(startVertex);
        
        cout << "BFS starting from " << startVertex << ": ";
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";
            
            for (int neighbor : adjList[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
    
    void DFS(int startVertex) {
        unordered_set<int> visited;
        stack<int> s;
        
        s.push(startVertex);
        visited.insert(startVertex);
        
        cout << "DFS starting from " << startVertex << ": ";
        
        while (!s.empty()) {
            int current = s.top();
            s.pop();
            cout << current << " ";
            
            // To match recursive DFS order, we push neighbors in reverse order
            for (auto it = adjList[current].rbegin(); it != adjList[current].rend(); ++it) {
                if (visited.find(*it) == visited.end()) {
                    visited.insert(*it);
                    s.push(*it);
                }
            }
        }
        cout << endl;
    }
    
    void recursiveDFSHelper(int vertex, unordered_set<int>& visited) {
        visited.insert(vertex);
        cout << vertex << " ";
        
        for (int neighbor : adjList[vertex]) {
            if (visited.find(neighbor) == visited.end()) {
                recursiveDFSHelper(neighbor, visited);
            }
        }
    }
    
    void recursiveDFS(int startVertex) {
        unordered_set<int> visited;
        cout << "Recursive DFS starting from " << startVertex << ": ";
        recursiveDFSHelper(startVertex, visited);
        cout << endl;
    }
};

// ====================== DEMONSTRATION FUNCTIONS ======================

void demonstrateBinarySearchTree() {
    cout << "\n=== BINARY SEARCH TREE DEMONSTRATION ===\n";
    
    BinarySearchTree<int> bst;
    
    cout << "Inserting values: 50, 30, 70, 20, 40, 60, 80\n";
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    cout << "\nTree Traversals:\n";
    bst.inorderTraversal();
    bst.preorderTraversal();
    bst.postorderTraversal();
    bst.levelOrderTraversal();
    
    cout << "\nSearch operations:\n";
    cout << "40 in tree? " << (bst.search(40) ? "Yes" : "No") << endl;
    cout << "90 in tree? " << (bst.search(90) ? "Yes" : "No") << endl;
    
    cout << "\nDeleting 20 (leaf node) and 30 (node with one child)\n";
    bst.remove(20);
    bst.remove(30);
    bst.inorderTraversal();
    
    cout << "\nDeleting 50 (root node with two children)\n";
    bst.remove(50);
    bst.inorderTraversal();
}

void demonstrateGraph() {
    cout << "\n=== GRAPH DEMONSTRATION ===\n";
    
    // Undirected graph
    cout << "\nUndirected Graph:\n";
    Graph undirectedGraph(false);
    
    cout << "Adding vertices 0-4 and edges (0-1), (0-2), (1-2), (1-3), (2-4)\n";
    for (int i = 0; i <= 4; ++i) {
        undirectedGraph.addVertex(i);
    }
    undirectedGraph.addEdge(0, 1);
    undirectedGraph.addEdge(0, 2);
    undirectedGraph.addEdge(1, 2);
    undirectedGraph.addEdge(1, 3);
    undirectedGraph.addEdge(2, 4);
    
    cout << "\nAdjacency List:\n";
    undirectedGraph.printGraph();
    
    cout << "\nTraversals from vertex 0:\n";
    undirectedGraph.BFS(0);
    undirectedGraph.DFS(0);
    undirectedGraph.recursiveDFS(0);
    
    // Directed graph
    cout << "\nDirected Graph:\n";
    Graph directedGraph(true);
    
    cout << "Adding vertices 0-4 and edges (0-1), (0-2), (1-3), (2-1), (3-2), (3-4)\n";
    for (int i = 0; i <= 4; ++i) {
        directedGraph.addVertex(i);
    }
    directedGraph.addEdge(0, 1);
    directedGraph.addEdge(0, 2);
    directedGraph.addEdge(1, 3);
    directedGraph.addEdge(2, 1);
    directedGraph.addEdge(3, 2);
    directedGraph.addEdge(3, 4);
    
    cout << "\nAdjacency List:\n";
    directedGraph.printGraph();
    
    cout << "\nTraversals from vertex 0:\n";
    directedGraph.BFS(0);
    directedGraph.DFS(0);
    directedGraph.recursiveDFS(0);
}

int main() {
    demonstrateBinarySearchTree();
    demonstrateGraph();
    
    return 0;
}