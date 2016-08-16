// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SHELL_DATA_PIPE_UTILS_H_
#define MOJO_SHELL_DATA_PIPE_UTILS_H_

#include <string>

#include "base/callback_forward.h"
#include "mojo/common/mojo_common_export.h"
#include "mojo/public/cpp/system/core.h"

namespace base {
class FilePath;
class TaskRunner;
}

namespace mojo {
namespace common {

void MOJO_COMMON_EXPORT CopyToFile(
    ScopedDataPipeConsumerHandle source,
    const base::FilePath& destination,
    base::TaskRunner* task_runner,
    const base::Callback<void(bool )>& callback);

bool MOJO_COMMON_EXPORT BlockingCopyToString(
    ScopedDataPipeConsumerHandle source,
    std::string* contents);

}  
}  

#endif  
