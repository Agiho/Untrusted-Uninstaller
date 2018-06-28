#ifndef Log_h
#define Log_h

#include <string>
#include "File.h"
#include <sstream>


// class what makes log file
class CLog
{

public:

	//Creates the file
	CLog();
	CLog(std::string Path);

	//Close the file
	~CLog();

	//Write text to file
	void WriteTxt(std::string TSempTxt);

	//convert number to string and writes it to file
	void WriteTxt(int IN);

private:

	//object for managing file
	CFile Log;

	//path to file
	std::string LogPath;

	//stream for conversions
	std::stringstream Stream;
};
#endif