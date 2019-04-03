#ifndef SScriptInfo_h
#define SScriptInfo_h

#include <string>

struct SScriptInfo
{

	std::string Name;// process name

	std::string FullPath;// path to script file

	bool BChecked; // needed in checkboxes
};

#endif