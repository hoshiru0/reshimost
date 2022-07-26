#pragma once
#include <initializer_list>
#include <iterator>
#include <cstdint>
#include <string.h>

template<typename T, bool swap_remove = false, bool use_realloc = false>
class SmartVector {
    uint32_t size_ {};
    uint32_t capacity_ {};
    T* data_ {};

public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = T;
    using value_type        = T;
    using reference         = T&;
    using pointer           = T*;
    using const_reference   = const T&;
    using const_pointer     = const T*;
    using size_type         = decltype(size_);

    struct iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::iterator_traits<T>;
        using value_type        = T;
        using reference         = T&;
        using pointer           = T*;

        iterator(T* ptr) : m_ptr(ptr) {}

        [[nodiscard]] T& operator*() { return *m_ptr; }
        [[nodiscard]] const T& operator*() const { return *m_ptr; }
        T* operator->() { return m_ptr; }
        operator T* () { return m_ptr; }
        operator const T* () const { return m_ptr; }
        iterator& operator++() { m_ptr++; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
        iterator& operator--() { m_ptr--; return *this; }
        iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }
        [[nodiscard]] iterator operator+(int x) const { return m_ptr+x; }
        [[nodiscard]] iterator operator-(int x) const { return m_ptr-x; }
        friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };

    private:
        T* m_ptr;
    };

    using const_iterator = const iterator;

    SmartVector(std::initializer_list<T> l) {
        capacity_ = l.size();
        realloc();
        for (auto& el : l) {
            push_back(el);
        }
    }

    SmartVector(SmartVector& other) {
        *this = other;
    }

    SmartVector(SmartVector&& other) {
        *this = std::move(other);
    }

    SmartVector() {
    }

    SmartVector& operator=(SmartVector&& other) {
        clear();
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = other.data_;

        other.data_ = 0;
        other.size_ = 0;
        other.capacity_ = 0;
        return *this;
    }

    SmartVector& operator=(SmartVector& other) {
        clear();
        capacity_ = other.capacity_;
        realloc();
        for (const auto& el : other) {
            push_back(el);
        }
        return *this;
    }

    [[nodiscard]] iterator begin() {
        return iterator(data_); }

    [[nodiscard]] iterator end() {
        return iterator(data_ + size_);
    }

    [[nodiscard]] T& back() {
        return *(--this->end());
    }

    [[nodiscard]] const iterator cbegin() {
        return iterator(data_);
    }

    [[nodiscard]] const iterator cend() {
        return end();
    }

    [[nodiscard]] T* data() const {
        return data_;
    }

    [[nodiscard]] uint32_t capacity() const {
        return capacity_;
    }

    [[nodiscard]] uint32_t size() const {
        return size_;
    }

    [[nodiscard]] T& operator[] (uint32_t i) {
        return *(data_ + i);
    }

    void realloc() {
        if constexpr (use_realloc) {
            data_ = (T*)::realloc((void*)data_, sizeof(T)*capacity_);
        } else {
            T* newdata = (T*) malloc(sizeof(T)*capacity_);
            for (uint32_t i{}; i<size_; i++) {
                new (newdata+i) T (std::move(data_[i]));
                data_[i].~T();
            }
            free(data_);
            data_ = newdata;
        }
    }

    void reserve(uint32_t n) {
        capacity_ = n;
        realloc();
    }

    void shrink_to_fit() {
        capacity_ = size_;
        realloc();
    }

    void grow() {
        if (capacity_) capacity_ *= 2;
        else capacity_ = 1;
        realloc();
    }

    T& push_back(T&& value) {
        return emplace_back(std::forward<T>(value));
    }

    T& push_back(const T& value) {
        return emplace_back(value);
    }

    void pop_back() {
        (*this)[--size_].~T();
    }

    template<typename... Ts>
    auto& emplace_back(Ts&&... args) {
        if (size_ == capacity_) {
            grow();
        }
        return *(new (data_+size_++) T (std::forward<Ts>(args)...));
    }

    SmartVector copy() {
        SmartVector copy {*this};
        return copy;
    }

    void erase(iterator it) {
        if constexpr (swap_remove) {
            *it = std::move(*--this->end());
        } else {
            for (;it!=this->end()-1; it++) {
                *it = std::move(*(it+1));
            }
        }
        pop_back();
    }

    void clear() {
        for (uint32_t i{size_}; i>0; i--) {
            pop_back();
        }
        size_ = 0;
        capacity_ = 0;
        free(data_);
        data_ = 0;
    }

    ~SmartVector() {
        clear();
    }
};