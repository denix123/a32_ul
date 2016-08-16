// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_NACL_MESSAGE_SCANNER_H_
#define PPAPI_PROXY_NACL_MESSAGE_SCANNER_H_

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/proxy/ppapi_proxy_export.h"

namespace IPC {
class Message;
}

namespace ppapi {
namespace proxy {

class SerializedHandle;

class PPAPI_PROXY_EXPORT NaClMessageScanner {
 public:
  NaClMessageScanner();
  ~NaClMessageScanner();

  
  
  // rewritten for NaCl, sets |new_msg_ptr| to the new message. If no handles
  
  
  
  
  
  
  
  
  
  
  
  bool ScanMessage(const IPC::Message& msg,
                   uint32_t type,
                   std::vector<SerializedHandle>* handles,
                   scoped_ptr<IPC::Message>* new_msg_ptr);

  
  // message had to be rewritten, sets |new_msg_ptr| to the new message.
  void ScanUntrustedMessage(const IPC::Message& untrusted_msg,
                            scoped_ptr<IPC::Message>* new_msg_ptr);

  
  class PPAPI_PROXY_EXPORT FileSystem {
   public:
    FileSystem();
    ~FileSystem();

    int64_t reserved_quota() const { return reserved_quota_; }

    
    bool UpdateReservedQuota(int64_t delta);

   private:
    base::Lock lock_;
    
    
    
    int64_t reserved_quota_;

    DISALLOW_COPY_AND_ASSIGN(FileSystem);
  };

  
  class PPAPI_PROXY_EXPORT FileIO {
   public:
    FileIO(FileSystem* file_system, int64_t max_written_offset);
    ~FileIO();

    int64_t max_written_offset() { return max_written_offset_; }

    void SetMaxWrittenOffset(int64_t max_written_offset);

    
    bool Grow(int64_t amount);

   private:
    base::Lock lock_;

    
    FileSystem* file_system_;

    // The maximum written offset. This is initialized by NaClMessageScanner
    
    
    int64_t max_written_offset_;

    DISALLOW_COPY_AND_ASSIGN(FileIO);
  };

  FileIO* GetFile(PP_Resource file_io);

 private:
  friend class NaClMessageScannerTest;
  void AuditNestedMessage(PP_Resource resource,
                          const IPC::Message& msg,
                          SerializedHandle* handle);

  
  
  
  typedef std::map<int32_t, FileSystem*> FileSystemMap;
  FileSystemMap file_systems_;
  typedef std::map<int32_t, FileIO*> FileIOMap;
  FileIOMap files_;

  DISALLOW_COPY_AND_ASSIGN(NaClMessageScanner);
};

}  
}  

#endif  
