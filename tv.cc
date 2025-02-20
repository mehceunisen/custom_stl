#include <iostream>
#include <cstddef>
#include <cstdint>
#include <memory>

class TV {
public:
  TV () : data_(std::make_unique<std::uint8_t[]>(size_)) {
     
  }
  
  template <typename T>
  void push_back(T&& arg) {
    new (&data_[last_index_]) T(std::forward<T>(arg));
    last_index_ += sizeof(T); 
  }
  
  template <typename T>
  void emplace_back(T&& arg) {
    push_back(std::forward<T>(arg));
  }

  template <typename T, typename ...U>
  void emplace_back(T&& t, U&&... u) {
    emplace_back(std::forward<T>(t));
    emplace_back(std::forward<U>(u)...);
  }

  template <typename T>
  T get(std::size_t idx) {
    return *reinterpret_cast<T*>(&data_[idx]);
  }

private:
  
  std::size_t size_ {30};
  std::size_t last_index_ {0};
  std::unique_ptr<std::uint8_t[]> data_;
};

int main() {
  TV tv;

  tv.emplace_back(11231,2,3, float(123.123), std::string("hellow"));
  std::cout << tv.get<std::string>(16) << std::endl;
}
