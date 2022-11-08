#include <iostream>
#include "src/RandomGraph.h"

using net = NetworkResilience::RandomGraph ;

void first_test(){
  std::string filename = "t/first_test.csv";
  int k =10;
  net g = *(std::make_shared<net>(500, 0.1));
  net::printStats(g.getDD());
}

int main() {
  first_test();
  return 0;
}
