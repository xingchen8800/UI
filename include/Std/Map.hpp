#ifndef __STD_MAP_HPP_
#define __STD_MAP_HPP_

//Code by GPT-4
namespace xc {
    namespace Std {
        template <typename K, typename V>
        class Map {
        private:
            struct Node {
                K key;  // 键
                V value;  // 值
                Node* left;  // 左子节点
                Node* right;  // 右子节点

                Node(K key, V value) : key(key), value(value), left(nullptr), right(nullptr) {}
            };

            Node* root;  // 根节点

            // 插入键值对的辅助函数
            Node* insert(Node* node, K key, V value) {
                if (node == nullptr) {
                    return new Node(key, value);
                }
                if (key < node->key) {
                    node->left = insert(node->left, key, value);
                } else if (key > node->key) {
                    node->right = insert(node->right, key, value);
                } else {
                    node->value = value;  // 键已经存在，更新值
                }
                return node;
            }

            // 获取键对应的值的辅助函数
            V get(Node* node, K key) const {
                if(node == nullptr) throw -1;
                if (key < node->key) {
                    return get(node->left, key);
                } else if (key > node->key) {
                    return get(node->right, key);
                } else {
                    return node->value;
                }
            }

            // 删除键值对的辅助函数
            Node* remove(Node* node, K key) {
                if (node == nullptr) {
                    return nullptr;
                }
                if (key < node->key) {
                    node->left = remove(node->left, key);
                } else if (key > node->key) {
                    node->right = remove(node->right, key);
                } else {
                    if (node->left == nullptr) {
                        Node* temp = node->right;
                        delete node;
                        return temp;
                    } else if (node->right == nullptr) {
                        Node* temp = node->left;
                        delete node;
                        return temp;
                    } else {
                        Node* temp = node->right;
                        while (temp->left != nullptr) {
                            temp = temp->left;
                        }
                        node->key = temp->key;
                        node->value = temp->value;
                        node->right = remove(node->right, temp->key);
                    }
                }
                return node;
            }

        public:
            // 构造函数
            Map() : root(nullptr) {}

            // 插入键值对
            void insert(K key, V value) {
                root = insert(root, key, value);
            }

            // 获取键对应的值
            V get(K key) const {
                return get(root, key);
            }

            // 删除键值对
            void remove(K key) {
                root = remove(root, key);
            }
        };
    }
}
#endif