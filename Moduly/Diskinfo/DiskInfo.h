#include <string>

struct SDiskInfo
{
	std::string Name; // disk name

	std::string Caption; // disk letter

	unsigned int FreeSpace; // free space on it

	unsigned int DriveType; // drivetype

	unsigned int LastError; // last error on disk

};