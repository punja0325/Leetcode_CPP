#include <iostream>
#include <unordered_map>

int main() {
    // 声明和初始化一个空的 unordered_map
    std::unordered_map<int, std::string> myMap;

    // 添加元素到 unordered_map
    myMap[1] = "one";
    myMap.insert({2, "two"});
    myMap.insert(std::make_pair(3, "three"));

    // 访问 unordered_map 中的元素
    std::cout << "Value of key 1: " << myMap[1] << std::endl;
    std::cout << "Value of key 2: " << myMap.at(2) << std::endl;

    // 检查 unordered_map 中是否存在键
    if (myMap.count(3) > 0) {
        std::cout << "Key 3 exists in the unordered_map" << std::endl;
    }

    // 遍历 unordered_map 中的所有元素
    for (const auto& pair : myMap) {
        int key = pair.first;
        std::string value = pair.second;
        std::cout << "Key: " << key << ", Value: " << value << std::endl;
    }

    // 删除 unordered_map 中的元素
    myMap.erase(1);
    myMap.clear();

    return 0;
}