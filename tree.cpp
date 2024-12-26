#include <iostream>

template <typename T>
struct Leaf {
  T data;
  Leaf<T>* left;
  Leaf<T>* right;

  Leaf(const T& data) {
    this->data = data;
    left = nullptr;
    right = nullptr;
  }

};

template <class T>
class Tree {
  public:
  Tree(const T& data) {
    m_root_ = new Leaf<T>(data);
  }
  
  void add_leaf(const T& data) {
    auto iter = m_root_;
    add_leaf_(data, iter);
  }

  void bfs() {
    auto iter = m_root_;
    bfs_(iter); 
  }

  Leaf<T>* add_leaf_(const T& data, Leaf<T>* iter) {
    if (iter == nullptr) {
      return new Leaf<T>(data);
    }
    if(data > iter->data) {
      iter->right = add_leaf_(data, iter->right);
    }
    else if (data <= iter->data) {
      iter->left = add_leaf_(data, iter->left);
    }
  }

  void bfs_(const Leaf<T>* l) {
    
    if (l == nullptr) {
      return;
    }

    bfs_(l->left);
    bfs_(l->right);
    std::cout << l->data << '\n';
  }

  Leaf<T>* m_root_;
};

int main() {
  int i = 0;
  Tree<int> t(10);
  t.add_leaf(3);
  t.add_leaf(4);
  t.add_leaf(9);
  t.add_leaf(8);
  t.add_leaf(24);
  t.add_leaf(123);
  t.bfs();
}
