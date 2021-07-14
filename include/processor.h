#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  Processor() : PreTotal_(0), PreIdle_(0), Total_(0), Idle_(0){};
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  long PreTotal_;
  long PreIdle_;
  long Total_;
  long Idle_;
};

#endif