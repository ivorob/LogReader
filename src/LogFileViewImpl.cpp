#include "LogFileViewImpl.h"

LogFileViewImpl::LogFileViewImpl()
    : fileHandle(INVALID_HANDLE_VALUE),
      fileMap(),
      buffer(),
      bufferSize(),
      position()
{
}

LogFileViewImpl::~LogFileViewImpl()
{
    close();
}

bool
LogFileViewImpl::open(const char *src)
{
    this->fileHandle = CreateFile(src, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL, nullptr);
    if (this->fileHandle != INVALID_HANDLE_VALUE) {
        this->bufferSize = GetFileSize(this->fileHandle, nullptr);
        this->fileMap = CreateFileMapping(this->fileHandle, nullptr, PAGE_READONLY, 0, 0, nullptr);
        if (this->fileMap != nullptr) {
            this->buffer = (const char *)MapViewOfFile(this->fileMap, FILE_MAP_READ,
                    0, 0, 0);
        }
    }

    return this->buffer != nullptr;
}

void
LogFileViewImpl::close()
{
    if (this->fileHandle != INVALID_HANDLE_VALUE) {
        if (this->fileMap != nullptr) {
            if (this->buffer != nullptr) {
                UnmapViewOfFile(this->buffer);
            }

            CloseHandle(this->fileMap);
        }

        CloseHandle(this->fileMap);
    }
}

bool
LogFileViewImpl::isSourceExists(const char *src) const
{
    return GetFileAttributes(src) != INVALID_FILE_ATTRIBUTES;
}

bool
LogFileViewImpl::isSourceOpen() const
{
    return this->buffer != nullptr;
}

void
LogFileViewImpl::resetPosition()
{
    this->position = 0;
}

const char *
LogFileViewImpl::readRecord(size_t& size)
{
    const char *line = &buffer[this->position];
    while (this->position < this->bufferSize && 
           buffer[this->position] != '\n' &&
           buffer[this->position] != '\r')
    {
        ++this->position;
    }

    size = &buffer[this->position] - line;

    //pass CRLF
    while (this->position < this->bufferSize &&
           (buffer[this->position] == '\n' ||
            buffer[this->position] == '\r'))
    {
        ++this->position;
    }

    return size != 0 ? line : nullptr;
}
