#define PIPE_SERVER
#include "rw_pipe.h"

#include <sys/stat.h>


int main() {
    umask(0);
    mkfifo(SWCR, 0666);
    mkfifo(SRCW, 0666);
    
    create_rw_pipe(SWCR, SRCW);

    return 0;
}
