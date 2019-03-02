#include <cmath>
#include <iostream>
#include "complexe.hpp"

using namespace std;

bool complexe::reel_pure(){
  bool res = false;
  if( i == 0.0) { res = true; }
  return res;
};
bool complexe::img_pure(){
  bool res = false;
  if( r == 0.0) { res = true; }
  return res;
};

double complexe::module(){
  double res=0;
  return sqrt(r*r+i*i);
};

complexe complexe::conjugue(){
  complexe res;
  res.r = r;
  res.i = -i;
  return res;
} 

complexe complexe::modify_reel(double reel){
  r = reel;
  return *this;
};
complexe complexe::modify_img(double img){
  i = img;
  return *this;
};

double complexe:: reel(){
  return r;
}
double complexe:: img(){
  return i;
}

complexe complexe:: operator + (complexe x){
  complexe res;
  res.r = r+x.r;
  res.i = i+x.i;
  return res;
};

complexe complexe:: operator * (complexe x){
  complexe res;
  res.r = r*x.r-i*x.i;
  res.i = r*x.i+i*x.r;
  return res;
};

complexe complexe:: operator - (complexe x){
  complexe res;
  res.r = r-x.r;
  res.i = i-x.i;
  return res;
};

complexe complexe :: operator / (complexe x){
  complexe res;
  double mod;
  mod = x.module();
  res.r = (r*x.r+i*x.i)/(mod*mod);
  res.i = (i*x.r-x.i*r)/(mod*mod);
  return res;
};

complexe & complexe:: operator = (const complexe & x){
  if(&x != this){
    r = x.r;
    i = x.i;
  }
  return *this;
};

bool complexe:: operator < (complexe x){
  bool res = false;
  if(this->module() < x.module() ) { res = true;}
  return res;
};

bool complexe:: operator > (complexe x){
  bool res = false;
  if(this->module() > x.module()) { res = true;}
  return res;
};

bool complexe:: operator == (complexe x){
  bool res = false;
  if(this->module() == x.module()) { res = true;}
  return res;
};

ostream & operator<<(ostream & out, const complexe & x){
  out<<x.r<<"+i "<<x.i;
  return out;
}

istream & operator>>(istream & in,complexe & x){
  cout<<" partie reel:"<<endl;
  in>>x.r;
  cout<<" partie img:"<<endl;
  in>>x.i;
  return in;
}

complexe operator *(double a, const complexe & x){
  complexe res;
  res.r = a*x.r;
  res.i = a*x.i;
  return res;
}

int complexe:: testu_1(){
  complexe x1(1,1);
  complexe x2(1,-2);
  double mod=0.0;
  
  *this = x1;
  *this = *this + x2 ; // *this = 2 -i
  x1 = x1.conjugue(); // x1  = 1 - i
  *this = *this * x1 ; // *this = 1 -3i
  mod = this->module(); // sqrt(10)
  *this = *this / x1; // *this = (1-3i)/(1-i) = (4- 2i)/10
  *this = (mod*mod) * (*this); // *this = 5(3-i)/2

  if(this->reel() == 4 && this->img() == -2) { return 0; }
  else { return 1; }
}

int complexe:: testu_2(){
  complexe x1(1,1);
  bool a=false,b=false,c=false,d=false;
  
  *this = x1;
  a= this->reel_pure();
  b= this->img_pure();
  this->modify_reel(0.0);
  c = this->img_pure();
  this->modify_reel(1.0);
  this->modify_img(0.0);
  d = this->reel_pure();

  if( a+b+c+d == 2) { return 0; }
  else { return 1; }

  return 0; 
}

int complexe:: testu_3(){
  complexe x1(1,1);
  complexe x2(1,2);
  complexe x3(sqrt(2.0),0.0);
  bool a=false,b=false,c=false;

  *this = x1;
  a = (*this < x2);
  b = (x2 > *this);
  c = (x3 == *this);
  if( a+b+c == 3) { return 0; }
  else { return 1; }

  return 0; 
}

int complexe:: all_testsu(){
  int c=0,t=0;
  complexe x;
  c=x.testu_1(); t = t +c;
  c=x.testu_2(); t = t +c;
  c=x.testu_3(); t = t +c;
  cout<<"Tests unitaires réussis, classe complexe: "<<3-t<<"/3"<<endl;
  return 0;
}
