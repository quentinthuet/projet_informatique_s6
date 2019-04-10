#include <cmath>
#include <iostream>
#include "complexe.hpp"
#include "signal_discret.hpp"
#include "signal_continu.hpp"
using namespace std;

/////////ACCESSEURS//////////

double signal_continu::get_t0() {
  return t0;
}

double signal_continu::get_t1() {
  return t1;
}

double signal_continu::get_eps() {
  return eps;
}

double signal_continu::get_s() {
  return s;
}

/////////MUTATEURS//////////

void signal_continu::set_temps(double nt0,double nt1) {
  t0 = nt0;
  t1 = nt1;
}

void signal_continu::set_eps(double neps) {
  eps = neps;
}

void signal_continu::set_s(double ns) {
  s = ns;
}

void signal_continu::set_f(complexe (*nf)(complexe)) {
  f = nf;
}

/////////METHODE ELEMENTAIRE//////////

complexe signal_continu::eval_f(complexe x) {
  return f(x);
}

/////////TESTEURS//////////

int signal_continu::testu_1(complexe (*f_test)(complexe)) {
  complexe c1(-4.0,1.3), c2(2.5,4.3);
  signal_continu sc1;
  signal_continu sc2(sc1);
  signal_continu sc3(f_test);
  sc1.set_temps(-3.0,4.12); sc1.set_eps(0.001); sc1.set_s(0.1); sc1.set_f(f_test);
  bool test1 = (abs(sc1.get_t0() + 3.0) < 1e-8 && abs(sc1.get_t1() - 4.12) < 1e-8 && abs(sc1.get_eps() - 0.001) < 1e-8 && sc1.eval_f(c1) == f_test(c1) && sc1.eval_f(c2) == f_test(c2));
  if (test1)
    return 1;
  else
    return 0;
}

int signal_continu::testu_2() {

  if (0)
    return 1;
  else
    return 0;
}

int signal_continu::testu_3() {
  
  if (0)
    return 1;
  else
    return 0;
}

void signal_continu::all_testu(complexe (*f_test)(complexe)) {
  signal_continu sc;
  int nb_tests = 1;
  int nb_reussis = 0;
  nb_reussis += sc.testu_1(f_test);
  nb_reussis += sc.testu_2();
  nb_reussis += sc.testu_3();
  cout << "SC/ " << nb_reussis << " tests sur " << nb_tests << " reussis\n";
}

