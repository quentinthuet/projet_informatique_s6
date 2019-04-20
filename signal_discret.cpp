#include <cmath>
#include <iostream>
#include "complexe.hpp"
#include "signal_discret.hpp"
using namespace std;


//////////ACCESSEURS//////////

int signal_discret::get_size(){
  return M_size;
}

complexe signal_discret::get_value(int i){
  complexe res(0,0);
  if (i < M_size && i >= 0)
    res = M_values[i];
  return M_values[i];
}



//////////MUTATEURS//////////

void signal_discret::set_value(int i, complexe c){
  complexe zero(0,0);
  if (i < M_size) //1
    M_values[i] = c; //
  else {
    complexe * temp = new complexe[M_size]; //2
    for (int j = 0; j < M_size; j++){
      temp[j] = M_values[j];
    } //
    delete [] M_values; //3
    M_values = new complexe[i + 1]; //
    for (int j = 0; j < M_size; j++){ //4
      M_values[j] = temp[j];
    }
    for (int j = M_size; j < i; j++){
      M_values[j] = zero;
    }
    M_values[i] = c; //
    delete [] temp; //5 //
    M_size = i + 1; //6 //
  }
}



//////////METHODES ELEMENTAIRES//////////

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



//////////METHODES AVANCEES//////////

complexe * signal_discret::tfd(){
  complexe * res = new complexe[M_size];
  complexe zero(0,0);
  for (int k = 0; k < M_size; k++){ //1
    res[k] = zero; //
    for (int n = 0; n < M_size; n++){ //2
      complexe temp(cos(-2 * M_PI * n * k /((double) M_size)), sin(-2 * M_PI * n * k /((double) M_size)));
      res[k] = res[k] + (M_values[n] * temp);
    } //
  }
  return res;
}

signal_discret signal_discret::convolution(signal_discret & sd){
  int size_max; //1
  size_max = max(M_size, sd.M_size); //
  signal_discret res(size_max); //2
  for (int n = 0; n < size_max; n++) { //3
    for (int k = 0; k < size_max; k++) { //
      if (k >= M_size || (n - k) < 0 || (n - k) >= sd.M_size ) //4
	continue; 
      else
	res.set_value(n,res.get_value(n) + this->get_value(k)*sd.get_value(n - k)); //
    }
  }
  return res;
}

signal_discret signal_discret::translation(const int k0){
  signal_discret res(M_size);
  complexe zero(0,0);
  for (int k = 0; k < M_size; k++){ //1
    if ((k - k0 >= 0) && (k - k0 < M_size))
      res.M_values[k] = M_values[k - k0];
    else
      res.M_values[k] = zero;
  } //
  return res;
}

signal_discret signal_discret::modulation(const double k0){
  signal_discret res(M_size);
  for (int k = 0; k < M_size; k++){ //1
    complexe temp(cos(k0),sin(k0));
    res.M_values[k] = temp * M_values[k]; //
  }
  return res;
}


//////////FONCTIONS EXTERNES A LA CLASSE//////////

signal_discret tfd_inverse(complexe * c_tab, const int size){
  complexe * res = new complexe[size]; //1 //
  complexe zero(0,0);
  complexe quotient(1 /((double) size),0);
  for (int n = 0; n < size; n++){ //2
    res[n] = zero; //
    for (int k = 0; k < size; k++){ //3
      complexe temp(cos(2 * M_PI * n * k /((double) size)), sin(2 * M_PI * n * k /((double) size)));
      res[n] = res[n] + (c_tab[k] * temp); //
    }
    res[n] = res[n] * quotient; //4 //
  }
  signal_discret sd_res(size); //5
  for (int i = 0; i < size; i++){
    sd_res.set_value(i,res[i]);
  }
  delete [] res; //
  return sd_res;
}



//////////OPERATEURS//////////

signal_discret & signal_discret::operator=(const signal_discret & sd){
  if (&sd != this){ //1 //
    delete [] M_values; //2 //
    M_size = sd.M_size; //3
    M_values = new complexe[M_size];
    for (int i = 0; i < M_size; i++){
      M_values[i] = sd.M_values[i];
    } //
  }
  return *this;
}

signal_discret signal_discret::operator+(const signal_discret & sd){
  int size_max,size_min; //1
  size_max = max(M_size, sd.M_size);
  size_min = min(M_size, sd.M_size); //
  signal_discret res(M_size);
  for (int i = 0; i < size_min; i++){ //2
    res.M_values[i] = M_values[i] + sd.M_values[i];
  } //
  if (size_max != size_min && size_min == M_size){ //3
    for (int i = size_min; i < size_max; i++){
      res.M_values[i] = sd.M_values[i];
    }
  }
  else if (size_max != size_min && size_min == sd.M_size){
    for (int i = size_min; i < size_max; i++){
      res.M_values[i] = M_values[i];
    }
  } //
  return res;
}

signal_discret signal_discret::operator*(const signal_discret & sd){
  int size_min; //1
  size_min = min(M_size, sd.M_size); //
  signal_discret res(M_size);
  for (int i = 0; i < size_min; i++){ //2
    res.M_values[i] = M_values[i] * sd.M_values[i];
  } //
  return res;
}

signal_discret signal_discret::operator-(const signal_discret & sd){
  int size_max,size_min; //1
  size_max = max(M_size, sd.M_size);
  size_min = min(M_size, sd.M_size); //
  signal_discret res(M_size);
  complexe zero(0,0);
  for (int i = 0; i < size_min; i++){ //2
    res.M_values[i] = M_values[i] - sd.M_values[i];
  } //
  if (size_max != size_min && size_min == M_size){ //3
    for (int i = size_min; i < size_max; i++){
      res.M_values[i] = zero - sd.M_values[i];
    }
  }
  else if (size_max != size_min && size_min == sd.M_size){
    for (int i = size_min; i < size_max; i++){
      res.M_values[i] = M_values[i];
    }
  } //
  return res;
}
complexe signal_discret::operator,(const signal_discret & sd){
  int size_min; //1
  size_min = min(M_size, sd.M_size); //
  complexe res(0,0);
  for (int i = 0; i < size_min; i++){ //2
    res = res + (M_values[i] * (sd.M_values[i]).conjugue());
  } //
  return res;  
}



//////////TESTEURS//////////

int signal_discret::testu_1(){ //test des constructeurs, destructeurs, accesseurs et mutateurs
  signal_discret sd1(5); //1 //
  signal_discret sd2; //2 //
  signal_discret sd3(sd1); //3
  signal_discret sd4(sd2); //
  bool test1 = (sd1.get_size() == 5); //4 //
  complexe c1(0,0), c2(5,6); //5 
  bool test2 = (sd1.get_value(3) == c1); //
  sd1.set_value(3,c2); sd1.set_value(7,c2); //6
  bool test3 = (sd1.get_value(3) == c2 && sd1.get_value(6) == c1 && sd1.get_value(7) == c2 && sd1.get_size() == 8); //
  if (test1 && test2 && test3)
    return 1;
  else
    return 0;
}

int signal_discret::testu_2(){//test des opérateurs et des méthodes élémentaires
  signal_discret sd1(5);
  signal_discret sd2;
  complexe c1(5,6); //1
  sd1.set_value(3, c1);
  sd2 = sd1; 
  bool test1 = (sd2.get_value(3) == c1); //
  signal_discret sd3; //2
  sd3 = (sd1 + sd2); 
  complexe c2(10,12);
  bool test2 = (sd3.get_value(3) == c2); //
  sd3 = (sd1 * sd2); //3
  complexe c3(-11,60);
  bool test3 = (sd3.get_value(3) == c3); //
  sd3 = (sd1 - sd2); //4
  complexe c4(0,0);
  bool test4 = (sd3.get_value(3) == c4); //
  sd3 = sd1.conjugue(); //5
  complexe c5(5,-6);
  bool test5 = (sd3.get_value(3) == c5); //
  complexe c6(1,-5); //6
  sd1.set_value(1,c6); 
  bool test6 = (abs(sd1.energie() - 87) < 1e-8); //
  complexe c7(2,-6); //7
  sd2.set_value(1,c7);
  complexe c8(93,-4);
  complexe c9;
  c9 = (sd1,sd2);
  bool test7 = (c8 == c9); //
  if (test1 && test2 && test3 && test4 && test5 && test6 && test7)
    return 1;
  else
    return 0;
}

int signal_discret::testu_3(){ //test des méthodes avancées et de la transformée inverse
  complexe zero(0,0);
  complexe c1(1,-2), c2(-3,4), c3(5,-6), c4(-7,8); //1
  signal_discret sd1(4);
  sd1.set_value(0,c1); sd1.set_value(1,c2); sd1.set_value(2,c3); sd1.set_value(3,c4);
  complexe c5(-4,4), c6(-8,0), c7(16,-20), c8(0,8);
  complexe * tfd = sd1.tfd();
  bool test1 = (tfd[0] == c5 && tfd[1] == c6 && tfd[2] == c7 && tfd[3] == c8); //
  signal_discret sd2 = tfd_inverse(tfd,4); //2
  bool test2 = (sd1.get_value(0) == sd2.get_value(0) && sd1.get_value(1) == sd2.get_value(1) && sd1.get_value(2) == sd2.get_value(2) && sd1.get_value(3) == sd2.get_value(3));
  delete [] tfd; //
  complexe ca(1,2), cb(3,4), cc(5,6), cd(7,8); //3
  signal_discret sda(2), sdb(2), sdc;
  sda.set_value(0,ca); sda.set_value(1,cb); sdb.set_value(0,cc); sdb.set_value(1,cd);
  sdc = sda.convolution(sdb);
  complexe caa(-7,16), cbb(-18,60);
  bool test3 = (sdc.get_value(0) == caa && sdc.get_value(1) == cbb); //
  signal_discret sd6(4), sd7, sd8; //4
  sd6.set_value(0,ca); sd6.set_value(1,cb); sd6.set_value(2,cc); sd6.set_value(3,cd);
  sd7 = sd6.translation(2); sd8 = sd6.translation(-1);
  bool test4 = (sd7.get_value(0) == zero & sd7.get_value(1) == zero && sd7.get_value(2) == ca && sd7.get_value(3) == cb && sd8.get_value(0) == cb && sd8.get_value(1) == cc && sd8.get_value(2) == cd && sd8.get_value(3) == zero); //
  signal_discret sd9; //5
  sd9 = sd6.modulation(3);
  complexe ce(-1.27223251272,-1.838864985141), cf(-3.534457522041,-3.536609962222), cg(-5.796682531361,-5.234354939306), ch(-8.058907540682,-6.932099916384);
  bool test5 = (sd9.get_value(0) == ce && sd9.get_value(1) == cf && sd9.get_value(2) == cg && sd9.get_value(3) == ch); //
  if (test1 && test2 && test3 && test4 && test5)
    return 1;
  else
    return 0;
}
  
void signal_discret::all_testu(){
  signal_discret sd;
  int nb_tests = 3;
  int nb_reussis = 0;
  nb_reussis += sd.testu_1();
  nb_reussis += sd.testu_2();
  nb_reussis += sd.testu_3();
  cout << "SD/ " << nb_reussis << " tests sur " << nb_tests << " reussis\n";
}


