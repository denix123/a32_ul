// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_STRING_H
#define ANDROID_BASE_STRING_H

#include <stddef.h>

namespace android {
namespace base {

class StringView;

class String {
public:
    
    String();

    
    String(const char* string);

    
    String(const String& other);

    
    explicit String(const StringView& other);

    
    String(const char* str, size_t len);

    
    String(size_t count, char fill);

    
    ~String();

    
    const char* c_str() const { return mStr; }

    void* data() { return mStr; }

    const void* data() const { return mStr; }

    
    size_t size() const { return mSize; }

    
    
    bool empty() const { return mSize == 0; }

    
    size_t capacity() const {
        return (mStr == mStorage) ?
                static_cast<size_t>(kMinCapacity) : mCapacity;
    }

    
    void clear() { resize(0); }

    
    char& operator[](size_t index) { return mStr[index]; }
    const char& operator[](size_t index) const { return mStr[index]; }

    
    String& assign(const char* str);
    String& assign(const char* str, size_t len);
    String& assign(const String& other);
    String& assign(const StringView& other);
    String& assign(size_t count, char fill);
    String& assign(char ch);

    
    String& operator=(const char* str) {
        return this->assign(str);
    }

    String& operator=(const String& other) {
        return this->assign(other);
    }

    String& operator=(const StringView& other) {
        return this->assign(other);
    }

    String& operator=(char ch) {
        return this->assign(ch);
    }

    
    String& append(const char* str);
    String& append(const char* str, size_t len);
    String& append(const String& other);
    String& append(const StringView& other);
    String& append(char ch);

    
    String& operator+=(const char* str) {
        return this->append(str);
    }

    String& operator+=(const String& other) {
        return this->append(other);
    }

    String& operator+=(const StringView& other) {
        return this->append(other);
    }

    String& operator+=(char ch) {
        return this->append(ch);
    }

    
    void resize(size_t newSize);

    
    
    void reserve(size_t newSize);

    
    int compare(const char* str, size_t len) const;
    int compare(const char* str) const;
    int compare(const String& other) const;
    int compare(const StringView& other) const;
    int compare(char ch) const;

    
    bool equals(const char* str, size_t len) const;
    bool equals(const char* str) const;
    bool equals(const String& other) const;
    bool equals(const StringView& other) const;
    bool equals(char ch) const;

    
    bool operator==(const char* str) const {
        return equals(str);
    }

    bool operator==(const String& other) const {
        return equals(other);
    }

    bool operator==(const StringView& other) const {
        return equals(other);
    }

    bool operator==(char ch) const {
        return equals(ch);
    }

    bool operator!=(const char* str) const {
        return !operator==(str);
    }

    bool operator!=(const String& other) const {
        return !operator==(other);
    }

    bool operator!=(const StringView& other) const {
        return !operator==(other);
    }

    bool operator!=(char ch) const {
        return !operator==(ch);
    }

    
    void swap(String* other);

protected:
    friend class StringVector;

    
    
    
    
    
    static void adjustMovedSlice(String* fromStrings,
                                 String* toStrings,
                                 size_t count);

    
    
    
    static void moveSlice(String* strings,
                          size_t from,
                          size_t to,
                          size_t count);

    
    
    static void finalizeSlice(String* strings, size_t count);

    
    
    
    
    enum {
        kMinCapacity = 15
    };

    char* mStr;
    size_t mSize;
    union {
        size_t mCapacity;
        char mStorage[kMinCapacity + 1U];
    };
};

}  
}  

#endif  
