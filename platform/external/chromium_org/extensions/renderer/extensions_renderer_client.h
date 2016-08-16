// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_EXTENSIONS_RENDERER_CLIENT_H_
#define EXTENSIONS_RENDERER_EXTENSIONS_RENDERER_CLIENT_H_

class ResourceBundleSourceMap;

namespace extensions {

class ExtensionsRendererClient {
 public:
  virtual ~ExtensionsRendererClient() {}

  
  virtual bool IsIncognitoProcess() const = 0;

  
  
  
  virtual int GetLowestIsolatedWorldId() const = 0;

  
  static ExtensionsRendererClient* Get();

  
  static void Set(ExtensionsRendererClient* client);
};

}  

#endif  
