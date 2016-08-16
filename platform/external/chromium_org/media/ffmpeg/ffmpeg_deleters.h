// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MEDIA_FFMPEG_FFMPEG_DELETERS_H_
#define MEDIA_FFMPEG_FFMPEG_DELETERS_H_

namespace media {

struct ScopedPtrAVFree {
  void operator()(void* x) const;
};

struct ScopedPtrAVFreePacket {
  void operator()(void* x) const;
};

struct ScopedPtrAVFreeContext {
  void operator()(void* x) const;
};

struct ScopedPtrAVFreeFrame {
  void operator()(void* x) const;
};

}  

#endif  
