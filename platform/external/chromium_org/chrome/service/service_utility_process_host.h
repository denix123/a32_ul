// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_SERVICE_SERVICE_UTILITY_PROCESS_HOST_H_
#define CHROME_SERVICE_SERVICE_UTILITY_PROCESS_HOST_H_

#include "build/build_config.h"

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/public/common/child_process_host_delegate.h"
#include "ipc/ipc_platform_file.h"

namespace base {
class CommandLine;
class File;
class FilePath;
class MessageLoopProxy;
class ScopedTempDir;
}  

namespace content {
class ChildProcessHost;
}

namespace printing {
class MetafilePlayer;
class PdfRenderSettings;
struct PageRange;
struct PrinterCapsAndDefaults;
struct PrinterSemanticCapsAndDefaults;
}  

class ServiceUtilityProcessHost : public content::ChildProcessHostDelegate {
 public:
  
  
  
  class Client : public base::RefCountedThreadSafe<Client> {
   public:
    Client() {}

    
    virtual void OnChildDied() {}

    virtual void OnRenderPDFPagesToMetafilePageDone(
        double scale_factor,
        const printing::MetafilePlayer& emf) {}

    
    virtual void OnRenderPDFPagesToMetafileDone(bool success) {}

    
    
    virtual void OnGetPrinterCapsAndDefaults(
        bool succedded,
        const std::string& printer_name,
        const printing::PrinterCapsAndDefaults& caps_and_defaults) {}

    
    
    virtual void OnGetPrinterSemanticCapsAndDefaults(
        bool succedded,
        const std::string& printer_name,
        const printing::PrinterSemanticCapsAndDefaults& caps_and_defaults) {}

   protected:
    virtual ~Client() {}

   private:
    friend class base::RefCountedThreadSafe<Client>;
    friend class ServiceUtilityProcessHost;

    
    
    bool MetafileAvailable(double scale_factor, base::File file);

    DISALLOW_COPY_AND_ASSIGN(Client);
  };

  ServiceUtilityProcessHost(Client* client,
                            base::MessageLoopProxy* client_message_loop_proxy);
  virtual ~ServiceUtilityProcessHost();

  
  
  
  bool StartRenderPDFPagesToMetafile(
      const base::FilePath& pdf_path,
      const printing::PdfRenderSettings& render_settings);

  
  
  
  
  bool StartGetPrinterCapsAndDefaults(const std::string& printer_name);

  
  
  
  
  bool StartGetPrinterSemanticCapsAndDefaults(const std::string& printer_name);

 protected:
  bool Send(IPC::Message* msg);

  
  virtual base::FilePath GetUtilityProcessCmd();

  
  virtual void OnChildDisconnected() OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual base::ProcessHandle GetHandle() const OVERRIDE;

 private:
  
  bool StartProcess(bool no_sandbox);

  
  bool Launch(base::CommandLine* cmd_line, bool no_sandbox);

  base::ProcessHandle handle() const { return handle_; }

  void OnMetafileSpooled(bool success);
  void OnPDFToEmfFinished(bool success);

  
  void OnRenderPDFPagesToMetafilesPageCount(int page_count);
  void OnRenderPDFPagesToMetafilesPageDone(bool success, double scale_factor);
  void OnGetPrinterCapsAndDefaultsSucceeded(
      const std::string& printer_name,
      const printing::PrinterCapsAndDefaults& caps_and_defaults);
  void OnGetPrinterCapsAndDefaultsFailed(const std::string& printer_name);
  void OnGetPrinterSemanticCapsAndDefaultsSucceeded(
      const std::string& printer_name,
      const printing::PrinterSemanticCapsAndDefaults& caps_and_defaults);
  void OnGetPrinterSemanticCapsAndDefaultsFailed(
      const std::string& printer_name);

  scoped_ptr<content::ChildProcessHost> child_process_host_;
  base::ProcessHandle handle_;
  
  scoped_refptr<Client> client_;
  scoped_refptr<base::MessageLoopProxy> client_message_loop_proxy_;
  bool waiting_for_reply_;

  
  base::Time start_time_;

  class PdfToEmfState;
  scoped_ptr<PdfToEmfState> pdf_to_emf_state_;

  base::WeakPtrFactory<ServiceUtilityProcessHost> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ServiceUtilityProcessHost);
};

#endif  
