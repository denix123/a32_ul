// Copyright 2008 Google Inc.  All rights reserved.
//     * Redistributions of source code must retain the above copyright
// copyright notice, this list of conditions and the following disclaimer
// this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT


#ifndef GOOGLE_PROTOBUF_GENERATED_MESSAGE_UTIL_H__
#define GOOGLE_PROTOBUF_GENERATED_MESSAGE_UTIL_H__

#include <string>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
namespace google {
namespace protobuf {
namespace internal {

#undef DEPRECATED_PROTOBUF_FIELD
#define PROTOBUF_DEPRECATED


LIBPROTOBUF_EXPORT double Infinity();
LIBPROTOBUF_EXPORT double NaN();

LIBPROTOBUF_EXPORT extern const ::std::string* empty_string_;
LIBPROTOBUF_EXPORT extern ProtobufOnceType empty_string_once_init_;

LIBPROTOBUF_EXPORT void InitEmptyString();

LIBPROTOBUF_EXPORT inline const ::std::string& GetEmptyString() {
  GoogleOnceInit(&empty_string_once_init_, &InitEmptyString);
  return *empty_string_;
}

LIBPROTOBUF_EXPORT int StringSpaceUsedExcludingSelf(const string& str);

}  
}  

}  
#endif  