#include <iostream>
#include "src/Algorithms.h"
#include "src/output.h"

using net = NetworkResilience::Algorithms ;
using out = NetworkResilience::output;

void main_loop(net* g, const std::string& of){
  std::string input;
  static unsigned int action = 0;
  do {
    std::cout<< "Next action "<<action<<" [(w)rite, (c)ontinue, (q)uit]: ";
    std::cin>>input;
    if(input == "w"){
      std::cout<< "Write to file."<<std::endl;
      g->write_output( of,g->get_connected_component_csv());
    }
    else if (input == "c"){
      std::cout<< "Continue."<<std::endl;
      g->random_rm();
      g->rerun();
      uint32_t cc = g->connected_components_count();
      std::cout<<"Connected Components: "<<cc<<std::endl;
    }
    else if (input == "q") {
      std::cout<< "Quiting."<<std::endl;
    }
    else {
      input = "c";
      continue;
    }
    std::cout<<std::endl;
    action++;
  }while(input!="q" || input.empty());
}

void first_test(){
  std::string filename = "t/first_test.csv";
  net *g = new net(5000, 0.00071);
  g->add_second_layer();
  g->run();
  g->run_second_layer();
  uint32_t cc = g->connected_components_count();
  std::cout<<"Connected Components: "<<cc<<std::endl;
  delete g;
}
void first_test_n(){

  uint32_t N = 128000;
  double p = 0.0000625;
  net *g = new net(128000, 0.0000625); // p = 0.0000625, avg degree = 4
  std::string of = "./dataOut/out_"+ to_string(N)+"_"+ to_string(p)+".csv";
  g->add_second_layer();
  g->run();
  g->run_second_layer();
  uint32_t cc = g->connected_components_count();
  std::cout<<"Connected Components: "<<cc<<std::endl;
//  g->printStats(*(g->getDD()));
  g->write_output( of,g->get_connected_component_csv());
  main_loop(g,of);

  delete g;
}
void test_large(){
  std::string filename = "t/first_test.csv";
  net *g = new net(1000000, 0.0000142);
  g->run();
  uint32_t cc = g->connected_components_count();
  std::cout<<"Connected Components: "<<cc<<std::endl;
  g->printStats(*(g->getDD()));
  delete g;
}

int main() {
  first_test_n();
//  test_large();
//  first_test();
  return 0;
}
