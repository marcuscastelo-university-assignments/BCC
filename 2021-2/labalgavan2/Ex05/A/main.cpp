#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}

    //Returns the pointer to the node that will replace the current node's position in the tree
    TreeNode *insert(int val) {
        if (val > this->val) {
            TreeNode *newParent = new TreeNode(val);
            newParent->left = this;
            return newParent;
        } else {
            if (this->right == nullptr) {
                this->right = new TreeNode(val);
                return this;
            } else {
                this->right = this->right->insert(val);
                return this;
            }
        }
    }

    //Returns the depth of the found value
    int find(int val, int depth = 0) {
        if (val == this->val) {
            return depth;
        }

        int depthInLeft = -1;
        if (this->left != nullptr) {
            depthInLeft = this->left->find(val, depth + 1);
        }

        int depthInRight = -1;
        if (this->right != nullptr) {
            depthInRight = this->right->find(val, depth + 1);
        }

        return max(depthInLeft, depthInRight);
    }

    void visitInfix() {
        if (this->left != nullptr) {
            this->left->visitInfix();
        }

        cout << this->val << " ";

        if (this->right != nullptr) {
            this->right->visitInfix();
        }
    }
};

struct Tree {
    unordered_map<int, int> depthCache = {};
    TreeNode *root = nullptr;

    void insert(int val) {
        if (root == nullptr) {
            root = new TreeNode(val);
            return;
        }

        this->root = root->insert(val);
    }

    int getDepth(int val) { 
        auto findIt = depthCache.find(val);

        if (findIt != depthCache.end()) {
            return findIt->second;
        }

        if (root == nullptr) {
            return -1;
        }

        return depthCache[val] = ( root->find(val) );
    }
};

void testcase() {
    Tree tree;
    int n;
    cin >> n;

    vector<int> permutation;
    permutation.reserve(n);
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        tree.insert(val);
        permutation.push_back(val);
    }

    // tree.root->visitInfix();
    // cout << endl;

    for (auto val: permutation) {
        cout << tree.getDepth(val) << " ";
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while (t-->0)
        testcase();
}