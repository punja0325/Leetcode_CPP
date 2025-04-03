#include <iostream>
#include <string>

int main() {
  // 1. 宣告一個空的 string 物件
  std::string str;

  // 2. 宣告一個 string 物件並初始化為 "hello"
  std::string str2 = "hello";

  // 3. 取得 string 的長度
  std::cout << "str2.size() = " << str2.size() << std::endl;

  // 4. 檢查 string 是否為空
  if (str.empty()) {
    std::cout << "str is empty" << std::endl;
  }

  // 5. 將 " world" 附加到 string 末尾
  str2 += " world";
  std::cout << "str2 = " << str2 << std::endl;

  // 6. 將兩個 string 合併
  std::string str3 = "hello" + " world";
  std::cout << "str3 = " << str3 << std::endl;

  // 7. 將 string 的前 5 個字元替換為 "hi"
  str2.replace(0, 5, "hi");
  std::cout << "str2 = " << str2 << std::endl;

  // 8. 刪除 string 的前 5 個字元
  str2.erase(0, 5);
  std::cout << "str2 = " << str2 << std::endl;

  // 9. 搜尋 "world" 在 string 中的位置
  size_t pos = str2.find("world");
  if (pos != std::string::npos) {
    std::cout << "found 'world' at position " << pos << std::endl;
  }

  // 10. 搜尋 "world" 在 string 中的最後出現位置
  pos = str2.rfind("world");
  if (pos != std::string::npos) {
    std::cout << "found 'world' at position " << pos << std::endl;
  }

  // 11. 搜尋 "abc" 中任一字元在 string 中的第一個出現位置
  pos = str2.find_first_of("abc");
  if (pos != std::string::npos) {
    std::cout << "found 'a' or 'b' or 'c' at position " << pos << std::endl;
  }

  // 12. 檢查 string 是否等於 "hello"
  if (str2 == "hello") {
    std::cout << "str2 is equal to 'hello'" << std::endl;
  }

  // 13. 將 string 轉換為整數
  int num = std::stoi(str2);
  std::cout << "num = " << num << std::endl;

  return 0;
}