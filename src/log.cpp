#include <ClanLib/core.h>
#include "log.hpp"

bool Log::isOpened = false;
std::string Log::filename = "\0";

void Log::open(std::string _filename)
{
	filename = _filename;

	std::ofstream logfile(Log::filename.c_str());
	if(logfile)
	{
		logfile << "Pongo Execution Log" << std::endl;
		logfile.close();
		
		isOpened = true;
	}
	else
	{
		throw CL_Error("Impossible d'ouvrir le fichier de log '" + filename + "'");
	}
}

void Log::print(MsgType msgType, std::string file, int line, std::string msg)
{
	if(Log::isOpened)
	{
		std::ofstream logfile(Log::filename.c_str(), std::ios_base::app);
		if(logfile)
		{
			std::string buf;

			switch(msgType)
			{
				case Log::MSG_INFORMATION:
					buf = "|ii|\t";
					break;
				case Log::MSG_ERROR:
					buf = "|EE|\t";
					break;
				default:
					buf = "|??|\t";;
					break;
			}
			
			buf += file + "\t";
			buf += CL_String::from_int(line) + "\t";
			buf += msg + "\n";
		
			logfile << buf;
			logfile.close();
		}
	}
}
