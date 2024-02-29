#include "BinaryFileWork.h"

bool Binary::OpenFile(char*& f, size_t& fsize, std::string filename)
{
	HANDLE hFile = CreateFile(
		filename.c_str(),		// file to open
		GENERIC_READ,			// open for reading
		FILE_SHARE_READ,		// share for reading
		NULL,					// default security
		OPEN_EXISTING,			// existing file only
		FILE_ATTRIBUTE_NORMAL,	// normal file
		NULL					// no attr. template
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to Open File\n";
		return false;
	}

	fsize = GetFileSize(hFile, NULL);
	if (fsize == 0)
	{
		std::cout << "Failed to read file. File is Empty?\n";
		return false;
	}

	f = new char[fsize];
	unsigned long dwBytesRead = 0;
	if (ReadFile(hFile, f, fsize, &dwBytesRead, NULL) == FALSE || dwBytesRead != fsize)
	{
		std::cout << "Failed to copy file into memory\n";

		fsize = 0;
		delete[] f;
		f = NULL;

		CloseHandle(hFile);
		return false;
	}

	CloseHandle(hFile);
	return true;
}

std::string Binary::WriteLong(int num)
{
	std::string Hex = "";
	std::stringstream s;
	s << std::hex << num;

	int zeroes = 8 - size(s.str());
	for (int i = 0; i < zeroes; i++)
		Hex += "0";
	Hex += s.str();

	int arr[] = { 0, 0, 0, 0 };
	int c = 3;
	for (int i = 0; i < Hex.length() - 1; i += 2)
	{
		std::stringstream h;
		h << Hex[i] << Hex[i + 1];
		h >> std::hex >> arr[c];
		c--;
	}

	Hex = "";
	for (int i = 0; i < 4; i++)
		Hex += char(uint8_t(arr[i]));

	return Hex;
}

std::string Binary::WriteFloat(float num)
{
	std::string strHEX = "";
	unsigned long a = 0;
	unsigned long a24 = 0;
	float n = num;

	memcpy(&a, &n, 4);
	strHEX += char(uint8_t(a));
	strHEX += char((uint16_t(a) - uint8_t(a)) / 0x00000100);

	memcpy(&a24, &n, 3);
	strHEX += char((a24 - int(uint16_t(a))) / 0x00010000);
	strHEX += char((a - a24) / 0x01000000);

	return strHEX;
}

std::string Binary::WriteShort(int num)
{
	int arr[] = { 0, 0 };
	while (num >= 256)
	{
		arr[1] += 1;
		num -= 256;
	}
	arr[0] = num;

	std::string hex;
	for (int i = 0; i < 2; i++)
		hex += char(arr[i]);

	return hex;
}

std::string Binary::WriteString(int size, std::string str)
{
	size -= str.length();

	std::string endLine = "";
	endLine += str;

	for (int i = 0; i < size; i++)
		endLine += char(uint8_t(0));

	return endLine;
}

std::string Binary::ReadString(char*& f, size_t& pos, int size)
{
	std::string result = "";

	for (int i = 0; i < size; i++)
	{
		result += f[pos];
		pos += 1;
	}

	return result;
}

std::string Binary::ReadStringWithout(char*& f, size_t& pos, int size)
{
	std::string result = "";
	bool isWriting = true;

	for (int i = 0; i < size; i++)
	{
		if (f[pos] != 0 && isWriting)
			result += f[pos];
		else
			isWriting = false;
		pos += 1;
	}

	return result;
}

float Binary::ReadFloat(char*& f, size_t& pos)
{
	float result = 0.0;
	unsigned long b = ReadLong(f, pos);
	memcpy(&result, &b, 4);

	return result;
}

unsigned long Binary::ReadLong(char*& f, size_t& pos)
{
	unsigned long result = {
		(unsigned int)((uint8_t)f[pos] * 0x00000001) + \
		(unsigned int)((uint8_t)f[pos + 1] * 0x00000100) + \
		(unsigned int)((uint8_t)f[pos + 2] * 0x00010000) + \
		(unsigned int)((uint8_t)f[pos + 3] * 0x01000000)
	};

	pos += 4;
	return result;
}

unsigned short Binary::ReadShort(char*& f, size_t& pos)
{
	unsigned short result = {
		(unsigned int)((uint8_t)f[pos] * 0x00000001) + \
		(unsigned int)((uint8_t)f[pos + 1] * 0x00000100)
	};

	pos += 2;
	return result;
}

std::string Binary::GetFilenameFile(const std::string str)
{
	size_t found;
	std::string strt;
	found = str.find_last_of("/\\");

	if (found < str.size())
	{
		strt = str.substr(found + 1, -1);
		found = strt.find(".");

		if (found < strt.size())
			strt = strt.substr(0, found);
	}
	else
		strt = str;

	size_t lastdot = strt.find_last_of(".");
	if (lastdot == std::string::npos)
		return strt;

	return strt.substr(0, lastdot);
}

std::string Binary::GetFileNamePath(const std::string str)
{
	size_t found;
	std::string strt;
	found = str.find_last_of("/\\");

	if (found != std::string::npos)
	{
		strt = str.substr(0, found);

		return (strt + "\\");
	}
	else
		return "";
}