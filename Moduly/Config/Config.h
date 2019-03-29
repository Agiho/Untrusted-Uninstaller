#ifndef Config_h
#define Config_h

#include <string>
#include "Log.h"

class CConfig
{

public:

	void Init(CLog *TLog); //reads config from file

	std::string GetMainLoc(); // return main localization

private:

	CLog *Log; //log pointer

	std::string MainLoc; //program and its files localization

};

#endif