#include <cmath>
#include <iostream>
#include <random>
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

signal_discret signal_continu::echantillonnage(int n, bool fenetrage) {
  double r = 1000.0; //1 //
  signal_discret res(n); //2
  double tcourant = t0, valcourant, gcourant; //
  default_random_engine generator; //3 //
  for (int i = 0; i < n; i++) {
    tcourant = (double) i / (double) n * (t1 - t0) + t0; //4 //
    normal_distribution<double> distribution(f(tcourant).module(),eps); //5 //
    valcourant = distribution(generator); //6 //
    if (fenetrage) { //7
      gcourant = (1.0/2.0*tanh(-r*(tcourant-s*(t1-t0)))+1.0/2.0)*(1.0/2.0*tanh(r*(tcourant+s*(t1-t0)))+1.0/2.0); 
      valcourant = valcourant * gcourant; //
    }
    complexe cvalcourant(valcourant,0.0); //8
    res.set_value(i,cvalcourant); //
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

void signal_continu::testu_2(complexe(*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 300;
  signal_discret sd1, sd2(n);
  complexe * tfd;
  double T = 1.0/150.0;
  sc1.set_temps(0.0,3*T); sc1.set_eps(0.0000000000001); sc1.set_s(0.1); sc1.set_f(f_test);
  sd1 = sc1.echantillonnage(n, false);
  sd1.sortie_fichier_time(1,0.0,3*T*(1.0-1.0/n));
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(1,0.0,3*T,true);
  delete [] tfd;
  sc1.set_eps(0.1);
  sd1 = sc1.echantillonnage(n,false);
  sd1.sortie_fichier_time(11,0.0,3*T*(1.0-1.0/n));
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(11,0.0,3*T,true);
  delete [] tfd;
  cout << "SC/ signal_time_1 et son spectre signal_freq_1 est l'echantillonnage de la fonction x |-> 5+0.5cos(300PIx)+0.5cos(600PIx+PI/2)+0.5cos(900PIx+PI/4)+0.05cos(6000PIx) en 300 points sur une durée de trois fois sa période, soit 0.020\n";
}

void signal_continu::all_testu(complexe (*f_test)(double)) {
  signal_continu sc;
  int nb_tests = 1;
  int nb_reussis = 0;
  nb_reussis += sc.testu_1(f_test);
  cout << "SC/ " << nb_reussis << " test sur " << nb_tests << " reussi\n";
  sc.testu_2(f_test);
}

