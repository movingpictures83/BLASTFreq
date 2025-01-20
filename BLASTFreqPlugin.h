#ifndef BLASTFreqLUGIN_H
#define BLASTFreqPLUGIN_H

#include "Plugin.h"
#include "PluginProxy.h"
#include <string>
#include <vector>

class BLASTFreqPlugin : public Plugin
{
public: 
 std::string toString() {return "BLASTFreq";}
 void input(std::string file);
 void run();
 void output(std::string file);

private: 
 std::string inputfile;
 std::string outputfile;
};

#endif
