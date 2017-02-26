#ifndef __TEAM4141_MSEE_LIDARSOURCE__
#define __TEAM4141_MSEE_LIDARSOURCE__

#include <vector>
#include <string>
#include "Source.h"
#include "Reading.h"
//#include "rplidar/rplidar.h" //RPLIDAR standard sdk, all-in-one header

//using namespace rp::standalone::rplidar;


class LidarSource :
	public Source
{
private:
	std::vector<Reading> scan;
	bool isSimulation;
	//std::string fileName;
	void simulate();
	void grabData();
	//	RPlidarDriver * drv;
	//	const char * opt_com_path;
	//	_u32 opt_com_baudrate;
	//	u_result   op_result;
public:
	LidarSource(std::string name, std::string device, std::string arName, std::string cvName);
	~LidarSource();
	void initialize();
	void setSimulate(bool);
	void showScan();
	//void saveScan();
	//void saveScan(std::string);
	//void imageScan();
	void shutdown();
	std::string getPipelineSegment();
};

#endif /* __TEAM4141_MSEE_LIDARSOURCE__ */
