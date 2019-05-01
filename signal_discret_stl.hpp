#ifndef SIGNAL_DISCRET_STL_HPP
#define SIGNAL_DISCRET_STL_HPP

#include <cmath>
#include <iostream>
#include <vector>
#include "complexe.hpp"
#include "signal_discret.hpp"
using namespace std;

class signal_discret_stl{
  vector<complexe> M_values;
public:
  //Constructeurs//
  signal_discret_stl() {
    //    cout << "SDS/constructeur defaut\n"; // debug
  }
  signal_discret_stl(int size) {
    complexe c_init(0,0);
    M_values.assign(size,c_init);
    //    cout << "SDS/constructeur taille\n"; // debug
  }
  signal_discret_stl(const signal_discret_stl & sds){
    M_values = sds.M_values;
    //    cout << "SDS/constructeur copie\n"; // debug
  }
  //Destructeur//
  ~signal_discret_stl() {
    M_values.clear();
    //    cout << "SD/destructeur\n"; // debug
  }
  //Fonctions de sortie de donnees//
  void sortie_fichier_time(int,double,double);
  void sortie_fichier_freq(int,double,double,bool);
  //Accesseurs//
  int get_size();
  complexe get_value(int);
  //Mutateur//
  void set_value(int,complexe);
  //Méthodes élémentaires//
  signal_discret_stl conjugue();
  double energie();
  //Méthodes avancées//
  complexe * tfd();
  signal_discret_stl convolution(signal_discret_stl &);
  signal_discret_stl translation(const int);
  signal_discret_stl modulation(double);
  //Opérateurs//
  signal_discret_stl & operator=(const signal_discret_stl &);
  signal_discret_stl & operator=(const signal_discret &);
  signal_discret_stl operator+(const signal_discret_stl &);
  signal_discret_stl operator*(const signal_discret_stl &);
  signal_discret_stl operator-(const signal_discret_stl &);
  complexe operator,(const signal_discret_stl &);
  //Fonction amie//
  friend signal_discret_stl tfd_inverse_stl(complexe*,int);
  //Testeurs//
  int testu_1();
  int testu_2();
  int testu_3();
  void all_testu();
};

//Fonction externe//
signal_discret_stl tfd_inverse_stl(complexe*,int);




#endif
