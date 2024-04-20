#include "../headers/commadline.h"


namespace cmd{
  arguments getCommandLineArguments(const int *argc, char **argv){
    arguments args;
    for(int i = 0; i < *argc; ++i){
      std::string arg = argv[i];
      if(arg == "-o" && i+1 < *argc && argv[i+1][0] != '-'){
        args.outputDir = argv[i+1];
        ++i;
      }else if (arg == "-i" && i+1 < *argc && argv[i+1][0] != '-'){
        args.inputDir = argv[i+1];
        ++i;
      }
    }
    return args;
  }
}

