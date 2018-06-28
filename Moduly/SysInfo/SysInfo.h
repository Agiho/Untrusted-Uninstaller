#include <string>

struct SSysInfo
{
	std::string Name; // system name

	std::string SP; //service pack

	std::string OSArch; // OS archicecture, example: 64-bit

	unsigned int FreeMem; // free memory

	unsigned int Lang;  //polish 1045

	unsigned int Type; //if not WindowsNT

};