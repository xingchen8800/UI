#ifndef __STD_STRING_HPP_
#define __STD_STRING_HPP_
#include "types.h"

//Code by GPT-4
namespace xc::Std {
    class String {
    private:
        char* buffer; // 字符缓冲区
        uint64_t length; // 字符串长度

    public:
        // 构造函数
        String(const char* initString = "\0") {
            if (initString) {
                length = 0;
                while (initString[length] != '\0') {
                    ++length;
                }

                buffer = new char[length + 1];
                for (uint64_t i = 0; i < length; ++i) {
                    buffer[i] = initString[i];
                }
                buffer[length] = '\0';
            } else {
                length = 0;
                buffer = new char[1];
                buffer[0] = '\0';
            }
        }

        // 拷贝构造函数
        String(const String& copySource) {
            length = copySource.length;
            buffer = new char[length + 1];
            for (uint64_t i = 0; i < length; ++i) {
                buffer[i] = copySource.buffer[i];
            }
            buffer[length] = '\0';
        }

        // 析构函数
        ~String() {
            delete[] buffer;
        }

        // 赋值运算符
        String& operator=(const String& copySource) {
            if (this != &copySource) {
                delete[] buffer;

                length = copySource.length;
                buffer = new char[length + 1];
                for (uint64_t i = 0; i < length; ++i) {
                    buffer[i] = copySource.buffer[i];
                }
                buffer[length] = '\0';
            }
            return *this;
        }

        // 获取长度函数
        uint64_t getLength() {
            return length;
        }

        // 打印函数
        // void pruint64_t() {
        //     for (uint64_t i = 0; i < length; ++i) {
        //         putchar(buffer[i]);
        //     }
        // }

        // 查找函数
        int64_t find(const String& substring) {
            for (uint64_t i = 0; i < length - substring.length + 1; ++i) {
                bool found = true;
                for (uint64_t j = 0; j < substring.length; ++j) {
                    if (buffer[i + j] != substring.buffer[j]) {
                        found = false;
                        break;
                    }
                }
                if (found) {
                    return i;
                }
            }
            return -1;
        }

        // 截取子串函数
        String substring(uint64_t start, uint64_t end) {
            if (start < 0 || end > length || start > end) {
                return String("");
            }

            char* subBuffer = new char[end - start + 1];
            for (uint64_t i = start; i < end; ++i) {
                subBuffer[i - start] = buffer[i];
            }
            subBuffer[end - start] = '\0';

            String result(subBuffer);
            delete[] subBuffer;
            return result;
        }

        void append(const String& other) {
            *this += other;
        }

        // 比较函数
        int64_t compare(const String& other) {
            uint64_t minLength = length < other.length ? length : other.length;
            for (uint64_t i = 0; i < minLength; ++i) {
                if (buffer[i] < other.buffer[i]) {
                    return -1;
                } else if (buffer[i] > other.buffer[i]) {
                    return 1;
                }
            }
            if (length < other.length) {
                return -1;
            } else if (length > other.length) {
                return 1;
            } else {
                return 0;
            }
        }

        String operator+(const String& rhs) {
            char* newBuffer = new char[length + rhs.length + 1];
            for (uint64_t i = 0; i < length; ++i) {
                newBuffer[i] = buffer[i];
            }
            for (uint64_t i = 0; i < rhs.length; ++i) {
                newBuffer[i + length] = rhs.buffer[i];
            }
            newBuffer[length + rhs.length] = '\0';

            String result(newBuffer);
            delete[] newBuffer;
            return result;
        }

        String operator+(char c) {
            char* newBuffer = new char[length + 2];
            for (uint64_t i = 0; i < length; ++i) {
                newBuffer[i] = buffer[i];
            }
            newBuffer[length] = c;
            newBuffer[length + 1] = '\0';

            String result(newBuffer);
            delete[] newBuffer;
            return result;
        }

        // += 运算符重载
        String& operator+=(const String& rhs) {
            *this = *this + rhs;
            return *this;
        }

        String& operator+=(char c) {
            *this = *this + c;
            return *this;
        }

        // - 运算符重载
        // 这个例子中，我们将"-"定义为删除右侧字符串中出现的所有字符
        String operator-(const String& rhs) {
            String result = *this;
            for (uint64_t i = 0; i < rhs.length; ++i) {
                for (uint64_t j = 0; j < result.length; ++j) {
                    if (result.buffer[j] == rhs.buffer[i]) {
                        for (uint64_t k = j; k < result.length - 1; ++k) {
                            result.buffer[k] = result.buffer[k + 1];
                        }
                        --result.length;
                    }
                }
            }
            result.buffer[result.length] = '\0';
            return result;
        }

        // -= 运算符重载
        String& operator-=(const String& rhs) {
            *this = *this - rhs;
            return *this;
        }

        // > 运算符重载
        bool operator>(const String& rhs) {
            return compare(rhs) > 0;
        }

        // < 运算符重载
        bool operator<(const String& rhs) {
            return compare(rhs) < 0;
        }

        // >= 运算符重载
        bool operator>=(const String& rhs) {
            return compare(rhs) >= 0;
        }

        // <= 运算符重载
        bool operator<=(const String& rhs) {
            return compare(rhs) <= 0;
        }

        char& operator[](uint64_t i) {
            if(i > length) { static char e = '\0'; return e; }
            else return buffer[i];
        }    

        int64_t toUint() const {
            int result = 0;
            for(int i = 0; i < length; i++) {
                if(buffer[i] < '0' || buffer[i] > '9') {
                    return -1;
                }
                result = result * 10 + (buffer[i] - '0');
            }
            return result;
        }

        static String toString(uint64_t number) {
            String buffer;
            int i = 0;
            while(number > 0) {
                buffer += '0' + (number % 10);
                number /= 10;
            }
            buffer[i] = '\0';

            for(int j = 0; j < i / 2; j++) {
                char tmp = buffer[j];
                buffer[j] = buffer[i - j - 1];
                buffer[i - j - 1] = tmp;
            }

            return buffer;
        }

        char* c_str() {
            return buffer;
        }
    };
}

#endif