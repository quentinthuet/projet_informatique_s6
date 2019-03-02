#include <cmath>
#include <iostream>
#include "complexe.hpp"
#include "signal_discret.hpp"
using namespace std;

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

//accesseurs
int signal_discret::get_size(){
  return M_size;
}

complexe signal_discret::get_value(int i){
  return M_values[i];
}

//mutateur
void signal_discret::set_value(int i, complexe c){
  if (i < M_size) M_values[i] = c;
}

//méthodes
signal_discret signal_discret::conjugue(){
  signal_discret res(M_size);
  for (int i = 0; i < M_size; i++){
    res.M_values[i] = M_values[i].conjugue();
  }
  return res;
}

double signal_discret::energie(){
  double res = 0.0;
  for (int i = 0; i < M_size; i++){
    res += (M_values[i].module()) * (M_values[i].module());
  }
  return res;
}

complexe * signal_discret::tfd(){
  complexe * res = new complexe[M_size];
  complexe zero(0,0);
  for (int k = 0; k < M_size; k++){
    res[k] = zero;
    for (int n = 0; n < M_size; n++){
      complexe temp(cos(-2 * M_PI * n * k /((double) M_size)), sin(-2 * M_PI * n * k /((double) M_size)));
      res[k] = res[k] + (M_values[n] * temp);
    }
  }
  return res;
}

signal_discret signal_discret::convolution(const signal_discret & sd){
  signal_discret res(M_size + sd.M_size - 1);
  int res_size;
  if (M_size <= sd.M_size) res_size = M_size;
  else res_size = sd.M_size;
  complexe zero(0,0);
  for (int n = 0; n < M_size + sd.M_size - 1; n++){
    res.M_values[n] = zero;
    for (int m = 0; m < res_size; m++){
      res.M_values[n] = res.M_values[n] + M_values[m] * sd.M_values[(n - m)%res_size];
    }
  }
  return res;
}

signal_discret & signal_discret::translation(const int k0){
  complexe * temp = new complexe[M_size];
  for (int k = 0; k < M_size; k++){
    M_values[k] = M_values[(k - k0)%M_size];
  }
  delete [] M_values;
  M_values = temp;
  return *this;
}


//opérateurs
signal_discret & signal_discret::operator=(const signal_discret & sd){
  if (&sd != this){
    delete [] M_values;
    M_size = sd.M_size;
    M_values = new complexe[M_size];
    for (int i = 0; i < M_size; i++){
      M_values[i] = sd.M_values[i];
    }
  }
  return *this;
}

signal_discret signal_discret::operator+(const signal_discret & sd){
  if (M_size != sd.M_size){
    cout << "SD/Sizes don't match\n";
    exit;
  }
  else{
    signal_discret res(M_size);
    for (int i = 0; i < M_size; i++){
      res.M_values[i] = M_values[i] + sd.M_values[i];
    }
    return res;
  }
}

signal_discret signal_discret::operator*(const signal_discret & sd){
  if (M_size != sd.M_size){
    cout << "SD/Sizes don't match\n";
    exit;
  }
  else{
    signal_discret res(M_size);
    for (int i = 0; i < M_size; i++){
      res.M_values[i] = M_values[i] * sd.M_values[i];
    }
    return res;
  }
}    

signal_discret signal_discret::operator-(const signal_discret & sd){
  if (M_size != sd.M_size){
    cout << "SD/Sizes don't match\n";
    exit;
  }
  else{
    signal_discret res(M_size);
    for (int i = 0; i < M_size; i++){
      res.M_values[i] = M_values[i] - sd.M_values[i];
    }
    return res;
  }
}

complexe signal_discret::operator,(const signal_discret & sd){
  if (M_size != sd.M_size){
    cout << "SD/Sizes don't match\n";
    exit;
  }
  else{
    complexe res(0,0);
    for (int i = 0; i < M_size; i++){
      res = res + (M_values[i] * (sd.M_values[i]).conjugue());
    }
    return res;
  }
}

//fonctions extérieures à la classe
signal_discret tfd_inverse(complexe * c_tab, const int size){
  complexe * res = new complexe[size];
  complexe zero(0,0);
  complexe quotient(1 /((double) size),0);
  for (int n = 0; n < size; n++){
    res[n] = zero;
    for (int k = 0; k < size; k++){
      complexe temp(cos(2 * M_PI * n * k /((double) size)), sin(2 * M_PI * n * k /((double) size)));
      res[n] = res[n] + (c_tab[k] * temp);
    }
    res[n] = res[n] * quotient;
  }
  signal_discret sd_res(size);
  for (int i = 0; i < size; i++){
    sd_res.set_value(i,res[i]);
  }
  delete [] res;
  return sd_res;
}
  
  

//testeurs

int signal_discret::testu_1(){ //test des constructeurs, destructeurs, accesseurs et mutateurs
  signal_discret sd1(5);
  signal_discret sd2;
  signal_discret sd3(sd2);
  bool test1 = (sd1.get_size() == 5);
  complexe c1(0,0), c2(5,6);
  bool test2 = (sd1.get_value(3) == c1);
  sd1.set_value(3,c2);
  bool test3 = (sd1.get_value(3) == c2);
  if (test1 && test2 && test3) return 1;
  else return 0;
}

int signal_discret::testu_2(){//test des opérateurs et des méthodes élémentaires
  signal_discret sd1(5);
  signal_discret sd2;
  complexe c1(5,6);
  sd1.set_value(3, c1);
  sd2 = sd1;
  bool test1 = (sd2.get_value(3) == c1);
  signal_discret sd3;
  sd3 = (sd1 + sd2);
  complexe c2(10,12);
  bool test2 = (sd3.get_value(3) == c2);
  sd3 = (sd1 * sd2);
  complexe c3(-11,60);
  bool test3 = (sd3.get_value(3) == c3);
  sd3 = (sd1 - sd2);
  complexe c4(0,0);
  bool test4 = (sd3.get_value(3) == c4);
  sd3 = sd1.conjugue();
  complexe c5(5,-6);
  bool test5 = (sd3.get_value(3) == c5);
  complexe c6(1,-5);
  sd1.set_value(1,c6);
  bool test6 = (abs(sd1.energie() - 87) < 1e-8);
  complexe c7(2,-6);
  sd2.set_value(1,c7);
  complexe c8(93,-4);
  complexe c9;
  c9 = (sd1,sd2);
  bool test7 = (abs(c8.module() - c9.module()) < 1e-8);//on teste l'égalité de la même manière qu'avec l'opérateur == de la classe complexe, mais en acceptant l'erreur due aux approximations machine
  if (test1 && test2 && test3 && test4 && test5 && test6 && test7) return 1;
  else return 0;
}

int signal_discret::testu_3(){ //test des méthodes avancées
  complexe c1(1,0), c2(0,0), c3(0,0), c4(1,0);
  signal_discret sd1(4);
  sd1.set_value(0,c1); sd1.set_value(1,c2); sd1.set_value(2,c3); sd1.set_value(3,c4);
  complexe c5(2,0), c6(1,1), c7(0,0), c8(1,-1);
  complexe * tfd = sd1.tfd();
  bool test1 = (abs(tfd[0].module() - c5.module()) < 1e-8 && abs(tfd[1].module() - c6.module()) < 1e-8 && abs(tfd[2].module() - c7.module()) < 1e-8 && abs(tfd[3].module() - c8.module()) < 1e-8);
  delete [] tfd;
  complexe c9(2,0), c10(-1,-1), c11(0,0), c12(-1,1);
  complexe * c_tab1 = new complexe[4];
  c_tab1[0] = c9; c_tab1[1] = c10; c_tab1[2] = c11; c_tab1[3] = c12;
  signal_discret sd2(4);
  sd2 = tfd_inverse(c_tab1, 4);
  bool test2 = (abs((sd2.get_value(0)).module() - c2.module()) < 1e-8 && abs((sd2.get_value(1)).module() - c1.module()) < 1e-8 && abs((sd2.get_value(2)).module() - c1.module()) < 1e-8 && abs((sd2.get_value(3)).module() - c2.module()) < 1e-8);
  delete [] c_tab1;
  signal_discret sd3(4), sd4(3);
  complexe c13(3,0), c14(-1,0);
  sd3.set_value(0,c1); sd3.set_value(1,c5); sd3.set_value(2,c5); sd3.set_value(3,c13); sd4.set_value(0,c5); sd4.set_value(1,c14); sd4.set_value(2,c13);
  signal_discret sd5;
  sd5 = sd3.convolution(sd4);
  cout << sd5.get_value(0) << " , " << sd5.get_value(1) << " , " << sd5.get_value(2) << " , " << sd5.get_value(3) << " , " << sd5.get_value(4) << " , " << sd5.get_value(5) << " , " <</* sd5.get_value(6) <<*/ endl;
  sd3.translation(4);
  if (test1 && test2) return 1;
  else return 0;
}
  

void signal_discret::all_testu(){
  signal_discret sd;
  int nb_tests = 3;
  int nb_reussis = 0;
  nb_reussis += sd.testu_1();
  nb_reussis += sd.testu_2();
  nb_reussis += sd.testu_3();
  cout << "SD/ " << nb_reussis << " tests sur " << nb_tests << " réussis\n";
}


