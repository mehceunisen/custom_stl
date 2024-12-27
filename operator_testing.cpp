#include <iostream>
#include <ostream>

class Entity {
public:
  Entity() {
    x = 42;
  }
 friend std::ostream& operator<<(std::ostream& os, const Entity& ent) {
    os << ent.x;
    return os;
  }
private:
  int x;
};

int main() {
  Entity ent;

  std::cout << ent;
}
