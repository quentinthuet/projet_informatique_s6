#include <cmath>
#include <iostream>
#include <random>
#include "complexe.hpp"
#include "signal_discret.hpp"
#include "signal_continu.hpp"
#include "filtre.hpp"
using namespace std;

int main(){
  default_random_engine generator;
  normal_distribution<double> distribution(5.0,2.0);
  for (int i = 0; i < 100; i++) {
    cout << distribution(generator) << endl;
  }
}
