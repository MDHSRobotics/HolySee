#include "Config.h"

#include <stdlib.h>  
#include <stdio.h>
#include <array>
#include <memory>
#include <string>

void trim(std::string& s) {
	while (s.compare(0, 1, " ") == 0)
		s.erase(s.begin()); // remove leading whitespaces
	while (s.size()>0 && s.compare(s.size() - 1, 1, " ") == 0)
		s.erase(s.end() - 1); // remove trailing whitespaces
}

std::vector<std::string> split(const char *str, char& delimiter)
{
	std::vector<std::string> result;

	do
	{
		const char *begin = str;

		while (*str != delimiter && *str)
			str++;

		result.push_back(std::string(begin, str));
	} while (0 != *str++);

	return result;
}

Config::Config(std::string& configRoot, std::string& configFileName) : configFileName(configFileName), configRoot(configRoot)
{
	std::string identifiyerToken("identifier");
	printf("config: %s\nname: %s\n", configFileName.c_str(), configRoot.c_str());

	try{

		pConf = new PropertyFileConfiguration(configFileName);
		for (std::string node : getNodes()){
			printf("node: %s\n", node.c_str());
			std::vector<std::string> keys;
			pConf->keys(node, keys);
			//build identifier map
			for (std::string paramKey : keys){
				std::string theKey(node+std::string(".")+paramKey);
				//printf("param: %s\n", theKey.c_str());
				if (paramKey == identifiyerToken){
					std::string identifier = get(theKey);
					trim(identifier);
					//printf("\tidentifier: %s\n", identifier.c_str());
					identifierMap[node]=identifier;
				}
			}
		}
		std::string usbText;
		std::string usbCommand("/usr/local/msee/lshw.sh");
		std::string cameraCommand("/usr/local/msee/v4l2.sh");
		discover(usbCommand,usbText);
		discoverUSB(usbText);

		std::string camerasText;
		discover(cameraCommand, camerasText);
		discoverCameras(camerasText);

	}
	catch (const std::exception& e){
		printf("Exception: %s\n",e.what());
		printf("%s\n", "Aborting!");
		std::exit(EXIT_FAILURE);
	}
}

std::vector<std::string> Config::getNodes(){
	if (nodes.size()<1){
		parseNodes();
	}
	return nodes;
}

void Config::parseNodes(){
	std::vector<std::string> keys;
	pConf->keys(configRoot,keys);
	for (std::string key : keys){
		nodes.push_back(configRoot+std::string(".")+key);
	}
}

void Config::discover(std::string& command, std::string& result){
		std::array<char, 128> buffer;
		result.clear();
		std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
		if (!pipe) throw std::runtime_error("popen() failed!");
		while (!feof(pipe.get())) {
			if (fgets(buffer.data(), 128, pipe.get()) != NULL)
				result += buffer.data();
		}
		//printf("command returned: \n%s\n",result.c_str());
}

void Config::discoverUSB(std::string& usbText){
	// data is in the format of:
	//		/dev/input/event7 - Logitech_USB_Receiver
	//		/dev/input/mouse1 - Logitech_USB_Receiver
	//		/dev/input/event8 - Logitech_USB_Receiver
	//		/dev/input/event9 - Logitech_USB_Receiver
	//		/dev/hidraw0 - Logitech_USB_Receiver
	//		/dev/hidraw1 - Logitech_USB_Receiver
	//		/dev/hidraw2 - Logitech_USB_Receiver
	//		/dev/hidraw3 - Logitech_USB_Receiver
	//		/dev/usb/hiddev0 - Logitech_USB_Receiver
	//		/dev/ttyUSB0 - Silicon_Labs_CP2102_USB_to_UART_Bridge_Controller_0001
	//		/dev/input/event6 - Chicony_Electronics_Co._Ltd._USB2.0_HD_UVC_WebCam_0x0001
	//		/dev/video0 - Chicony_Electronics_Co._Ltd._USB2.0_HD_UVC_WebCam_0x0001
	char lineDelimiter = '\n';
	char fieldDelimiter = '-';
	std::vector<std::string> lines = split(usbText.c_str(), lineDelimiter);
	int i = 0;
	for (std::string line : lines){
		i++;
		std::vector<std::string> tokens = split(line.c_str(), fieldDelimiter);
		if (tokens.size() == 2){
			std::string device = tokens.at(0);
			trim(device);
			std::string description = tokens.at(1).c_str();
			trim(description);
			for (auto const& entry : identifierMap) {
				//printf("checking conf entry :-->%s<--: -->%s<-- against -->%s<--\n", entry.first.c_str(), entry.second.c_str(),description.c_str());
				if (entry.second == description){
					printf("usb device[path:%s, description:%s]\n", device.c_str(), description.c_str());
					//TODO:  create lidar - match found between what's in the config and what was discovered through the system
					break;
				}
			}
		}
	}
}

std::string Config::get(std::string& key){
	//printf("retrieving param %s: %s \n", (node + "." + key).c_str(), pConf->getString(node + "." + key).c_str());
	return pConf->getString(key);
}


void Config::discoverCameras(std::string& camerasText){
	// data is in the format of:
	// Zebra CAMERA(usb - 0000:00 : 1d.7 - 1) :
	//         / dev / video1
	// UVC Camera(046d:0819) (usb - 0000:00 : 1d.7 - 2) :
	//         / dev / video0
	// HD Pro Webcam C920(usb - musb - hdrc.1.auto - 1) :
	//         / dev / video2


	/*   Java code
	StringTokenizer st = new StringTokenizer(camerasText,"\n"); //get each line 1 at a time
	while(st.hasMoreTokens()){
	String line1 = st.nextToken().trim();
	String line2 = st.nextToken().trim();
	if(line1 == null || line2 == null){
	System.err.printf("Invalid camera definition.  line1  = %s.  line 2 = %s\n",line1,line2);
	}
	String id= null;
	String name= null;
	String path = null;
	if(line2!=null && line2.length()>0){
	id = line2;
	}
	//			if(id!=null) System.out.printf("id -->%s<--\n",id);

	if(line1!=null && line1.length()>0){
	if(line1.lastIndexOf(" (")>=0){
	name = line1.substring(0,line1.lastIndexOf(" (")).trim();
	}
	}
	//			if(name!=null) System.out.printf("name -->%s<--\n",name);

	if(line1!=null && line1.length()>0){
	if(line1.lastIndexOf(" (")>=0 && line1.indexOf("):",line1.lastIndexOf(" ("))>=0){
	path = line1.substring(line1.lastIndexOf(" (")+" (".length(),line1.indexOf("):",line1.lastIndexOf(" ("))).trim();
	}
	}
	//			if(path!=null) System.out.printf("path -->%s<--\n",path);
	if(id!=null && name!=null && path!=null && sources.containsKey(name)){
	VideoDevice dev = new VideoDevice(id,name,path);
	cameras.add(dev);
	}
	}
	}
	*/
	char lineDelimiter = '\n';
	char fieldDelimiter = '-';
	std::vector<std::string> lines = split(camerasText.c_str(), lineDelimiter);
	//printf("%d camera lines\n", lines.size());
	if (lines.size() > 0){
		for (int i = 0; i < lines.size()-1; i++){
			std::string line1 = lines.at(i);
			trim(line1);
			//printf("camera line %d - %s\n", i, line1.c_str());
			i++;
			std::string line2 = lines.at(i);
			trim(line2);
			//printf("camera line %d - %s\n", i, line2.c_str());

			//parse line1
			//bus info is in between parenthesis
			//line terminates with a :
			char delim1 = '(';
			char delim2 = ')';
			char delim3 = ':';
			//check that line 1 has all three and that the position of each is good
			int posDelim1 = line1.find_last_of(delim1);
			int posDelim2 = line1.find_last_of(delim2);
			int posDelim3 = line1.find_last_of(delim3);
			if (posDelim1 != std::string::npos && posDelim2 != std::string::npos && posDelim3 != std::string::npos &&
				posDelim1 < posDelim2 && posDelim2 < posDelim3){
				//valid line, ignore others
				std::string id = line1.substr(0, posDelim1-1);
				trim(id);
				std::string name = line1.substr(posDelim1 + 1, posDelim2 - posDelim1-1);
				trim(name);
				std::string path = line2;
				trim(path);
				for (auto const& entry : identifierMap) {
					if (entry.second == id){
						printf("camera[id:%s, name:%s, path:%s]\n", id.c_str(), name.c_str(), path.c_str());
						//TODO:  create lidar - match found between what's in the config and what was discovered through the system
						break;
					}
				}
			}
		}
	}

}
