#ifndef FILTRE_HPP
#define FILTRE_HPP

#include <cmath>
#include <iostream>
#include "complexe.hpp"
#include "signal_discret.hpp"
#include "signal_discret_stl.hpp"

using namespace std;

template <class U>
class filtre {
protected:
  U signal_apply, signal_filtre;
  double duree, freq_coupe;
public:
  //Constructeurs//
  filtre() {
    duree = 1.0;
    freq_coupe = 0.0;
    //    cout << "F/constructeur defaut\n"; // debug
  }
  filtre(U nsignal_apply,double nfreq_coupe, double nduree) {
    duree = nduree;
    freq_coupe = nfreq_coupe;
    signal_apply = nsignal_apply;
    //    cout << "F/constructeur par signal_apply, frequence de coupure et duree\n"; // debug
  }
  filtre(const filtre & f) {
    signal_apply = f.signal_apply;
    signal_filtre = f.signal_filtre;
    duree = f.duree;
    freq_coupe = f.freq_coupe;
    //    cout << "F/constructeur copie\n"; // debug
  }
  //Destructeur//
  ~filtre() {
    //    cout << "F/destructeur\n"; // debug
  }
  //Accesseurs//
  double get_duree();
  U get_signal_apply();
  U get_signal_filtre();
  double get_freq_coupe();
  //Mutateurs//
  void set_duree(double);
  void set_signal_apply(U);
  void set_signal_filtre(U);
  void set_freq_coupe(double);
  //Methodes//
  void apply();
  virtual void construct() = 0;
};

template <class U>
class passe_bas_ideal : public filtre<U> {
public:
  //Constructeurs//
  passe_bas_ideal() {
    //    cout << "F/PBI/constructeur defaut\n"; // debug
  }
  passe_bas_ideal(U nsignal_apply,double freq_coupe, double duree) : filtre<U>(nsignal_apply, freq_coupe, duree) {
    //    cout << "F/PBI/constructeur par signal_apply, frequence de coupure et duree\n"; // debug
  }
  passe_bas_ideal(const passe_bas_ideal & pbi) : filtre<U>(pbi) {
    //    cout << "F/PBI/constructeur par copie\n"; // debug
  }
  //Destructeur//
  ~passe_bas_ideal() {
    //    cout << "F/PBI/destructeur\n"; // debug
  }
  //Methode//
  void construct();
  //Test//
  void test(complexe (*)(double));
};

template <class U>
class passe_haut_ideal : public filtre<U> {
public:
  //Constructeurs//
  passe_haut_ideal() {
    //    cout << "F/PHI/constructeur defaut\n"; // debug
  }
  passe_haut_ideal(U nsignal_apply,double freq_coupe, double duree) : filtre<U>(nsignal_apply, freq_coupe, duree) {
    //    cout << "F/PHI/constructeur par signal_apply, frequence de coupure et duree\n"; // debug
  }
  passe_haut_ideal(const passe_haut_ideal & phi) : filtre<U>(phi) {
    //    cout << "F/PHI/constructeur par copie\n"; // debug
  }
  //Destructeur//
  ~passe_haut_ideal() {
    //    cout << "F/PHI/destructeur\n"; // debug
  }
  //Methode//
  void construct();
  //Test//
  void test(complexe (*)(double));
};

template <class U>
class passe_bas_ordre_1 : public filtre<U> {
public:
  //Constructeurs//
  passe_bas_ordre_1() {
    //    cout << "F/PBO1/constructeur defaut\n"; // debug
  }
  passe_bas_ordre_1(U nsignal_apply,double freq_coupe, double duree) : filtre<U>(nsignal_apply, freq_coupe, duree) {
    //    cout << "F/PBO1/constructeur par signal_apply, frequence de coupure et duree\n"; // debug
  }
  passe_bas_ordre_1(const passe_bas_ordre_1 & pbo1) : filtre<U>(pbo1) {
    //    cout << "F/PBO1/constructeur par copie\n"; // debug
  }
  //Destructeur//
  ~passe_bas_ordre_1() {
    //    cout << "F/PBO1/destructeur\n"; // debug
  }
  //Methode//
  void construct();
  //Test//
  void test(complexe (*)(double));
};

template <class U>
class passe_haut_ordre_1 : public filtre<U> {
public:
  //Constructeurs//
  passe_haut_ordre_1() {
    //    cout << "F/PHO1/constructeur defaut\n"; // debug
  }
  passe_haut_ordre_1(U nsignal_apply,double freq_coupe, double duree) : filtre<U>(nsignal_apply, freq_coupe, duree) {
    //    cout << "F/PHO1/constructeur par signal_apply, frequence de coupure et duree\n"; // debug
  }
  passe_haut_ordre_1(const passe_haut_ordre_1 & pho1) : filtre<U>(pho1) {
    //    cout << "F/PHO1/constructeur par copie\n"; // debug
  }
  //Destructeur//
  ~passe_haut_ordre_1() {
    //    cout << "F/PHO1/destructeur\n"; // debug
  }
  //Methode//
  void construct();
  //Test//
  void test(complexe (*)(double));
};


template <class U>
class passe_bas_ordre_2 : public filtre<U> {
public:
  //Constructeurs//
  passe_bas_ordre_2() {
    //    cout << "F/PBO2/constructeur defaut\n"; // debug
  }
  passe_bas_ordre_2(U nsignal_apply,double freq_coupe, double duree) : filtre<U>(nsignal_apply, freq_coupe, duree) {
    //    cout << "F/PBO2/constructeur par signal_apply, frequence de coupure et duree\n"; // debug
  }
  passe_bas_ordre_2(const passe_bas_ordre_2 & pbo2) : filtre<U>(pbo2) {
    //    cout << "F/PBO2/constructeur par copie\n"; // debug
  }
  //Destructeur//
  ~passe_bas_ordre_2() {
    //    cout << "F/PBO2/destructeur\n"; // debug
  }
  //Methode//
  void construct();
  //Test//
  void test(complexe (*)(double));
};

template <class U>
class passe_haut_ordre_2 : public filtre<U> {
public:
  //Constructeurs//
  passe_haut_ordre_2() {
    //    cout << "F/PHO2/constructeur defaut\n"; // debug
  }
  passe_haut_ordre_2(U nsignal_apply,double freq_coupe, double duree) : filtre<U>(nsignal_apply, freq_coupe, duree) {
    //    cout << "F/PHO2/constructeur par signal_apply, frequence de coupure et duree\n"; // debug
  }
  passe_haut_ordre_2(const passe_haut_ordre_2 & pho2) : filtre<U>(pho2) {
    //    cout << "F/PHO2/constructeur par copie\n"; // debug
  }
  //Destructeur//
  ~passe_haut_ordre_2() {
    //    cout << "F/PHO2/destructeur\n"; // debug
  }
  //Methode//
  void construct();
  //Test//
  void test(complexe (*)(double));
};

template <class U>
class coupe_bande_ideal : public passe_bas_ideal<U>, public passe_haut_ideal<U> {
public:
  //Constructeurs//
  coupe_bande_ideal() : passe_bas_ideal<U>(), passe_haut_ideal<U>() {
    //    cout << "F/CBI/constructeur defaut\n"; // debug
  }
  coupe_bande_ideal(U nsignal_apply,double freq_coupe_bas, double freq_coupe_haut, double duree) :  passe_bas_ideal<U>(nsignal_apply, freq_coupe_bas, duree), passe_haut_ideal<U>(nsignal_apply, freq_coupe_haut, duree) {
    //    cout << "F/CBI/constructeur par signal_apply, frequence de coupure basse et haute et duree\n"; // debug
  }
  coupe_bande_ideal(const coupe_bande_ideal & cbi) : passe_bas_ideal<U>(cbi), passe_haut_ideal<U>(cbi) {
    //    cout << "F/CBI/constructeur par copie\n"; // debug
  }
  //Destructeur//
  ~coupe_bande_ideal() {
    //    cout << "F/CBI/destructeur\n"; // debug
  }
  //Methode//
  void construct();
  //Test//
  void test(complexe (*)(double));
};


/***************FILTRE***************/

/////////ACCESSEURS//////////

template <class U>
double filtre<U>::get_duree() {
  return this->duree;
}

template <class U>
U filtre<U>::get_signal_apply() {
  return this->signal_apply;
}

template <class U>
U filtre<U>::get_signal_filtre() {
  return this->signal_filtre;
}

/////////MUTATEURS//////////

template <class U>
void filtre<U>::set_duree(double nduree) {
  this->duree = nduree;
}

template <class U>
void filtre<U>::set_signal_apply(U nsignal_apply) {
  this->signal_apply = nsignal_apply;
}

template <class U>
void filtre<U>::set_signal_filtre(U nsignal_filtre) {
  this->signal_filtre = nsignal_filtre;
}

template <class U>
void filtre<U>::set_freq_coupe(double n_freq_coupe) {
  this->freq_coupe = n_freq_coupe;
}

template <class U>
double filtre<U>::get_freq_coupe() {
  return this->freq_coupe;
}

/////////METHODE/////////

template <class U>
void filtre<U>::apply() {
  int size = this->signal_apply.get_size(); //1
  complexe * tfd; 
  complexe values_spectre_filtre[size]; 
  U spectre(size), spectre_filtre(size); //
  tfd = this->signal_apply.tfd(); //2
  for (int i = 0; i < size; i++) {
    spectre.set_value(i,tfd[i]);
  } 
  delete [] tfd; //
  spectre_filtre = spectre * this->signal_filtre; //3 //
  for (int i = 0; i < size; i++) { //4
    values_spectre_filtre[i] = spectre_filtre.get_value(i);
  } //
  this->signal_apply = tfd_inverse(values_spectre_filtre,size); //5 //
}


/***************PASSE-BAS IDEAL***************/

//////////METHODE//////////

template <class U>
void passe_bas_ideal<U>::construct() {
  int size = this->signal_apply.get_size(); //1 //
  double w = 1.0 / this->duree; //2
  double freq_p = w; //
  complexe c1(1.0,0.0), c0(0.00000001,0.0); //3 
  for (int i = 0; i < size/2; i++) { 
    if (freq_p < this->freq_coupe) {
      this->signal_filtre.set_value(i,c1);
      this->signal_filtre.set_value(size - 1 - i, c1);
    }
    else {
      this->signal_filtre.set_value(i,c0);
      this->signal_filtre.set_value(size - 1 - i, c0);
    }
    freq_p += w;
  } //
}

//////////TEST//////////

template <class U>
void passe_bas_ideal<U>::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  U sd1, sd2(n),sd3;
  complexe * tfd;
  double T = 1.0/50.0;
  sc1.set_temps(0.0,T); sc1.set_eps(0.01); sc1.set_s(1.0); sc1.set_f(f_test);
  sd1 = sc1.echantillonnage(n, false);
  sd1.sortie_fichier_time(2,0.0,T*(1.0-1.0/n));
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(2,0.0,T,true);
  passe_bas_ideal pbi1(sd1,2000,T);
  pbi1.construct();
  pbi1.apply();
  sd3 = pbi1.signal_apply;
  sd3.sortie_fichier_time(21,0.0,T*(1.0-1.0/n));
  delete [] tfd;
  tfd = sd3.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(21,0.0,T,true);
  delete [] tfd;
  cout << "F/PBI/test effectue, signal_time_21 de spectre signal_freq_21 est le resultat du filtrage passe-bas de signal_time_2 de spectre signal_freq_2 a 600Hz\n"; 
}


/***************PASSE-HAUT IDEAL***************/

//////////METHODE//////////

template <class U>
void passe_haut_ideal<U>::construct() {
  int size = this->signal_apply.get_size();
  double w = 1.0 / this->duree;
  double freq_p = w;
  complexe c1(1.0,0.0), c0(0.00000001,0.0);
  for (int i = 0; i < size/2; i++) {
    if (freq_p < this->freq_coupe && i != 0) { //On vérifie que l'on ne filtre pas la valeur moyenne du signal 
      this->signal_filtre.set_value(i,c0);
      this->signal_filtre.set_value(size - 1 - i, c0);
    }
    else {
      this->signal_filtre.set_value(i,c1);
      this->signal_filtre.set_value(size - 1 - i, c1);
    }
    freq_p += w;
  }
}

//////////TEST//////////

template <class U>
void passe_haut_ideal<U>::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  U sd1, sd2(n),sd3;
  complexe * tfd;
  double T = 1.0/50.0;
  sc1.set_temps(0.0,T); sc1.set_eps(0.01); sc1.set_s(1.0); sc1.set_f(f_test);
  sd1 = sc1.echantillonnage(n, false);
  sd1.sortie_fichier_time(3,0.0,T*(1.0-1.0/n));
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(3,0.0,T,true);
  passe_haut_ideal phi1(sd1,2000,T);
  phi1.construct();
  phi1.apply();
  sd3 = phi1.signal_apply;
  sd3.sortie_fichier_time(31,0.0,T*(1.0-1.0/n));
  delete [] tfd;
  tfd = sd3.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(31,0.0,T,true);
  delete [] tfd;  
  cout << "F/PHI/test effectue, signal_time_31 de spectre signal_freq_31 est le resultat du filtrage passe-haut de signal_time_3 de spectre signal_freq_3 a 2000Hz\n";
}


/***************PASSE-BAS 1er ORDRE***************/

//////////METHODE//////////

template <class U>
void passe_bas_ordre_1<U>::construct() {
  int size = this->signal_apply.get_size(); //1 //
  double w = 1.0 / this->duree; //2
  double freq_p = w; //
  for (int i = 0; i < size/2; i++) { //3
    complexe temp(1.0/sqrt(1.0+(freq_p/this->freq_coupe)*(freq_p/this->freq_coupe)),0.0);
    this->signal_filtre.set_value(i,temp);
    this->signal_filtre.set_value(size - 1 - i, temp);
    freq_p += w;
  } //
}

//////////TEST//////////

template <class U>
void passe_bas_ordre_1<U>::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  U sd1, sd2(n),sd3;
  complexe * tfd;
  double T = 1.0/50.0;
  sc1.set_temps(0.0,T); sc1.set_eps(0.01); sc1.set_s(1.0); sc1.set_f(f_test);
  sd1 = sc1.echantillonnage(n, false);
  sd1.sortie_fichier_time(4,0.0,T*(1.0-1.0/n));
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(4,0.0,T,true);
  passe_bas_ordre_1 pbo11(sd1,2000,T);
  pbo11.construct();
  pbo11.apply();
  sd3 = pbo11.signal_apply;
  sd3.sortie_fichier_time(41,0.0,T*(1.0-1.0/n));
  delete [] tfd;
  tfd = sd3.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(41,0.0,T,true);
  delete [] tfd;  
  cout << "F/PBO1/test effectue, signal_time_41 de spectre signal_freq_41 est le resultat du filtrage passe-bas de signal_time_4 de spectre signal_freq_4 a 600Hz\n";
}


/***************PASSE-HAUT 1er ORDRE***************/

//////////METHODE//////////

template <class U>
void passe_haut_ordre_1<U>::construct() {
  int size = this->signal_apply.get_size();
  double w = 1.0 / this->duree;
  double freq_p = 2.0*w;
  complexe c1(1.0,0.0);
  this->signal_filtre.set_value(0,c1); //On vérifie que l'on ne filtre pas la valeur moyenne du signal en commencant la boucle a i = 1 et le filtre a 1 pour i = 0
  for (int i = 1; i < size/2; i++) {
    complexe temp(freq_p/this->freq_coupe/sqrt(1.0+(freq_p/this->freq_coupe)*(freq_p/this->freq_coupe)),0.0);
    this->signal_filtre.set_value(i,temp);
    this->signal_filtre.set_value(size - 1 - i, temp);
    freq_p += w;
  }
}


//////////TEST//////////

template <class U>
void passe_haut_ordre_1<U>::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  U sd1, sd2(n),sd3;
  complexe * tfd;
  double T = 1.0/50.0;
  sc1.set_temps(0.0,T); sc1.set_eps(0.01); sc1.set_s(1.0); sc1.set_f(f_test);
  sd1 = sc1.echantillonnage(n, false);
  sd1.sortie_fichier_time(5,0.0,T*(1.0-1.0/n));
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(5,0.0,T,true);
  passe_haut_ordre_1 pho11(sd1,2000,T);
  pho11.construct();
  pho11.apply();
  sd3 = pho11.signal_apply;
  sd3.sortie_fichier_time(51,0.0,T*(1.0-1.0/n));
  delete [] tfd;
  tfd = sd3.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(51,0.0,T,true);
  delete [] tfd;  
  cout << "F/PHO1/test effectue, signal_time_51 de spectre signal_freq_51 est le resultat du filtrage passe-haut de signal_time_5 de spectre signal_freq_5 a 2000Hz\n";
}

/***************PASSE-BAS 2eme ORDRE***************/

//////////METHODE//////////

template <class U>
void passe_bas_ordre_2<U>::construct() {
  int size = this->signal_apply.get_size();
  double Q = 0.1;
  double w = 1.0 / this->duree;
  double freq_p = 2.0*w;
  complexe c1(1.0,0.0);
  this->signal_filtre.set_value(0,c1); //On vérifie que l'on ne filtre pas la valeur moyenne du signal en commencant la boucle a i = 1 et le filtre a 1 pour i = 0
  for (int i = 1; i < size/2; i++) {
    complexe temp(1.0/sqrt((1.0-(freq_p/this->freq_coupe)*(freq_p/this->freq_coupe))*(1.0-(freq_p/this->freq_coupe)*(freq_p/this->freq_coupe))+(freq_p/this->freq_coupe/Q)*(freq_p/this->freq_coupe/Q)),0.0);
    this->signal_filtre.set_value(i,temp);
    this->signal_filtre.set_value(size - 1 - i, temp);
    freq_p += w;
  }
}


//////////TEST//////////

template <class U>
void passe_bas_ordre_2<U>::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  U sd1, sd2(n),sd3;
  complexe * tfd;
  double T = 1.0/50.0;
  sc1.set_temps(0.0,T); sc1.set_eps(0.01); sc1.set_s(1.0); sc1.set_f(f_test);
  sd1 = sc1.echantillonnage(n, false);
  sd1.sortie_fichier_time(6,0.0,T*(1.0-1.0/n));
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(6,0.0,T,true);
  passe_bas_ordre_2 pbo21(sd1,2000,T);
  pbo21.construct();
  pbo21.apply();
  sd3 = pbo21.signal_apply;
  sd3.sortie_fichier_time(61,0.0,T*(1.0-1.0/n));
  delete [] tfd;
  tfd = sd3.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(61,0.0,T,true);
  delete [] tfd;  
  cout << "F/PBO2/test effectue, signal_time_61 de spectre signal_freq_61 est le resultat du filtrage passe-bas de signal_time_6 de spectre signal_freq_6 a 2000Hz\n";
}


/***************PASSE-HAUT 2eme ORDRE***************/

//////////METHODE//////////

template <class U>
void passe_haut_ordre_2<U>::construct() {
  int size = this->signal_apply.get_size();
  double Q = 0.1;
  double w = 1.0 / this->duree;
  double freq_p = 2.0*w;
  complexe c1(1.0,0.0);
  this->signal_filtre.set_value(0,c1); //On vérifie que l'on ne filtre pas la valeur moyenne du signal en commencant la boucle a i = 1 et le filtre a 1 pour i = 0
  for (int i = 1; i < size/2; i++) {
    complexe temp((freq_p/this->freq_coupe)*(freq_p/this->freq_coupe)/sqrt((1.0-(freq_p/this->freq_coupe)*(freq_p/this->freq_coupe))*(1.0-(freq_p/this->freq_coupe)*(freq_p/this->freq_coupe))+(freq_p/this->freq_coupe/Q)*(freq_p/this->freq_coupe/Q)),0.0);
    this->signal_filtre.set_value(i,temp);
    this->signal_filtre.set_value(size - 1 - i, temp);
    freq_p += w;
  }
}


//////////TEST//////////

template <class U>
void passe_haut_ordre_2<U>::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  U sd1, sd2(n),sd3;
  complexe * tfd;
  double T = 1.0/50.0;
  sc1.set_temps(0.0,T); sc1.set_eps(0.01); sc1.set_s(1.0); sc1.set_f(f_test);
  sd1 = sc1.echantillonnage(n, false);
  sd1.sortie_fichier_time(7,0.0,T*(1.0-1.0/n));
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(7,0.0,T,true);
  passe_haut_ordre_2 pho21(sd1,1000,T);
  pho21.construct();
  pho21.apply();
  sd3 = pho21.signal_apply;
  sd3.sortie_fichier_time(71,0.0,T*(1.0-1.0/n));
  delete [] tfd;
  tfd = sd3.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(71,0.0,T,true);
  delete [] tfd;  
  cout << "F/PHO2/test effectue, signal_time_71 de spectre signal_freq_71 est le resultat du filtrage passe-haut de signal_time_7 de spectre signal_freq_7 a 1000Hz\n";
}


/***************COUPE-BANDE IDEAL***************/

///////////METHODE//////////

template <class U>
void coupe_bande_ideal<U>::construct() {
  double freq_coupe_bas = passe_bas_ideal<U>::get_freq_coupe(), freq_coupe_haut = passe_haut_ideal<U>::get_freq_coupe();
  int size = passe_bas_ideal<U>::signal_apply.get_size();
  double w = 1.0 / passe_bas_ideal<U>::duree;
  double freq_p = w;
  complexe c1(1.0,0.0), c0(0.00000001,0.0);
  for (int i = 0; i < size/2; i++) {
    if (freq_coupe_bas <= freq_p && freq_p <= freq_coupe_haut && i != 0) { //On vérifie que l'on ne filtre pas la valeur moyenne du signal 
      passe_bas_ideal<U>::signal_filtre.set_value(i,c0);
      passe_bas_ideal<U>::signal_filtre.set_value(size - 1 - i, c0);
    }
    else {
      passe_bas_ideal<U>::signal_filtre.set_value(i,c1);
      passe_bas_ideal<U>::signal_filtre.set_value(size - 1 - i, c1);
    }
    freq_p += w;
  }
}

///////////TEST//////////

template <class U>
void coupe_bande_ideal<U>::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  U sd1, sd2(n),sd3;
  complexe * tfd;
  double T = 1.0/50.0;
  sc1.set_temps(0.0,T); sc1.set_eps(0.01); sc1.set_s(1.0); sc1.set_f(f_test);
  sd1 = sc1.echantillonnage(n, false);
  sd1.sortie_fichier_time(8,0.0,T*(1.0-1.0/n));
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(8,0.0,T,true);
  coupe_bande_ideal cbi1(sd1,2900,3100,T);
  cbi1.construct();
  cbi1.passe_bas_ideal<U>::apply();
  sd3 = cbi1.passe_bas_ideal<U>::signal_apply;
  sd3.sortie_fichier_time(81,0.0,T*(1.0-1.0/n));
  delete [] tfd;
  tfd = sd3.tfd();
  for (int i = 0; i < n; i++) {
    sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(81,0.0,T,true);
  delete [] tfd;  
  cout << "F/CBI/test effectue, signal_time_81 de spectre signal_freq_81 est le resultat du filtrage coupe-bande ideal de signal_time_8 de spectre signal_freq_8 entre 2900 et 3100 Hz\n";
}


/***************FONCTION HORS CLASSE***************/

//////////TESTEUR//////////

//Testeur//
template <class V>
void filtre_all_testu(complexe (*f_test)(double)) {
  passe_bas_ideal<V> pbi;
  pbi.test(f_test);
  passe_haut_ideal<V> phi;
  phi.test(f_test);
  passe_bas_ordre_1<V> pbo1;
  pbo1.test(f_test);
  passe_haut_ordre_1<V> pho1;
  pho1.test(f_test);
  passe_bas_ordre_2<V> pbo2;
  pbo2.test(f_test);
  passe_haut_ordre_2<V> pho2;
  pho2.test(f_test);
  coupe_bande_ideal<V> cbi;
  cbi.test(f_test);
}

#endif
