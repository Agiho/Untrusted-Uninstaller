#include "Log.h"


CLog::CLog()
{
	LogPath = "log.txt";
	//Open and creates file
	Log.Init("log.txt", std::ios::out | std::ios::trunc);
	Log.Close();
}

CLog::CLog(std::string Path)
{
	LogPath = Path;
	//Open and creates file
	Log.Init(Path.c_str(), std::ios::out | std::ios::trunc);
	Log.Close();
}

CLog::~CLog()
{
	//close file
	Log.Close();
}

void CLog::WriteTxt(std::string STempTxt)
{
	Log.ReOpen(LogPath.c_str(), std::fstream::out | std::fstream::app);
	//Write text to file
	Log.WriteTxt(STempTxt);
	Log.Close();

}

void CLog::WriteTxt(int IN)
{
	Log.ReOpen(LogPath.c_str(), std::fstream::out | std::fstream::app);
	Stream.clear();
	Stream.str("");
	Stream << IN;
	Log.WriteTxt(Stream.str());
	Log.Close();
}