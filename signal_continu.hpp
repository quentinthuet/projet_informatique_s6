#ifndef SIGNAL_CONTINU_HPP
#define SIGNAL_CONTINU_HPP

#include <cmath>
#include <iostream>
#include "complexe.hpp"
#include "signal_discret.hpp"
using namespace std;

class signal_continu {
  double t0, t1, eps, s;
  complexe (*f)(double);
public:
  //Constructeurs//
  signal_continu() {
    t0 = 0.0;
    t1 = 1.0;
    eps = 0.0;
    s = 1.0;
    f = NULL;
    //    cout << "SC/constructeur defaut\n"; // debug
  }
  signal_continu(complexe (*ff)(double)) {
    t0 = 0.0;
    t1 = 1.0;
    eps = 0.0;
    s = 1.0;
    f = ff;
    //    cout << "SC/constructeur pointeur sur fonction\n"; // debug
  }
  signal_continu(const signal_continu & sc) {
    t0 = sc.t0;
    t1 = sc.t1;
    eps = sc.eps;
    s = sc.s;
    if (sc.f != NULL)
      f = sc.f;
    //    cout << "SC/constructeur copie\n"; // debug
  }
  //Destructeur//
  ~signal_continu() {
    //    cout << "SC/destructeur\n"; // debug
  }
  //Accesseurs//
  double get_t0();
  double get_t1();
  double get_eps();
  double get_s();
  //Mutateurs//
  void set_temps(double,double);
  void set_eps(double);
  void set_s(double);
  void set_f(complexe (*)(double));
  //M�thode �l�mentaire//
  complexe eval_f(double);
  //M�thode avanc�e//
  signal_discret echantillonnage(int,bool);
  //Testeurs//
  int testu_1(complexe (*)(double));
  void testu_2(complexe (*)(double));
  void all_testu(complexe (*)(double));
};


#endif
