// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SHELL_MOJO_URL_RESOLVER_H_
#define MOJO_SHELL_MOJO_URL_RESOLVER_H_

#include <map>
#include <set>

#include "url/gurl.h"

namespace mojo {
namespace shell {

class MojoURLResolver {
 public:
  MojoURLResolver();
  ~MojoURLResolver();

  
  
  
  
  void SetBaseURL(const GURL& base_url);

  
  void AddCustomMapping(const GURL& mojo_url, const GURL& resolved_url);

  
  
  void AddLocalFileMapping(const GURL& mojo_url);

  
  
  GURL Resolve(const GURL& mojo_url) const;

 private:
  std::map<GURL, GURL> url_map_;
  std::set<GURL> local_file_set_;
  GURL default_base_url_;
  GURL base_url_;
};

}  
}  

#endif  
