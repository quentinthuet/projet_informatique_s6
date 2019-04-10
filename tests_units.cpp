#include <cmath>
#include <iostream>
#include "complexe.hpp"
#include "signal_discret.hpp"
#include "signal_continu.hpp"
using namespace std;

complexe f_test1(complexe x) {
  complexe c1(1.0,0.0);
  return x * x - 2.0 * x + c1;
}


int main(){
  signal_discret sd;
  sd.all_testu();
  signal_continu sc;
  sc.all_testu(f_test1);
  return 0;
}
