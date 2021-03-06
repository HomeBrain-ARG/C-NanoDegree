// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>


#ifndef INCLUDE_ROUTE_MODEL_H_
#define INCLUDE_ROUTE_MODEL_H_

#include <limits>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include "model.h"

class RouteModel : public Model {
 public:
  class Node : public Model::Node {
   public:
    Node * parent = nullptr;
    float h_value = std::numeric_limits<float>::max();
    float g_value = 0.0;
    float f_value = this->g_value + this->h_value;
    bool visited = false;
    std::vector<Node *> neighbors;

    void FindNeighbors();
    float distance(Node other) const {
      return std::sqrt(std::pow((x - other.x), 2) + std::pow((y - other.y), 2));
    }
    Node() {}
    Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}

   private:
    int index;
    Node * FindNeighbor(std::vector<int> node_indices);
    RouteModel * parent_model = nullptr;
  };
  explicit RouteModel(const std::vector<std::byte> &xml);
  Node &FindClosestNode(float x, float y);
  auto &SNodes() {return m_Nodes;}
  std::vector<Node> path;

 private:
  void CreateNodeToRoadHashmap();
  std::unordered_map<int, std::vector<const Model::Road *>> node_to_road;
  std::vector<Node> m_Nodes;
};

#endif  // INCLUDE_ROUTE_MODEL_H_
