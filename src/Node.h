//
// Created by Mike Yang on 11/4/2022.
//

#ifndef RESEARCH_NODE_H
#define RESEARCH_NODE_H


#include <string>
#include <set>
#include <utility>
#include <memory>
#include <iostream>
#include <unordered_set>


namespace NetworkResilience {

/**
 * Node types.
 * */
  typedef uint32_t G_size;
  typedef G_size NODE_ID;
  typedef std::unordered_set<NODE_ID> NODE_LINKS;

  class Node {
  public:
    NODE_ID id;
    NODE_LINKS links = NODE_LINKS ();
    G_size link_count =0;

    G_size link_size(){
      return links.size();
    }

    /**
    * Initializes a node in a Network.
    * @param nodeID; required to input a node ID.
    * */
    explicit Node (const NODE_ID& a){
      id = a;
    }
    /**
    * Initializes a node in a Network, and suggest a capacity
    * with a expected size of links
    * @param nodeID; required to input a node ID.
    * */
    explicit Node (const NODE_ID& a, const size_t& exp_size){
      id = a;
      links.reserve(exp_size*3);
    }
    /**
     * Links this node with another node.
     * This is a directed operation(only adds to this node).
     * @param incomingNode; the node tobe linked with.
     * */
    void link (const Node& incomingNode) {link_count++;links.insert(incomingNode.id);}
    /**
     * Links this node with another node.
     * This is a directed operation(only adds to this node).
     * @param incomingNodeid; the node id tobe linked with.
     * */
    void link (const NODE_ID& incomingNodeid) {link_count++;links.insert(incomingNodeid);}

    /**
     * Removes a node.
     * @param incomingNodeId ; incoming node id.
     * @return 1 if removal successful, else 0.
     * */
    size_t unlink(const NODE_ID& incomingNodeId){
      link_count--;
      return links.erase(incomingNodeId);
    }

    /**
     * Return all links of this node.
     * @return list of nodes connected.
     * */
//    NODE_ID[] getLinks(){
//      return links.toArray(new String[0]);
//    }
    /**
     * Return all links of this node.
     *
     * @return set of nodes connected.
     */
    const NODE_LINKS& getLinksSet() const{
      return links;
    }
    /**
     * Checks if this is linked with the node in question.
     * @param incomingNode; input node to be checked.
     * */
    int isLinkedWith(const Node& incomingNode) const {
      return links.count(incomingNode.id);
    }
    /**
     * Checks if this is linked with the node in question.
     * @param incomingNodeId; input node id.
     * */
    int isLinkedWith(const NODE_ID& incomingNodeId) const{
      return links.count(incomingNodeId);
    }

    /**
     * Get the csv representation of this node's links.
     * @return a shared pointer of string representation of the node's links
     * */
    std::string getCSVString() const {
       std::string out;
      for (const auto& s : links) {
        out.append(std::to_string(id));
        out.append(",");
        out.append(std::to_string(s));
        out.append("\n");
      }
      return out;
    }

    /**
     * Return the degree of the node.
     * */
    size_t getDegree() const{
      return links.size();
    }
  };

} // NetworkResilience

#endif //RESEARCH_NODE_H
