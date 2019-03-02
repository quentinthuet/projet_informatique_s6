#ifndef SIGNAL_DISCRET_HPP
#define SIGNAL_DISCRET_HPP

#include <cmath>
#include <iostream>
#include "complexe.hpp"
using namespace std;

class signal_discret{
  complexe * M_values;
  int M_size;
public:
  //constructeurs
  signal_discret() : M_size(0), M_values(NULL) {
    cout << "SD/constructeur défaut\n"; // debug
  }
  signal_discret(int size) : M_size(size) {
    M_values = new complexe[size];
    complexe c_init(0,0);
    for (int i = 0; i < size; i++){
      M_values[i] = c_init;
    }
    //    cout << "SD/constructeur\n"; // debug
  }
  signal_discret(const signal_discret & sd) : M_size(sd.M_size){
    M_values = new complexe[M_size];
    for (int i = 0; i < M_size; i++){
      M_values[i] = sd.M_values[i];
    }
    //    cout << "SD/constructeur copie\n"; // debug
  }
  //destructeur
  ~signal_discret() {
    delete [] M_values;
    //    cout << "SD/destructeur\n"; // debug
  }
  //accesseurs
  int get_size();
  complexe get_value(int);
  //mutateur
  void set_value(int,complexe);
  //méthodes
  signal_discret conjugue();
  complexe * tfd();
  double energie();
  signal_discret convolution(const signal_discret &);
  signal_discret & translation(const int);
  signal_discret & modulation(double);
  //opérateurs
  signal_discret & operator=(const signal_discret &);
  signal_discret operator+(const signal_discret &);
  signal_discret operator*(const signal_discret &);
  signal_discret operator-(const signal_discret &);
  complexe operator,(const signal_discret &);
  //testeurs
  int testu_1();
  int testu_2();
  int testu_3();
  void all_testu();
};

//fonctions externes
signal_discret tfd_inverse(complexe *, int);




#endif
