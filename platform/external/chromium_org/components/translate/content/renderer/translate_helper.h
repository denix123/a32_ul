// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CONTENT_RENDERER_TRANSLATE_HELPER_H_
#define COMPONENTS_TRANSLATE_CONTENT_RENDERER_TRANSLATE_HELPER_H_

#include <string>

#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "components/translate/content/renderer/renderer_cld_data_provider.h"
#include "components/translate/core/common/translate_errors.h"
#include "content/public/renderer/render_view_observer.h"
#include "url/gurl.h"

namespace blink {
class WebDocument;
class WebFrame;
}

namespace content {
class RendererCldDataProvider;
}

namespace translate {

class TranslateHelper : public content::RenderViewObserver {
 public:
  explicit TranslateHelper(content::RenderView* render_view,
                           int world_id,
                           int extension_group,
                           const std::string& extension_scheme);
  virtual ~TranslateHelper();

  
  void PageCaptured(const base::string16& contents);

  
  
  
  void PrepareForUrl(const GURL& url);

 protected:
  
  
  void OnTranslatePage(int page_seq_no,
                       const std::string& translate_script,
                       const std::string& source_lang,
                       const std::string& target_lang);
  void OnRevertTranslation(int page_seq_no);

  
  
  virtual bool IsTranslateLibAvailable();

  
  virtual bool IsTranslateLibReady();

  
  virtual bool HasTranslationFinished();

  
  
  virtual bool HasTranslationFailed();

  
  
  
  virtual bool StartTranslation();

  
  
  
  virtual std::string GetOriginalPageLanguage();

  
  
  virtual base::TimeDelta AdjustDelay(int delayInMs);

  
  virtual void ExecuteScript(const std::string& script);

  
  
  
  virtual bool ExecuteScriptAndGetBoolResult(const std::string& script,
                                             bool fallback);

  
  
  
  virtual std::string ExecuteScriptAndGetStringResult(
      const std::string& script);

  
  
  
  virtual double ExecuteScriptAndGetDoubleResult(const std::string& script);

 private:
  FRIEND_TEST_ALL_PREFIXES(TranslateHelperTest, AdoptHtmlLang);
  FRIEND_TEST_ALL_PREFIXES(TranslateHelperTest,
                           CLDAgreeWithLanguageCodeHavingCountryCode);
  FRIEND_TEST_ALL_PREFIXES(TranslateHelperTest,
                           CLDDisagreeWithWrongLanguageCode);
  FRIEND_TEST_ALL_PREFIXES(TranslateHelperTest,
                           InvalidLanguageMetaTagProviding);
  FRIEND_TEST_ALL_PREFIXES(TranslateHelperTest, LanguageCodeTypoCorrection);
  FRIEND_TEST_ALL_PREFIXES(TranslateHelperTest, LanguageCodeSynonyms);
  FRIEND_TEST_ALL_PREFIXES(TranslateHelperTest, ResetInvalidLanguageCode);
  FRIEND_TEST_ALL_PREFIXES(TranslateHelperTest, SimilarLanguageCode);
  FRIEND_TEST_ALL_PREFIXES(TranslateHelperTest, WellKnownWrongConfiguration);

  enum LanguageDetectionTiming {
    ON_TIME,   
    DEFERRED,  
    RESUMED,   
    LANGUAGE_DETECTION_TIMING_MAX_VALUE  
  };

  
  static void ConvertLanguageCodeSynonym(std::string* code);

  
  
  
  static bool IsTranslationAllowed(blink::WebDocument* document);

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  void PageCapturedImpl(int page_seq_no, const base::string16& contents);

  
  
  void CancelPendingTranslation();

  
  
  
  void CheckTranslateStatus(int page_seq_no);

  
  
  void TranslatePageImpl(int page_seq_no, int count);

  
  
  void NotifyBrowserTranslationFailed(TranslateErrors::Type error);

  
  
  blink::WebFrame* GetMainFrame();

  
  void CancelCldDataPolling();

  
  
  
  
  
  
  void DeferPageCaptured(const int page_id, const base::string16& contents);

  
  
  
  void SendCldDataRequest(const int delay_millis, const int next_delay_millis);

  
  void OnCldDataAvailable();

  
  
  
  void RecordLanguageDetectionTiming(LanguageDetectionTiming timing);

  
  
  int page_seq_no_;

  
  bool translation_pending_;
  std::string source_lang_;
  std::string target_lang_;

  
  
  base::TimeTicks language_determined_time_;

  
  scoped_ptr<RendererCldDataProvider> cld_data_provider_;

  
  bool cld_data_polling_started_;

  
  bool cld_data_polling_canceled_;

  
  
  bool deferred_page_capture_;

  
  
  int deferred_page_seq_no_;

  
  int world_id_;

  
  int extension_group_;

  
  std::string extension_scheme_;

  
  
  base::string16 deferred_contents_;

  
  base::WeakPtrFactory<TranslateHelper> weak_method_factory_;

  DISALLOW_COPY_AND_ASSIGN(TranslateHelper);
};

}  

#endif  
