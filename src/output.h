//
// Created by 18604 on 12/1/2022.
//

#ifndef RESEARCH_OUTPUT_H
#define RESEARCH_OUTPUT_H

#include <string>
#include <iostream>
#include <fstream>

namespace NetworkResilience {
  class output {
  public:
     static int write_to( std::ofstream & file, const std::string& input){
      if(file.is_open()) {
        file << input;
      } else {std::cout<<"Cannot open file"<<std::endl;return 0;}
      return 1;
    }
  };
}

#endif //RESEARCH_OUTPUT_H
