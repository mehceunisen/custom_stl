#include <algorithm>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <utility>
#include <cassert>

template <typename T, typename... Types>
struct Index;

template <typename T, typename U, typename... Types>
struct Index<T, U, Types...> {
  static constexpr size_t value = std::is_same_v<T, U> ? 0 : 1 + Index<T, Types...>::value; };

template <typename T>
struct Index<T> {
  static constexpr size_t value = -1;
};

template <typename... Types>
class Variant {
  public:
    union Storage {
      
      template<typename T>
      Storage(T&& value) {
        new (&data) T(std::forward<T>(value));
      }
      
      template<typename T>
      void store(T&& value) {
        new (&data) T(std::forward<T>(value));
      }

      std::uint8_t data[std::max({sizeof(Types)...})];
    };
    
    template<typename T>
    Variant(T&& data) : m_storage(std::forward<T>(data)){
      m_index = Index<T, Types...>::value;
    }

    template <typename T>
    T& get() {
      assert((m_index == Index<T, Types...>::value) && "Poor casting");
      return *reinterpret_cast<T*>(m_storage.data);
    }

    template <typename T>
    void operator=(T&& other) {
      static_assert(Index<T, Types...>::value != -1 && "Poor assignment");
      this->m_index = Index<T, Types...>::value;
      this->m_storage = Storage(std::forward<T>(other));
    }

  private:
    Storage m_storage;
    std::size_t m_index;
};

int main() {
  Variant<int, double> v(1);
  v = 12.123123;
  std::cout << v.get<double>() << "\n";
  v = 1.23124;
}


