// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_SEARCH_SUGGESTION_PARSER_H_
#define COMPONENTS_OMNIBOX_SEARCH_SUGGESTION_PARSER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/strings/string16.h"
#include "components/omnibox/autocomplete_match.h"
#include "components/omnibox/autocomplete_match_type.h"
#include "url/gurl.h"

class AutocompleteInput;
class AutocompleteSchemeClassifier;

namespace base {
class DictionaryValue;
class Value;
}

namespace net {
class URLFetcher;
}

class SearchSuggestionParser {
 public:
  
  
  
  
  
  
  
  class Result {
   public:
    Result(bool from_keyword_provider,
           int relevance,
           bool relevance_from_server,
           AutocompleteMatchType::Type type,
           const std::string& deletion_url);
    virtual ~Result();

    bool from_keyword_provider() const { return from_keyword_provider_; }

    const base::string16& match_contents() const { return match_contents_; }
    const ACMatchClassifications& match_contents_class() const {
      return match_contents_class_;
    }

    AutocompleteMatchType::Type type() const { return type_; }
    int relevance() const { return relevance_; }
    void set_relevance(int relevance) { relevance_ = relevance; }
    bool received_after_last_keystroke() const {
      return received_after_last_keystroke_;
    }
    void set_received_after_last_keystroke(
        bool received_after_last_keystroke) {
      received_after_last_keystroke_ = received_after_last_keystroke;
    }

    bool relevance_from_server() const { return relevance_from_server_; }
    void set_relevance_from_server(bool relevance_from_server) {
      relevance_from_server_ = relevance_from_server;
    }

    const std::string& deletion_url() const { return deletion_url_; }

    
    
    
    
    virtual int CalculateRelevance(const AutocompleteInput& input,
                                   bool keyword_provider_requested) const = 0;

   protected:
    
    base::string16 match_contents_;
    ACMatchClassifications match_contents_class_;

    
    bool from_keyword_provider_;

    AutocompleteMatchType::Type type_;

    
    int relevance_;

   private:
    
    
    
    
    
    bool relevance_from_server_;

    
    
    
    bool received_after_last_keystroke_;

    
    
    
    std::string deletion_url_;
  };

  class SuggestResult : public Result {
   public:
    SuggestResult(const base::string16& suggestion,
                  AutocompleteMatchType::Type type,
                  const base::string16& match_contents,
                  const base::string16& match_contents_prefix,
                  const base::string16& annotation,
                  const base::string16& answer_contents,
                  const base::string16& answer_type,
                  const std::string& suggest_query_params,
                  const std::string& deletion_url,
                  bool from_keyword_provider,
                  int relevance,
                  bool relevance_from_server,
                  bool should_prefetch,
                  const base::string16& input_text);
    virtual ~SuggestResult();

    const base::string16& suggestion() const { return suggestion_; }
    const base::string16& match_contents_prefix() const {
      return match_contents_prefix_;
    }
    const base::string16& annotation() const { return annotation_; }
    const std::string& suggest_query_params() const {
      return suggest_query_params_;
    }

    const base::string16& answer_contents() const { return answer_contents_; }
    const base::string16& answer_type() const { return answer_type_; }

    bool should_prefetch() const { return should_prefetch_; }

    
    
    
    
    void ClassifyMatchContents(const bool allow_bolding_all,
                               const base::string16& input_text);

    
    virtual int CalculateRelevance(
        const AutocompleteInput& input,
        bool keyword_provider_requested) const OVERRIDE;

   private:
    
    base::string16 suggestion_;

    
    
    
    
    base::string16 match_contents_prefix_;

    
    
    
    base::string16 annotation_;

    
    std::string suggest_query_params_;

    
    base::string16 answer_contents_;

    
    base::string16 answer_type_;

    
    bool should_prefetch_;
  };

  class NavigationResult : public Result {
   public:
    NavigationResult(const AutocompleteSchemeClassifier& scheme_classifier,
                     const GURL& url,
                     AutocompleteMatchType::Type type,
                     const base::string16& description,
                     const std::string& deletion_url,
                     bool from_keyword_provider,
                     int relevance,
                     bool relevance_from_server,
                     const base::string16& input_text,
                     const std::string& languages);
    virtual ~NavigationResult();

    const GURL& url() const { return url_; }
    const base::string16& description() const { return description_; }
    const base::string16& formatted_url() const { return formatted_url_; }

    
    
    
    
    
    void CalculateAndClassifyMatchContents(const bool allow_bolding_nothing,
                                           const base::string16& input_text,
                                           const std::string& languages);

    
    virtual int CalculateRelevance(
        const AutocompleteInput& input,
        bool keyword_provider_requested) const OVERRIDE;

   private:
    
    GURL url_;

    
    
    base::string16 formatted_url_;

    
    base::string16 description_;
  };

  typedef std::vector<SuggestResult> SuggestResults;
  typedef std::vector<NavigationResult> NavigationResults;

  
  
  
  
  
  struct Results {
    Results();
    ~Results();

    
    
    void Clear();

    
    
    bool HasServerProvidedScores() const;

    
    SuggestResults suggest_results;

    
    NavigationResults navigation_results;

    
    
    
    int verbatim_relevance;

    
    std::string metadata;

    
    bool field_trial_triggered;

    
    bool relevances_from_server;

    
    std::vector<GURL> answers_image_urls;

   private:
    DISALLOW_COPY_AND_ASSIGN(Results);
  };

  
  static std::string ExtractJsonData(const net::URLFetcher* source);

  
  
  
  static scoped_ptr<base::Value> DeserializeJsonData(std::string json_data);

  
  
  
  
  static bool ParseSuggestResults(
      const base::Value& root_val,
      const AutocompleteInput& input,
      const AutocompleteSchemeClassifier& scheme_classifier,
      int default_result_relevance,
      const std::string& languages,
      bool is_keyword_result,
      Results* results);

 private:
  FRIEND_TEST_ALL_PREFIXES(SearchSuggestionParser,
                           GetAnswersImageURLsWithoutImagelines);
  FRIEND_TEST_ALL_PREFIXES(SearchSuggestionParser,
                           GetAnswersImageURLsWithValidImage);

  
  static void GetAnswersImageURLs(const base::DictionaryValue* answer_json,
                                  std::vector<GURL>* urls);

  DISALLOW_COPY_AND_ASSIGN(SearchSuggestionParser);
};

#endif  
