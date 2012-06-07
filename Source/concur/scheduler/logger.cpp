// Contains logging funcitonality

#include <fstream>
#include <string>
#include <sstream>
#include "utilities.h"
#include "logger.h"


// fields
LogMode logMode = OFF;
ofstream outFile;
char* outFilename;

// prototypes
void initializeLogging(char* mode);
void logToFile(const char* text);
void endLogging();
bool isLogging();
string getLogModeString();


/*
* Set up logging.
*/
void initializeLogging(char* level) {
  stringstream ss;
  ss << level;
  string levelStr = ss.str();
  stoupper(levelStr); // convert to all caps
  // set logging mode
  if (strcmp(levelStr.c_str(), "OFF") == 0) {
    logMode = OFF;
  } else if ( strcmp(levelStr.c_str(), "ON") == 0 ) {
    logMode = ON;
  } else { //this should never happen
    printf("Error:  received an invalid log mode choice: %d\n", level);
    exit(EXIT_FAILURE);
  }

  if (logMode == ON) {
    // get current timestamp for filename
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime (buffer,80,"output/output-%Y%m%d_%X.txt",timeinfo);
    puts (buffer);

    outFilename = buffer;
    outFile.open(outFilename);
    logToFile("Program Trail Start:\n\n");
  }
}

void logToFile(const char* text) {
  if (isLogging()) {
      outFile << text << endl;
  }
}

void endLogging() {
  if( outFile.is_open() ) {
    outFile << "\nEnd Program Trail\n";
    outFile.close();
  }
}

bool isLogging() {
  return ((logMode == ON) && (outFile.is_open()));
}

/*
 * Returns the logging mode.
 */
LogMode getLogMode() {
  return logMode;
}


// Log Mode
string getLogModeString() {
  string modeName = "";
  switch(logMode) {
        case ON:
                modeName = "ON";
                break;
        case OFF:
                modeName = "OFF";
                break;
        default:
                modeName = "Error";
        }
  return modeName;
}
