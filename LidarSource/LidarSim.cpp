// LidarSim.cpp : main project file.

#include "LidarSource.h"


int main(int argc,char *argv[]){
	const char* path = "/dev/ttyUSB0";
	LidarSource* lidar = new LidarSource(path);
	lidar->setSimulate(false);
	lidar->initialize();
    printf("initialization completed.\n");
	lidar->showScan();
	lidar->shutdown();
	delete lidar;
    return 0;
}
