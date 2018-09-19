#ifndef SProcessInfo_h
#define SProcessInfo_h

#include <string>

struct SProcessInfo
{
	unsigned int PID; //process ID

	unsigned int SID; //user session ID 

	std::string Name;// process name

	bool BChecked; // needed in checkboxes
};

#endif