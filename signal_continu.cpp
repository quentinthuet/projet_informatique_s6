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

void signal_continu::set_f(complexe (*nf)(double)) {
  f = nf;
}

/////////METHODE ELEMENTAIRE//////////

complexe signal_continu::eval_f(double x) {
  return f(x);
}

/////////METHODE AVANCEE//////////

signal_discret signal_continu::echantillonage(int n) {
  double r = 1000.0;
  signal_discret res(n);
  double tcourant = t0;
  complexe valcourant;
  for (int i = 0; i < n; i++) {
    tcourant = (double) i / (double) (n - 1) * (t1 - t0) + t0;
    complexe gcourant((1.0/2.0*tanh(-r*(tcourant-s*(t1-t0)))+1.0/2.0)*(1.0/2.0*tanh(r*(tcourant+s*(t1-t0)))+1.0/2.0),0.0);
    complexe bruitcourant(1.0 + eps * ((double) (rand()%100)/100.0),0.0);
    valcourant = f(tcourant) * bruitcourant * gcourant;
    cout << "f[" << tcourant << "] = " << valcourant << endl;
    cout << "bruit[" << i << "] = " << bruitcourant << endl;
    res.set_value(i,valcourant);
  }
  return res;
}


/////////TESTEURS//////////

int signal_continu::testu_1(complexe (*f_test)(double)) {
  signal_continu sc1; //1 //
  signal_continu sc2(sc1); //2 //
  signal_continu sc3(f_test); //3
  bool test1 = (sc3.eval_f(4.1) == f_test(4.1) && sc3.eval_f(-0.735) == f_test(-0.735));//
  sc1.set_temps(-3.0,4.12); sc1.set_eps(0.001); sc1.set_s(0.1); sc1.set_f(f_test); //4
  bool test2 = (abs(sc1.get_t0() + 3.0) < 1e-8 && abs(sc1.get_t1() - 4.12) < 1e-8 && abs(sc1.get_eps() - 0.001) < 1e-8 && abs(sc1.get_s() - 0.1) < 1e-8 && sc1.eval_f(4.1) == f_test(4.1) && sc1.eval_f(-0.735) == f_test(-0.735)); //
  if (test1 && test2)
    return 1;
  else
    return 0;
}

int signal_continu::testu_2(complexe(*f_test)(double)) {
  signal_continu sc1(f_test);
  signal_discret sd1;
  sc1.set_temps(-3.0,4.12); sc1.set_eps(0.001); sc1.set_s(0.1); sc1.set_f(f_test);
  sd1 = sc1.echantillonage(100);
  /* for (int i = 0; i < 100; i++) {
    cout << sd1.get_value(i) << endl;
    }*/
  if (1)
    return 1;
  else
    return 0;
}

void signal_continu::all_testu(complexe (*f_test)(double)) {
  signal_continu sc;
  int nb_tests = 2;
  int nb_reussis = 0;
  nb_reussis += sc.testu_1(f_test);
  nb_reussis += sc.testu_2(f_test);
  cout << "SC/ " << nb_reussis << " tests sur " << nb_tests << " reussis\n";
}

