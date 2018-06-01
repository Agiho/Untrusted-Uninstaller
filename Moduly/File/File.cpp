#include "File.h"

CFile::CFile()
{}
//Close file
CFile::~CFile()
{
	File.close();
}

void CFile::Init(const char *FileName, std::ios_base::openmode Mode)
{

	BOpen = false;	
	// Open the file
	File.open (FileName, Mode);
 
	//Check is it open
  if (File.is_open())
  {
	File.seekg(std::ios_base::beg);
	BOpen = true;
  }
}
void CFile::ReOpen(const char *FileName, std::ios_base::openmode Mode)
{
	File.open (FileName, Mode);
}
bool CFile::AllOk()
{
	bool BOk  = File.good();
	return BOk;
}

bool CFile::IsErr()
{
	bool BOk = File.fail();
	return BOk;
}

bool CFile::Bad()
{
	bool BOk = File.bad();
	return BOk;
}

bool CFile::EoF()
{
	//Check is it end of file
	bool BOk = File.eof();
	return BOk;
}

bool CFile::IsOpened()
{
	return BOpen;
}

void CFile::Close()
{
	File.close();
}

//////////////////////////////////////////////////////////////////////////
//Write
//////////////////////////////////////////////////////////////////////////

void CFile::SetWritePos(std::streampos Pos)
{
	File.seekp (Pos);
}

void CFile::WriteTxt(std::string STxt)
{
 	//streams text to file end send end of line
	File << STxt.c_str()<< "\n";

}

long CFile::GetWritePos()
{
	long i = File.tellp();
	return i;
}

//////////////////////////////////////////////////////////////////////////
//Read
//////////////////////////////////////////////////////////////////////////


void CFile::SetReadPos(std::streampos Pos)
{
	File.seekg(Pos);
}

void CFile::GetLineTxt(char * Text, std::streamsize Size, const char Endl)
{

	//gets line of text
	File.getline(Text, Size, Endl);

}

long CFile::NrOfChar()
{
	//how many characters is in file
	long i = File.gcount();
	return i;
}

long CFile::WhereReadPos()
{
	//where is read cursor is
	long i = File.tellg ();
	return i;
}