// kserver.c
//
// Daniel Dreise
// December 6 2019

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define BUF_SZ 128

int main(){

    char buf[BUF_SZ];
    char tmp[BUF_SZ];
    int fd, i;
    time_t cur_time;
    struct tm * timeinfo;

    // To get current time
    time (&cur_time);
    timeinfo = localtime (&cur_time);


    // Open module
    fd = open("/dev/kmembuff",O_RDWR);
    if (!fd) printf("Cannot open module!\n");

    // Read from driver
    printf("Server is reading...\n");
    read(fd, &tmp, BUF_SZ);

    printf("Server read: %s", tmp);

    // Process client request
    if (strcmp("when\n", tmp) == 0)  strcpy(tmp, asctime(timeinfo));
    else if (strcmp("who\n", tmp) == 0) strcpy(tmp, "Daniel Dreise");
    else if (strcmp("where\n", tmp) == 0) strcpy(tmp, "Conestoga College");
    else {
        printf("Server did not receive command or invalid input\n");
        strcpy(tmp, "");
    };


    for(i = 0; i < BUF_SZ; i++){
        buf[i] = tmp[i];
    }

    printf("Server wrote: %s", buf);

    // Write to device
    write(fd, &buf, BUF_SZ);

    close(fd);


    return 0;
}