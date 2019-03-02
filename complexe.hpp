#ifndef COMPLEXE_HPP
#define COMPLEXE_HPP

#include <cmath>
#include <iostream>
using namespace std;

class complexe {
  double r;
  double i;
public:
  complexe (){
    r = 0;
    i = 0;

  }
  complexe (double reel , double img){
    r = reel;  i = img;
  }
  complexe (const complexe & x){
    r = x.r;  i = x.i;
  }
  ~complexe (){
  }
  bool reel_pure();
  bool img_pure();
  complexe modify_reel(double reel);
  complexe  modify_img(double img);
  double  module();
  complexe conjugue();
  double reel();
  double img();
  complexe operator + (complexe);
  complexe operator - ( complexe);
  complexe operator * ( complexe);
  complexe operator / ( complexe);
  complexe & operator = (const complexe &);
  bool operator < (complexe);
  bool operator > (complexe);
  bool operator == (complexe);
  bool operator != (complexe);
  friend ostream & operator<<(ostream &, const complexe &);
  friend istream & operator>>(istream &, complexe &);
  friend complexe operator *(double, const complexe &);
  int testu_1();
  int testu_2();
  int testu_3();
  int all_testsu();
};
#endif
