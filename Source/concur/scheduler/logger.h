// Header file for logger.cpp
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
using namespace std;


/*
 * Logger mode.
 */
enum LogMode {
  ON,
  OFF
};





void initializeLogging(char* mode);
void logToFile(const char* text);
void endLogging();
bool isLogging();
LogMode getLogMode();
string getLogModeString();

#endif

