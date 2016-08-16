// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_CONTAINERS_STRING_VECTOR_H
#define ANDROID_BASE_CONTAINERS_STRING_VECTOR_H

#include "android/base/containers/PodVector.h"
#include "android/base/String.h"
#include "android/base/StringView.h"

namespace android {
namespace base {

class StringVector : public PodVector<String> {
public:
    
    StringVector() : PodVector<String>() {}

    
    StringVector(const StringVector& other);

    
    StringVector& operator=(const StringVector& other);

    
    ~StringVector();

    
    
    
    void resize(size_t newSize);
    void reserve(size_t newSize);

    void remove(size_t index);
    String* emplace(size_t index);
    void insert(size_t index, const String& str);
    void prepend(const String& str);
    void append(const String& str);
    void swap(StringVector* other);

    
    void push_back(const String& str) { append(str);  }
    void pop() { remove(0U);  }

    
    
    
    
    void insert(size_t index, const StringView& view);
    void prepend(const StringView& view);
    void append(const StringView& view);
};

}  
}  

#endif  
