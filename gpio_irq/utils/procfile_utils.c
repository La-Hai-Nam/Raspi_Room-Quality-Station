/*
* @file procfile_utils.c
* @brief This file provides an API for reading and setting the operating mode, by reading from and writing to 
*        the Procfile of our kernelmodule.
* @author Maximilian Lausch, HTW-Berlin s0578304
* @bug Currently there are no known bugs
*/

/*
* @brief This function gets the current operating mode by reading from the Procfile.
* @param fd The file descriptor of the Profile.
*
* @return The current mode.
*/
int get_procfile_mode_number(int fd) {
	if(fd == NULL) return -2;

	char buffer[10];

	lseek(procfile_fd, 0, SEEK_SET);
	int bytes_read = read(procfile_fd, buffer, 5);

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
	if(fd == NULL) return -1;

	char buffer[100];
	int len = sprintf(buffer, "%d", num);

	lseek(procfile_fd, 0, SEEK_SET);
	if(write(procfile_fd, buffer, len) != len) {
		printf("in interrupt.c change_count() error writing to proc file\n");
		return -2;
	}

	return 0;
}
