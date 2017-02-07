// MSee2.cpp : main project file.

#include "MSee.h"

//MSee is the orchestrator
//It is responsible for 
//  * discovering devices
//  * discovering roborio (DNSSD)
//  * connecting with roborio (WebSockets)
//  * Instantiating CSee
//  * configuration




int main(int argc,char *argv[])
{
	std::string instanceName("Tegra");
	std::string configFile("src/msee.conf");

	MSee* msee = new MSee(instanceName,configFile);

	delete msee;
    return 0;
}
