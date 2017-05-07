#include <windows.h>
#include <gtest/gtest.h>

namespace {

class Environment : public ::testing::Environment {
public:
    void SetUp() override {
        setAppDirectoryAsCurrent();
    }
private:
    void setAppDirectoryAsCurrent() {
        char buffer[1024];
        DWORD count = GetModuleFileName(GetModuleHandle(nullptr), buffer, sizeof(buffer));
        if (count != 0) {
            while (buffer[count] != '\\' && count != 0) {
                --count;
            }

            if (count != 0) {
                buffer[count] = 0;
                SetCurrentDirectory(buffer);
            }
        }
    }
};

}

int
main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new Environment);
    return RUN_ALL_TESTS();
}
