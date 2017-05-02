#include <stdio.h>
#include <cstdlib>

namespace {

void
usage(const char *appname)
{
    fprintf(stderr, "%s filename mask\n", appname);
}

bool
isFileExists(const char *filename)
{
    return GetFileAttributes(filename) != INVALID_FILE_ATTRIBUTES;
}

}

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *filter = argv[2];
    if (isFileExists(filename)) {
        CLogReader logReader;
        if (logReader.SetFilter(filter) && logReader.Open(filename)) {
            fprintf(stdout, "Result of work:\n");

            char buffer[1024];
            while (logReader.GetNextLine(buffer, sizeof(buffer))) {
                fprintf(stdout, "%s\n", buffer);
            }
        } else {
            fprintf(stderr, "Some unknown error is occured during work of logger");
        }
    } else {
        fprintf(stderr, "%s isn't found!\n", filename);
    }

    return EXIT_SUCCESS; 
}
