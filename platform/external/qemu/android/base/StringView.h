// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_STRING_VIEW_H
#define ANDROID_BASE_STRING_VIEW_H

#include <string.h>

namespace android {
namespace base {

class String;

class StringView {
public:
    StringView() : mString(NULL), mSize(0U) {}

    StringView(const StringView& other) :
        mString(other.data()), mSize(other.size()) {}

    
    StringView(const char* string) :
            mString(string), mSize(strlen(string)) {}

    explicit StringView(const String& str);

    StringView(const char* str, size_t len) : mString(str), mSize(len) {}

    const char* str() const { return mString; }
    const char* data() const { return mString; }
    size_t size() const { return mSize; }

    typedef const char* iterator;
    typedef const char* const_iterator;

    const_iterator begin() const { return mString; }
    const_iterator end() const { return mString + mSize; }

    bool empty() const { return !size(); }

    void clear() {
        mSize = 0;
        mString = NULL;
    }

    char operator[](size_t index) {
        return mString[index];
    }

    void set(const char* data, size_t len) {
        mString = data;
        mSize = len;
    }

    void set(const char* str) {
        mString = str;
        mSize = ::strlen(str);
    }

    void set(const StringView& other) {
        mString = other.mString;
        mSize = other.mSize;
    }

    
    int compare(const StringView& other) const;

    StringView& operator=(const StringView& other) {
        set(other);
        return *this;
    }

private:
    const char* mString;
    size_t mSize;
};


bool operator==(const StringView& x, const StringView& y);

inline bool operator!=(const StringView& x, const StringView& y) {
    return !(x == y);
}

inline bool operator<(const StringView& x, const StringView& y) {
    return x.compare(y) < 0;
}

inline bool operator>=(const StringView& x, const StringView& y) {
    return !(x < y);
}

inline bool operator >(const StringView& x, const StringView& y) {
    return x.compare(y) > 0;
}

inline bool operator<=(const StringView& x, const StringView& y) {
    return !(x > y);
}

}  
}  

#endif  
