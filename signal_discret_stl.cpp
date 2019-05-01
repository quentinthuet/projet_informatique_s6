#include <cmath>
#include <iostream>
#include "complexe.hpp"
#include "signal_discret.hpp"
#include "signal_discret_stl.hpp"
using namespace std;

//////////FONCTIONS DE SORTIE DE DONNEES//////////

void signal_discret_stl::sortie_fichier_time(int nb, double t0, double t1) {
  char string[255];
  FILE *fileresult = NULL;
  int size = M_values.size();
  double dt = 0.0, time;
  sprintf(string, "%s%d", "signal_time_", nb);
  fileresult = fopen(string, "w");
  dt = (t1 - t0) / (double) (size - 1);
  time = t0;
  for (int i = 0; i < size; i++) {
    fprintf(fileresult, "%e %e\n", time, M_values[i].module());
    time += dt;
  }
  fclose(fileresult);
}

void signal_discret_stl::sortie_fichier_freq(int nb, double t0, double t1, bool log_on) {
  char string[255];
  FILE *fileresult = NULL;
  int size = M_values.size();
  double w = 0.0, freq;
  sprintf(string, "%s%d", "signal_freq_", nb);
  fileresult = fopen(string, "w");
  w = 1.0 / (t1 - t0);
  freq = w;
  for (int i = 1; i < size/2; i++) {
    if (log_on)
      fprintf(fileresult, "%e %e\n", freq, log(M_values[i].module()));
    else
      fprintf(fileresult, "%e %e\n", freq, (M_values[i].module()));
    freq += w;
  }
  fclose(fileresult);
}

//////////ACCESSEURS//////////

int signal_discret_stl::get_size(){
  return M_values.size();
}

complexe signal_discret_stl::get_value(int i){
  complexe res(0,0);
  if (i < M_values.size() && i >= 0)
    res = M_values[i];
  return res;
}



//////////MUTATEURS//////////

void signal_discret_stl::set_value(int i, complexe c){
  complexe zero(0,0);
  if (i < M_values.size()) //1
    M_values[i] = c; //
  else {
    for (int j = M_values.size(); j < i; j++){
      M_values.push_back(zero);
    }
    M_values.push_back(c); //
  }
}



//////////METHODES ELEMENTAIRES//////////

signal_discret_stl signal_discret_stl::conjugue(){
  signal_discret_stl res(M_values.size());
  for (int i = 0; i < M_values.size(); i++){
    res.M_values[i] = M_values[i].conjugue();
  }
  return res;
}

double signal_discret_stl::energie(){
  double res = 0.0;
  for (int i = 0; i < M_values.size(); i++){
    res += (M_values[i].module()) * (M_values[i].module());
  }
  return res;
}



//////////METHODES AVANCEES//////////

complexe * signal_discret_stl::tfd(){
  int size = M_values.size();
  complexe * res = new complexe[size];
  complexe zero(0,0);
  for (int k = 0; k < size; k++){ //1
    res[k] = zero; //
    for (int n = 0; n < size; n++){ //2
      complexe temp(cos(-2 * M_PI * n * k /((double) size)), sin(-2 * M_PI * n * k /((double) size)));
      res[k] = res[k] + (M_values[n] * temp);
    } //
  }
  return res;
}

signal_discret_stl signal_discret_stl::convolution(signal_discret_stl & sds){
  int size_max, lsize = M_values.size(), rsize = sds.M_values.size(); //1
  size_max = max(lsize,rsize); //
  signal_discret_stl res(size_max); //2 //
  for (int n = 0; n < size_max; n++) { //3
    for (int k = 0; k < size_max; k++) { //
      if (k >= lsize || (n - k) < 0 || (n - k) >= rsize ) //4
	continue; 
      else
	res.set_value(n,res.get_value(n) + this->get_value(k)*sds.get_value(n - k)); //
    }
  }
  return res;
}

signal_discret_stl signal_discret_stl::translation(const int k0){
  int size = M_values.size();
  signal_discret_stl res(size);
  complexe zero(0,0);
  for (int k = 0; k < size; k++){ //1
    if ((k - k0 >= 0) && (k - k0 < size))
      res.M_values[k] = M_values[k - k0];
    else
      res.M_values[k] = zero;
  } //
  return res;
}

signal_discret_stl signal_discret_stl::modulation(const double k0){
  int size = M_values.size();
  signal_discret_stl res(size);
  for (int k = 0; k < size; k++){ //1
    complexe temp(cos(k0),sin(k0));
    res.M_values[k] = temp * M_values[k]; //
  }
  return res;
}


//////////FONCTIONS EXTERNES A LA CLASSE//////////

signal_discret_stl tfd_inverse_stl(complexe * c_tab, const int size){
  signal_discret_stl res(size);
  complexe zero(0,0);
  complexe quotient(1 /((double) size),0);
  for (int n = 0; n < size; n++){ //2
    res.M_values[n] = zero; //
    for (int k = 0; k < size; k++){ //3
      complexe temp(cos(2 * M_PI * n * k /((double) size)), sin(2 * M_PI * n * k /((double) size)));
      res.M_values[n] = res.M_values[n] + (c_tab[k] * temp); //
    }
    res.M_values[n] = res.M_values[n] * quotient; //4 //
  }
  return res;
}
/*


//////////OPERATEURS//////////
*/
signal_discret_stl & signal_discret_stl::operator=(const signal_discret_stl & sds){
  if (&sds != this){ //1 //
    M_values = sds.M_values;
  }
  return *this;
}

signal_discret_stl & signal_discret_stl::operator=(const signal_discret & sd){
  signal_discret temp = sd;
  int size = temp.get_size();
  M_values.clear();
  for (int i = 0; i < size; i++) {
    M_values.push_back(temp.get_value(i));
  }
  return *this;
}

signal_discret_stl signal_discret_stl::operator+(const signal_discret_stl & sds){
  double lsize = this->M_values.size(), rsize = sds.M_values.size();
  signal_discret_stl res;
  for (int i = 0; i < lsize && i < rsize; i++) {
    res.M_values.push_back(this->M_values[i] + sds.M_values[i]);
  }  
  return res;
}

signal_discret_stl signal_discret_stl::operator*(const signal_discret_stl & sds){
 double lsize = this->M_values.size(), rsize = sds.M_values.size();
  signal_discret_stl res;
  for (int i = 0; i < lsize && i < rsize; i++) {
    res.M_values.push_back(this->M_values[i] * sds.M_values[i]);
  }
  return res;
}

signal_discret_stl signal_discret_stl::operator-(const signal_discret_stl & sds){
   double lsize = this->M_values.size(), rsize = sds.M_values.size();
  signal_discret_stl res;
  for (int i = 0; i < lsize && i < rsize; i++) {
    res.M_values.push_back(this->M_values[i] - sds.M_values[i]);
  }  
  return res;
}

complexe signal_discret_stl::operator,(const signal_discret_stl & sds){
  int size_min; //1
  size_min = min(M_values.size(), sds.M_values.size()); //
  complexe res(0,0), temp;
  for (int i = 0; i < size_min; i++){ //2
    temp = sds.M_values[i];
    res = res + (M_values[i] * temp.conjugue());
  } //
  return res;  
}


//////////TESTEURS//////////

int signal_discret_stl::testu_1(){ //test des constructeurs, destructeurs, accesseurs et mutateurs
  signal_discret_stl sds1(5); //1 //
  
  signal_discret_stl sds2; //2 //

  signal_discret_stl sds3(sds1); //3
  signal_discret_stl sds4(sds2); //

  bool test1 = (sds1.get_size() == 5); //4 //

  complexe c1(0,0), c2(5,6); //5 
  bool test2 = (sds1.get_value(3) == c1); //

  sds1.set_value(3,c2); sds1.set_value(7,c2); //6
  bool test3 = (sds1.get_value(3) == c2 && sds1.get_value(6) == c1 && sds1.get_value(7) == c2 && sds1.get_size() == 8); //
  
  if (test1 && test2 && test3)
    return 1;
  else
    return 0;
}

int signal_discret_stl::testu_2(){//test des opérateurs et des méthodes élémentaires
  signal_discret_stl sds1(5);
  signal_discret_stl sds2;

  complexe c1(5,6); //1
  sds1.set_value(3, c1);
  sds2 = sds1; 
  bool test1 = (sds2.get_value(3) == c1); //

  signal_discret_stl sds3; //2
  sds3 = (sds1 + sds2); 
  complexe c2(10,12);
  bool test2 = (sds3.get_value(3) == c2); //

  sds3 = (sds1 * sds2); //3
  complexe c3(-11,60);
  bool test3 = (sds3.get_value(3) == c3); //

  sds3 = (sds1 - sds2); //4
  complexe c4(0,0);
  bool test4 = (sds3.get_value(3) == c4); //
  
  sds3 = sds1.conjugue(); //5
  complexe c5(5,-6);
  bool test5 = (sds3.get_value(3) == c5); //

  complexe c6(1,-5); //6
  sds1.set_value(1,c6); 
  bool test6 = (abs(sds1.energie() - 87) < 1e-8); //
  
  complexe c7(2,-6); //7
  sds2.set_value(1,c7);
  complexe c8(93,-4);
  complexe c9;
  c9 = (sds1,sds2);
  bool test7 = (c8 == c9); //
  
  if (test1 && test2 && test3 && test4 && test5 && test6 && test7)
    return 1;
  else
    return 0;
}

int signal_discret_stl::testu_3(){ //test des méthodes avancées et de la transformée inverse
  complexe zero(0,0);

  complexe c1(1,-2), c2(-3,4), c3(5,-6), c4(-7,8); //1
  signal_discret_stl sds1(4);
  sds1.set_value(0,c1); sds1.set_value(1,c2); sds1.set_value(2,c3); sds1.set_value(3,c4);
  complexe c5(-4,4), c6(-8,0), c7(16,-20), c8(0,8);
  complexe * tfd = sds1.tfd();
  bool test1 = (tfd[0] == c5 && tfd[1] == c6 && tfd[2] == c7 && tfd[3] == c8); //

  signal_discret_stl sds2 = tfd_inverse_stl(tfd,4); //2
  bool test2 = (sds1.get_value(0) == sds2.get_value(0) && sds1.get_value(1) == sds2.get_value(1) && sds1.get_value(2) == sds2.get_value(2) && sds1.get_value(3) == sds2.get_value(3));
  delete [] tfd; //

  complexe ca(1,2), cb(3,4), cc(5,6), cd(7,8); //3
  signal_discret_stl sdsa(2), sdsb(2), sdsc;
  sdsa.set_value(0,ca); sdsa.set_value(1,cb); sdsb.set_value(0,cc); sdsb.set_value(1,cd);
  sdsc = sdsa.convolution(sdsb);
  complexe caa(-7,16), cbb(-18,60);
  bool test3 = (sdsc.get_value(0) == caa && sdsc.get_value(1) == cbb); //
  
  signal_discret_stl sds6(4), sds7, sds8; //4
  sds6.set_value(0,ca); sds6.set_value(1,cb); sds6.set_value(2,cc); sds6.set_value(3,cd);
  sds7 = sds6.translation(2); sds8 = sds6.translation(-1);
  bool test4 = (sds7.get_value(0) == zero & sds7.get_value(1) == zero && sds7.get_value(2) == ca && sds7.get_value(3) == cb && sds8.get_value(0) == cb && sds8.get_value(1) == cc && sds8.get_value(2) == cd && sds8.get_value(3) == zero); //

  signal_discret_stl sds9; //5
  sds9 = sds6.modulation(3);
  complexe ce(-1.27223251272,-1.838864985141), cf(-3.534457522041,-3.536609962222), cg(-5.796682531361,-5.234354939306), ch(-8.058907540682,-6.932099916384);
  bool test5 = (sds9.get_value(0) == ce && sds9.get_value(1) == cf && sds9.get_value(2) == cg && sds9.get_value(3) == ch); //
  
  if (test1 && test2 && test3 && test4 && test5)
    return 1;
  else
    return 0;
}

void signal_discret_stl::all_testu(){
  signal_discret_stl sds;
  int nb_tests = 3;
  int nb_reussis = 0;
  nb_reussis += sds.testu_1();
  nb_reussis += sds.testu_2();
  nb_reussis += sds.testu_3();
  cout << "SDS/ " << nb_reussis << " tests sur " << nb_tests << " reussis\n";
}


