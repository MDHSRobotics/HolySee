// MSee2.cpp : main project file.

#include <chrono>
#include <thread>
#include <iostream>
#include "MSee.h"
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

//handler
int mygetch ( void )
{
	printf("%s\n","mygetch.." );
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
	int channels = handler->getChannelCount();
	int currentChannel = 0;
	bool done = false;
		printf("%s\n","Press enter to switch channels or X key to exit ..." );
		while(!done){
			int c = mygetch();
	   	    printf("Char: 0x%02x\n", c);
	   	    if(c==0x0a){
	   			printf("%s\n","switching..." );
	   			currentChannel ++;
	   			currentChannel = currentChannel%channels;
	   			handler->switchTo(currentChannel);
	   	    }
	   	    else if(c==0x78){
	   			printf("%s\n","quitting..." );
	   			done = true;
	   			handler->stop();;
	   			continue;
	   	    }
		}
		printf("%s\n","exiting..." );
}

int main(int argc,char *argv[])
{
	std::string instanceName("Tegra");
	std::string configFile("../msee.conf");

	MSee* msee = new MSee(argc,argv,instanceName,configFile);

	//start a dnssd browser - find the robot!
	std::thread browser(&DNSSDBrowser::scan,msee);
	browser.detach();

	//start a keyboard listener
	std::thread keyboardListener(processKeys,msee);
   keyboardListener.detach();

	msee->start();

	delete msee;
    return 0;
}
