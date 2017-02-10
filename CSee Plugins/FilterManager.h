#ifndef __GST_ARFILTER_FILTER_MANAGER__
#define __GST_ARFILTER_FILTER_MANAGER__

#include <string>
#include <map>
#include <memory>
#include "Filter.h"

class FilterManager
{

private:
	std::map<std::string, std::shared_ptr<Filter*>> filters;
	void initialize();
	FilterManager();

public:
	FilterManager(FilterManager const&) = delete;
	void operator=(FilterManager const&) = delete;
	void add(std::string&, Filter*);
	bool contains(std::string&);
	Filter* get(std::string&);
	static FilterManager& getInstance();
};


#endif /* __GST_ARFILTER_FILTER_MANAGER__ */