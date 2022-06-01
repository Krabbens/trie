#pragma once
#include <cstddef>

template <typename T>
class array_list {
public:
    array_list();
    array_list(const array_list& other);
    array_list(array_list&& other) noexcept;
    explicit array_list(const int& size);
    ~array_list();
    void push_back(T val);
    void remove(int idx);
    int length() const;
    T get(int idx) const;
    void set(int idx, T val);
    T& operator[](int idx);
    const T& operator[](int idx) const;

    array_list<T>& operator=(const array_list<T>& other);
    array_list<T>& operator=(array_list<T>&& other) noexcept;
    array_list<T>& operator+=(const array_list<T>& other);
    array_list<T>& operator+=(const T& val);
    bool operator==(const array_list<T>& other) const;
    bool operator!=(const array_list<T>& other) const;
    bool operator<(const array_list<T>& other) const;
    bool operator>(const array_list<T>& other) const;
    bool operator>=(const array_list<T>& other) const;
    bool operator<=(const array_list<T>& other) const;

    array_list<T> operator+(const array_list<T>& other) const;
    array_list<T> sublist(int start, int end) const;
    T* begin();
    T* end();
private:
    T* data_;
    int size_;
    int max_size_;
    void resize();
};

template<typename T>
inline array_list<T>::array_list() : data_(new T[2]), size_(0), max_size_(2) {}

template<typename T>
inline array_list<T>::array_list(const array_list& other) : data_(new T[other.max_size_]), size_(other.size_), max_size_(other.max_size_) {
    for (int i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
    }
}

template<typename T>
inline array_list<T>::array_list(array_list&& other)  noexcept : data_(other.data_), size_(other.size_), max_size_(other.max_size_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.max_size_ = 0;
}

template<typename T>
inline array_list<T>::array_list(const int& size) : data_(new T[size]), size_(0), max_size_(size) {}

template<typename T>
inline array_list<T>::~array_list()
{
    size_ = NULL;
    max_size_ = NULL;
    delete[] data_;
}

template<typename T>
inline void array_list<T>::push_back(T val)
{
    if (size_ + 1 > max_size_) resize();
    data_[size_++] = val;
}

template<typename T>
inline void array_list<T>::remove(const int idx)
{
    if (idx < 0 || idx >= size_) return;
    for (int i = idx; i < size_ - 1; i++)
    {
        data_[i] = data_[i + 1];
    }
    size_--;
}

template<typename T>
inline int array_list<T>::length() const
{
    return size_;
}

template<typename T>
inline T array_list<T>::get(int idx) const
{
    return data_[idx];
}

template<typename T>
inline void array_list<T>::set(int idx, T val)
{
    data_[idx] = val;
}

template<typename T>
inline T& array_list<T>::operator[](int idx)
{
    return data_[idx];
}

template<typename T>
inline const T& array_list<T>::operator[](int idx) const
{
    return data_[idx];
}

template<typename T>
inline array_list<T>& array_list<T>::operator=(const array_list<T>& other)
{
    if (&other != this) {
        delete[] data_;
        data_ = new T[other.size_];
        for (int i = 0; i < other.size_; i++)
        {
            data_[i] = other.data_[i];
        }
        size_ = other.size_;
        max_size_ = other.max_size_;
    }
    return *this;
}

template<typename T>
inline array_list<T>& array_list<T>::operator=(array_list<T>&& other) noexcept
{
    if (this == &other) return *this;
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    max_size_ = other.max_size_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.max_size_ = 0;
    return *this;
}

template<typename T>
inline array_list<T>& array_list<T>::operator+=(const array_list<T>& other)
{
    if (size_ + other.size_ > max_size_) resize();
    for (int i = 0; i < other.size_; i++)
    {
        data_[size_++] = other.data_[i];
    }
    return *this;
}

template<typename T>
inline array_list<T>& array_list<T>::operator+=(const T& val)
{
    if (size_ + 1 > max_size_) resize();
    data_[size_++] = val;
    return *this;
}

template<typename T>
inline bool array_list<T>::operator==(const array_list<T>& other) const
{
    if (size_ != other.size_) return false;
    for (int i = 0; i < size_; i++)
    {
        if (data_[i] != other.data_[i]) return false;
    }
    return true;
}

template<typename T>
inline bool array_list<T>::operator!=(const array_list<T>& other) const
{
    return !(*this == other);
}

template<typename T>
inline bool array_list<T>::operator<(const array_list<T>& other) const
{
    if (size_ < other.size_) return true;
    if (size_ > other.size_) return false;
    for (int i = 0; i < size_; i++)
    {
        if (data_[i] < other.data_[i]) return true;
        if (data_[i] > other.data_[i]) return false;
    }
    return false;
}

template<typename T>
inline bool array_list<T>::operator>(const array_list<T>& other) const
{
    return other < *this;
}

template<typename T>
inline bool array_list<T>::operator>=(const array_list<T>& other) const
{
    return !(*this < other);
}

template<typename T>
inline bool array_list<T>::operator<=(const array_list<T>& other) const
{
    return !(*this > other);
}

template<typename T>
inline array_list<T> array_list<T>::operator+(const array_list<T>& other) const
{
    array_list<T> result(*this);
    result += other;
    return result;
}

template<typename T>
inline array_list<T> array_list<T>::sublist(const int start, int end) const
{
    if (start < 0 || start >= size_) return array_list<T>();
    if (end < 0 || end >= size_) end = size_;
    if (start > end) return array_list<T>();
    array_list<T> result(end - start);
    for (int i = start; i < end; i++)
    {
        result.push_back(data_[i]);
    }
    return result;
}

template<typename T>
inline T* array_list<T>::begin()
{
    return data_;
}

template<typename T>
inline T* array_list<T>::end()
{
    return data_ + size_;
}

template<typename T>
inline void array_list<T>::resize()
{
    max_size_ *= 2;
    T* temp = new T[max_size_];
    for (int i = 0; i < size_; ++i) {
        temp[i] = data_[i];
    }
    delete[] data_;
    data_ = temp;
}