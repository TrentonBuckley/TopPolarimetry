#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// working arrays
const int nxmax = 1000;
double sfit1[nxmax] = {0};
double sfit2[nxmax] = {0};
double dfit[nxmax] = {0};
int nxfit = 0;

double xlog(double par1, double par2)
{
  double sum = 0;
  for (int ix = 0; ix<nxfit; ++ix) {
    double pred = par1*sfit1[ix] + par2*sfit2[ix];
    if (pred>0) sum += pred - dfit[ix]*log(pred);
  }
  return 2.*sum;
}

void print(double par1, double par2)
{
  cout << "par1=" << par1 << ", par2=" << par2 << ", LLH=" << xlog(par1,par2) << endl;
}

void fill()
{
  nxfit = 12;

  ifstream fin_template1("template1.txt");
  for (int i = 0; i<nxfit; ++i) {
    fin_template1 >> sfit1[i];
  }

  ifstream fin_template2("template2.txt");
  for (int i = 0; i<nxfit; ++i) {
    fin_template2 >> sfit2[i];
  }

  ifstream fin_data("data.txt");
  for (int i = 0; i<nxfit; ++i) {
    fin_data >> dfit[i];
  }
}

int main()
{
  // load data and templates
  fill();

  // print some points
  print(1.,1.);
  print(1.,2.);
  print(1.,3.);
  print(2.,1.);
  print(2.,2.);
  print(2.,3.);
  print(3.,1.);
  print(3.,2.);
  print(3.,3.);
}
