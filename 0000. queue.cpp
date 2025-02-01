#include <queue>
#include <iostream>

int main() {
    // 創建一個隊列，元素類型為 int
    std::queue<int> q;

    // 將元素 1、2、3 加入隊列尾部
    q.push(1);
    q.push(2);
    q.push(3);

    // 返回隊列頭部的元素，不會移除元素
    std::cout << "Front: " << q.front() << std::endl;

    // 移除隊列頭部的元素
    q.pop();

    // 返回隊列尾部的元素，不會移除元素
    std::cout << "Back: " << q.back() << std::endl;

    // 返回隊列中的元素數量
    std::cout << "Size: " << q.size() << std::endl;

    // 檢查隊列是否為空
    if (q.empty()) {
        std::cout << "Queue is empty." << std::endl;
    } else {
        std::cout << "Queue is not empty." << std::endl;
    }

    return 0;
}