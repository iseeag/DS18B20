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

// For DS18B20 in Linux environment 
#define PATH                "/sys/bus/w1/devices"  // System path to one-wire 
#define DS18B20_HEAD        "28-"     // the starting two digits 
#define DS18B20_ID_L        16 // the length of device id 
#define DS18B20_BUFFER      8 // max number of device
#define DS18B20_PATH_L      128 // as long as it's longer than PATH + ID_L + W1_READ it's ok
#define W1_READ             "w1_slave"
#define DS18B20_DATA_LENGTH 5 // digits reported by device

uint8_t numDev(const char* devpath, const char* devhead);

void devId(char idList[DS18B20_BUFFER][DS18B20_ID_L], const char* devpath, const char* devhead);

void devPath(char pathList[DS18B20_BUFFER][DS18B20_PATH_L], char idList[DS18B20_BUFFER][DS18B20_ID_L], const char* devpath, uint8_t num);

void devTemp(float tempList[DS18B20_BUFFER], char pathList[DS18B20_BUFFER][DS18B20_PATH_L], uint8_t num, uint8_t dataDigits);
