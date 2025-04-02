#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <iostream>
#include <memory>
#include <cassert>

#include "my_iterator.hpp"

template <class T, int N, class Allocator = std::allocator<T>>
class Vector
{
private:
    using base_alloc = std::allocator_traits<Allocator>;
    using pointer = typename base_alloc::pointer;
public:
    using value_type = T;
    using iterator = Iterator<T>;

public:
    Vector(const Allocator& = Allocator()) : size(0), capacity(1), arr(new T[1]) {
        arr[0] = N;
        // std::cout << "Vector()" << std::endl;
    }
    Vector(size_t cols) : size(cols), capacity(cols), arr(new T[cols]) {
        for(size_t j = 0; j < size; ++j) arr[j] = N;
        // std::cout << "Vector(size_t cols)" << std::endl;
    }
    ~Vector() {
        // std::cout << "~Vector()" << std::endl;
        for (size_t i = 0; i < capacity; ++i) {
            base_alloc::destroy(alloc, &arr[i]);
        }
    }
    void push_back(T&& element) {
        if (size == capacity) {
            reserve(2 * capacity);
        }
        arr[size] = std::move(element);
        size++;
    }
    void reserve(size_t am) {
        if(am <= capacity) {
            return;
        } else {
            T *temp = base_alloc::allocate(alloc, am);
            for (size_t i = 0; i < am; ++i) {
                base_alloc::construct(alloc, &temp[i], arr[i]);
            }
            for (size_t i = 0; i < am; ++i) {
                base_alloc::destroy(alloc, &arr[i]);
            }
            base_alloc::deallocate(alloc, arr, capacity);
            capacity = am;
            arr = temp;
        }
    }
    T& operator[](size_t i) {
        i_ = i;
        if(empty()) {
            reserve(2 * capacity);
            ++size;

        }
        return arr[i];
    }
    const T& operator[](size_t i) const {
        assert(!empty());
        return arr[i];
    }
    void print_sub_mtrx(const std::initializer_list<int>& pair) const {
        auto row_p_ = std::make_pair(*pair.begin(), *(pair.begin() + 1));
        std::cout << " ";
        for (size_t k = row_p_.first; k < row_p_.second; ++k)
            std::cout << (*this)[k] << " ";
        std::cout << std::endl;
    }
    size_t size_no_empty() const {
        size_t count = 0;
        for (size_t k = 0; k < size; ++k)
            if((*this)[k] != T(0)) count++;
        return count;
    }
    template <typename... Args>
    void print_no_empty(Args&&... args) const {
        for (size_t k = 0; k < size; ++k)
            if((*this)[k] != T(0)) {
                std::cout << "value = " << (*this)[k] << "; index = {" << k;
                ((std::cout << ',' << std::forward<Args>(args)), ...);
                std::cout << "}\n";
            }
   }
    iterator begin() const {
        return (iterator(&arr[0]));
    }
    iterator end() const {
        return (iterator(&arr[size]));
    }
    size_t size_() const {
        return size;
    }
    bool empty() const {
        return begin() == end();
    }
    friend std::ostream& operator << (std::ostream& os, const Vector<T, N>& A) {
        os << " ";
        for (size_t k = 0; k < A.size_(); ++k)
            os << A[k] << " ";
        os << std::endl;
        return os;
    }

private:
    size_t size = 0;
    size_t capacity = 0;
    pointer arr;
    Allocator alloc;
public:
    size_t i_ = 0;
};


#endif // MY_VECTOR_HPP
