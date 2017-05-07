#ifndef __CLOG_READER_H__
#define __CLOG_READER_H__

#include <windows.h>
#include "LogReaderImpl.h"

class CLogReader {
public:
    CLogReader();
    ~CLogReader() = default;

    bool Open(const char *filename);
    bool SetFilter(const char *filter);

    bool GetNextLine(char *buffer, int size);

    LogReaderImpl *getImpl() const;
    void setImpl(LogReaderImpl *impl);
private:
    bool hasValidFilter() const;
    bool applyFilter(const char *line, size_t size) const;
    void normalizeFilter();
private:
    char *filter;
    LogReaderImpl *impl;
};

#endif //__CLOG_READER_H__
