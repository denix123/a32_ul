// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BOOKMARKS_COMMON_ANDROID_BOOKMARK_ID_H_
#define COMPONENTS_BOOKMARKS_COMMON_ANDROID_BOOKMARK_ID_H_

#include <jni.h>

namespace bookmarks {
namespace android {

long JavaBookmarkIdGetId(JNIEnv* env, jobject obj);

int JavaBookmarkIdGetType(JNIEnv* env, jobject obj);

bool RegisterBookmarkId(JNIEnv* env);

}  
}  

#endif  
