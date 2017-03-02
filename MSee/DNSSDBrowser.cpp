/*
 * DNSSDBrowser.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: team4141
 */

#include "DNSSDBrowser.h"
#include "stdio.h"

DNSSDBrowser::DNSSDBrowser(MSee* msee): msee(msee) {

}

DNSSDBrowser::~DNSSDBrowser() {
}

void DNSSDBrowser::scan(MSee* msee){
	std::string result;
	std::string command("/usr/local/msee/avahi.sh");
	bool foundRobot = false;
	int attempts = 0;
	int limit = 20;
	std::string robotURI;
	while(! foundRobot && attempts < limit){
		Config::discover(command,result);
		if(result.length()>0){
			foundRobot = discoverDNSSD(result,robotURI);
		}
		attempts++;
	}
	if(!foundRobot){
		throw std::runtime_error("Unable to find robot");
	}
	msee->robotDiscovered(robotURI);
}



bool  DNSSDBrowser::discoverDNSSD(std::string& dnssdText,std::string& serverURI){
	// data is in the format of:
//	+   eth0 IPv4 Team4141Robot                                 _ws._tcp             local
//	=   eth0 IPv4 Team4141Robot                                 _ws._tcp             local
//	   hostname = [roboRIO-4141-FRC.local]
//	   address = [10.41.41.20]
//	   port = [5808]
//	   txt = []

	char lineDelimiter = '\n';
	char serviceResolveIndicator='=';
	char serviceDiscoverIndicator='+';
	std::string addressToken("address = [");
	std::string portToken("port = [");
	std::string endToken("]");
	std::string nameToken("roboRIO-4141-FRC");
	std::string serviceToken("_ni._tcp");


	//what we want to do is identify the service resolve line, which starts with an =
	//we want to check if that line contains our service token _ws._tcp
	//then check that the line contains our name token TEAM4141
	//if these conditions are met, we have found the service details we need

	std::vector<std::string> lines = Config::split(dnssdText.c_str(), lineDelimiter);
	int pos= std::string::npos;
	std::string address;
	std::string port("5808");

	for(int i=0;i<lines.size();i++){
		std::string & line = lines[i];
		
		if(line[0]==serviceResolveIndicator && line.find(serviceToken)!=std::string::npos && line.find(nameToken)!=std::string::npos){
			//found service resolution header for our robot, matches protocol and name
			printf("%d - %s\n",i,line.c_str());
			i++;
			while( i<lines.size()){
				printf("%d - %s\n",i,line.c_str());
				line = lines[i];
				if(line[0]==serviceResolveIndicator || line[0]==serviceDiscoverIndicator) break;  //done with resolve block
				pos = line.find(addressToken);
				if(pos!=std::string::npos){
					//value is inside [ ]
					address = line.substr(pos+addressToken.length(),line.find(endToken) -( pos+addressToken.length()));
//					printf("examining: %s\n",line.c_str());
				}
//				pos = line.find(portToken);
//				if(pos!=std::string::npos){
//					//value is inside [ ]
//					port = line.substr(pos+portToken.length(),line.find(endToken) -( pos+portToken.length()));
//				}
				i++;
			}
		}
	}

	if(!address.empty() && !port.empty()){
		printf("address:port = %s:%s\n",address.c_str(),port.c_str());
		serverURI.append("ws://");
		serverURI.append(address);
		serverURI.append(":");
		serverURI.append(port);
		return true;
	}

	return false;
}
