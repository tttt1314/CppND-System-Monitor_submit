#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"


#include "format.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
  System system;
  NCursesDisplay::Display(system);
  ////  below are the modified one   ////
  /*
	int n=30;
    std::vector<Process> processes;
  
  while(true){
    std::cout<<"System Metrics"<<std::endl;    
    std::cout<<"CPU utilization "<<system.Cpu().Utilization()* 100<<std::endl;
  	std::cout<<"Memory utilization "<<system.MemoryUtilization()* 100<<std::endl;
    std::cout<<"Total Processes "<<system.TotalProcesses()<<std::endl;
    std::cout<<"Running Processes "<<system.RunningProcesses()<<std::endl;
    std::cout<<"System Uptime "<<Format::ElapsedTime(system.UpTime())<<std::endl;
    std::cout<<" "<<std::endl;
    processes=system.Processes();
    std::cout<<"Processes: "<<std::endl;
    std::cout<<" "<<std::endl;
    for (int i = 0; i < n; ++i) {
      int pid = processes[i].Pid();
      std::cout<<processes[i].Command()<<std::endl;
      std::cout<<"Process ID "<< pid <<std::endl;
      std::cout<<"UID "<<LinuxParser::Uid(pid)<<std::endl;
      std::cout<<"User "<<processes[i].User()<<std::endl;
      std::cout<<"CPU utilization "<<processes[i].CpuUtilization() * 100<<std::endl;
      std::cout<<"Memory utilization "<<processes[i].Ram()<<std::endl;
      std::cout<<"Process Uptime "<<Format::ElapsedTime(processes[i].UpTime())<<std::endl;
      std::cout<<" "<<std::endl;
  }
  std::this_thread::sleep_for(std::chrono::seconds(1)); // wait for one second, as otherwise printouts will be coming in too fast
  }
  */
}