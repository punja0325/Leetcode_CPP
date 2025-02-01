#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    // 創建一個空的向量，元素類型為 int
    std::vector<int> v1;

    // 向量的大小為 0
    std::cout << "Size: " << v1.size() << std::endl;

    // 創建一個具有初始元素的向量，元素類型為 int
    std::vector<int> v2 = {1, 2, 3, 4, 5};

    // 向量的大小為 5
    std::cout << "Size: " << v2.size() << std::endl;

    // 遍歷向量中的元素
    for (int i = 0; i < v2.size(); i++) {
        std::cout << "Element: " << v2[i] << std::endl;
    }

    // 創建一個空的向量，元素類型為 int
    std::vector<int> v3;

    // 擴展向量，將元素 1、2、3 加入向量尾部
    v3.push_back(1);
    v3.push_back(2);
    v3.push_back(3);

    // 向量的大小為 3
    std::cout << "Size: " << v3.size() << std::endl;

    // 向量的第二個位置插入元素 4
    v3.insert(v3.begin() + 1, 4);

    // 遍歷向量中的元素
    for (int i = 0; i < v3.size(); i++) {
        std::cout << "Element: " << v3[i] << std::endl;
    }

    // 創建一個具有初始元素的向量，元素類型為 int
    std::vector<int> v4 = {1, 2, 3, 4, 5};

    // 刪除向量的第二個元素
    v4.erase(v4.begin() + 1);

    // 向量的大小為 4
    std::cout << "Size: " << v4.size() << std::endl;

    // 向量的第一個位置替換元素為 10
    v4[0] = 10;

    // 遍歷向量中的元素
    for (int i = 0; i < v4.size(); i++) {
        std::cout << "Element: " << v4[i] << std::endl;
    }

    // 創建一個具有初始元素的向量，元素類型為 int
    std::vector<int> v5 = {5, 2, 8, 1, 9};

    // 查找向量中的元素 8
    auto it = std::find(v5.begin(), v5.end(), 8);
    if (it != v5.end()) {
        std::cout << "Element 8 found at index " << std::distance(v5.begin(), it) << std::endl;
    }

    // 將向量中的元素進行排序
    std::sort(v5.begin(), v5.end());

    // 遍歷向量中的元素
    for (int i = 0; i < v5.size(); i++) {
        std::cout << "Element: " << v5[i] << std::endl;
    }

    return 0;
}