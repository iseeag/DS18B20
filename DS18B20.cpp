// Based on http://bradsrpi.blogspot.com.au/2014/01/c-program-to-read-temperature-from.html
// use g++ to compile
// in my opinion what the code achieve high level stupidity the reading speed is ultra slow! 
// consider how slow it is it should have its own thread or it slows down everybody
// to do list: 
// either find a better driver or make one yourself 
#include <stdint.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "DS18B20.h"



int main() {
    //setup 
    uint8_t num;
    num = numDev(PATH,DS18B20_HEAD);
    printf("number of device: %i\n", num);

    //get IDs
    char idList[DS18B20_BUFFER][DS18B20_ID_L];
    devId(idList, PATH, DS18B20_HEAD);
    for(int i = 0; i < num; i++) 
        printf("device ID: %s\n", idList[i]);
    
    //get Paths
    char pathList[DS18B20_BUFFER][DS18B20_PATH_L];
    devPath(pathList, idList, PATH, num);
    for(int i = 0; i < num; i++)
        printf("device Path: %s\n", pathList[i]);

    //get float
    float tempList[DS18B20_BUFFER];
    devTemp(tempList, pathList, num, DS18B20_DATA_LENGTH);
    for(int i = 0; i < num; i++)
        printf("%lf  ", tempList[i]);
    printf("\n");
    
    //loop
    while(1) {
        devTemp(tempList, pathList, num, DS18B20_DATA_LENGTH);
        for(int i = 0; i < num; i++)
            printf("%lf  ", tempList[i]);
        printf("C\n");
    }




    return 0;
} 

// Count the number of DS18B20 in the bus 
uint8_t numDev(const char* devpath, const char* devhead) {
    // relies on <dirent.h>
    DIR *dir;
    struct dirent *dirent;
    uint8_t i=0;

    dir = opendir(devpath);
    if(dir != NULL) {
        while((dirent = readdir(dir))) {
            if(dirent->d_type == DT_LNK && strstr(dirent->d_name, devhead) != NULL) {
                i++;
            }
        }
        (void) closedir(dir);
    }
    else {
        perror("Couldn't open the w1 devices directory");
        return 0;
    }
    return i;
}

// store device IDs in the bus in a array
// para: pointer to array that stores the IDs of device
// system path, device specific digits or the devhead, the length of its id 
void devId(char idList[DS18B20_BUFFER][DS18B20_ID_L], const char* devpath, const char* devhead) {
    // relies on <dirent.h> 
    DIR *dir;
    struct dirent *dirent;
    uint8_t i = 0;

    dir = opendir(devpath);
    if(dir != NULL) {
        while((dirent = readdir(dir)) && i < DS18B20_BUFFER) {
            if(dirent->d_type == DT_LNK && strstr(dirent->d_name, devhead) != NULL) {
                strcpy(idList[i], dirent->d_name);
                i++;
            }
        }
        (void) closedir(dir);
    }
    else {
        perror("Couldn't open the w1 devices directory");
    }
}

// store device paths 
// para: pointer to store paths, IDs array, system device path, number of device 
void devPath(char pathList[DS18B20_BUFFER][DS18B20_PATH_L], char idList[DS18B20_BUFFER][DS18B20_ID_L], const char* devpath, uint8_t num) {
    for(uint8_t i = 0; i < num; i++) {
        sprintf(pathList[i], "%s/%s/%s", devpath, idList[i], W1_READ);
    }
}

void devTemp(float tempList[DS18B20_BUFFER], char pathList[DS18B20_BUFFER][DS18B20_PATH_L], uint8_t num, uint8_t dataDigits) {
    ssize_t numRead;
    char buf[256];
    char tmpData[dataDigits];
    for(int i = 0; i < num; i++) {
        int fd = open(pathList[i], O_RDONLY);
        if(fd == -1) 
            perror("Couldn't open the w1 device.");

        while((numRead = read(fd, buf, 256)) > 0) {
            strncpy(tmpData, strstr(buf, "t=") + 2, 5);
            tempList[i] = strtof(tmpData, NULL)/1000;
        }
        close(fd);
    }
}
