#ifndef FILTRE_HPP
#define FILTRE_HPP

#include <cmath>
#include <iostream>
#include "complexe.hpp"
#include "signal_discret.hpp"

using namespace std;

class filtre {
protected:
  signal_discret signal_apply, signal_filtre;
  double duree, freq_coupe;
public:
  filtre() {
    duree = 1.0;
    freq_coupe = 0.0;
    cout << "F/constructeur defaut\n"; // debug
  }
  filtre(signal_discret nsignal_apply,double nfreq_coupe, double nduree) {
    duree = nduree;
    freq_coupe = nfreq_coupe;
    signal_apply = nsignal_apply;
    cout << "F/constructeur par signal_apply, frequence de coupure et duree\n"; // debug
  }
  filtre(const filtre & f) {
    signal_apply = f.signal_apply;
    signal_filtre = f.signal_filtre;
    duree = f.duree;
    freq_coupe = f.freq_coupe;
    cout << "F/constructeur copie\n"; // debug
  }
  ~filtre() {
    cout << "F/destructeur\n"; // debug
  }
  void set_duree(double);
  void set_signal_apply(signal_discret);
  void set_signal_filtre(signal_discret);
  void set_freq_coupe(double);
  double get_duree();
  signal_discret get_signal_apply();
  signal_discret get_signal_filtre();
  double get_freq_coupe();
  void apply();
  virtual void construct() = 0;
};

class passe_bas_ideal : public filtre {
public:
  passe_bas_ideal() {
    cout << "F/PBI/constructeur defaut\n"; // debug
  }
  passe_bas_ideal(signal_discret nsignal_apply,double freq_coupe, double duree) : filtre(nsignal_apply, freq_coupe, duree) {
    cout << "F/PBI/constructeur par signal_apply, frequence de coupure et duree\n"; // debug
  }
  passe_bas_ideal(const passe_bas_ideal & pbi) : filtre(pbi) {
    cout << "F/PBI/constructeur par copie\n"; // debug
  }
  void construct();
  int testu_1(complexe (*)(double));
  void all_testu(complexe (*)(double));
};

class passe_haut_ideal : public filtre {
  public:
  passe_haut_ideal() {
    cout << "F/PHI/constructeur defaut\n"; // debug
  }
  passe_haut_ideal(signal_discret nsignal_apply,double freq_coupe, double duree) : filtre(nsignal_apply, freq_coupe, duree) {
    cout << "F/PHI/constructeur par signal_apply, frequence de coupure et duree\n"; // debug
  }
  passe_haut_ideal(const passe_haut_ideal & phi) : filtre(phi) {
    cout << "F/PHI/constructeur par copie\n"; // debug
  }
  void construct();
  int testu_1(complexe (*)(double));
  void all_testu(complexe (*)(double));
};

class passe_bas_ordre_1 : public filtre {
public:
  passe_bas_ordre_1() {
    cout << "F/PBO1/constructeur defaut\n"; // debug
  }
  passe_bas_ordre_1(signal_discret nsignal_apply,double freq_coupe, double duree) : filtre(nsignal_apply, freq_coupe, duree) {
    cout << "F/PBO1/constructeur par signal_apply, frequence de coupure et duree\n"; // debug
  }
  passe_bas_ordre_1(const passe_bas_ordre_1 & pbo1) : filtre(pbo1) {
    cout << "F/PBO1/constructeur par copie\n"; // debug
  }
  void construct();
  int testu_1(complexe (*)(double));
  void all_testu(complexe (*)(double));
};

class passe_haut_ordre_1 : public filtre {
public:
  passe_haut_ordre_1() {
    cout << "F/PHO1/constructeur defaut\n"; // debug
  }
  passe_haut_ordre_1(signal_discret nsignal_apply,double freq_coupe, double duree) : filtre(nsignal_apply, freq_coupe, duree) {
    cout << "F/PHO1/constructeur par signal_apply, frequence de coupure et duree\n"; // debug
  }
  passe_haut_ordre_1(const passe_haut_ordre_1 & pho1) : filtre(pho1) {
    cout << "F/PHO1/constructeur par copie\n"; // debug
  }
  void construct();
  int testu_1(complexe (*)(double));
  void all_testu(complexe (*)(double));
};

#endif
