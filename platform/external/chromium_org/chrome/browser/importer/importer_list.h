// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_IMPORTER_IMPORTER_LIST_H_
#define CHROME_BROWSER_IMPORTER_IMPORTER_LIST_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"

namespace importer {
struct SourceProfile;
}

class ImporterList {
 public:
  ImporterList();
  ~ImporterList();

  
  
  
  
  
  
  
  
  
  void DetectSourceProfiles(const std::string& locale,
                            bool include_interactive_profiles,
                            const base::Closure& profiles_loaded_callback);

  
  size_t count() const { return source_profiles_.size(); }

  
  
  
  const importer::SourceProfile& GetSourceProfileAt(size_t index) const;

 private:
  
  
  void SourceProfilesLoaded(
      const base::Closure& profiles_loaded_callback,
      const std::vector<importer::SourceProfile*>& profiles);

  
  ScopedVector<importer::SourceProfile> source_profiles_;

  base::WeakPtrFactory<ImporterList> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ImporterList);
};

#endif  
