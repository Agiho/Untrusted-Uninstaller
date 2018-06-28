#include <windows.h>
#include <string>
#include "Log.h"

class CRSrvStart
{
public:

	CRSrvStart();

	// sets log
	void InsertLog( CLog *LTog);

	//starts service on computer
	int StartRemoteService(std::string Where, std::string Which);

	//stops service on computer
	int StopRemoteService(std::string Where, std::string Which);

private:

	CLog *Log;

	//Computer IP adress Where service will be stared
	std::string RemoteLoc;

	//service name to start
	std::string WhichSrv;

	//true when service is started
	bool Started;

	//handle to share to handle service
	SC_HANDLE hSCM;
};