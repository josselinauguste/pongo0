#ifndef LOGH
#define LOGH

#include <fstream>
#include <string>

class Log
{
public:
	typedef enum {MSG_UNKNOWN, MSG_INFORMATION, MSG_ERROR, MSG_MAX} MsgType;
	
	static void open(std::string);
	static void print(MsgType, std::string, int, std::string);

private:
	Log();
	~Log();
	
	static bool isOpened;
	static std::string filename;
};

#define LOG_INFO Log::MSG_INFORMATION, __FILE__, __LINE__
#define LOG_ERR Log::MSG_ERROR, __FILE__, __LINE__

#endif
