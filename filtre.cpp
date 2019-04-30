#include <cmath>
#include <iostream>
#include "complexe.hpp"
#include "signal_discret.hpp"
#include "signal_continu.hpp"
#include "filtre.hpp"

using namespace std;


/***************FILTRE***************/

/////////ACCESSEURS//////////

double filtre::get_duree() {
  return duree;
}

signal_discret filtre::get_signal_apply() {
  return signal_apply;
}

signal_discret filtre::get_signal_filtre() {
  return signal_filtre;
}

/////////MUTATEURS//////////

void filtre::set_duree(double nduree) {
  duree = nduree;
}

void filtre::set_signal_apply(signal_discret nsignal_apply) {
  signal_apply = nsignal_apply;
}

void filtre::set_signal_filtre(signal_discret nsignal_filtre) {
  signal_filtre = nsignal_filtre;
}

void filtre::set_freq_coupe(double n_freq_coupe) {
  freq_coupe = n_freq_coupe;
}

double filtre::get_freq_coupe() {
  return freq_coupe;
}

/////////METHODE//////////

void filtre::apply() {
  int size = signal_apply.get_size(); //1
  complexe * tfd; 
  complexe values_spectre_filtre[size]; 
  signal_discret spectre(size), spectre_filtre(size); //
  tfd = signal_apply.tfd(); //2
  for (int i = 0; i < size; i++) {
    spectre.set_value(i,tfd[i]);
  } 
  delete [] tfd; //
  spectre_filtre = spectre * signal_filtre; //3 //
  for (int i = 0; i < size; i++) { //4
    values_spectre_filtre[i] = spectre_filtre.get_value(i);
  } //
  signal_apply = tfd_inverse(values_spectre_filtre,size); //5 //
}


/***************PASSE-BAS IDEAL***************/

//////////METHODE//////////

void passe_bas_ideal::construct() {
  int size = signal_apply.get_size(); //1 //
  double w = 1.0 / duree; //2
  double freq_p = w; //
  complexe c1(1.0,0.0), c0(0.0001,0.0); //3 
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
  } //
}

//////////TEST//////////

void passe_bas_ideal::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  signal_discret sd1, sd2(n),sd3;
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

//////////TEST//////////

void passe_haut_ideal::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  signal_discret sd1, sd2(n),sd3;
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

void passe_bas_ordre_1::construct() {
  int size = signal_apply.get_size(); //1 //
  double w = 1.0 / duree; //2
  double freq_p = w; //
  for (int i = 0; i < size/2; i++) { //3
    complexe temp(1.0/sqrt(1.0+(freq_p/freq_coupe)*(freq_p/freq_coupe)),0.0);
    signal_filtre.set_value(i,temp);
    signal_filtre.set_value(size - 1 - i, temp);
    freq_p += w;
  } //
}

//////////TEST//////////

void passe_bas_ordre_1::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  signal_discret sd1, sd2(n),sd3;
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

void passe_haut_ordre_1::construct() {
  int size = signal_apply.get_size();
  double w = 1.0 / duree;
  double freq_p = 2.0*w;
  complexe c1(1.0,0.0);
  signal_filtre.set_value(0,c1); //On vérifie que l'on ne filtre pas la valeur moyenne du signal en commencant la boucle a i = 1 et le filtre a 1 pour i = 0
  for (int i = 1; i < size/2; i++) {
    complexe temp(freq_p/freq_coupe/sqrt(1.0+(freq_p/freq_coupe)*(freq_p/freq_coupe)),0.0);
    signal_filtre.set_value(i,temp);
    signal_filtre.set_value(size - 1 - i, temp);
    freq_p += w;
  }
}


//////////TEST//////////

void passe_haut_ordre_1::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  signal_discret sd1, sd2(n),sd3;
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

void passe_bas_ordre_2::construct() {
  int size = signal_apply.get_size();
  double Q = 0.1;
  double w = 1.0 / duree;
  double freq_p = 2.0*w;
  complexe c1(1.0,0.0);
  signal_filtre.set_value(0,c1); //On vérifie que l'on ne filtre pas la valeur moyenne du signal en commencant la boucle a i = 1 et le filtre a 1 pour i = 0
  for (int i = 1; i < size/2; i++) {
    complexe temp(1.0/sqrt((1.0-(freq_p/freq_coupe)*(freq_p/freq_coupe))*(1.0-(freq_p/freq_coupe)*(freq_p/freq_coupe))+(freq_p/freq_coupe/Q)*(freq_p/freq_coupe/Q)),0.0);
    signal_filtre.set_value(i,temp);
    signal_filtre.set_value(size - 1 - i, temp);
    freq_p += w;
  }
}


//////////TEST//////////

void passe_bas_ordre_2::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  signal_discret sd1, sd2(n),sd3;
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

void passe_haut_ordre_2::construct() {
  int size = signal_apply.get_size();
  double Q = 0.1;
  double w = 1.0 / duree;
  double freq_p = 2.0*w;
  complexe c1(1.0,0.0);
  signal_filtre.set_value(0,c1); //On vérifie que l'on ne filtre pas la valeur moyenne du signal en commencant la boucle a i = 1 et le filtre a 1 pour i = 0
  for (int i = 1; i < size/2; i++) {
    complexe temp((freq_p/freq_coupe)*(freq_p/freq_coupe)/sqrt((1.0-(freq_p/freq_coupe)*(freq_p/freq_coupe))*(1.0-(freq_p/freq_coupe)*(freq_p/freq_coupe))+(freq_p/freq_coupe/Q)*(freq_p/freq_coupe/Q)),0.0);
    signal_filtre.set_value(i,temp);
    signal_filtre.set_value(size - 1 - i, temp);
    freq_p += w;
  }
}


//////////TEST//////////

void passe_haut_ordre_2::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  signal_discret sd1, sd2(n),sd3;
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

void coupe_bande_ideal::construct() {
  double freq_coupe_bas = passe_bas_ideal::get_freq_coupe(), freq_coupe_haut = passe_haut_ideal::get_freq_coupe();
  int size = passe_bas_ideal::signal_apply.get_size();
  double w = 1.0 / passe_bas_ideal::duree;
  double freq_p = w;
  complexe c1(1.0,0.0), c0(0.0001,0.0);
  for (int i = 0; i < size/2; i++) {
    if (freq_coupe_bas <= freq_p && freq_p <= freq_coupe_haut && i != 0) { //On vérifie que l'on ne filtre pas la valeur moyenne du signal 
      passe_bas_ideal::signal_filtre.set_value(i,c0);
      passe_bas_ideal::signal_filtre.set_value(size - 1 - i, c0);
    }
    else {
      passe_bas_ideal::signal_filtre.set_value(i,c1);
      passe_bas_ideal::signal_filtre.set_value(size - 1 - i, c1);
    }
    freq_p += w;
  }
}

///////////TEST//////////

void coupe_bande_ideal::test(complexe (*f_test)(double)) {
  signal_continu sc1(f_test);
  int n = 1000;
  signal_discret sd1, sd2(n),sd3;
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
  cbi1.passe_bas_ideal::apply();
  sd3 = cbi1.passe_bas_ideal::signal_apply;
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

void filtre_all_testu(complexe (*f_test)(double)) {
  passe_bas_ideal pbi;
  pbi.test(f_test);
  passe_haut_ideal phi;
  phi.test(f_test);
  passe_bas_ordre_1 pbo1;
  pbo1.test(f_test);
  passe_haut_ordre_1 pho1;
  pho1.test(f_test);
  passe_bas_ordre_2 pbo2;
  pbo2.test(f_test);
  passe_haut_ordre_2 pho2;
  pho2.test(f_test);
  coupe_bande_ideal cbi;
  cbi.test(f_test);
}



