#ifndef MY_SPATIAL_HPP
#define MY_SPATIAL_HPP

#include <type_traits>

#include "my_vector.hpp"

template<typename T, int N, int M>
class Matrix : std::enable_if_t<(M > 2), std::true_type> {
private:
    using base = Matrix<T, N, M - 1>;
    using pointer = base*;
    using iterator = Iterator<base>;
public:
    Matrix() : size_(0), arr(new base[1]) {
    }
    template<typename Nv, typename ...Args, std::enable_if_t<std::is_same_v<size_t, Nv>
                                                             && (std::is_same_v<size_t, Args> && ...)
                                                             && (sizeof... (Args) == M - 1)>* = nullptr>
    Matrix(Nv rows, Args... Dims) : size_(rows), arr(new base[rows]) {
        for (size_t i = 0; i < rows; ++i) {
            arr[i] = base{Dims...};
        }
    }
    base& operator[](size_t i) {
        if(i > size_) {
            size_ = 1;
            return arr[0];

        } else
            return arr[i];
    }
    const base& operator[](size_t i) const {
        assert(arr);
        return arr[i];
    }
    iterator begin() const {
        return (iterator(&arr[0]));
    }
    iterator end() const {
        return (iterator(&arr[size_]));
    }
    size_t size() const {
        return size_;
    }
    bool empty() const {
        return begin() == end();
    }
    friend std::ostream& operator << (std::ostream& os, const Matrix<T, N, M>& A) {
        os << " ";
        for (size_t k = 0; k < A.size(); ++k)
            os << A[k] << " ";
        os << std::endl;
        return os;
    }
private:
    size_t size_ = 0;
    pointer arr;
};

template<typename T, int N>
class Matrix<T, N, 2> {
public:
    using base = Vector<T, N>;
    using pointer = base*;
    using iterator = Iterator<base>;
public:
    Matrix() : size_(0), arr(new base[1]) {
    }
    Matrix(size_t rows, size_t cols) : size_(rows), arr(new base[rows]) {
        for (size_t i = 0; i < rows; ++i) {
            arr[i] = base{cols};
        }
    }
    base& operator[](size_t i) {
        if(i > size_) {
            size_ = 1;
            return arr[0];

        } else
            return arr[i];
    }
    const base& operator[](size_t i) const {
        assert(arr);
        return arr[i];
    }
    iterator begin() const {
        return (iterator(&arr[0]));
    }
    iterator end() const {
        return (iterator(&arr[size_]));
    }
    size_t size() const {
        return size_;
    }
    bool empty() const {
        return begin() == end();
    }
    friend std::ostream& operator << (std::ostream& os, const Matrix<T, N, 2>& A) {
        os << " ";
        for (size_t k = 0; k < A.size(); ++k)
            os << A[k] << " ";
        os << std::endl;
        return os;
    }
private:
    size_t size_ = 0;
    pointer arr;
};


#endif // MY_SPATIAL_HPP
