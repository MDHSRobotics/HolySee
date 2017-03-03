#include "LidarDevice.h"
#include <chrono>
#define _USE_MATH_DEFINES
#include <math.h>  
#include <thread>  //for Unix
//#include <windows.h> //for Windows


void simulateFrame(Frame& frame);

LidarDevice::LidarDevice(char * device,bool isSimulation) : device(std::string(device)),isSimulation(isSimulation)
{
}

LidarDevice::~LidarDevice()
{
}

Frame LidarDevice::read(){
	//printf("reading ...");
	Frame frame;
	if (isSimulation){
		//printf("simulate frame");
		simulateFrame(frame);
	}
	else{
		
	}
	//printf("\n");
	return frame;
}


Reading createReading(float angle, float distance, unsigned char qualityFlag, unsigned char syncFlag){
	Reading reading;
	reading.angle = angle;
	reading.distance = distance;
	reading.qualityFlag = qualityFlag;
	reading.syncFlag = syncFlag;
	return reading;
}


void simulateFrame(Frame& frame)
{
	//simulate a scan

	std::this_thread::sleep_for(std::chrono::milliseconds(200)); //simulates 5 frames per second, Unix
	//Sleep(200); //simulates 5 frames per second, Windows

	frame.readings.push_back(createReading(352.718750f, 1706.000000f, 0x47, 0x01));
	frame.readings.push_back(createReading( 353.921875f, 1687.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 356.312500f, 1663.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 357.515625f, 1652.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 358.843750f, 1643.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 0.046875f, 1640.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 1.250000f, 1637.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 2.375000f, 0.000000f, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 2.453125f, 1622.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 3.656250f, 1617.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 4.859375f, 1615.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 6.046875f, 1611.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 7.125000f, 1604.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 8.453125f, 1603.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 9.656250f, 1604.000000f, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 10.859375f, 1597.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 12.062500, 1598.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 13.265625, 1598.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 14.468750, 1598.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 15.656250, 1599.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 16.859375, 1598.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 18.062500, 1599.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 19.140625, 1605.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 20.468750, 1607.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 21.671875, 1614.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 22.875000, 1616.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 24.078125, 1628.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 25.281250, 1640.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 26.484375, 1643.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 27.562500, 1654.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 28.765625, 1660.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 30.093750, 1672.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 31.296875, 1679.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 32.500000, 1694.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 33.578125, 1709.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 34.781250, 1722.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 35.984375, 1744.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 37.187500, 1759.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 38.390625, 1778.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 39.593750, 1797.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 40.796875, 1816.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 42.000000, 1838.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 43.203125, 1858.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 44.406250, 1881.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 45.484375, 1907.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 46.687500, 1941.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 47.890625, 1966.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 49.093750, 1995.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 50.296875, 2026.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 51.500000, 2056.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 52.703125, 2085.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 53.890625, 2124.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 55.078125, 2156.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 56.281250, 2196.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 57.468750, 2231.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 58.671875, 2280.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 59.734375, 2321.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 60.921875, 2369.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 62.125000, 2422.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 63.312500, 2479.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 64.515625, 2539.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 65.703125, 2606.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 66.890625, 2674.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 68.093750, 2758.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 69.281250, 2834.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 70.359375, 2918.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 71.546875, 3025.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 72.734375, 3130.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 81.562500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 75.250000, 2758.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 83.953125, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 77.515625, 3401.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 78.703125, 3401.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 79.906250, 3354.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 81.093750, 3331.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 82.296875, 3292.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 91.109375, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 92.296875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 85.875000, 3218.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 87.062500, 3207.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 88.265625, 3183.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 89.453125, 3066.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 90.656250, 3059.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 91.843750, 3054.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 93.031250, 3050.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 94.218750, 3047.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 95.421875, 3042.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 96.609375, 3033.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 97.796875, 3034.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 99.000000, 3016.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 100.187500, 3017.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 101.375000, 3029.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 102.578125, 3032.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 103.765625, 3033.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 104.953125, 3024.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 106.156250, 3105.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 114.968750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 116.156250, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 117.359375, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 118.546875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 119.734375, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 119.171875, 242.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 122.125000, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 123.312500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 124.500000, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 125.703125, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 126.890625, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 128.078125, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 129.281250, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 130.468750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 131.656250, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 132.859375, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 134.046875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 135.234375, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 136.437500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 137.625000, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 131.187500, 3506.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 132.390625, 3555.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 133.578125, 3262.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 134.781250, 3206.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 135.968750, 3187.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 137.171875, 3169.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 138.359375, 3158.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 139.562500, 3108.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 140.750000, 3111.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 141.953125, 3191.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 143.140625, 3244.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 151.968750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 145.531250, 3119.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 146.734375, 3114.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 147.921875, 3193.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 149.109375, 3433.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 157.937500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 159.125000, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 160.328125, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 161.515625, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 162.718750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 163.906250, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 165.109375, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 166.296875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 167.500000, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 168.687500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 169.890625, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 171.078125, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 172.281250, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 173.468750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 174.671875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 175.859375, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 177.062500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 178.265625, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 179.468750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 180.671875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 181.859375, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 183.062500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 184.265625, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 185.468750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 186.671875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 187.859375, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 189.062500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 190.265625, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 191.468750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 192.671875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 193.875000, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 195.062500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 196.265625, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 197.468750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 198.671875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 199.875000, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 201.062500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 202.265625, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 203.468750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 204.671875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 205.875000, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 207.062500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 200.890625, 2243.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 202.093750, 2237.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 203.296875, 2210.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 204.500000, 2231.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 213.078125, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 206.890625, 2111.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 208.093750, 2124.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 209.281250, 2132.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 210.484375, 2147.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 211.671875, 2159.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 212.875000, 2176.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 214.078125, 2191.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 215.265625, 2207.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 216.468750, 2225.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 217.656250, 2241.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 220.359375, 673.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 221.562500, 659.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 222.750000, 643.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 224.078125, 629.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 227.890625, 296.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 229.718750, 290.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 231.296875, 277.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 232.109375, 271.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 234.187500, 264.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 235.250000, 260.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 236.703125, 259.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 236.906250, 256.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 238.093750, 256.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 239.546875, 257.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 240.734375, 258.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 241.937500, 258.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 242.640625, 262.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 244.203125, 264.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 247.781250, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 245.968750, 283.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 247.921875, 281.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 249.000000, 276.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 250.562500, 274.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 251.750000, 275.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 252.687500, 281.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 254.000000, 274.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 255.437500, 277.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 256.125000, 280.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 257.203125, 280.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 258.265625, 281.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 259.078125, 283.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 263.265625, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 264.453125, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 261.890625, 323.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 263.718750, 325.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 264.406250, 330.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 265.468750, 336.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 266.781250, 343.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 267.593750, 358.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 272.781250, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 273.968750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 275.171875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 276.359375, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 277.546875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 271.984375, 1182.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 273.046875, 1178.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 274.234375, 1174.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 275.437500, 1169.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 276.625000, 1169.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 277.937500, 1167.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 279.125000, 1160.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 280.312500, 1160.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 281.375000, 1156.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 282.578125, 1138.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 283.890625, 1136.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 284.968750, 1139.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 286.281250, 1160.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 287.484375, 1161.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 288.687500, 1135.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 289.750000, 1142.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 297.828125, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 299.031250, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 300.218750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 301.421875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 302.625000, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 303.812500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 298.015625, 1313.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 306.218750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 307.406250, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 308.609375, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 309.812500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 304.250000, 1111.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 312.203125, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 313.406250, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 314.593750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 315.796875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 310.000000, 1418.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 311.187500, 1395.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 312.390625, 1358.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 313.718750, 1317.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 314.781250, 1339.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 316.109375, 1215.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 317.312500, 1197.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 318.500000, 1206.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 319.828125, 1169.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 321.031250, 1161.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 322.234375, 1173.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 330.187500, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 324.265625, 1530.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 325.468750, 1561.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 326.671875, 1592.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 327.875000, 1624.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 329.078125, 1657.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 330.281250, 1692.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 331.359375, 1740.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 332.562500, 1781.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 334.140625, 1208.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 342.218750, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 343.421875, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 337.625000, 1378.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 338.828125, 1440.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 340.046875, 1414.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 341.125000, 1508.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 342.328125, 1441.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 350.656250, 0.000000, 0x00, 0x00 ));
	frame.readings.push_back(createReading( 345.109375, 1063.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 346.312500, 1062.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 347.390625, 1222.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 348.468750, 1260.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading( 349.546875, 1506.000000, 0x47, 0x00 ));
	frame.readings.push_back(createReading(350.625000, 1730.000000, 0x47, 0));

	Header header;
	header.U = 0x00;
	header.size = frame.readings.size() * sizeof frame.readings[0]+ sizeof frame.header;
	header.count = frame.readings.size();

	frame.header = header;
}

const float LidarDevice::Range = 6000;

int LidarDevice::calculateX(Reading& reading, double scale, int width, int xOffset){
	int x;
	unsigned char quadrant;
	if (reading.angle >= 270) quadrant = 4;
	else if (reading.angle >= 180) quadrant = 3;
	else if (reading.angle >= 90) quadrant = 2;
	else quadrant = 0;
	float _dis = reading.distance * scale;
	if (reading.distance > LidarDevice::Range) _dis = LidarDevice::Range*scale;

	switch (quadrant){
	case 1:
		x = (int)round(((float)sin(M_PI * reading.angle / 180.0f))*_dis + LidarDevice::Range*scale) + xOffset;
		break;
	case 2:
		x = (int)round(((float)sin(M_PI*(180.0 - reading.angle) / 180.0f))*_dis + LidarDevice::Range*scale) + xOffset;
		break;
	case 3:
		x = (int)round(((float)sin(M_PI*(180.0 - reading.angle) / 180.0f))*_dis + LidarDevice::Range*scale) + xOffset;
		break;
	default:
		x = (int)round(((float)sin(M_PI * reading.angle / 180.0f))*_dis + LidarDevice::Range*scale) + xOffset;
	}
	
	return x;
}

int LidarDevice::calculateY(Reading& reading, double scale, int height, int yOffset){
	int y;
	unsigned char quadrant;
	if (reading.angle >= 270) quadrant = 4;
	else if (reading.angle >= 180) quadrant = 3;
	else if (reading.angle >= 90) quadrant = 2;
	else quadrant = 0;
	float _dis = reading.distance * scale;
	if (reading.distance > LidarDevice::Range) _dis = LidarDevice::Range*scale;

	switch (quadrant){
	case 1:
		y = (int)round(-((float)cos(M_PI * reading.angle / 180.0f))*_dis + LidarDevice::Range*scale) + yOffset;
		break;
	case 2:
		y = (int)round(((float)cos(M_PI*(180.0 - reading.angle) / 180.0f))*_dis + LidarDevice::Range*scale) + yOffset;
		break;
	case 3:
		y = (int)round(((float)cos(M_PI*(180.0 - reading.angle) / 180.0f))*_dis + LidarDevice::Range*scale) + yOffset;
		break;
	default:
		y = (int)round(-((float)cos(M_PI * reading.angle / 180.0f))*_dis + LidarDevice::Range*scale) + yOffset;
	}
	return y;
}

unsigned char LidarDevice::calculateColor(Reading& reading){
	unsigned char color = 255;  //default to white
	if (reading.distance > 0 && reading.distance < LidarDevice::Range){
		color = (unsigned char)((int)(reading.distance*255.0f / LidarDevice::Range));
	}
	return color;
}
