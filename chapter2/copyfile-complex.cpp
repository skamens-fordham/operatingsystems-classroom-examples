// Simple program to copy a source file to a destination file.
//
// Arguments:
//    --infile <input_file> 
//    --outfile <output_file>

#include <getopt.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

// These external variables are defined and used by the getopt()
// functions.
extern char *optarg;
extern int optind, opterr, optopt;

int
main(int argc, char ** argv)
{
    std::string in_file = "";
    std::string out_file = "";

    // Process command line arguments

    static struct option program_options[] = {
        {"infile", required_argument, 0, 1},
        {"outfile", required_argument, 0, 2},
        {0, 0, 0, 0}
    };

    int option_index = 0;

    int c = 0;

    while(c != -1) {
        c = getopt_long(argc, argv, "",
                        program_options, &option_index);

        switch (c) {
            case -1:
                // getopt_long returns -1 when it reaches the end of
                // the argument list.
                break;
            case 1:
                // infile
                if (! in_file.empty()) {
                    // Input file specified more than once.
                    fprintf(stderr, "Error: --infile specified more than once!\n");
                    return(1);
                    break;
                }

                in_file = optarg;
                break;
            case 2:
                // outfile
                if (! out_file.empty()) {
                    // Output file specified more than once.
                    fprintf(stderr, "Error: --outfile specified more than once!\n");
                    return(2);
                    break;
                }

                out_file = optarg;
                break;
            case '?':
                // Unknown argument
                fprintf(stderr, "Error: Invalid argument: %s\n", argv[optind]);
                return(3);          
        }     
    }

    // If we haven't reached the end of the argument list, that means we must
    // have an extra argument.
    if (optind < argc) {
        fprintf(stderr, "Error: Extra Argument: %s\n", argv[optind]);
        return (4);
    }

    // Make sure they specified both files
    if (in_file.empty() || out_file.empty()) {
        fprintf(stderr, "Error: Both --infile and --outfile must be specified!\n");
        return(5);
    }

    printf("infile=%s\n", in_file.c_str());
    printf("outfile=%s\n", out_file.c_str());

    // Try to open the input file. If the file does not exist, 
    // we will handle the error

    int in_fd = open(in_file.c_str(), O_RDONLY);
    if (in_fd == -1) {
        fprintf(stderr,
                "Error: Could not open file %s for read. Error code %d (%s)\n",
                in_file.c_str(), errno, strerror(errno));
        return 6;
    }

    // Try to open the output file for write
    int out_fd = open(out_file.c_str(), O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (out_fd == -1) {
        fprintf(stderr, 
                "Error: Could not open file %s for write. Error code %d (%s)\n",
                out_file.c_str(), errno, strerror(errno));
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