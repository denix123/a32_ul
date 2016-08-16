// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_SEARCH_TERM_BREAK_ITERATOR_H_
#define UI_APP_LIST_SEARCH_TERM_BREAK_ITERATOR_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "ui/app_list/app_list_export.h"

namespace base {
namespace i18n {
class UTF16CharIterator;
}
}

namespace app_list {

class APP_LIST_EXPORT TermBreakIterator {
 public:
  
  explicit TermBreakIterator(const base::string16& word);
  ~TermBreakIterator();

  
  bool Advance();

  
  
  const base::string16 GetCurrentTerm() const;

  size_t prev() const { return prev_; }
  size_t pos() const { return pos_; }

  static const size_t npos = static_cast<size_t>(-1);

 private:
  enum State {
    STATE_START,   
    STATE_NUMBER,  
    STATE_UPPER,   
    STATE_LOWER,   
    STATE_CHAR,    
    STATE_LAST,
  };

  
  State GetNewState(base::char16 ch);

  const base::string16& word_;
  size_t prev_;
  size_t pos_;

  scoped_ptr<base::i18n::UTF16CharIterator> iter_;
  State state_;

  DISALLOW_COPY_AND_ASSIGN(TermBreakIterator);
};

}  

#endif  
