#ifndef __LOG_FILE_VIEW_IMPL_H__
#define __LOG_FILE_VIEW_IMPL_H__

#include <windows.h>
#include "LogReaderImpl.h"

class LogFileViewImpl : public LogReaderImpl {
public:
    LogFileViewImpl();
    ~LogFileViewImpl();

    bool isSourceExists(const char *src) const override;
    bool isSourceOpen() const override;
    bool open(const char *src) override;
    void close() override;

    void resetPosition() override;
    const char *readRecord(size_t& size) override;
private:
    HANDLE fileHandle;
    HANDLE fileMap;
    const char *buffer;
    DWORD bufferSize;
    DWORD position;
};

#endif //__LOG_FILE_VIEW_IMPL_H__
