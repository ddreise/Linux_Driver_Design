// kclient.c

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SZ 128

int main(){

	int fd = 0;
	int i = 0;
	char buf[BUF_SZ];

	printf("Opening module...\n");
	
	fd = open("/dev/kmembuff", O_RDWR);
	if (!fd) printf("Cannot open module!\n");

	read(fd, &buf, BUF_SZ);

	printf("Printing out contents\n");
	for(i = 0; i < BUF_SZ; i++){
		printf("%c", buf[i]);
	}	 

	printf("\nClosing module... \n");
	close(fd);



	return 0;
}
