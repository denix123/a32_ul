// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_LOG_H
#define ANDROID_BASE_LOG_H

#include <errno.h>
#include <stdarg.h>
#include <stddef.h>

namespace android {
namespace base {

typedef int LogSeverity;
const LogSeverity LOG_VERBOSE = -1;
const LogSeverity LOG_INFO = 0;
const LogSeverity LOG_WARNING = 1;
const LogSeverity LOG_ERROR = 2;
const LogSeverity LOG_FATAL = 3;
const LogSeverity LOG_NUM_SEVERITIES = 4;

#ifdef NDEBUG
const LogSeverity LOG_DFATAL = LOG_ERROR;
#else
const LogSeverity LOG_DFATAL = LOG_FATAL;
#endif

LogSeverity getMinLogLevel();

#define LOG_IS_ON(severity) \
  ((::android::base::LOG_ ## severity) >=  \
        ::android::base::getMinLogLevel())

#define LOG_LAZY_EVAL(condition, expr) \
  !(condition) ? (void)0 : ::android::base::LogStreamVoidify() & (expr)

#define LOG(severity)  \
        LOG_LAZY_EVAL(LOG_IS_ON(severity), \
        LOG_MESSAGE_STREAM_COMPACT(severity))

#define LOG_IF(severity, condition) \
        LOG_LAZY_EVAL(LOG_IS_ON(severity) && (condition), \
                      LOG_MESSAGE_STREAM_COMPACT(severity))


#define PLOG(severity)  \
        LOG_LAZY_EVAL(LOG_IS_ON(severity), \
        PLOG_MESSAGE_STREAM_COMPACT(severity))

#define PLOG_IF(severity, condition) \
        LOG_LAZY_EVAL(LOG_IS_ON(severity) && (condition), \
                      PLOG_MESSAGE_STREAM_COMPACT(severity))

#define CHECK(condition) \
    LOG_IF(FATAL, !(condition)) << "Check failed: " #condition ". "


#define PCHECK(condition) \
    PLOG_IF(FATAL, !(condition)) << "Check failed: " #condition ". "


#ifndef ENABLE_DLOG
#  if defined(NDEBUG)
#    define ENABLE_DLOG 0
#  else
#    define ENABLE_DLOG 1
#  endif
#endif

#ifndef ENABLE_DCHECK
#  if defined(NDEBUG)
#    define ENABLE_DCHECK 1
#  else
#    define ENABLE_DCHECK 2
#  endif
#endif

#if ENABLE_DLOG
#  define DLOG_IS_ON(severity) LOG_IS_ON(severity)
#else
#  define DLOG_IS_ON(severity) false
#endif

#if ENABLE_DCHECK == 0
    
    
#  define DCHECK_IS_ON()  false
#elif ENABLE_DCHECK == 1
#  define DCHECK_IS_ON()  ::android::base::dcheckIsEnabled()
#else
#  define DCHECK_IS_ON()  true
#endif

bool dcheckIsEnabled();

bool setDcheckLevel(bool enabled);

#define DLOG(severity)  LOG_IF(severity, DLOG_IS_ON())

#define DLOG_IF(severity, condition)  \
        LOG_IF(severity, DLOG_IS_ON() && (condition))

#define DCHECK(condition) \
        LOG_IF(FATAL, DCHECK_IS_ON() && !(condition)) \
            << "Check failed: " #condition ". "

class LogString {
public:
    LogString(const char* fmt, ...);
    ~LogString();
    const char* string() const { return mString; }
private:
    char* mString;
};

struct LogParams {
    LogParams() : file(NULL), lineno(-1), severity(-1) {}

    LogParams(const char* a_file, int a_lineno, LogSeverity a_severity)
            : file(a_file), lineno(a_lineno), severity(a_severity) {}

    const char* file;
    int lineno;
    LogSeverity severity;
};

class LogStream {
public:
    LogStream(const char* file, int lineno, LogSeverity severity);
    ~LogStream();

    inline LogStream& operator<<(const char* str) {
        append(str);
        return *this;
    }

    inline LogStream& operator<<(const LogString& str) {
        append(str.string());
        return *this;
    }

    
    LogStream& operator<<(const void* v);

    LogStream& operator<<(char ch);
    LogStream& operator<<(int v);
    LogStream& operator<<(unsigned v);
    LogStream& operator<<(long v);
    LogStream& operator<<(unsigned long v);
    
    LogStream& operator<<(long long v);
    LogStream& operator<<(unsigned long long v);
    LogStream& operator<<(float v);
    LogStream& operator<<(double v);

    const char* string() const { return mString ? mString : ""; }
    size_t size() const { return mSize; }
    const LogParams& params() const { return mParams; }

private:
    void append(const char* str);
    void append(const char* str, size_t len);

    LogParams mParams;
    char* mString;
    size_t mSize;
    size_t mCapacity;
};

class LogStreamVoidify {
 public:
  LogStreamVoidify() { }
  
  
  void operator&(LogStream&) { }
};

class LogMessage {
public:
    LogMessage(const char* file, int line, LogSeverity severity);
    ~LogMessage();

    LogStream& stream() const { return *mStream; }
protected:
    
    LogStream* mStream;
};

#define LOG_MESSAGE_COMPACT(severity) \
    ::android::base::LogMessage( \
            __FILE__, \
            __LINE__, \
            ::android::base::LOG_ ## severity)

#define LOG_MESSAGE_STREAM_COMPACT(severity) \
    LOG_MESSAGE_COMPACT(severity).stream()


class ErrnoLogMessage {
public:
    ErrnoLogMessage(const char* file,
                    int line,
                    LogSeverity severity,
                    int errnoCode);
    ~ErrnoLogMessage();

    LogStream& stream() const { return *mStream; }
private:
    LogStream* mStream;
    int mErrno;
};

#define PLOG_MESSAGE_COMPACT(severity) \
    ::android::base::ErrnoLogMessage( \
            __FILE__, \
            __LINE__, \
            ::android::base::LOG_ ## severity, \
            errno)

#define PLOG_MESSAGE_STREAM_COMPACT(severity) \
    PLOG_MESSAGE_COMPACT(severity).stream()

namespace testing {

class LogOutput {
public:
    LogOutput() {}
    virtual ~LogOutput() {}

    
    
    
    
    
    virtual void logMessage(const LogParams& params,
                            const char* message,
                            size_t message_len) = 0;

    
    
    
    
    static LogOutput* setNewOutput(LogOutput* newOutput);
};

}  

}  
}  

#endif  
