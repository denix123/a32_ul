// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_ZIP_H
#define CRAZY_ZIP_H


namespace crazy {

int FindStartOffsetOfFileInZipFile(const char* zip_file, const char* filename);

}

#endif  
