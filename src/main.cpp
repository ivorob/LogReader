#include <stdio.h>
#include <cstdlib>
#include "CLogReader.h"

namespace {

void
usage(const char *appname)
{
    fprintf(stderr, "%s filename mask\n", appname);
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

    return EXIT_SUCCESS; 
}
