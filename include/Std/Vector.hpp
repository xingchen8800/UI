#ifndef __STD_VECTOR_HPP_
#define __STD_VECTOR_HPP_
#include "types.h"

//Code by GPT-4

namespace xc {
    namespace Std {
    template<typename T>
    class Vector {
    private:
        T* arr;  // 动态数组
        uint64_t capacity;  // 数组的容量
        uint64_t current;  // 当前数组的大小

    public:
        // 构造函数
        Vector() {
            arr = new T[1];  // 初始化数组
            capacity = 1;  // 初始化容量
            current = 0;  // 初始化当前大小
        }

        // 添加元素
        void push(T data) {
            // 如果当前大小等于容量，需要扩大数组
            if (current == capacity) {
                T* temp = new T[2 * capacity];  // 创建一个新的两倍大的数组

                // 将旧数组的元素复制到新数组中
                for (int i = 0; i < capacity; i++) {
                    temp[i] = arr[i];
                }

                delete[] arr;  // 删除旧数组
                capacity *= 2;  // 更新容量
                arr = temp;  // 更新数组指针
            }

            // 添加新元素
            arr[current] = data;
            current++;  // 更新当前大小
        }

        // 删除最后一个元素
        void pop() {
            current--;  // 更新当前大小
        }

        // 获取当前大小
        int size() const {
            return current;
        }

        // 获取给定索引的元素
        T get(int index) const {
            if (index < current) {
                return arr[index];
            }
        }

        // 查找给定元素，返回其索引，如果没有找到，返回-1
        int64_t find(T data) const {
            for (int i = 0; i < current; i++) {
                if (arr[i] == data) {
                    return i;
                }
            }
            return -1;
        }

        // 删除给定索引的元素
        void deleteAt(int index) {
            if (index < current) {
                // 将后面的所有元素向前移动一位
                for (int i = index; i < current - 1; i++) {
                    arr[i] = arr[i + 1];
                }
                current--;  // 更新当前大小
            }
        }

        void clear() {
            delete[] arr;
            arr = new T[1];
            capacity = 1;
            current = 0;
        }

        bool empty() { return current == 0; }

        T at(uint64_t i) { return arr[i]; }

        T* begin() {
            return arr;
        }

        T* end() {
            return arr + current;
        }
    };
    }
}

#endif