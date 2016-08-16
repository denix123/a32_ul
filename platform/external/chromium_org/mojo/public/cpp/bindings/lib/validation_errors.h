// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_LIB_VALIDATION_ERRORS_H_
#define MOJO_PUBLIC_CPP_BINDINGS_LIB_VALIDATION_ERRORS_H_

#include "mojo/public/cpp/system/macros.h"

namespace mojo {
namespace internal {

enum ValidationError {
  
  VALIDATION_ERROR_NONE,
  
  VALIDATION_ERROR_MISALIGNED_OBJECT,
  
  
  VALIDATION_ERROR_ILLEGAL_MEMORY_RANGE,
  
  
  
  
  
  
  VALIDATION_ERROR_UNEXPECTED_STRUCT_HEADER,
  
  
  
  
  
  VALIDATION_ERROR_UNEXPECTED_ARRAY_HEADER,
  
  VALIDATION_ERROR_ILLEGAL_HANDLE,
  
  VALIDATION_ERROR_UNEXPECTED_INVALID_HANDLE,
  
  VALIDATION_ERROR_ILLEGAL_POINTER,
  
  VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
  
  VALIDATION_ERROR_MESSAGE_HEADER_INVALID_FLAG_COMBINATION,
  
  
  VALIDATION_ERROR_MESSAGE_HEADER_MISSING_REQUEST_ID,
};

const char* ValidationErrorToString(ValidationError error);

void ReportValidationError(ValidationError error,
                           const char* description = NULL);

class ValidationErrorObserverForTesting {
 public:
  ValidationErrorObserverForTesting();
  ~ValidationErrorObserverForTesting();

  ValidationError last_error() const { return last_error_; }
  void set_last_error(ValidationError error) { last_error_ = error; }

 private:
  ValidationError last_error_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(ValidationErrorObserverForTesting);
};

bool ReportSerializationWarning(ValidationError error);

class SerializationWarningObserverForTesting {
 public:
  SerializationWarningObserverForTesting();
  ~SerializationWarningObserverForTesting();

  ValidationError last_warning() const { return last_warning_; }
  void set_last_warning(ValidationError error) { last_warning_ = error; }

 private:
  ValidationError last_warning_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(SerializationWarningObserverForTesting);
};

}  
}  

#define MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING( \
    condition, error, description) \
  MOJO_DLOG_IF(FATAL, (condition) && !ReportSerializationWarning(error)) \
      << "The outgoing message will trigger " \
      << ValidationErrorToString(error) << " at the receiving side (" \
      << description << ").";

#endif  
