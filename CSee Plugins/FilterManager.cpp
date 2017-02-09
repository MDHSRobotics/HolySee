#include "stdafx.h"
#include "FilterManager.h"

//add includes for your filters here ----------
#include "SquareAR.h"
#include "CircleAR.h"
//---------------------------------------------

void FilterManager::initialize(){
	Filter* filter;

	//add filters here---------------------
	filter = new SquareAR();
	add(filter->getName(), filter);

	filter = new CircleAR();
	add(filter->getName(), filter);
	//-------------------------------------
}

FilterManager::FilterManager()
{
	initialize();
}


void FilterManager::add(std::string& name, Filter* filter){
	std::shared_ptr<Filter*> pFilter = std::make_shared<Filter*>(filter);
	filters[name]=pFilter;
}

bool FilterManager::contains(std::string& name){
	return filters.count(name) > 0;
}

Filter* FilterManager::get(std::string& name){
	return *filters[name].get();
}

FilterManager& FilterManager::getInstance(){
	static FilterManager    instance;   // Guaranteed to be destroyed.
										// Instantiated on first use.
	return instance;
}
