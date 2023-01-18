#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
	char buf[100];
	int fd = open("/proc/mydev", O_RDWR);
	if(fd < 0) {
		printf("error\n");
		close(fd);
		return 1;
	}

	char wbuf[10];
	int j = 0;
	
	while(1) {
		sleep(1);	
		
		read(fd, buf, 1);
		printf("%s\n", buf);

		snprintf(wbuf, 2, "%d", j);
		write(fd, wbuf, 1);
		j += 1;
		if(j > 9) j = 0;
		
	}	
	return 0;
}
