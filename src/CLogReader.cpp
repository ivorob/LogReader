#if defined(_WIN32)
#include <windows.h>
#endif

#include "CLogReader.h"
#include "LogFileViewImpl.h"
#include "Stack.h"

CLogReader::CLogReader()
    : filter(),
      impl()
{
    setImpl(new LogFileViewImpl);
}

CLogReader::~CLogReader()
{
    delete this->impl;
}

bool
CLogReader::Open(const char *filename)
{
    if (filename != nullptr) { 
        return getImpl()->open(filename);
    }

    return false;
}

bool
CLogReader::SetFilter(const char *filter)
{
    if (filter == nullptr || filter[0] == 0) {
        return false;
    }

    delete[] this->filter;

    this->filter = new char[lstrlen(filter) + 1];
    if (this->filter != nullptr) {
        lstrcpy(this->filter, filter);

        normalizeFilter();
        getImpl()->resetPosition();
    }

    return hasValidFilter();
}

bool
CLogReader::hasValidFilter() const
{
    return this->filter != nullptr;
}

bool
CLogReader::GetNextLine(char *buffer, int size)
{
    if (buffer == nullptr || size == 0 || !getImpl()->isSourceOpen() || !hasValidFilter()) {
        return false;
    }

    size_t lineSize = 0;
    const char *line = nullptr;
    while ((line = getImpl()->readRecord(lineSize)) != nullptr) {
        if (applyFilter(line, lineSize)) {
            int minSize = ((size - 1) > lineSize) ? lineSize : (size - 1);
            memcpy(buffer, line, minSize);
            buffer[minSize] = 0;
            break;
        }
    }

    return line != nullptr;
}

bool
CLogReader::applyFilter(const char *line, size_t size) const
{
    Stack<size_t> positionStack;
    Stack<size_t> maskPositionStack;
    positionStack.push(0);
    maskPositionStack.push(0);

    size_t position = 0;
    size_t maskPosition = 0;
    while (position < size && this->filter[maskPosition] != 0) {
        char currentSymbol = line[position];
        char maskSymbol = this->filter[maskPosition];

        switch (maskSymbol) {
            case '?':
                ++position;
                ++maskPosition;
                break;
            case '*':
                maskPositionStack.push(maskPosition);

                ++maskPosition;
                while (this->filter[maskPosition] != line[position] && position < size) {
                    ++position;
                }

                positionStack.push(position);
                break;
            default:
                if (currentSymbol != maskSymbol) {
                    position = positionStack.back();
                    maskPosition = maskPositionStack.back();

                    if (!positionStack.empty()) {
                        positionStack.pop();
                        maskPositionStack.pop();
                    }

                    positionStack.push(++position);
                    maskPositionStack.push(maskPosition);
                } else {
                    ++position;
                    ++maskPosition;
                }

                break;
        }
    }

    return this->filter[maskPosition] == 0;
}

void
CLogReader::setImpl(LogReaderImpl *impl)
{
    delete this->impl;
    this->impl = impl;
}

LogReaderImpl *
CLogReader::getImpl() const
{
    return this->impl;
}

void
CLogReader::normalizeFilter()
{
    int length = lstrlen(this->filter) + 1;
    if (length < 1) {
        return;
    }

    char *buffer = new char[length];
    if (buffer != nullptr) {
        char lastSymbol = 0;
        int position = 0;
        for (int i = 0; i < length; ++i) {
            if (this->filter[i] == '*') { 
                if (this->filter[i] != lastSymbol) {
                    buffer[position++] = '*';
                }

                lastSymbol = '*';
            } else {
                buffer[position++] = this->filter[i];
            }
        }

        delete[] this->filter;
        this->filter = buffer;

        //remove last *
        length = lstrlen(this->filter);
        if (this->filter[length - 1] == '*') {
            this->filter[length - 1] = 0;
        }
    }
}
