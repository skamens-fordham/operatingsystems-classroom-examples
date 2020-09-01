// Simple program to copy a source file to a destination file.
//

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int
main(int argc, char ** argv)
{

    // Process command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file", 
                argv[0]);
    }

    printf("infile=%s\n", argv[1]);
    printf("outfile=%s\n", argv[2]);

    // Try to open the input file. If the file does not exist, 
    // we will handle the error

    int in_fd = open(argv[1], O_RDONLY);
    if (in_fd == -1) {
        fprintf(stderr,
                "Error: Could not open file %s for read. Error code %d (%s)\n",
                argv[1], errno, strerror(errno));
        return 6;
    }

    // Try to open the output file for write
    int out_fd = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (out_fd == -1) {
        fprintf(stderr, 
                "Error: Could not open file %s for write. Error code %d (%s)\n",
                argv[2], errno, strerror(errno));
        close(in_fd); // Need to close the input file since we successfully opened it above.
        return 7;
    }

    // OK, the input file and output files are both open. Let's read from
    // the input and write to the output
    char buf[128];
    ssize_t num_read = 0;
    ssize_t num_written = 0;
    while ((num_read = read(in_fd, buf, sizeof(buf))) > 0) {

        if ((num_written = write(out_fd, buf, num_read)) < 0) {
            fprintf(stderr, "Error writing file. Error code %d (%s)\n",
                    errno, strerror(errno));
            close(in_fd);
            close(out_fd);
            return 8;
        }
    }

    if (num_read < 0) {
        fprintf(stderr, "Error reading from input file. Error code %d (%s)\n",
                errno, strerror(errno));
        close(in_fd);
        close(out_fd);
        return 9;
    }

    close(in_fd);
    close(out_fd);

    return 0;
}