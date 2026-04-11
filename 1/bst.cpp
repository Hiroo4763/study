#include <cstdio>

// 이진 탐색 트리의 노드 구조체 정의
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : value(x), left(NULL), right(NULL) {}
};

// 이진 탐색 트리 클래스 정의
class BinarySearchTree {
public:
    TreeNode* root;

    BinarySearchTree() : root(NULL) {}


    void insert(int x) {
        TreeNode* node = root;
        TreeNode* parent = NULL;

        while (node != NULL) {
            parent = node;
            if (node->value > x) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }

        if (parent == NULL) {
            root = new TreeNode(x);
        }

        else if (parent->value > x) {
            parent->left = node;
        }

        else {
            parent->right = node;
        }

    }

    TreeNode* deleteNode(TreeNode* node, int x) {
        if (node == NULL) return node;

        if (node->value > x) {
            node = deleteNode(node->left, x);
        }
        else if (node->value < x) {
            node = deleteNode(node->right, x);
        }
        else {
            if (node->value == x) {
                return node;
            }

            else if (node->left == NULL) {
                
            }
        }

        
    }
    TreeNode* findMin(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    void inorderTraversal(TreeNode* node) {
        if (node == NULL) return;
        inorderTraversal(node->left);
        printf("%d ", node->value);
        inorderTraversal(node->right);
    }

    void display() {
        inorderTraversal(root);
        printf("\n");
    }

    void remove(int x) {
        root = deleteNode(root, x);
    }
};

int main() {
    BinarySearchTree bst;
    int insertCount, deleteCount;

    // 삽입할 원소의 수와 삭제할 원소의 수 입력
    scanf("%d %d", &insertCount, &deleteCount);

    // 삽입할 원소 입력
    for (int i = 0; i < insertCount; ++i) {
        int value;
        scanf("%d", &value);
        bst.insert(value);
    }

    // 삭제할 원소 입력
    for (int i = 0; i < deleteCount; ++i) {
        int value;
        scanf("%d", &value);
        bst.remove(value);
    }

    // 최종 트리 상태 출력
    bst.display();

    return 0;
}

/*
class BinarySearchTree {
public:
    TreeNode* root;

    BinarySearchTree() : root(NULL) {}


    void insert(int x) {
        TreeNode* node = root;
        TreeNode* parent = NULL;

        while (node != NULL) {
            parent = node;
            if (node->value > x)
                node = node->left;
            else
                node = node->right;
        }

        if (parent == NULL) {
            root = new TreeNode(x);
        }
        else if (parent->value > x) {
            parent->left = new TreeNode(x);
        }
        else {
            // 여기에 프로그램을 작성하세요
        }
    }

    TreeNode* deleteNode(TreeNode* node, int x) {
        if (node == NULL) return node;

        if (x < node->value) {
            node->left = deleteNode(node->left, x);
        }
        else if (x > node->value) {
            node->right = deleteNode(node->right, x);
        }
        else {
            if (node->left == NULL) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == NULL) {
                // 여기에 프로그램을 작성하세요
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* succ = findMin(node->right);
            node->value = succ->value;
            node->right = deleteNode(node->right, succ->value);
        }
        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    void inorderTraversal(TreeNode* node) {
        if (node == NULL) return;
        inorderTraversal(node->left);
        printf("%d ", node->value);
        inorderTraversal(node->right);
    }

    void display() {
        inorderTraversal(root);
        printf("\n");
    }

    void remove(int x) {
        root = deleteNode(root, x);
    }
};

*/
