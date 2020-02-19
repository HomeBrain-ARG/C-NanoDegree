#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// ________________________________________________________________________________________________
Process::Process(int pid){
  _pid = pid;
}

// ________________________________________________________________________________________________
// Return this process's ID
int Process::Pid() {   
  return _pid; 
}


// ________________________________________________________________________________________________
void Process::setRam(std::string value) {
  _ram = value;
}

// ________________________________________________________________________________________________
std::string Process::getRam() {
  return _ram;
}

// ________________________________________________________________________________________________
void Process::setCommand(std::string name) {
  _command = name;
}

// ________________________________________________________________________________________________
std::string Process::getCommand() {
  return _command;
}

// ________________________________________________________________________________________________
void Process::setUpTime(long int time) {
  _upTime = time;
}

// ________________________________________________________________________________________________
long int Process::getUpTime() {
  return _upTime;
}

// ________________________________________________________________________________________________
void Process::setUserName(std::string name) {
  _userName = name;
}
// ________________________________________________________________________________________________
// Return this process's CPU utilization
float Process::CpuUtilization() { 
  return _cpu; 
}

// ________________________________________________________________________________________________
// Return the command that generated this process
string Process::Command() { 
  return _command; 
}

// ________________________________________________________________________________________________
// TODO: Return this process's memory utilization
string Process::Ram() { 
  return _ram; 
}
void Process::setCpuUtilization(float cpu) {
  _cpu = cpu;
}
// ________________________________________________________________________________________________
// TODO: Return the user (name) that generated this process
string Process::User() {  
  return _userName; 
}

// ________________________________________________________________________________________________
// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  return _upTime; }

// ________________________________________________________________________________________________
// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  // std::cout << "sort " << std::endl;
  // return _command < a._command;
  // return _ram > a._ram; 
  return _cpu > a._cpu;
}
