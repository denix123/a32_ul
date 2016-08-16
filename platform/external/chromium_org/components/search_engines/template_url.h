// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_H_
#define COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_H_

#include <string>
#include <utility>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "components/metrics/proto/omnibox_event.pb.h"
#include "components/metrics/proto/omnibox_input_type.pb.h"
#include "components/search_engines/template_url_data.h"
#include "components/search_engines/template_url_id.h"
#include "ui/gfx/geometry/size.h"
#include "url/gurl.h"
#include "url/url_parse.h"

class SearchTermsData;
class TemplateURL;



class TemplateURLRef {
 public:
  
  
  
  
  enum AcceptedSuggestion {
    NO_SUGGESTION_CHOSEN = -1,
    NO_SUGGESTIONS_AVAILABLE = -2,
  };

  
  
  
  enum Type {
    SEARCH,
    SUGGEST,
    INSTANT,
    IMAGE,
    NEW_TAB,
    CONTEXTUAL_SEARCH,
    INDEXED
  };

  
  
  
  
  
  typedef std::pair<std::string, std::string> PostContent;

  
  
  
  struct SearchTermsArgs {
    explicit SearchTermsArgs(const base::string16& search_terms);
    ~SearchTermsArgs();

    struct ContextualSearchParams {
      ContextualSearchParams();
      
      
      
      
      ContextualSearchParams(const int version,
                             const std::string& selection,
                             const std::string& base_page_url,
                             const bool resolve);
      
      ContextualSearchParams(const int version,
                             const size_t start,
                             const size_t end,
                             const std::string& selection,
                             const std::string& content,
                             const std::string& base_page_url,
                             const std::string& encoding,
                             const bool resolve);
      ~ContextualSearchParams();

      
      int version;

      
      size_t start;

      
      size_t end;

      
      std::string selection;

      
      std::string content;

      
      std::string base_page_url;

      
      std::string encoding;

      
      
      
      bool resolve;
    };

    
    base::string16 search_terms;

    
    base::string16 original_query;

    
    metrics::OmniboxInputType::Type input_type;

    
    
    
    
    
    
    std::string assisted_query_stats;

    
    int accepted_suggestion;

    
    
    size_t cursor_position;

    
    
    bool enable_omnibox_start_margin;

    
    
    std::string current_page_url;

    
    metrics::OmniboxEventProto::PageClassification page_classification;

    
    bool bookmark_bar_pinned;

    
    std::string session_token;

    
    std::string prefetch_query;
    std::string prefetch_query_type;

    
    std::string suggest_query_params;

    
    
    
    
    
    
    
    bool append_extra_query_params;

    
    
    std::string image_thumbnail_content;

    
    
    GURL image_url;

    
    gfx::Size image_original_size;

    
    
    
    
    bool force_instant_results;

    
    
    bool from_app_list;

    ContextualSearchParams contextual_search_params;
  };

  TemplateURLRef(TemplateURL* owner, Type type);
  TemplateURLRef(TemplateURL* owner, size_t index_in_owner);
  ~TemplateURLRef();

  
  std::string GetURL() const;

  
  
  std::string GetPostParamsString() const;

  
  bool SupportsReplacement(const SearchTermsData& search_terms_data) const;

  
  
  
  
  
  
  
  
  std::string ReplaceSearchTerms(const SearchTermsArgs& search_terms_args,
                                 const SearchTermsData& search_terms_data,
                                 PostContent* post_content) const;

  
  
  
  std::string ReplaceSearchTerms(
      const SearchTermsArgs& search_terms_args,
      const SearchTermsData& search_terms_data) const {
    return ReplaceSearchTerms(search_terms_args, search_terms_data, NULL);
  }

  
  
  bool IsValid(const SearchTermsData& search_terms_data) const;

  
  
  base::string16 DisplayURL(const SearchTermsData& search_terms_data) const;

  
  
  static std::string DisplayURLToURLRef(const base::string16& display_url);

  
  
  const std::string& GetHost(const SearchTermsData& search_terms_data) const;
  const std::string& GetPath(const SearchTermsData& search_terms_data) const;

  
  
  const std::string& GetSearchTermKey(
      const SearchTermsData& search_terms_data) const;

  
  base::string16 SearchTermToString16(const std::string& term) const;

  
  
  bool HasGoogleBaseURLs(const SearchTermsData& search_terms_data) const;

  
  
  
  
  
  
  
  
  bool ExtractSearchTermsFromURL(
      const GURL& url,
      base::string16* search_terms,
      const SearchTermsData& search_terms_data,
      url::Parsed::ComponentType* search_term_component,
      url::Component* search_terms_position) const;

  
  bool UsesPOSTMethod(const SearchTermsData& search_terms_data) const;

 private:
  friend class TemplateURL;
  FRIEND_TEST_ALL_PREFIXES(TemplateURLTest, SetPrepopulatedAndParse);
  FRIEND_TEST_ALL_PREFIXES(TemplateURLTest, ParseParameterKnown);
  FRIEND_TEST_ALL_PREFIXES(TemplateURLTest, ParseParameterUnknown);
  FRIEND_TEST_ALL_PREFIXES(TemplateURLTest, ParseURLEmpty);
  FRIEND_TEST_ALL_PREFIXES(TemplateURLTest, ParseURLNoTemplateEnd);
  FRIEND_TEST_ALL_PREFIXES(TemplateURLTest, ParseURLNoKnownParameters);
  FRIEND_TEST_ALL_PREFIXES(TemplateURLTest, ParseURLTwoParameters);
  FRIEND_TEST_ALL_PREFIXES(TemplateURLTest, ParseURLNestedParameter);
  FRIEND_TEST_ALL_PREFIXES(TemplateURLTest, URLRefTestImageURLWithPOST);
  FRIEND_TEST_ALL_PREFIXES(TemplateURLTest, ReflectsBookmarkBarPinned);

  
  enum ReplacementType {
    ENCODING,
    GOOGLE_ASSISTED_QUERY_STATS,
    GOOGLE_BASE_URL,
    GOOGLE_BASE_SUGGEST_URL,
    GOOGLE_BOOKMARK_BAR_PINNED,
    GOOGLE_CURRENT_PAGE_URL,
    GOOGLE_CURSOR_POSITION,
    GOOGLE_FORCE_INSTANT_RESULTS,
    GOOGLE_IMAGE_ORIGINAL_HEIGHT,
    GOOGLE_IMAGE_ORIGINAL_WIDTH,
    GOOGLE_IMAGE_SEARCH_SOURCE,
    GOOGLE_IMAGE_THUMBNAIL,
    GOOGLE_IMAGE_URL,
    GOOGLE_INPUT_TYPE,
    GOOGLE_INSTANT_EXTENDED_ENABLED,
    GOOGLE_NTP_IS_THEMED,
    GOOGLE_OMNIBOX_START_MARGIN,
    GOOGLE_CONTEXTUAL_SEARCH_VERSION,
    GOOGLE_CONTEXTUAL_SEARCH_CONTEXT_DATA,
    GOOGLE_ORIGINAL_QUERY_FOR_SUGGESTION,
    GOOGLE_PAGE_CLASSIFICATION,
    GOOGLE_PREFETCH_QUERY,
    GOOGLE_RLZ,
    GOOGLE_SEARCH_CLIENT,
    GOOGLE_SEARCH_FIELDTRIAL_GROUP,
    GOOGLE_SEARCH_VERSION,
    GOOGLE_SESSION_TOKEN,
    GOOGLE_SUGGEST_CLIENT,
    GOOGLE_SUGGEST_REQUEST_ID,
    GOOGLE_UNESCAPED_SEARCH_TERMS,
    LANGUAGE,
    SEARCH_TERMS,
  };

  
  struct Replacement {
    Replacement(ReplacementType type, size_t index)
        : type(type), index(index), is_post_param(false) {}
    ReplacementType type;
    size_t index;
    
    
    
    bool is_post_param;
  };

  
  typedef std::vector<struct Replacement> Replacements;
  
  typedef std::pair<std::string, std::string> PostParam;
  typedef std::vector<PostParam> PostParams;

  
  
  void InvalidateCachedValues() const;

  
  
  
  
  
  
  
  
  
  bool ParseParameter(size_t start,
                      size_t end,
                      std::string* url,
                      Replacements* replacements) const;

  
  
  
  
  
  
  
  
  std::string ParseURL(const std::string& url,
                       Replacements* replacements,
                       PostParams* post_params,
                       bool* valid) const;

  
  
  
  void ParseIfNecessary(const SearchTermsData& search_terms_data) const;

  
  void ParseHostAndSearchTermKey(
      const SearchTermsData& search_terms_data) const;

  
  
  
  bool EncodeFormData(const PostParams& post_params,
                      PostContent* post_content) const;

  
  
  
  
  void HandleReplacement(const std::string& name,
                         const std::string& value,
                         const Replacement& replacement,
                         std::string* url) const;

  
  
  
  std::string HandleReplacements(
      const SearchTermsArgs& search_terms_args,
      const SearchTermsData& search_terms_data,
      PostContent* post_content) const;

  
  TemplateURL* const owner_;

  
  const Type type_;

  
  
  const size_t index_in_owner_;

  
  mutable bool parsed_;

  
  mutable bool valid_;

  
  
  mutable std::string parsed_url_;

  
  mutable bool supports_replacements_;

  
  
  mutable Replacements replacements_;

  
  
  mutable std::string host_;
  mutable std::string path_;
  mutable std::string search_term_key_;
  mutable url::Parsed::ComponentType search_term_key_location_;

  mutable PostParams post_params_;

  
  bool prepopulated_;

  DISALLOW_COPY_AND_ASSIGN(TemplateURLRef);
};



class TemplateURL {
 public:
  enum Type {
    
    NORMAL,
    
    NORMAL_CONTROLLED_BY_EXTENSION,
    
    OMNIBOX_API_EXTENSION,
  };

  
  
  struct AssociatedExtensionInfo {
    AssociatedExtensionInfo(Type type, const std::string& extension_id);
    ~AssociatedExtensionInfo();

    Type type;

    std::string extension_id;

    
    bool wants_to_be_default_engine;

    
    
    base::Time install_time;
  };

  explicit TemplateURL(const TemplateURLData& data);
  ~TemplateURL();

  
  
  
  static base::string16 GenerateKeyword(const GURL& url);

  
  static GURL GenerateFaviconURL(const GURL& url);

  
  
  static bool MatchesData(const TemplateURL* t_url,
                          const TemplateURLData* data,
                          const SearchTermsData& search_terms_data);

  const TemplateURLData& data() const { return data_; }

  const base::string16& short_name() const { return data_.short_name; }
  
  
  base::string16 AdjustedShortNameForLocaleDirection() const;

  const base::string16& keyword() const { return data_.keyword(); }

  const std::string& url() const { return data_.url(); }
  const std::string& suggestions_url() const { return data_.suggestions_url; }
  const std::string& instant_url() const { return data_.instant_url; }
  const std::string& image_url() const { return data_.image_url; }
  const std::string& new_tab_url() const { return data_.new_tab_url; }
  const std::string& contextual_search_url() const {
    return data_.contextual_search_url;
  }
  const std::string& search_url_post_params() const {
    return data_.search_url_post_params;
  }
  const std::string& suggestions_url_post_params() const {
    return data_.suggestions_url_post_params;
  }
  const std::string& instant_url_post_params() const {
    return data_.instant_url_post_params;
  }
  const std::string& image_url_post_params() const {
    return data_.image_url_post_params;
  }
  const std::vector<std::string>& alternate_urls() const {
    return data_.alternate_urls;
  }
  const GURL& favicon_url() const { return data_.favicon_url; }

  const GURL& originating_url() const { return data_.originating_url; }

  bool show_in_default_list() const { return data_.show_in_default_list; }
  
  
  bool ShowInDefaultList(const SearchTermsData& search_terms_data) const;

  bool safe_for_autoreplace() const { return data_.safe_for_autoreplace; }

  const std::vector<std::string>& input_encodings() const {
    return data_.input_encodings;
  }

  TemplateURLID id() const { return data_.id; }

  base::Time date_created() const { return data_.date_created; }
  base::Time last_modified() const { return data_.last_modified; }

  bool created_by_policy() const { return data_.created_by_policy; }

  int usage_count() const { return data_.usage_count; }

  int prepopulate_id() const { return data_.prepopulate_id; }

  const std::string& sync_guid() const { return data_.sync_guid; }

  
  const std::string& search_terms_replacement_key() const {
    return data_.search_terms_replacement_key;
  }

  const TemplateURLRef& url_ref() const { return url_ref_; }
  const TemplateURLRef& suggestions_url_ref() const {
    return suggestions_url_ref_;
  }
  const TemplateURLRef& instant_url_ref() const { return instant_url_ref_; }
  const TemplateURLRef& image_url_ref() const { return image_url_ref_; }
  const TemplateURLRef& new_tab_url_ref() const { return new_tab_url_ref_; }
  const TemplateURLRef& contextual_search_url_ref() const {
    return contextual_search_url_ref_;
  }

  
  
  void set_extension_info(scoped_ptr<AssociatedExtensionInfo> extension_info) {
    extension_info_ = extension_info.Pass();
  }

  
  bool SupportsReplacement(const SearchTermsData& search_terms_data) const;

  
  bool HasGoogleBaseURLs(const SearchTermsData& search_terms_data) const;

  
  
  
  bool IsGoogleSearchURLWithReplaceableKeyword(
      const SearchTermsData& search_terms_data) const;

  
  
  
  bool HasSameKeywordAs(const TemplateURLData& other,
                        const SearchTermsData& search_terms_data) const;

  Type GetType() const;

  
  
  
  std::string GetExtensionId() const;

  
  
  size_t URLCount() const;

  
  
  
  
  const std::string& GetURL(size_t index) const;

  
  
  
  
  
  
  
  
  
  
  bool ExtractSearchTermsFromURL(const GURL& url,
                                 const SearchTermsData& search_terms_data,
                                 base::string16* search_terms);

  
  
  
  bool IsSearchURL(const GURL& url, const SearchTermsData& search_terms_data);

  
  
  
  
  
  
  bool HasSearchTermsReplacementKey(const GURL& url) const;

  
  
  
  
  
  bool ReplaceSearchTermsInURL(
      const GURL& url,
      const TemplateURLRef::SearchTermsArgs& search_terms_args,
      const SearchTermsData& search_terms_data,
      GURL* result);

  
  
  
  
  
  void EncodeSearchTerms(
      const TemplateURLRef::SearchTermsArgs& search_terms_args,
      bool is_in_query,
      std::string* input_encoding,
      base::string16* encoded_terms,
      base::string16* encoded_original_query) const;

  
  
  GURL GenerateSearchURL(const SearchTermsData& search_terms_data) const;

 private:
  friend class TemplateURLService;
  FRIEND_TEST_ALL_PREFIXES(TemplateURLTest, ReflectsBookmarkBarPinned);

  void CopyFrom(const TemplateURL& other);

  void SetURL(const std::string& url);
  void SetPrepopulateId(int id);

  
  
  
  
  void ResetKeywordIfNecessary(const SearchTermsData& search_terms_data,
                               bool force);

  
  
  
  
  bool FindSearchTermsInURL(const GURL& url,
                            const SearchTermsData& search_terms_data,
                            base::string16* search_terms,
                            url::Parsed::ComponentType* search_terms_component,
                            url::Component* search_terms_position);

  TemplateURLData data_;
  TemplateURLRef url_ref_;
  TemplateURLRef suggestions_url_ref_;
  TemplateURLRef instant_url_ref_;
  TemplateURLRef image_url_ref_;
  TemplateURLRef new_tab_url_ref_;
  TemplateURLRef contextual_search_url_ref_;
  scoped_ptr<AssociatedExtensionInfo> extension_info_;

  

  DISALLOW_COPY_AND_ASSIGN(TemplateURL);
};

#endif  
