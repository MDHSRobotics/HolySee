// MSee2.cpp : main project file.

#include <chrono>
#include <thread>
#include <iostream>
#include "MSee.h"
#include "Streamer.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include"DNSSDBrowser.h"

//MSee is the orchestrator
//It is responsible for 
//  * discovering devices
//  * discovering roborio (DNSSD)
//  * connecting with roborio (WebSockets)
//  * Instantiating CSee
//  * configuration

#define CONF_TOKEN std::string("-conf")

void moveToEnd(int* argc, char * argv[], int positionToMoveToEnd);  //strip command line arguments
int mygetch ( void );  //implements a keystroke listener on the msee console, keystrokes are processed by the processKeys method
void processKeys( MSee*  handler); //method that handles the keystrokes: switch channel (enter key) and exit (x key)

int main(int argc,char *argv[])
{
	std::string instanceName("Tegra"); //default name
	std::string configFile("msee.conf"); //default config file location

	for (int i = 1; i < argc; i++){
		if (argv[i][0] != '-'){
			// this argument is the instance name
			//move this element to the end of the argv char * array and backfill the void by moving up other elements
			instanceName = std::string(argv[i]);
			moveToEnd(&argc, argv, i);
			i--;
		}
		else if (strncmp(argv[i], CONF_TOKEN.c_str(), CONF_TOKEN.length()) == 0){
			// this argument is the location of the config file
			//move this element to the end of the argv char * array and backfill the void by moving up other elements
			configFile = std::string(argv[i]);
			configFile = conf.substr(CONF_TOKEN.length());
			moveToEnd(&argc, argv, i);
			i--;
		}
	}
	printf("instance name = %s\n", instanceName.c_str());
	printf("conf = %s\n", configFile.c_str());
	printf("%d gstreamer args:\n",argc-1);
	for (int k = 1; k < argc; k++){
		printf("\t%d: %s\n", k,argv[k]);
	}

	MSee* msee = new MSee(argc,argv,instanceName,configFile);

	//start a dnssd browser - find the robot!
	std::thread browser(&DNSSDBrowser::scan,msee);
	browser.detach();

	//start a keyboard listener
	std::thread keyboardListener(processKeys,msee);
	keyboardListener.detach();
	
	while(!MSee::streamer->isReady()){
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); //Unix
	}
	
	msee->start();

	delete msee;
    return 0;
}

void moveToEnd(int* argc, char * argv[], int positionToMoveToEnd){
	//printf("argc=%d, position=%d \n",*argc, positionToMoveToEnd);
	char * temp = argv[positionToMoveToEnd];
	for (int j = positionToMoveToEnd + 1; j < *argc; j++){
		argv[j - 1] = argv[j];
	}
	argv[*argc - 1] = temp;
	//printf("results of move \n ------------------------\n");
	//for (int k = 0; k < *argc; k++){
	//	printf("argv[%d]=%s\n", k, argv[k]);
	//}
	//printf("------------------------\n");
	*argc = *argc-1;
}

int mygetch ( void )
{
//	printf("%s\n","mygetch.." );
  int ch;
  struct termios oldt, newt;

  tcgetattr ( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

  return ch;
}

void processKeys( MSee*  handler){
	int currentChannel = 0;
	bool done = false;
		printf("%s\n","Press enter to switch channels or X key to exit ..." );
		while(!done){
			int c = mygetch();
	//   	    printf("Char: 0x%02x\n", c);
	   	    if(c==0x0a){
	   		//	printf("%s\n","switching..." );
	   			currentChannel ++;
	   			currentChannel = currentChannel%handler->getChannelCount();
	   			MSee::switchTo(currentChannel);
	   	    }
	   	    else if(c==0x78){
	   			//printf("%s\n","exitting..." );
	   			done = true;
	   			handler->stop();;
	   			continue;
	   	    }
		}
		printf("%s\n","exiting..." );
}
