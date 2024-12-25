#include <algorithm>
#include <iostream>
#include <cstddef>
#include <utility>
#include <cassert>
#include <initializer_list>

class Entity {
public:
    Entity() {}
    Entity(const Entity& other) {
        std::cout << "copied\n";
    }

    Entity(Entity&& other) {
        std::cout << "moved\n";
    }

    Entity&& operator= (Entity&& other){
        return std::move(other);
    }

    Entity operator = (Entity& other) = delete;
    Entity& operator = (const Entity& other) = delete;
};

template <typename T>
class Vector {
public:
    Vector() : size_(4), last_idx_(0) {
        data_ = new T[size_];
    }

    Vector(std::size_t _size) : size_(_size), last_idx_(0) {
        data_ = new T[size_];
    }
    
    Vector(std::initializer_list<T> _list) : size_(_list.size() * 2), last_idx_(_list.size()) {
        data_ = new T[_list.size()];
        std::transform(_list.begin(), _list.end(), data_, [](T elem) 
        { 
            return std::move(elem);
        });
    }
    
    T& operator[](std::int64_t index) {
        assert((index >= 0 && index < last_idx_) && "Index out of range");
        return data_[index]; 
    }
    const T& operator[](std::int64_t index) const {
        assert((index >= 0 && index < last_idx_) && "Index out of range");
        return data_[index]; 
    }
    
    

    void print() const {
        for (int i = 0; i < last_idx_; ++i) {
            std::cout << data_[i] << " ";
        }
        std::cout << "\n";
    }

    void push_back(T&& x) {
        if (last_idx_ == size_) {
            re_alloc(size_ + (size_ / 2));    
        }

        data_[last_idx_++] = std::forward<T>(x);
    }
    
    const T& pop() {
        assert(last_idx_ > 0 && "Unable to pop from empty vector");
        
        if (last_idx_ <= size_ / 4) {
            re_alloc(size_ - (size_ / 2));
        }

        return std::move(data_[--last_idx_]);
    }

    std::size_t size() const {
        return size_;
    }

private:
    std::size_t size_;
    std::size_t last_idx_;

    T* data_;

    void re_alloc(std::size_t new_size) {
        T* new_data = new T[new_size];

        for (int i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]); 
        }

        delete[] data_;
        size_ = new_size;
        data_ = new_data;
    }
};

int main() {
    ::Vector<Entity> xvec;
    Entity e;
    xvec.push_back(std::move(e));
}
