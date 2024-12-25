#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstddef>
class Entity {
public:
    Entity() {
        std::fill(data_, &data_[200], 10);
    }
    struct Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = int*;
        using reference = int&;
        
        Iterator(pointer pointer) : pointer_(pointer) {
        }

        reference operator*() const {
            return *pointer_;
        }
        pointer operator->() {
            return pointer_;
        }
        Iterator& operator++() {
            pointer_++;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.pointer_ == b.pointer_; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.pointer_ != b.pointer_; };     


    private:
        pointer pointer_;
    };
    
    Iterator begin() {
        return Iterator(data_); 
    }
    Iterator end() {
        return Iterator(&data_[200]);
    }

private:
    int data_[200];
};

int main () {

    Entity e;
    
    std::transform(e.begin(), e.end(), e.begin(), [] (int& elem) {
        return elem + 31;
    });

    for (const auto& x: e) {
        std::cout << x << " ";
    }
}

