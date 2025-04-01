// #include "verilated_fst_c.h"
#include "Vtop.h"
#include "verilated.h"
#include <nvboard.h>
#define MAX_TIME 100

void nvboard_bind_all_pins(TOP_NAME *top);

int main(int argc, char **argv)
{
  VerilatedContext *contextp = new VerilatedContext;
  // Verilated::traceEverOn(true);
  // VerilatedFstC *tfp = new VerilatedFstC;
  contextp->commandArgs(argc, argv);
  TOP_NAME *top = new TOP_NAME{contextp};
  // top->trace(tfp, 99);
  // tfp->open("waveform.fst");
  // int sim_time = 0;
  nvboard_bind_all_pins(top);
  nvboard_init();
  while (!contextp->gotFinish())
  {
    top->a = 0;
    top->b = 0;
    top->eval();
    // tfp->dump(sim_time);
    nvboard_update();
    // sim_time++;
    top->a = 0;
    top->b = 0;
    top->eval();
    // tfp->dump(sim_time);
    nvboard_update();
    // sim_time++;
    top->a = 0;
    top->b = 1;
    top->eval();
    // tfp->dump(sim_time);
    nvboard_update();
    // sim_time++;
    top->a = 0;
    top->b = 1;
    top->eval();
    nvboard_update();
    // tfp->dump(sim_time);
    // sim_time++;
  }
  // tfp->close();
  // delete tfp;
  delete top;
  delete contextp;
  return 0;
}
