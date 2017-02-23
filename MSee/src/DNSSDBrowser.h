/*
 * DNSSDBrowser.h
 *
 *  Created on: Feb 15, 2017
 *      Author: team4141
 */

#ifndef DNSSDBROWSER_H_
#define DNSSDBROWSER_H_
#include "MSee.h"
#include <string>

class DNSSDBrowser {
private:
	MSee* msee = NULL;
	static bool discoverDNSSD(std::string&,std::string&);

 public:
	DNSSDBrowser(MSee*);
	virtual ~DNSSDBrowser();
	static void scan(MSee *);
};

#endif /* DNSSDBROWSER_H_ */
