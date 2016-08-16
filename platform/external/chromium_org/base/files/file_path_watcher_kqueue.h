// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_FILES_FILE_PATH_WATCHER_KQUEUE_H_
#define BASE_FILES_FILE_PATH_WATCHER_KQUEUE_H_

#include <sys/event.h>
#include <vector>

#include "base/files/file_path.h"
#include "base/files/file_path_watcher.h"
#include "base/message_loop/message_loop.h"
#include "base/message_loop/message_loop_proxy.h"

namespace base {

class FilePathWatcherKQueue : public FilePathWatcher::PlatformDelegate,
                              public MessageLoopForIO::Watcher,
                              public MessageLoop::DestructionObserver {
 public:
  FilePathWatcherKQueue();

  
  virtual void OnFileCanReadWithoutBlocking(int fd) OVERRIDE;
  virtual void OnFileCanWriteWithoutBlocking(int fd) OVERRIDE;

  
  virtual void WillDestroyCurrentMessageLoop() OVERRIDE;

  
  virtual bool Watch(const FilePath& path,
                     bool recursive,
                     const FilePathWatcher::Callback& callback) OVERRIDE;
  virtual void Cancel() OVERRIDE;

 protected:
  virtual ~FilePathWatcherKQueue();

 private:
  class EventData {
   public:
    EventData(const FilePath& path, const FilePath::StringType& subdir)
        : path_(path), subdir_(subdir) { }
    FilePath path_;  
    FilePath::StringType subdir_;  
  };

  typedef std::vector<struct kevent> EventVector;

  
  virtual void CancelOnMessageLoopThread() OVERRIDE;

  
  bool AreKeventValuesValid(struct kevent* kevents, int count);

  
  
  
  void HandleAttributesChange(const EventVector::iterator& event,
                              bool* target_file_affected,
                              bool* update_watches);

  
  
  
  void HandleDeleteOrMoveChange(const EventVector::iterator& event,
                                bool* target_file_affected,
                                bool* update_watches);

  
  
  
  void HandleCreateItemChange(const EventVector::iterator& event,
                              bool* target_file_affected,
                              bool* update_watches);

  
  
  
  bool UpdateWatches(bool* target_file_affected);

  
  
  
  static int EventsForPath(FilePath path, EventVector *events);

  
  static void ReleaseEvent(struct kevent& event);

  
  
  static uintptr_t FileDescriptorForPath(const FilePath& path);

  static const uintptr_t kNoFileDescriptor = static_cast<uintptr_t>(-1);

  
  static void CloseFileDescriptor(uintptr_t* fd);

  
  static bool IsKeventFileDescriptorOpen(const struct kevent& event) {
    return event.ident != kNoFileDescriptor;
  }

  static EventData* EventDataForKevent(const struct kevent& event) {
    return reinterpret_cast<EventData*>(event.udata);
  }

  EventVector events_;
  scoped_refptr<base::MessageLoopProxy> io_message_loop_;
  MessageLoopForIO::FileDescriptorWatcher kqueue_watcher_;
  FilePathWatcher::Callback callback_;
  FilePath target_;
  int kqueue_;

  DISALLOW_COPY_AND_ASSIGN(FilePathWatcherKQueue);
};

}  

#endif  
