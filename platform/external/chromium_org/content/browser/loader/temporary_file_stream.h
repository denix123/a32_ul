// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_LOADER_TEMPORARY_FILE_STREAM_H_
#define CONTENT_BROWSER_LOADER_TEMPORARY_FILE_STREAM_H_

#include "base/callback_forward.h"
#include "base/files/file.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"

namespace net {
class FileStream;
}

namespace storage {
class ShareableFileReference;
}

namespace content {

typedef base::Callback<void(base::File::Error,
                            scoped_ptr<net::FileStream>,
                            storage::ShareableFileReference*)>
    CreateTemporaryFileStreamCallback;

CONTENT_EXPORT void CreateTemporaryFileStream(
    const CreateTemporaryFileStreamCallback& callback);

}  

#endif  
