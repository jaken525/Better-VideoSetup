#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <windows.h>
#include <shlwapi.h>

struct Binary
{
public:
	static unsigned short ReadShort(char*& f, size_t& pos);
	static unsigned long ReadLong(char*& f, size_t& pos);
	static float ReadFloat(char*& f, size_t& pos);
	static std::string ReadStringWithout(char*& f, size_t& pos, int size);
	static std::string ReadString(char*& f, size_t& pos, int size);

	static std::string WriteString(int size, std::string str);
	static std::string WriteShort(int num);
	static std::string WriteFloat(float num);
	static std::string WriteLong(int num);

	static bool OpenFile(char*& f, size_t& fsize, std::string filename);
	static std::string GetFileNamePath(const std::string str);
	static std::string GetFilenameFile(const std::string str);
};