#include <dirent.h>
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>

#include "walk.h"


static const char etype[] = {
    '?',   // DT_UNKNOWN - unknown
    'p',   // DT_FIFO    - named pipe
    'c',   // DT_CHR     - character device
    '\0',
    'd',   // DT_DIR     - directory
    '\0',
    'b',   // DT_BLK     - block device
    '\0',
    '-',   // DT_REG     - regular file
    '\0',
    'l',   // DT_LNK     - symbolic link
    '\0',
    's'    // DT_SOCK    - local-domain socket
};


char root[PATH_MAX + 1];
char fullpath[PATH_MAX + 1];

void _walk(FILE *);


void walk(const char *path, FILE *log) {
    getcwd(root, sizeof(root));

    chdir(path);
    _walk(log);

    chdir(root);
}


void _walk(FILE *log) {
    DIR *cur = opendir(".");
    struct dirent *entry;
    struct stat info;
    char time[25];

    while ((entry = readdir(cur)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") * strcmp(entry->d_name, "..") != 0) {
                chdir(entry->d_name);
                _walk(log);
                chdir("..");
            }
        }
        else {
            realpath(entry->d_name, fullpath);
            stat(entry->d_name, &info);
            strftime(time, sizeof(time), "%c", localtime(&info.st_mtim.tv_sec));

            fprintf(log,
                "%c%c%c%c%c%c%c%c%c%c %s %s %s\n",
                etype[entry->d_type],
                (info.st_mode & S_IRUSR) ? 'r' : '-',
                (info.st_mode & S_IWUSR) ? 'w' : '-',
                (info.st_mode & S_IXUSR) ? 'x' : '-',
                (info.st_mode & S_IRGRP) ? 'r' : '-',
                (info.st_mode & S_IWGRP) ? 'w' : '-',
                (info.st_mode & S_IXGRP) ? 'x' : '-',
                (info.st_mode & S_IROTH) ? 'r' : '-',
                (info.st_mode & S_IWOTH) ? 'w' : '-',
                (info.st_mode & S_IXOTH) ? 'x' : '-',
                getpwuid(info.st_uid)->pw_name,
                time,
                fullpath
            );

            // utime(fullpath, NULL);
        }
    }

    closedir(cur);
}