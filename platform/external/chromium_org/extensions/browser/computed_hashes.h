// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_COMPUTED_HASHES_H_
#define EXTENSIONS_BROWSER_COMPUTED_HASHES_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"

namespace base {
class FilePath;
class ListValue;
}

namespace extensions {

class ComputedHashes {
 public:
  class Reader {
   public:
    Reader();
    ~Reader();
    bool InitFromFile(const base::FilePath& path);

    
    
    bool GetHashes(const base::FilePath& relative_path,
                   int* block_size,
                   std::vector<std::string>* hashes);

   private:
    typedef std::pair<int, std::vector<std::string> > HashInfo;

    
    std::map<base::FilePath, HashInfo> data_;
  };

  class Writer {
   public:
    Writer();
    ~Writer();

    
    
    void AddHashes(const base::FilePath& relative_path,
                   int block_size,
                   const std::vector<std::string>& hashes);

    bool WriteToFile(const base::FilePath& path);

   private:
    
    
    scoped_ptr<base::ListValue> file_list_;
  };

  
  
  static void ComputeHashesForContent(const std::string& contents,
                                      size_t block_size,
                                      std::vector<std::string>* hashes);
};

}  

#endif  
