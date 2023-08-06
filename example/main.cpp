#include "../include/Object/xBaseObject.h"
#include <iostream>
using namespace std;
using namespace xc;

//回调函数
void onInput(xBaseObject* obj, const char* data) {
    cout << "input:" << data << endl;
}

int main() {
    xBaseObject* obj1 = new xBaseObject(nullptr);   //创建一个空的xBaseObject
    obj1->RegisterCallBack("input", onInput);       //注册input事件触发时的回调函数
    string a;   
    cin >> a;   //创建并输入字符串a
    xBaseObject::SendEvent(obj1, "input", a.c_str());   //向obj1发送input事件
    return 0;   
}
