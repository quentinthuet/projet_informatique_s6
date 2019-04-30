#include <cmath>
#include <iostream>
#include "complexe.hpp"
#include "signal_discret.hpp"
#include "signal_discret_stl.hpp"
#include "signal_continu.hpp"
#include "filtre.hpp"
using namespace std;

complexe f_test1(double x) {
  complexe c(5.0+0.5*cos(150.0*2*M_PI*x)+0.5*cos(300.0*2*M_PI*x+M_PI/2.0)+0.5*cos(450.0*2*M_PI*x+M_PI/4.0)+0.05*cos(3000.0*2*M_PI*x),0.0);
  return c;
}


int main(){/*
  signal_discret sd;
  sd.all_testu();*/
  signal_discret_stl sds;
  sds.all_testu();/*
  signal_continu sc;
  sc.all_testu(f_test1);
  filtre_all_testu(f_test1);*/
  return 0;
}
