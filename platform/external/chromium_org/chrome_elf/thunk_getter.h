// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_ELF_THUNK_GETTER_H_
#define CHROME_ELF_THUNK_GETTER_H_

namespace sandbox {
class ServiceResolverThunk;
}

sandbox::ServiceResolverThunk* GetThunk(bool relaxed);

#endif  
