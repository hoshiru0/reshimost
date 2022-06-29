#pragma once
#include <iostream>
#include <cstdint>
#include <string.h>

template<typename T, bool swap_remove = false, bool use_realloc = false>
class SmartVector {
    uint32_t size_ {};
    uint32_t capacity_ {16};
    uint32_t min_capacity_ {16};
    T* data_ {(T*)malloc(0)};

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
        capacity_ = capacity_ < 16 ? 16 : capacity_;
        min_capacity_ = capacity_;
        realloc();
        for (auto& e : l) {
            push_back(e);
        }
    }
    SmartVector() {
        capacity_ = 16;
        min_capacity_ = 16;
        realloc();
    }

    [[nodiscard]] iterator begin() {
        return iterator(data_);
    }

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
        return iterator(data_);
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
        min_capacity_ = n;
        capacity_ = n;
        realloc();
    }

    void shrink() {
        capacity_ = capacity_/2;
        realloc();
    }

    void grow() {
        capacity_ *= 2;
        realloc();
    }

    auto& push_back(const T& value) {
        if (size_ == capacity_) {
            grow();
        }

        return *(new (data_+size_++) T (value));
    }

    template<bool call_destr = true>
    void pop_back() {
        if constexpr (call_destr) {
            (*this)[size_-1].~T();
        } 
        size_--;
        if (uint32_t c = (capacity_/4); capacity_ > min_capacity_ && size_ == c) {
            shrink();
        }
    }

    template<typename... Ts>
    auto& emplace_back(Ts&&... args) {
        if (size_ == capacity_) {
            grow();
        }
        return *(new (data_+size_++) T (std::forward<Ts>(args)...));
    }

    void erase(iterator it) {
        it->~T();
        if constexpr (swap_remove) {
            new (it) T (std::move(*--this->end()));
            //memcpy(it, --this->end(), sizeof(T));
        } else {
            for (;it!=this->end()-1; it++) {
                *it = *(it+1);
            }
            //memmove(it, it+1, sizeof(T)*(--this->end()-it));
        }
        pop_back<false>();
        
    }

    void clear() {
        for (uint32_t i{size_}; i>0; i--) {
            this->pop_back();
        }
    }

    ~SmartVector() {
        clear();
        free(data_);
    }
};