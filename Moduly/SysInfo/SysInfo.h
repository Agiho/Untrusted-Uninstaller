#include <string>

struct SSysInfo
{
	std::string Name;

	std::string SP; //service pack

	std::string OSArch;

	unsigned int FreeMem;

	unsigned int Lang;  //polish 1045

	unsigned int Type; //if not WindowsNT

};