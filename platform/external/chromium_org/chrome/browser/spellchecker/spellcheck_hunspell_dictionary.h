// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SPELLCHECKER_SPELLCHECK_HUNSPELL_DICTIONARY_H_
#define CHROME_BROWSER_SPELLCHECKER_SPELLCHECK_HUNSPELL_DICTIONARY_H_

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/move.h"
#include "base/observer_list.h"
#include "chrome/browser/spellchecker/spellcheck_dictionary.h"
#include "net/url_request/url_fetcher_delegate.h"

class GURL;
class SpellcheckService;

namespace net {
class URLFetcher;
class URLRequestContextGetter;
}  

class SpellcheckHunspellDictionary
    : public SpellcheckDictionary,
      public net::URLFetcherDelegate,
      public base::SupportsWeakPtr<SpellcheckHunspellDictionary> {
 public:
  
  class Observer {
   public:
    
    virtual void OnHunspellDictionaryInitialized() = 0;

    
    virtual void OnHunspellDictionaryDownloadBegin() = 0;

    
    virtual void OnHunspellDictionaryDownloadSuccess() = 0;

    
    virtual void OnHunspellDictionaryDownloadFailure() = 0;
  };

  SpellcheckHunspellDictionary(
      const std::string& language,
      net::URLRequestContextGetter* request_context_getter,
      SpellcheckService* spellcheck_service);
  virtual ~SpellcheckHunspellDictionary();

  
  virtual void Load() OVERRIDE;

  
  void RetryDownloadDictionary(
      net::URLRequestContextGetter* request_context_getter);

  
  virtual bool IsReady() const;

  const base::File& GetDictionaryFile() const;
  const std::string& GetLanguage() const;
  bool IsUsingPlatformChecker() const;

  
  void AddObserver(Observer* observer);

  
  void RemoveObserver(Observer* observer);

  
  bool IsDownloadInProgress();

  
  bool IsDownloadFailure();

 private:
  
  enum DownloadStatus {
    DOWNLOAD_NONE,
    DOWNLOAD_IN_PROGRESS,
    DOWNLOAD_FAILED,
  };

  
  struct DictionaryFile {
    MOVE_ONLY_TYPE_FOR_CPP_03(DictionaryFile, RValue)
   public:
    DictionaryFile();
    ~DictionaryFile();

    
    DictionaryFile(RValue other);
    DictionaryFile& operator=(RValue other);

    
    base::FilePath path;

    
    base::File file;
  };

  
  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  GURL GetDictionaryURL();

  
  void DownloadDictionary(GURL url);

  
  
  static DictionaryFile OpenDictionaryFile(const base::FilePath& path);

  
  static DictionaryFile InitializeDictionaryLocation(
      const std::string& language);

  
  
  void InitializeDictionaryLocationComplete(DictionaryFile file);

  
  
  void SaveDictionaryDataComplete(bool dictionary_saved);

  
  void InformListenersOfInitialization();

  
  void InformListenersOfDownloadFailure();

  
  std::string language_;

  
  bool use_platform_spellchecker_;

  
  
  net::URLRequestContextGetter* request_context_getter_;

  
  scoped_ptr<net::URLFetcher> fetcher_;

  SpellcheckService* spellcheck_service_;

  
  ObserverList<Observer> observers_;

  
  DownloadStatus download_status_;

  
  DictionaryFile dictionary_file_;

  base::WeakPtrFactory<SpellcheckHunspellDictionary> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SpellcheckHunspellDictionary);
};

#endif  
