// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PRINTING_PRINTED_DOCUMENT_H_
#define PRINTING_PRINTED_DOCUMENT_H_

#include <map>

#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "base/synchronization/lock.h"
#include "printing/print_settings.h"
#include "ui/gfx/native_widget_types.h"

namespace base {
class RefCountedMemory;
class TaskRunner;
}

namespace printing {

class MetafilePlayer;
class PrintedPage;
class PrintedPagesSource;
class PrintingContext;

class PRINTING_EXPORT PrintedDocument
    : public base::RefCountedThreadSafe<PrintedDocument> {
 public:
  
  
  PrintedDocument(const PrintSettings& settings,
                  PrintedPagesSource* source,
                  int cookie,
                  base::TaskRunner* blocking_runner);

  
  
  void SetPage(int page_number,
               scoped_ptr<MetafilePlayer> metafile,
#if defined(OS_WIN)
               double shrink,
#endif  
               const gfx::Size& paper_size,
               const gfx::Rect& page_rect);

  
  
  
  scoped_refptr<PrintedPage> GetPage(int page_number);

  
  
#if defined(OS_WIN) || defined(OS_MACOSX) && !defined(USE_AURA)
  void RenderPrintedPage(const PrintedPage& page,
                         gfx::NativeDrawingContext context) const;
#elif defined(OS_POSIX)
  void RenderPrintedPage(const PrintedPage& page,
                         PrintingContext* context) const;
#endif

  
  
  
  bool IsComplete() const;

  
  
  void DisconnectSource();

  
  
  
  void set_page_count(int max_page);

  
  
  int page_count() const;

  
  
  
  
  int expected_page_count() const;

  
  const PrintSettings& settings() const { return immutable_.settings_; }
  const base::string16& name() const { return immutable_.name_; }
  int cookie() const { return immutable_.cookie_; }

  
  
  static void set_debug_dump_path(const base::FilePath& debug_dump_path);

  
  
  
  static base::FilePath CreateDebugDumpPath(
      const base::string16& document_name,
      const base::FilePath::StringType& extension);

  
  void DebugDumpData(const base::RefCountedMemory* data,
                     const base::FilePath::StringType& extension);

 private:
  friend class base::RefCountedThreadSafe<PrintedDocument>;

  virtual ~PrintedDocument();

  
  typedef std::map<int, scoped_refptr<PrintedPage> > PrintedPages;

  
  
  struct Mutable {
    explicit Mutable(PrintedPagesSource* source);
    ~Mutable();

    
    
    PrintedPagesSource* source_;

    
    
    PrintedPages pages_;

    
    
    int expected_page_count_;

    
    int page_count_;

#if defined(OS_POSIX) && !defined(OS_MACOSX)
    
    int first_page;
#endif
  };

  
  
  
  struct Immutable {
    Immutable(const PrintSettings& settings,
              PrintedPagesSource* source,
              int cookie,
              base::TaskRunner* blocking_runner);
    ~Immutable();

    
    PrintSettings settings_;

    
    base::string16 name_;

    
    
    
    
    
    
    int cookie_;

    
    scoped_refptr<base::TaskRunner> blocking_runner_;
  };

  
  
  mutable base::Lock lock_;

  
  Mutable mutable_;

  
  const Immutable immutable_;

  DISALLOW_COPY_AND_ASSIGN(PrintedDocument);
};

}  

#endif  
