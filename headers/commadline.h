#pragma once

#include <string>

namespace cmd{

  struct arguments{
    std::string outputDir;
    std::string inputDir;
  };

  arguments getCommandLineArguments(const int *argc, char **argv);
}