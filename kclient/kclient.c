// kclient.c

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SZ 128

int main(){

	int fd = 0;
	char buf[128] = "This is a test\n";
	
	fd = open("/dev/kmembuff", O_RDWR);
	write(fd, buf, BUF_SZ);
	close(fd);



	return 0;
}
