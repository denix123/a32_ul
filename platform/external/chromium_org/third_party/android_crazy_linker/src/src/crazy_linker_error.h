// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_ERROR_H
#define CRAZY_LINKER_ERROR_H

namespace crazy {

class Error {
 public:
  Error() { buff_[0] = '\0'; }

  Error(const char* message) { Set(message); }

  Error(const Error& other) { Set(other.buff_); }

  const char* c_str() const { return buff_; }

  void Set(const char* message);

  void Format(const char* fmt, ...);

  void Append(const char* message);

  void AppendFormat(const char* fmt, ...);

 private:
  char buff_[512];
};

}  

#endif  
