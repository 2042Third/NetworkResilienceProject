#include <iostream>
#include "src/RandomGraph.h"

using net = NetworkResilience::RandomGraph ;

void first_test(){
  std::string filename = "t/first_test.csv";
  int k =10;
  net g = *(std::make_shared<net>(500, 0.1));
  g.run();
  net::printStats(g.getDD());
}
void first_test_n(){
  std::string filename = "t/first_test.csv";
  int k =10;
  net g = *(std::make_shared<net>(5000, 0.1));
  g.run();
  net::printStats(g.getDD());
}

int main() {
  first_test();
  first_test_n();
  return 0;
}
