#include <windows.h>
#include <string>
#include "Log.h"

class CRSrvStart
{
public:

	CRSrvStart();

	void InsertLog( CLog *LTog);

	int StartRemoteService(std::string Where, std::string Which);

	int StopRemoteService(std::string Where, std::string Which);

private:

	CLog *Log;

	//Computer IP adress Where service will be stared
	std::string RemoteLoc;

	std::string WhichSrv;

	bool Started;

	SC_HANDLE hSCM;
};