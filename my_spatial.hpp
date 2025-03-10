#ifndef MY_SPATIAL_HPP
#define MY_SPATIAL_HPP

#include <type_traits>

#include "my_vector.hpp"

template<typename T, int N, int M>
class Matrix : public std::unique_ptr<Matrix<T, N, M - 1>[]> {
private:
    using base = Matrix<T, N, M - 1>;
    using pointer = std::unique_ptr<Matrix<T, N, M - 1>[]>;
    using iterator = Iterator<base>;
public:
    Matrix() : size_(0), arr(new base[1]) {
    }
    template<typename Nv, typename ...Args, std::enable_if_t<(std::is_same_v<size_t, Nv>
                                                             && ((std::is_same_v<size_t, Args> && ... )
                                                             && (sizeof... (Args) == M - 1))), bool> = true>
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
    size_t size() const {
        return size_;
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
class Matrix<T, N, 2> : public std::unique_ptr<Vector<T, N>[]> {
private:
    using base = Vector<T, N>;
    using pointer = std::unique_ptr<Vector<T, N>[]>;
    using iterator = Iterator<std::tuple<size_t, size_t, T>>;
    using pointer_iter = std::unique_ptr<std::tuple<size_t, size_t, T>[]>;
    size_t size_ = 0;
    pointer arr;
    pointer_iter arr_it;
public:
    size_t j_ = 0;
public:
    Matrix() : size_(0), arr(new base[1]), arr_it(new std::tuple<size_t, size_t, T>[1]) {
    }
    Matrix(size_t rows, size_t cols) : size_(rows), arr(new base[rows]), arr_it(new std::tuple<size_t, size_t, T>[rows]) {
        for (size_t i = 0; i < rows; ++i) {
            arr[i] = base{cols};
        }
    }
    base& operator[](size_t i) {
        j_ = i;
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
        arr_it[0] = std::make_tuple(j_, arr[0].i_, arr[0][arr[0].i_]);
        return iterator(&arr_it[0]);
    }
    iterator end() const {
        arr_it[size_] = std::make_tuple(size_, arr[size_].size_(), arr[0][0]);
        return iterator(&arr_it[size_]);
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
};


#endif // MY_SPATIAL_HPP
