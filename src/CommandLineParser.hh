// $Id$

#ifndef __COMMANDLINEPARSER_HH__
#define __COMMANDLINEPARSER_HH__

#include <string>
#include <map>
#include "openmsx.hh"
#include "config.h"
#include "MSXConfig.hh"

class CommandLineParser
{
  public:
    static CommandLineParser* instance();
    int checkFileType(char* parameter,int &i, char **argv);
    int checkFileExt(char* filename);
    void parse(MSXConfig::Backend* Backconfig,int argc, char **argv);

    void showHelp(const char* progname);

    void configureDisk(char* filename);
    void configureTape(char* filename);
    void configureCartridge(char* filename);
    void configureMusMod(std::string mode);
    void configureFmPac(std::string mode);


    enum CLIoption {
      HELP,MSX1,MSX2,MSX2PLUS,TURBOR,
      FMPAC,MUSMOD,MBSTEREO,JOY
    };

    void addOption(CLIoption id,std::string cliOption,bool usesParameter, std::string help);
    bool isUsed(CLIoption id);
    char* getParameter(CLIoption id);

  protected:
      CommandLineParser();

  private:
    // some parameters for internal use.
    MSXConfig::Backend* config;
    int nrXMLfiles;
    char driveLetter;
    byte cartridgeNr;
    class CommandLineOption
    {
      public:
	std::string option;
	bool hasParameter;
	std::string helpLine;
	bool used;
	char* parameter;

	CommandLineOption(std::string cliOption,bool usesParameter, std::string help);
    };

    std::map<CLIoption,CommandLineParser::CommandLineOption*> optionList;

    static CommandLineParser* oneInstance;
};

#endif
