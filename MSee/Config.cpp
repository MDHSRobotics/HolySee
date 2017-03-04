#include "Config.h"

#include <stdlib.h>  
#include <stdio.h>
#include <array>
#include <memory>
#include <string>

#include "VideoSource.h"
#include "LidarSource.h"

void trim(std::string& s) {
	while (s.compare(0, 1, " ") == 0 || s.compare(0, 1, "\t") == 0 )
		s.erase(s.begin()); // remove leading whitespaces
	while (s.size()>0 && (s.compare(s.size() - 1, 1, " ")==0 || s.compare(0, 1, "\t")== 0))
		s.erase(s.end() - 1); // remove trailing whitespaces
}

std::vector<std::string> Config::split(const char *str, char& delimiter)
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
	devices.clear();

	try{

		pConf = new PropertyFileConfiguration(configFileName);
		for (std::string node : getNodes()){
			printf("node: %s\n", node.c_str());
			std::vector<std::string> keys;
			pConf->keys((configRoot+std::string(".")+node), keys);
			//build identifier map
			for (std::string paramKey : keys){
				std::string theKey((configRoot+std::string(".")+node)+std::string(".")+paramKey);
				//printf("param: %s\n", theKey.c_str());
				if (paramKey == identifiyerToken){
					std::string identifier = get(theKey);
					trim(identifier);
					//printf("\tidentifier: %s\n", identifier.c_str());
					identifierMap[node]=identifier;
				}
			}
		}

		std::string usbCommand("./lshw.sh");
		std::string cameraCommand("./v4l2.sh");
		
		std::string camerasText;
		discover(cameraCommand, camerasText);
		discoverCameras(camerasText);
		
		std::string usbText;
		discover(usbCommand,usbText);
		discoverUSB(usbText);

		//printf("%d devices\n",devices.size());
		//printf("pipelineDefinition:\n\t%s\n",getPipelineDefinition().c_str());
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
//		nodes.push_back(configRoot+std::string(".")+key);
		nodes.push_back(key);
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
					std::string name = entry.first;
					std::vector<std::string> keys;
					pConf->keys((configRoot+std::string(".")+name), keys);
					std::string arFilter;
					std::string cvFilter;
					if(keys.size()>0){
						for(std::string key : keys){
							std::string paramName = configRoot+std::string(".")+name+std::string(".")+key;
							//printf("retrieving %s\n",paramName.c_str());
							if(key == AR_TOKEN){
								arFilter=get(paramName);
							}
							if(key == CV_TOKEN){
								cvFilter=get(paramName);
							}

						}
					}

					//printf("usb device[name: %s,path:%s, description:%s]\n",name.c_str(), device.c_str(), description.c_str());
					std::shared_ptr<Source> dev(new LidarSource(name,device,arFilter,cvFilter));
					devices[name]=dev;
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

	char lineDelimiter = '\n';
	char fieldDelimiter = '-';
	std::vector<std::string> lines = split(camerasText.c_str(), lineDelimiter);
	//printf("%d camera lines\n", lines.size());
	if (lines.size() > 0){
		for (int i = 0; i < lines.size()-1; i++){
			std::string line1 = lines.at(i);
			trim(line1);
//			printf("camera line %d - %s\n", i, line1.c_str());
			std::string line2 = lines.at(i+1);
			trim(line2);
//			printf("camera line %d - %s\n", i+1, line2.c_str());

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
				std::string busInfo = line1.substr(posDelim1 + 1, posDelim2 - posDelim1-1);
				trim(busInfo);
				std::string path = line2;
				trim(path);
				for (auto const& entry : identifierMap) {
					if (entry.second == id){
						std::string name = entry.first;
						std::vector<std::string> keys;
						pConf->keys((configRoot+std::string(".")+name), keys);

						std::string arFilter;
						std::string cvFilter;
						std::string source;

						if(keys.size()>0){
							for(std::string key : keys){
								std::string paramName = configRoot+std::string(".")+name+std::string(".")+key;
								if(key == AR_TOKEN){
									arFilter=get(paramName);
								}
								if(key == CV_TOKEN){
									cvFilter=get(paramName);
								}
								if(key == source_TOKEN){
									source = get(paramName);
								}
							}
						}
						//printf("camera[name: %s, path:%s, id:%s, busInfo:%s]\n",name.c_str(), path.c_str(), id.c_str(), busInfo.c_str());
						std::shared_ptr<Source> dev;
						if(source.empty()) dev = std::shared_ptr<Source>(new VideoSource(name,path,false,arFilter,cvFilter));
						else dev = std::shared_ptr<Source>(new VideoSource(name,path,false,arFilter,cvFilter,source));
						name.insert(0,std::to_string(devices.size())+std::string("_"));
						devices[name]=dev;
						break;
					}
				}
				i++;
			}
		}
	}

}

std::map<std::string, std::shared_ptr<Source>> Config::getDevices(){
	return devices;
}

std::string Config::getPipelineDefinition(){
	if(pipelineDefinition.empty()){
		createPipelineDefinition();
	}
	printf("pipeline: \n\t%s\n",pipelineDefinition.c_str());
	return pipelineDefinition;
}

void Config::createPipelineDefinition(){
	std::string streamName("stream");
	int countChannels=0;
	int channelIndex=1;
	std::vector<std::string> channelNames;
	std::string tokenRaw("_raw");
	std::string tokenAR("AR");

	for (auto const& entry : devices) {
		Source* dev = entry.second.get();
		//printf("found %s @ %s\n",dev->getName().c_str(),dev->getDevice().c_str());
		if (dev->countChannels()>0){
			//printf("dev %s has %d connections and %d channels.\n", dev->getName().c_str(), dev->countConnections(), dev->countChannels());
			for (int c = 0; c < dev->getChannelNames().size(); c++){
				std::string channelName = std::string(std::to_string(channelIndex) + "." + (dev->getChannelNames()[c]));
				channelNames.push_back(channelName);
				channelIndex++;
			}
		}
	}


	printf("streamer has %d channels:\n", channelNames.size());
	for (int i = 0; i < channelNames.size(); i++){
		printf("channel: %s\n", channelNames[i].c_str());
	}


	//start by defining the end of the pipeline
	if ( channelNames.size() > 1){
		pipelineDefinition.append("input-selector sync-mode=clock cache-buffers=true name=");
		pipelineDefinition.append(streamName);
		pipelineDefinition.append(" ! videoconvert ! xvimagesink "); //include the trailing space to create a separator that we know we will need
	}
	else if ( channelNames.size() > 0){
		pipelineDefinition.append("queue name="); //include the trailing space to create a separator that we know we will need
		pipelineDefinition.append(streamName);
		pipelineDefinition.append(" ! videoconvert ! xvimagesink ");
	}

	int sinkId=0;
	//next add the definition to each source.  they will need to tie into the specified output, which in our case is called stream
	for (auto const& entry : devices) {
		Source* dev = entry.second.get();
		if (dev->countConnections()>0){
			//source will need to be added to pipeline
			std::string base = dev->getPipelineSegment();
			pipelineDefinition.append(base);
			pipelineDefinition.append(" ! ");

			if (dev->countConnections() > 1){
				//tee needed
				pipelineDefinition.append("tee name=");
				pipelineDefinition.append(dev->getName());
				pipelineDefinition.append(" ");
			}
			else{
				//tee needed
				pipelineDefinition.append("queue name=");
				pipelineDefinition.append(dev->getName());
				pipelineDefinition.append(" ");
			}
			for(std::string &channelName : dev->getChannelNames()){
					//printf("channel: %s\n",channelName.c_str());
					pipelineDefinition.append(dev->getName());
					pipelineDefinition.append(". ");
					if(dev->countConnections() > 1){
						pipelineDefinition.append("! queue name=");
						pipelineDefinition.append(channelName);
						pipelineDefinition.append("   ");
						pipelineDefinition.append(channelName);
						pipelineDefinition.append(".  !  ");
					}
					else{
						pipelineDefinition.append("  !  ");
					}
					int pos = channelName.find(tokenAR);
					//printf("(AR)channelName: %s, pos:%d, npos:%d\n",channelName.c_str(),pos,channelName.npos);
					if (pos!=std::string::npos){
						//printf("AR  channelName found\n");
						pos = channelName.find_last_of(std::string("_"));
						std::string filterName = channelName.substr(pos+1);
						pipelineDefinition.append("arfilter filter=");
						pipelineDefinition.append(filterName);
						pipelineDefinition.append(" ! ");
					}
					pipelineDefinition.append(streamName);
					pipelineDefinition.append(". ");
			}
		}
	}
}

