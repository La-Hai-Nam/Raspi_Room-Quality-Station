/*
* @file procfile_utils.c
* @brief This file provides an API for reading and setting the operating mode, by reading from and writing to 
*        the Procfile of our kernelmodule.
* @author Maximilian Lausch, HTW-Berlin s0578304
* @bug Currently there are no known bugs
*/

void open_procfile() {
	int fd = open("/proc/mydev", O_RDWR | O_NONBLOCK);
	if(fd < 0) {
		printf("in open_procfile() error, can not open proc file\n");
	}	

	return fd;
}
/*
* @brief This function gets the current operating mode by reading from the Procfile.
* @param fd The file descriptor of the Profile.
*
* @return The current mode.
*/
int get_procfile_mode_number(int fd) {
	if(fd < 0) return -1;

	char buffer[10];

	lseek(fd, 0, SEEK_SET);
	int bytes_read = read(fd, buffer, 5);

	return atoi(buffer);
}


/*
* @brief This function sets the operating mode by writing to the Procfile.
* @param fd The file descriptor of the Profile.
* @param mode The mode that is going to be set.
*
* @return Error code.
*/
int set_procfile_mode_number(int fd, int mode) {
	if(fd < 0) return -1;

	char buffer[100];
	int len = sprintf(buffer, "%d", mode);

	lseek(fd, 0, SEEK_SET);
	if(write(fd, buffer, len) != len) {
		printf("in set_procfile_mode_number(): Error writing to proc file\n");
		return -2;
	}

	return 0;
}
