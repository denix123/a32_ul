// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_CONTAINERS_POD_VECTOR_H
#define ANDROID_BASE_CONTAINERS_POD_VECTOR_H

#include <android/base/Limits.h>
#include <android/base/Log.h>

#include <stddef.h>
#include <stdint.h>

namespace android {
namespace base {


class PodVectorBase {
protected:
    PodVectorBase() : mBegin(NULL), mEnd(NULL), mLimit(NULL) {}
    explicit PodVectorBase(const PodVectorBase& other);
    PodVectorBase& operator=(const PodVectorBase& other);
    ~PodVectorBase();

    bool empty() const { return mEnd == mBegin; }

    size_t byteSize() const { return mEnd - mBegin; }

    size_t byteCapacity() const { return mLimit - mBegin; }

    void* begin() { return mBegin; }
    const void* begin() const { return mBegin; }
    void* end() { return mEnd; }
    const void* end() const { return mEnd; }

    void* itemAt(size_t pos, size_t itemSize) {
        const size_t kMaxCapacity = SIZE_MAX / itemSize;
        DCHECK(pos <= kMaxCapacity);
        return mBegin + pos * itemSize;
    }

    const void* itemAt(size_t pos, size_t itemSize) const {
        const size_t kMaxCapacity = SIZE_MAX / itemSize;
        DCHECK(pos <= kMaxCapacity);
        return mBegin + pos * itemSize;
    }

    void assignFrom(const PodVectorBase& other);

    inline size_t itemCount(size_t itemSize) const {
        DCHECK(itemSize > 0) << "Item size cannot be 0!";
        return byteSize() / itemSize;
    }

    inline size_t itemCapacity(size_t itemSize) const {
        DCHECK(itemSize > 0) << "Item size cannot be 0!";
        return byteCapacity() / itemSize;
    }

    inline size_t maxItemCapacity(size_t itemSize) const {
        DCHECK(itemSize > 0) << "Item size cannot be 0!";
        return SIZE_MAX / itemSize;
    }

    void resize(size_t newSize, size_t itemSize);
    void reserve(size_t newSize, size_t itemSize);

    void removeAt(size_t index, size_t itemSize);
    void* insertAt(size_t index, size_t itemSize);
    void swapAll(PodVectorBase* other);

    char* mBegin;
    char* mEnd;
    char* mLimit;

private:
    void initFrom(const void* from, size_t fromLen);
};


template <typename T>
class PodVector : public PodVectorBase {
public:
    
    PodVector() : PodVectorBase() {}

    
    
    PodVector(const PodVector& other) : PodVectorBase(other) {}

    
    PodVector& operator=(const PodVector& other) {
        this->assignFrom(other);
        return *this;
    }

    
    
    ~PodVector() {}

    
    
    bool empty() const { return PodVectorBase::empty(); }

    
    size_t size() const { return PodVectorBase::itemCount(sizeof(T)); }

    
    
    
    size_t capacity() const {
        return PodVectorBase::itemCapacity(sizeof(T));
    }

    
    static inline size_t maxCapacity() { return SIZE_MAX / sizeof(T); }

    
    
    
    void resize(size_t newSize) {
        PodVectorBase::resize(newSize, sizeof(T));
    }

    
    
    
    void reserve(size_t newSize) {
        PodVectorBase::reserve(newSize, sizeof(T));
    }

    
    
    
    T* begin() {
        return reinterpret_cast<T*>(PodVectorBase::begin());
    }

    
    
    
    const T* begin() const {
        return reinterpret_cast<T*>(PodVectorBase::begin());
    }

    
    
    
    T* end() {
        return reinterpret_cast<T*>(PodVectorBase::end());
    }

    
    
    
    const T* end() const {
        return reinterpret_cast<T*>(PodVectorBase::end());
    }

    
    
    T& operator[](size_t index) {
        return *reinterpret_cast<T*>(
                PodVectorBase::itemAt(index, sizeof(T)));
    }

    const T& operator[](size_t index) const {
        return *reinterpret_cast<const T*>(
                PodVectorBase::itemAt(index, sizeof(T)));
    }

    
    
    
    
    T* emplace(size_t index) {
        return reinterpret_cast<T*>(
                PodVectorBase::insertAt(index, sizeof(T)));
    }

    
    
    
    
    void insert(size_t index, const T& item) {
        *(this->emplace(index)) = item;
    }

    
    
    
    void prepend(const T& item) {
        *(this->emplace(0U)) = item;
    }

    
    
    void append(const T& item) {
        *(this->emplace(this->size())) = item;
    }

    
    
    
    
    void remove(size_t index) {
        PodVectorBase::removeAt(index, sizeof(T));
    }

    void swap(PodVector* other) {
        PodVectorBase::swapAll(other);
    }

    
    void push_back(const T& item) { append(item); }
    void pop() { remove(0U); }

    typedef T* iterator;
    typedef const T* const_iterator;
};

}  
}  


#endif  
