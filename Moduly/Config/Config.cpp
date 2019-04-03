#include "Config.h"

void CConfig::Init(CLog *TLog)
{
	Log = TLog;
	CFile Cfg;
	Cfg.Init("Conf.ini", std::ios::in);
	if (!(Cfg.IsOpened())) Log->WriteTxt("Can't open conf.ini file");
	else
	{
		//stream variable
		std::stringstream stream;
		stream.clear();
		//set reading from begin of file
		Cfg.SetReadPos();
		// text from file
		char Text[256];

		//get mail localization
		Cfg.GetLineTxt(Text, 255);
		MainLoc = Text;
	}
}

std::string CConfig::GetMainLoc()
{
	return MainLoc;
}