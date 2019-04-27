#include <cmath>
#include <iostream>
#include "complexe.hpp"
#include "signal_discret.hpp"
#include "signal_continu.hpp"
#include "filtre.hpp"

using namespace std;

void filtre::set_duree(double nduree) {
  duree = nduree;
}

void filtre::set_signal_apply(signal_discret nsignal_apply) {
  signal_apply = nsignal_apply;
}

void filtre::set_signal_filtre(signal_discret nsignal_filtre) {
  signal_filtre = nsignal_filtre;
}

double filtre::get_duree() {
  return duree;
}

signal_discret filtre::get_signal_apply() {
  return signal_apply;
}

signal_discret filtre::get_signal_filtre() {
  return signal_filtre;
}

void filtre::apply() {
  complexe * tfd;
  int size = signal_apply.get_size();
  signal_discret spectre(size), spectre_filtre(size);
  tfd = signal_apply.tfd();
  for (int i = 0; i < size; i++) {
    spectre.set_value(i,tfd[i]);
  }
  spectre_filtre = spectre * signal_filtre;
  complexe values_spectre_filtre[size];
  for (int i = 0; i < size; i++) {
    values_spectre_filtre[i] = spectre_filtre.get_value(i);
  }
  signal_apply = tfd_inverse(values_spectre_filtre,size);
}

void filtre::set_freq_coupe(double n_freq_coupe) {
  freq_coupe = n_freq_coupe;
}

double filtre::get_freq_coupe() {
  return freq_coupe;
}

void passe_bas_ideal::construct() {
  int size = signal_apply.get_size();
  double w = 1.0 / duree;
  double freq_p = w;
  complexe c1(1.0,0.0), c0(0.0001,0.0);
  for (int i = 0; i < size/2; i++) {
    if (freq_p < freq_coupe) {
      signal_filtre.set_value(i,c1);
      signal_filtre.set_value(size - 1 - i, c1);
    }
    else {
      signal_filtre.set_value(i,c0);
      signal_filtre.set_value(size - 1 - i, c0);
    }
    freq_p += w;
  }
}

int passe_bas_ideal::testu_1(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  signal_discret sd1, sd2(n),sd3;
  complexe * tfd;
  double fonda = 1.0;
  double T = 1.0/50.0;
  //premier echantillonage sur une periode pour plus de visibilité
  sc1.set_temps(0.0,T); sc1.set_eps(0.01); sc1.set_s(1.0); sc1.set_f(f_test);
  sd1 = sc1.echantillonage(n);
  sd1.sortie_fichier_time(2,0.0,T*(1.0-1.0/n));
  sc1.set_temps(0.0,T);
  sd1 = sc1.echantillonage(n);
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
      sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(2,0.0,T,true);
  passe_bas_ideal pbi1(sd1,600,T);
  pbi1.construct();
  pbi1.apply();
  sd3 = pbi1.signal_apply;
  sd3.sortie_fichier_time(21,0.0,T*(1.0-1.0/n));
  tfd = sd3.tfd();
  for (int i = 0; i < n; i++) {
      sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(21,0.0,T,true);
  delete [] tfd;  
  return 1;
}

void passe_bas_ideal::all_testu(complexe (*f_test)(double)) {
  passe_bas_ideal pbi;
  int nb_tests = 1;
  int nb_reussis = 0;
  nb_reussis += pbi.testu_1(f_test);
  cout << "F/PBI/ " << nb_reussis << " tests sur " << nb_tests << " reussis\n";
};


void passe_haut_ideal::construct() {
  int size = signal_apply.get_size();
  double w = 1.0 / duree;
  double freq_p = w;
  complexe c1(1.0,0.0), c0(0.0001,0.0);
  for (int i = 0; i < size/2; i++) {
    if (freq_p < freq_coupe && i != 0) { //On vérifie que l'on ne filtre pas la valeur moyenne du signal 
      signal_filtre.set_value(i,c0);
      signal_filtre.set_value(size - 1 - i, c0);
    }
    else {
      signal_filtre.set_value(i,c1);
      signal_filtre.set_value(size - 1 - i, c1);
    }
    freq_p += w;
  }
}

int passe_haut_ideal::testu_1(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  signal_discret sd1, sd2(n),sd3;
  complexe * tfd;
  double fonda = 1.0;
  double T = 1.0/50.0;
  //premier echantillonage sur une periode pour plus de visibilité
  sc1.set_temps(0.0,T); sc1.set_eps(0.01); sc1.set_s(1.0); sc1.set_f(f_test);
  sd1 = sc1.echantillonage(n);
  sd1.sortie_fichier_time(3,0.0,T*(1.0-1.0/n));
  sc1.set_temps(0.0,T);
  sd1 = sc1.echantillonage(n);
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
      sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(3,0.0,T,true);
  passe_haut_ideal phi1(sd1,250,T);
  phi1.construct();
  phi1.apply();
  sd3 = phi1.signal_apply;
  sd3.sortie_fichier_time(31,0.0,T*(1.0-1.0/n));
  tfd = sd3.tfd();
  for (int i = 0; i < n; i++) {
      sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(31,0.0,T,true);
  delete [] tfd;  
  return 1;
}

void passe_haut_ideal::all_testu(complexe (*f_test)(double)) {
  passe_haut_ideal phi;
  int nb_tests = 1;
  int nb_reussis = 0;
  nb_reussis += phi.testu_1(f_test);
  cout << "F/PHI/ " << nb_reussis << " tests sur " << nb_tests << " reussis\n";
};


void passe_bas_ordre_1::construct() {
  int size = signal_apply.get_size();
  double w = 1.0 / duree;
  double freq_p = w;
  for (int i = 0; i < size/2; i++) {
    complexe temp(1.0/sqrt(1.0+(freq_p/freq_coupe)*(freq_p/freq_coupe)),0.0);
    signal_filtre.set_value(i,temp);
    signal_filtre.set_value(size - 1 - i, temp);
    freq_p += w;
  }
}

int passe_bas_ordre_1::testu_1(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  signal_discret sd1, sd2(n),sd3;
  complexe * tfd;
  double fonda = 1.0;
  double T = 1.0/50.0;
  //premier echantillonage sur une periode pour plus de visibilité
  sc1.set_temps(0.0,T); sc1.set_eps(0.01); sc1.set_s(1.0); sc1.set_f(f_test);
  sd1 = sc1.echantillonage(n);
  sd1.sortie_fichier_time(4,0.0,T*(1.0-1.0/n));
  sc1.set_temps(0.0,T);
  sd1 = sc1.echantillonage(n);
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
      sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(4,0.0,T,true);
  passe_bas_ordre_1 pbo11(sd1,600,T);
  pbo11.construct();
  pbo11.apply();
  sd3 = pbo11.signal_apply;
  sd3.sortie_fichier_time(41,0.0,T*(1.0-1.0/n));
  tfd = sd3.tfd();
  for (int i = 0; i < n; i++) {
      sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(41,0.0,T,true);
  delete [] tfd;  
  return 1;
}

void passe_bas_ordre_1::all_testu(complexe (*f_test)(double)) {
  passe_bas_ordre_1 pbo1;
  int nb_tests = 1;
  int nb_reussis = 0;
  nb_reussis += pbo1.testu_1(f_test);
  cout << "F/PBO1/ " << nb_reussis << " tests sur " << nb_tests << " reussis\n";
};


void passe_haut_ordre_1::construct() {
  int size = signal_apply.get_size();
  double w = 1.0 / duree;
  double freq_p = w;
  for (int i = 0; i < size/2; i++) {
    complexe temp(freq_p/freq_coupe/sqrt(1.0+(freq_p/freq_coupe)*(freq_p/freq_coupe)),0.0);
    signal_filtre.set_value(i,temp);
    signal_filtre.set_value(size - 1 - i, temp);
    freq_p += w;
  }
}

int passe_haut_ordre_1::testu_1(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  signal_discret sd1, sd2(n),sd3;
  complexe * tfd;
  double fonda = 1.0;
  double T = 1.0/50.0;
  //premier echantillonage sur une periode pour plus de visibilité
  sc1.set_temps(0.0,T); sc1.set_eps(0.01); sc1.set_s(1.0); sc1.set_f(f_test);
  sd1 = sc1.echantillonage(n);
  sd1.sortie_fichier_time(5,0.0,T*(1.0-1.0/n));
  sc1.set_temps(0.0,T);
  sd1 = sc1.echantillonage(n);
  tfd = sd1.tfd();
  for (int i = 0; i < n; i++) {
      sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(5,0.0,T,true);
  passe_haut_ordre_1 pho11(sd1,10000,T);
  pho11.construct();
  pho11.apply();
  sd3 = pho11.signal_apply;
  sd3.sortie_fichier_time(51,0.0,T*(1.0-1.0/n));
  tfd = sd3.tfd();
  for (int i = 0; i < n; i++) {
      sd2.set_value(i,tfd[i]);
  }
  sd2.sortie_fichier_freq(51,0.0,T,true);
  delete [] tfd;  
  return 1;
}

void passe_haut_ordre_1::all_testu(complexe (*f_test)(double)) {
  passe_haut_ordre_1 pho1;
  int nb_tests = 1;
  int nb_reussis = 0;
  nb_reussis += pho1.testu_1(f_test);
  cout << "F/PHO1/ " << nb_reussis << " tests sur " << nb_tests << " reussis\n";
};
