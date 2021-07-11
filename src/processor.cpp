#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    PreIdle_ = Idle_;
    PreTotal_ = Total_;
    Idle_ = LinuxParser::IdleJiffies();
    Total_ = LinuxParser::ActiveJiffies() + Idle_;
    long DIdle = Idle_ - PreIdle_;
    long DTotal = Total_ - PreTotal_;

    return 1.0 - (DIdle + 0.0) / DTotal;
}