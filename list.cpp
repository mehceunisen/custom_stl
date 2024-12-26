#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <algorithm>
#include <optional>

template <class T>
class Node {
public:
  Node(const T& val) : next(nullptr), prev(nullptr) {
    data = val;
  }
  ~Node() {
  }
  Node(const T& val, std::shared_ptr<Node<T>> next, std::shared_ptr<Node<T>> prev) {
    data = val;
    this->next = next;
    this->prev = prev;
  }
  
  std::optional<T> data;
  std::shared_ptr<Node<T>> next;
  std::shared_ptr<Node<T>> prev;

};

template <class T>
class List {
public:
  struct Iterator {
    public:
      using iterator_category = std::bidirectional_iterator_tag;
      using value_type = Node<T>;
      using difference_type = std::ptrdiff_t;
      using pointer = Node<T>*;
      using reference = Node<T>&;

      Iterator(pointer p) : p_(std::make_shared<value_type>(p)) {}
      
      reference operator*() const {
        return *p_;
      }
      pointer operator->() {
        return p_.get();
      }
      Iterator& operator++() {
        p_ = p_->next;
        return *this;
      }
      Iterator operator++(int) {
        Iterator swap = *this;
        ++(*this);
        return swap;
      }
      
      friend bool operator== (const Iterator& a, const Iterator& b)  {
        return a.p_ == b.p_; 
      } 
      friend bool operator!= (const Iterator& a, const Iterator& b)  {
        return a.p_ == b.p_; 
      } 
    private:
      std::shared_ptr<value_type> p_;
  };


  List() {
    head_ = std::make_shared<Node<T>>(Node<T>(1, nullptr, nullptr));
    tail_ = std::make_shared<Node<T>>(Node<T>(2, head_, head_));
    head_.get()->next = tail_;
    head_.get()->prev = tail_;

    size_ = 2;
    empty_ = 0;
  }

  void append(T&& data) {
    if (empty_ == 0) {
      auto iter = extend_space(size_ + (size_ / 2));
    }

  }

  Iterator begin() {
   return Iterator(head_.get());
  }

  Iterator end() {
    return Iterator(tail_.get());
  }

    
  private:
  Node<T>* extend_space(std::size_t new_size) {
    auto tmp = tail_;
    
    for (int i = 0; i < new_size - size_; ++i){
      tail_.get()->next = std::make_shared<Node<T>>(0, head_, tail_);
      tail_ = tail_.get()->next;
    }
    size_ = new_size;

    return (*tmp)->next.get();
  }

  std::shared_ptr<Node<T>> head_;
  std::shared_ptr<Node<T>> tail_;
  
  std::size_t size_;
  std::size_t empty_;
};

int main() {
  List<int> l;
}
