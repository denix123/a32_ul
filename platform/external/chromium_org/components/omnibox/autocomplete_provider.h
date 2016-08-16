// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_AUTOCOMPLETE_PROVIDER_H_
#define COMPONENTS_OMNIBOX_AUTOCOMPLETE_PROVIDER_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/strings/string16.h"
#include "components/metrics/proto/omnibox_event.pb.h"
#include "components/omnibox/autocomplete_match.h"

class AutocompleteInput;

typedef std::vector<metrics::OmniboxEventProto_ProviderInfo> ProvidersInfo;

class AutocompleteProvider
    : public base::RefCountedThreadSafe<AutocompleteProvider> {
 public:
  
  enum Type {
    TYPE_BOOKMARK         = 1 << 0,
    TYPE_BUILTIN          = 1 << 1,
    TYPE_HISTORY_QUICK    = 1 << 2,
    TYPE_HISTORY_URL      = 1 << 3,
    TYPE_KEYWORD          = 1 << 4,
    TYPE_SEARCH           = 1 << 5,
    TYPE_SHORTCUTS        = 1 << 6,
    TYPE_ZERO_SUGGEST     = 1 << 7,
  };

  explicit AutocompleteProvider(Type type);

  
  static const char* TypeToString(Type type);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void Start(const AutocompleteInput& input, bool minimal_changes) = 0;

  
  
  
  
  virtual void Stop(bool clear_cached_results);

  
  
  
  metrics::OmniboxEventProto_ProviderType AsOmniboxEventProviderType() const;

  
  
  
  
  
  
  virtual void DeleteMatch(const AutocompleteMatch& match);

  
  
  
  
  virtual void AddProviderInfo(ProvidersInfo* provider_info) const;

  
  
  
  virtual void ResetSession();

  
  const ACMatches& matches() const { return matches_; }

  
  bool done() const { return done_; }

  
  Type type() const { return type_; }

  
  const char* GetName() const;

  
  
  
  
  static const size_t kMaxMatches;

 protected:
  friend class base::RefCountedThreadSafe<AutocompleteProvider>;
  FRIEND_TEST_ALL_PREFIXES(BookmarkProviderTest, InlineAutocompletion);

  typedef std::pair<bool, base::string16> FixupReturn;

  virtual ~AutocompleteProvider();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static FixupReturn FixupUserInput(const AutocompleteInput& input);

  
  
  
  
  static size_t TrimHttpPrefix(base::string16* url);

  ACMatches matches_;
  bool done_;

  Type type_;

 private:
  DISALLOW_COPY_AND_ASSIGN(AutocompleteProvider);
};

#endif  
