// kclient.c
//
// Daniel Dreise
// December 6, 2019

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SZ 128

int main(){

	int fd = 0;
	int i = 0;
	char menu_choice[BUF_SZ];
	char buf[BUF_SZ];
	char tmp1[BUF_SZ], tmp2[BUF_SZ];

	// Create device
	system("mknod -m 0666 /dev/kmembuff c 240 0");

	// Menu
	printf("\n******** Client Menu ********\n\n");
	printf("when:	output the current time\n");
	printf("who:	output your name\n");
	printf("where:	output your school name\n");

	// Get user input
	printf("\nEnter command: ");
	fgets(menu_choice, BUF_SZ, stdin);

	// Fork and run server process
	if (fork() == 0){
		execl("./kserver", "kserver", NULL);
		printf("Return not expected, must be error with execl()\n");
		exit(1);
	}
	else;


	printf("Opening module...\n");
	
	// Open device
	fd = open("/dev/kmembuff", O_RDWR);
	if (!fd) printf("Cannot open module!\n");

	strcpy(tmp1, menu_choice);

	for (i = 0; i < BUF_SZ; i++){
		buf[i] = tmp1[i];
 	}

	// Write menu choice to device
	printf("\nClient writing to device...\n");
	write(fd, &buf, BUF_SZ);

	// Wait for server to respond and fill device with new info
	sleep(1);

	// Read from device
	read(fd, &tmp2, BUF_SZ);

	printf("Client printing out contents...\n");
	printf("%s", tmp2);	 

	printf("\nClosing module... \n");
	close(fd);



	return 0;
}
