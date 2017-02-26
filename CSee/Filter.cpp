#include "Filter.h"


Filter::Filter(std::string& name): name(name)
{
}

std::string& Filter::getName(){
	return name;
}
