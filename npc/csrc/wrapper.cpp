// #include "verilated_fst_c.h"
#include "Vlight.h"
#include "verilated.h"
#include <nvboard.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX_TIME 100

TOP_NAME *top;
void nvboard_bind_all_pins(TOP_NAME *top);

void single_cycle()
{
  top->clk = 0;
  top->eval();
  nvboard_update();
  top->clk = 1;
  top->eval();
  nvboard_update();
}

// Reset the design for n cycles
void reset(int n)
{
  top->rst = 1;
  while (n-- > 0)
    single_cycle();
  top->rst = 0;
}

// ... reset(10); // reset for 10 cycles
// while(???)
// {
//   ... single_cycle();
//   ...
// }

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
  reset(10); // reset for 10 cycles
  while (!contextp->gotFinish())
  {
    single_cycle();
  }
  // tfp->close();
  // delete tfp;
  nvboard_quit();
  delete top;
  delete contextp;
  return 0;
}
