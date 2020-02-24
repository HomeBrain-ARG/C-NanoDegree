// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>


#ifndef INCLUDE_ROUTE_PLANNER_H_
#define INCLUDE_ROUTE_PLANNER_H_

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
 public:
  RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
  // Add public variables or methods declarations here.
  float GetDistance() const {return distance;}
  void AStarSearch();

  // The following methods have been made public so we can test them individually.
  void AddNeighbors(RouteModel::Node *current_node);
  float CalculateHValue(RouteModel::Node const *node);
  std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *);
  RouteModel::Node *NextNode();

 private:
  // Add private variables or methods declarations here.
  std::vector<RouteModel::Node*> open_list;
  RouteModel::Node *start_node;
  RouteModel::Node *end_node;

  float distance = 0.0f;
  RouteModel &m_Model;
};

#endif  // INCLUDE_ROUTE_PLANNER_H_