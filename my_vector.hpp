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
    }
    Vector(size_t cols) : size(cols), capacity(cols), arr(new T[cols]) {
        for(size_t j = 0; j < size; ++j) arr[j] = N;
        // std::cout << "Matrix " << 1 << std::endl;
    }
    void push_back(T&& element) {
        if (size == capacity) {
            reserve(2 * capacity);
        }
        arr[size] = std::move(element);
        size++;
    }
    virtual void reserve(size_t am) {
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
    virtual T& operator[](size_t i) {
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
private:
    pointer arr;
    Allocator alloc;
};


#endif // MY_VECTOR_HPP
