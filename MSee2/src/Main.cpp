// MSee2.cpp : main project file.

#include "stdafx.h"
#include "MSee.h"

using namespace System;

//MSee is the orchestrator
//It is responsible for 
//  * discovering devices
//  * discovering roborio (DNSSD)
//  * connecting with roborio (WebSockets)
//  * Instantiating CSee
//  * configuration




int main(array<System::String ^> ^args)
{
	MSee* msee = new MSee(std::string("Tegra"), std::string("..\\msee.conf"));

	delete msee;
    return 0;
}
