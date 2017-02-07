	#pragma once

#include "Source.h"

class VideoSource :
	public Source
{
private:

public:
	VideoSource(std::string& name, std::string& device, bool showRaw, std::string& arName, std::string& cvName);
	~VideoSource();
	std::string getPipelineSegment();
};

