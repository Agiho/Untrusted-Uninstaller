#ifndef File_h
#define File_h

#include <fstream>
#include <sstream>

class CFile
{

public:

	CFile();
	~CFile();

	//Initialize and open file
	void Init(const char *FileName, std::ios_base::openmode Mode);

	//Open file
	void ReOpen(const char *FileName, std::ios_base::openmode Mode);

	//Checks is it end of file
	bool EoF();

	//Cheks the file is good and can be read
	bool AllOk();

	//Checks for Error
	bool IsErr();

	// checking if the file is bad
	bool Bad();

	//checks is file opened
	bool IsOpened();

	//Close File
	void Close();

	////////////////////////////
	//Write to file
	///////////////////////////

	// Set Where to write
	void SetWritePos(std::streampos Pos);

	//Write text in file
	void WriteTxt(std::string STxt);

	// Get Where we Writing
	long GetWritePos();

	//////////////////////////////////
	//Read from file
	/////////////////////////////

	// Set Where to read
	void SetReadPos(std::streampos Pos = std::ios_base::beg);

	// Read Line of text from file
	void GetLineTxt(char * Text, std::streamsize Size, const char Endl = '\n');

	//How many character to read
	long NrOfChar();

	//Get Where we reading
	long WhereReadPos();

private:

	//file variable
	std::fstream File;
	// when is open
	bool BOpen;
};

#endif