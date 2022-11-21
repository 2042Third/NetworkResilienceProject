//
// Created by 18604 on 11/13/2022.
//

#ifndef RESEARCH_LINKREP_H
#define RESEARCH_LINKREP_H

#include <iostream>

namespace NetworkResilience {

  typedef std::string NODE_ID;

  class LinkRep {
  public:
    NODE_ID **allLinks;

    LinkRep();
    ~LinkRep();

  };
}

#endif //RESEARCH_LINKREP_H
