// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_FILEAPI_SAFE_MEDIA_METADATA_PARSER_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_FILEAPI_SAFE_MEDIA_METADATA_PARSER_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/common/extensions/api/media_galleries.h"
#include "chrome/common/media_galleries/metadata_types.h"
#include "content/public/browser/utility_process_host.h"
#include "content/public/browser/utility_process_host_client.h"

namespace IPC {
class Message;
}

class Profile;

namespace metadata {

class SafeMediaMetadataParser : public content::UtilityProcessHostClient {
 public:
  
  typedef base::Callback<
      void(bool parse_success,
           scoped_ptr<base::DictionaryValue> metadata_dictionary,
           scoped_ptr<std::vector<AttachedImage> > attached_images)>
      DoneCallback;

  SafeMediaMetadataParser(Profile* profile, const std::string& blob_uuid,
                          int64 blob_size, const std::string& mime_type,
                          bool get_attached_images);

  
  void Start(const DoneCallback& callback);

 private:
  enum ParserState {
    INITIAL_STATE,
    STARTED_PARSING_STATE,
    FINISHED_PARSING_STATE,
  };

  
  virtual ~SafeMediaMetadataParser();

  
  void StartWorkOnIOThread(const DoneCallback& callback);

  
  
  void OnParseMediaMetadataFinished(
      bool parse_success, const base::DictionaryValue& metadata_dictionary,
      const std::vector<AttachedImage>& attached_images);

  
  
  void OnUtilityProcessRequestBlobBytes(int64 request_id, int64 byte_start,
                                        int64 length);
  void StartBlobReaderOnUIThread(int64 request_id, int64 byte_start,
                                 int64 length);
  void OnBlobReaderDoneOnUIThread(int64 request_id,
                                  scoped_ptr<std::string> data,
                                  int64 );
  void FinishRequestBlobBytes(int64 request_id, scoped_ptr<std::string> data);

  
  
  virtual void OnProcessCrashed(int exit_code) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  Profile* const profile_;
  const std::string blob_uuid_;
  const int64 blob_size_;
  const std::string mime_type_;
  bool get_attached_images_;

  DoneCallback callback_;

  base::WeakPtr<content::UtilityProcessHost> utility_process_host_;

  
  
  ParserState parser_state_;

  DISALLOW_COPY_AND_ASSIGN(SafeMediaMetadataParser);
};

}  

#endif  
