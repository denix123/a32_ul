// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_FOLDER_FINDER_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_FOLDER_FINDER_H_

#include <map>
#include <vector>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/sequenced_task_runner.h"
#include "chrome/browser/media_galleries/media_scan_types.h"

class MediaFolderFinder {
 public:
  
  
  typedef std::map<base::FilePath, MediaGalleryScanResult>
      MediaFolderFinderResults;

  
  
  typedef base::Callback<void(bool ,
                              const MediaFolderFinderResults& )>
      MediaFolderFinderResultsCallback;

  
  
  
  
  
  explicit MediaFolderFinder(const MediaFolderFinderResultsCallback& callback);
  virtual ~MediaFolderFinder();

  
  virtual void StartScan();

  const std::vector<base::FilePath>& graylisted_folders() const;

 private:
  friend class MediaFolderFinderTest;
  friend class MediaGalleriesPlatformAppBrowserTest;

  class Worker;
  struct WorkerReply {
    WorkerReply();
    ~WorkerReply();

    MediaGalleryScanResult scan_result;
    std::vector<base::FilePath> new_folders;
  };

  enum ScanState {
    SCAN_STATE_NOT_STARTED,
    SCAN_STATE_STARTED,
    SCAN_STATE_FINISHED,
  };

  void SetRootsForTesting(const std::vector<base::FilePath>& roots);

  void OnInitialized(const std::vector<base::FilePath>& roots);

  
  void ScanFolder();

  
  void GotScanResults(const base::FilePath& path, const WorkerReply& reply);

  const MediaFolderFinderResultsCallback results_callback_;
  MediaFolderFinderResults results_;

  std::vector<base::FilePath> graylisted_folders_;
  std::vector<base::FilePath> folders_to_scan_;
  ScanState scan_state_;

  scoped_refptr<base::SequencedTaskRunner> worker_task_runner_;

  
  Worker* worker_;

  
  bool has_roots_for_testing_;
  std::vector<base::FilePath> roots_for_testing_;

  base::WeakPtrFactory<MediaFolderFinder> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MediaFolderFinder);
};

#endif  
