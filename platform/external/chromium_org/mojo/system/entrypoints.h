// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_ENTRYPOINTS_H
#define MOJO_SYSTEM_ENTRYPOINTS_H

namespace mojo {
namespace system {

class Core;

namespace entrypoints {

void SetCore(Core* core);
Core* GetCore();

}  
}  
}  

#endif  
