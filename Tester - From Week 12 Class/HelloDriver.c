#include <fcntl.h>
#include <stdio.h>

int main()
{
	char writeBuffer[1];
	char readBuffer[1];
	int fd;

	fd = open("/dev/mydev", O_RDWR);  //which static driver routine is this calling?
	writeBuffer[0] = 'A';
	
	write(fd, writeBuffer, 1, NULL);  //which static routine?
	read(fd, readBuffer, 1, NULL);    //which static routine?

	printf("Value : %s\n", readBuffer[0]);  //Am I going to get any readout data here?

	close(fd);  //which static routine?

	//You can use "dmesg" to check the Kernel messages produced by the driver via printk().
}
