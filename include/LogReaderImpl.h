#ifndef __LOG_READER_IMPL_H__
#define __LOG_READER_IMPL_H__

class LogReaderImpl {
public:
    virtual ~LogReaderImpl() = default;

    virtual bool isSourceExists(const char *src) const = 0;
    virtual bool isSourceOpen() const = 0;
    virtual bool open(const char *src) = 0;
    virtual void close() = 0;

    virtual const char *readRecord(size_t& size) = 0;
};

#endif //__LOG_READER_IMPL_H__
