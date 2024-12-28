#include <iostream>
#include <memory>

struct Entity {
  Entity() {

  }

  Entity(const Entity& other) {
    std::cout << "Copy Constructor\n";
  }

  Entity(Entity&&) { 
    std::cout << "Move Constructor\n";  
  }
};


template <class T>
class Optional {
  public:
    
    Optional() {
      m_data = nullptr;
    }

    const bool has_value() {
      if(m_data.get())
        return true;
      return false;
    }

    const T& value_or(const T& data) {
      if (has_value()) {
        return *(m_data.get());
      }
      return data;
    }

    const Optional<T>& operator=(T&& other) {
      m_data = std::make_unique<T>(std::forward<T>(other));
      return *this;
    }

    operator bool() const {
      return has_value();
    }

  private:
    std::unique_ptr<T> m_data; 
};

int main() {
  
  ::Optional<int> o;
  o = 13;
  std::cout << o.value_or(-1);

  Optional<Entity> t;
  Entity e;
  t = std::move(e);

}
