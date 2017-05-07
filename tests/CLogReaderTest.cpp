#include <gtest/gtest.h>
#include "CLogReader.h"

TEST(CLogReaderTest, Open)
{
    CLogReader logReader;
    ASSERT_FALSE(logReader.Open(nullptr));
    ASSERT_FALSE(logReader.Open(""));
    ASSERT_FALSE(logReader.Open("someunknownfile"));

    ASSERT_TRUE(logReader.Open("test_data\\logfile.txt"));
}

TEST(CLogReaderTest, SetFilter)
{
    CLogReader logReader;
    ASSERT_FALSE(logReader.SetFilter(nullptr));
    ASSERT_FALSE(logReader.SetFilter(""));

    ASSERT_TRUE(logReader.SetFilter("order*closed"));
}

TEST(CLogReaderTest, GetNextLine)
{
    CLogReader logReader;

    char buffer[1024];
    ASSERT_FALSE(logReader.GetNextLine(buffer, sizeof(buffer))); //because of Open

    ASSERT_TRUE(logReader.Open("test_data\\logfile.txt"));
    ASSERT_FALSE(logReader.GetNextLine(buffer, sizeof(buffer))); //because of SetFilter

    ASSERT_TRUE(logReader.SetFilter("or??r***clos?d"));
    ASSERT_TRUE(logReader.GetNextLine(buffer, sizeof(buffer)));
    ASSERT_FALSE(logReader.GetNextLine(buffer, sizeof(buffer))); //end of file
}
