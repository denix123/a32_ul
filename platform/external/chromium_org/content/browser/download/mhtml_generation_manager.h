// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DOWNLOAD_MHTML_GENERATION_MANAGER_H_
#define CONTENT_BROWSER_DOWNLOAD_MHTML_GENERATION_MANAGER_H_

#include <map>

#include "base/files/file.h"
#include "base/memory/singleton.h"
#include "base/process/process.h"
#include "ipc/ipc_platform_file.h"

namespace base {
class FilePath;
}

namespace content {

class WebContents;

class MHTMLGenerationManager {
 public:
  static MHTMLGenerationManager* GetInstance();

  typedef base::Callback<void(int64 )>
      GenerateMHTMLCallback;

  
  
  void SaveMHTML(WebContents* web_contents,
                 const base::FilePath& file,
                 const GenerateMHTMLCallback& callback);

  
  
  void StreamMHTML(WebContents* web_contents,
                   base::File file,
                   const GenerateMHTMLCallback& callback);

  
  
  
  void MHTMLGenerated(int job_id, int64 mhtml_data_size);

 private:
  friend struct DefaultSingletonTraits<MHTMLGenerationManager>;
  class Job;

  MHTMLGenerationManager();
  virtual ~MHTMLGenerationManager();

  
  void CreateFile(int job_id,
                  const base::FilePath& file,
                  base::ProcessHandle renderer_process);

  
  
  
  void FileAvailable(int job_id,
                     base::File browser_file,
                     IPC::PlatformFileForTransit renderer_file);

  
  void CloseFile(base::File file);

  
  
  
  void JobFinished(int job_id, int64 mhtml_data_size);

  
  int NewJob(WebContents* web_contents, const GenerateMHTMLCallback& callback);

  
  void RenderProcessExited(Job* job);

  typedef std::map<int, Job*> IDToJobMap;
  IDToJobMap id_to_job_;

  DISALLOW_COPY_AND_ASSIGN(MHTMLGenerationManager);
};

}  

#endif  
