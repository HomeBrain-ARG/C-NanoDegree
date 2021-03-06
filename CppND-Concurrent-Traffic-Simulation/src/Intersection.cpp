// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>


#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <random>
#include <vector>

#include "../include/Street.h"
#include "../include/Intersection.h"
#include "../include/Vehicle.h"

/* Implementation of class "WaitingVehicles" */

// ________________________________________________________________________________________________
int WaitingVehicles::getSize() {
  std::lock_guard<std::mutex> lock(_mutex);
  return _vehicles.size();
}

// ________________________________________________________________________________________________
void WaitingVehicles::pushBack(std::shared_ptr<Vehicle> vehicle, std::promise<void> &&promise) {
  std::lock_guard<std::mutex> lock(_mutex);
  _vehicles.push_back(vehicle);
  _promises.push_back(std::move(promise));
}

// ________________________________________________________________________________________________
void WaitingVehicles::permitEntryToFirstInQueue() {
  std::lock_guard<std::mutex> lock(_mutex);
  // get entries from the front of both queues
  auto firstPromise = _promises.begin();
  auto firstVehicle = _vehicles.begin();

  // fulfill promise and send signal back that permission to enter has been granted
  firstPromise->set_value();

  // remove front elements from both queues
  _vehicles.erase(firstVehicle);
  _promises.erase(firstPromise);
}

/* Implementation of class "Intersection" */

// ________________________________________________________________________________________________
Intersection::Intersection() {
  _type = ObjectType::objectIntersection;
  _isBlocked = false;
}

// ________________________________________________________________________________________________
void Intersection::addStreet(std::shared_ptr<Street> street) {
  _streets.push_back(street);
}

// ________________________________________________________________________________________________
std::vector<std::shared_ptr<Street>> Intersection::queryStreets(std::shared_ptr<Street> incoming) {
  // store all outgoing streets in a vector ...
  std::vector<std::shared_ptr<Street>> outgoings;
  for (auto it : _streets) {
    // ... except the street making the inquiry
    if (incoming->getID() != it->getID()) {
      outgoings.push_back(it);
    }
  }
  return outgoings;
}

// adds a new vehicle to the queue and returns once the vehicle is allowed to enter
// ________________________________________________________________________________________________
void Intersection::addVehicleToQueue(std::shared_ptr<Vehicle> vehicle) {
  std::unique_lock<std::mutex> lck(_mtx);
  std::cout << "Intersection #" << _id << "::addVehicleToQueue: thread id = " << std::this_thread::get_id() << std::endl;
  lck.unlock();

  // add new vehicle to the end of the waiting line
  std::promise<void> prmsVehicleAllowedToEnter;
  std::future<void> ftrVehicleAllowedToEnter = prmsVehicleAllowedToEnter.get_future();
  _waitingVehicles.pushBack(vehicle, std::move(prmsVehicleAllowedToEnter));
  // wait until the vehicle is allowed to enter
  ftrVehicleAllowedToEnter.wait();
  lck.lock();
  std::cout << "Intersection #" << _id << ": Vehicle #" << vehicle->getID() << " is granted entry." << std::endl;
  std::cout << "current phase " << _trafficLight.getCurrentPhase() << std::endl;
  // FP.6b : use the methods TrafficLight::getCurrentPhase and TrafficLight::waitForGreen to block the execution until the traffic light turns green.
  std::cout << "wait " << _id << std::endl;
  if (!trafficLightIsGreen()) {
    _trafficLight.waitForGreen();
  }
  std::cout << "go " << _id << std::endl;
  lck.unlock();
}

// ________________________________________________________________________________________________
void Intersection::vehicleHasLeft(std::shared_ptr<Vehicle> vehicle) {
  // std::cout << "Intersection #" << _id << ": Vehicle #" << vehicle->getID() << " has left." << std::endl;
  // unblock queue processing
  this->setIsBlocked(false);
}

// ________________________________________________________________________________________________
void Intersection::setIsBlocked(bool isBlocked) {
    _isBlocked = isBlocked;
    // std::cout << "Intersection #" << _id << " isBlocked=" << isBlocked << std::endl;
}

// ________________________________________________________________________________________________
// virtual function which is executed in a thread
void Intersection::simulate()  {
  // using threads + promises/futures + exceptions
  // FP.6a : In Intersection.h, add a private member _trafficLight of type TrafficLight. At this position, start the simulation of _trafficLight.
  // launch vehicle queue processing in a thread
  _trafficLight.simulate();
  threads.emplace_back(std::thread(&Intersection::processVehicleQueue, this));
}

// ________________________________________________________________________________________________
void Intersection::processVehicleQueue() {
  // print id of the current thread
  // std::cout << "Intersection #" << _id << "::processVehicleQueue: thread id = " << std::this_thread::get_id() << std::endl;

  // continuously process the vehicle queue
  while (true) {
    // sleep at every iteration to reduce CPU usage
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // only proceed when at least one vehicle is waiting in the queue
    if (_waitingVehicles.getSize() > 0 && !_isBlocked) {
      // set intersection to "blocked" to prevent other vehicles from entering
      this->setIsBlocked(true);
      // permit entry to first vehicle in the queue (FIFO)
      _waitingVehicles.permitEntryToFirstInQueue();
    }
  }
}

// ________________________________________________________________________________________________
bool Intersection::trafficLightIsGreen() {
  // please include this part once you have solved the final project tasks
  if (_trafficLight.getCurrentPhase() == TrafficLightPhase::green) {
    return true;
  }
  return false;
}
