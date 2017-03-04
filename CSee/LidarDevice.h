#pragma once

#include <string>
#include <vector>
#include "rplidar/rplidar.h" //RPLIDAR standard sdk, all-in-one header

//   The data buffer is set to 4k, which is 4096 bytes
//   the header indicates how many readings were provided in the frame, it is 6 bytes in size
//   there is only 1 header per frame, it is the first 6 bytes of the frame
//   Fields:  
//   U - Unused, reserved for future, 2 bytes, unsigned short
//   Count - Count of readings, 4 bytes, unsigned int
//   !--------!-----!-----!
//   !    U   ! Size!Count!
//   !--------!-----!-----!
//   !   4    !    2!    2!
//   !--------!-----!-----!
//   
//   each reading indicates whether a value was obtained and if so, the distance measured for the indicated angle, a reading is 10 bytes in size
//   there is a limit of 409 readings per frame
//   Fields:  
//   S - Sync flag, 1 byte, unsigned char
//   Angle - Sync flag, 4 bytes, float
//   Distance - Sync flag, 4 bytes, float
//   Q - Quality flag, 1 byte, unsigned char
//   see RPLidar A1 documentation from slamtec for more information on the meaning of these flags
//   !--------!--------!--!--!
//   !Angle   !Distance! Q! S!
//   !--------!--------!--!--!
//   !       4!       4! 1! 1!
//   !--------!--------!--!--!
//   this arrangement is more memory efficient due to c++ byte padding

#define FRAME_SIZE 4096
#define READING_LIMIT 409

typedef struct _Header{
	unsigned int U=0;      //unused, defaulted to 0; 
	unsigned short size;   //bufferSize
	unsigned short count;  //number of readings in buffer
} Header;

typedef struct _Reading{
	float angle;
	float distance;
	unsigned char qualityFlag;
	unsigned char syncFlag;
} Reading;

typedef struct _Frame{
	Header header;
	std::vector<Reading> readings;
} Frame;

class LidarDevice
{
private:
	std::string device;
	bool isSimulation;
	rp::standalone::rplidar::RPlidarDriver * drv;
	const char * opt_com_path;
	_u32 opt_com_baudrate;
	u_result   op_result;	
	void deviceRead(Frame& frame);
public:
	LidarDevice(char*,bool);
	~LidarDevice();
	Frame read();
	static const float Range;
	static int calculateX(Reading&,double,int,int);
	static int calculateY(Reading&,double,int,int);
	static unsigned char calculateColor(Reading&);
	void initialize();
};
	
