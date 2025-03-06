#include <iostream>
#include <unordered_set>
#include <string>

int main() {
    // 宣告一個 unordered_set
    std::unordered_set<std::string> mySet;

    // 插入元素
    mySet.insert("apple");
    mySet.insert("banana");
    mySet.insert("orange");

    // 查找元素
    if (mySet.find("apple") != mySet.end()) {
        std::cout << "找到 apple" << std::endl;
    }

    // 刪除元素
    mySet.erase("banana");

    // 檢查元素是否存在
    if (mySet.count("orange") > 0) {
        std::cout << "找到 orange" << std::endl;
    }

    return 0;
}