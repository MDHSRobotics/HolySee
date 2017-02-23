/*
 * ARFilter.h
 *
 *  Created on: Feb 12, 2017
 *      Author: team4141
 */

#ifndef ARFILTER_H_
#define ARFILTER_H_

#include <string>

class ARFilter {
private:
	std::string&  name;
public:
	ARFilter(std::string&);
	virtual ~ARFilter();
};

#endif /* ARFILTER_H_ */
