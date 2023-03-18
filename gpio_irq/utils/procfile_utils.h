#ifndef PROCFILE_UTILS_H
#define PROCFILE_UTILS_H

int open_procfile();
int get_procfile_mode_number(int fd);
int set_procfile_mode_number(int fd, int mode);

#endif
