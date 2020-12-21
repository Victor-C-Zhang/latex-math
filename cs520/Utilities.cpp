#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define endl '\n'
#define int long long int

pair<int,double> find_j(double beta) {
  double maxval = INT_MIN;
  int j = 0;

  double betas[10] {};
  betas[1] = beta;
  for (int i=1;i<9;++i) {
    betas[i+1] = betas[i]*i*beta/(10-10*beta+beta*i);
  }
  for (int i=1;i<=9;++i) {
    double temp = 101;
    for (int j = 1; j < i; ++j) {
      temp += betas[j]*(1000-100*j)/(10-10*beta+j*beta);
    }
    temp -= betas[i]*255;
    if (temp/(1-betas[i]*beta) > maxval) {
      maxval = temp/(1-betas[i]*beta);
      j = i;
    }
  }
  return {j,maxval};
}

vector<double> utilities(double beta, int j) {
  double betas[10] {};
  betas[1] = beta;
  for (int i=1;i<9;++i) {
    betas[i+1] = betas[i]*i*beta/(10-10*beta+beta*i);
  }
  double unew = 101;
  for (int k = 1; k < j; ++k) {
    unew += betas[k]*(1000-100*k)/(10-10*beta+k*beta);
  }
  unew -= betas[j]*255;
  unew = unew/(1-betas[j]*beta);
  double uused[10];
  uused[1] = (unew-101)/beta;
  for (int i=1;i<j;++i) {
    uused[i+1] = (uused[i] - 100 + 10*i - beta*(10-i)/10*uused[i])*10/i/beta;
  }
  vector<double> retval;
  retval.push_back(unew);
  for (int i = 1; i <= j; ++i) {
    retval.push_back(uused[i]);
  }
  return retval;
}

double break_even(double beta) {
  double betas[10] {};
  betas[1] = beta;
  for (int i=1;i<9;++i) {
    betas[i+1] = betas[i]*i*beta/(10-10*beta+beta*i);
  }
  double ureplace;
  double l = 0, r = 100000;
  while (l < r) {
    double maxval = INT_MIN;
    int j;
    for (int i=1;i<=9;++i) {
      double temp = 101;
      for (int j = 1; j < i; ++j) {
        temp += betas[j]*(1000-100*j)/(10-10*beta+j*beta);
      }
      temp -= betas[i]*(l+r)/2;
      if (temp/(1-betas[i]*beta) > maxval) {
        maxval = temp/(1-betas[i]*beta);
        j = i;
      }
    }
    maxval = beta*maxval - (l+r)/2;
    if (abs(maxval) < 0.000001) break;
    if (maxval > 0) l = (l+r)/2;
    else r = (l+r)/2;
  }
  return (l+r)/2;
}

signed main(){
  cout << "-------------- SECTION 1 AND 2 --------------" << endl;
  auto best = find_j(0.9);
  cout << "Found optimal policy for beta = " << 0.9 << endl;
  cout << "j = " << best.first << " with max utility " << best.second << endl;
  cout << endl;
  auto utils = utilities(0.9, best.first);
  cout << "Utilities for j = " << best.first << endl;
  cout << "New: " << utils[0] << endl;
  for (int i=1;i<=best.first;++i) cout << "Used" << i << ": " << utils[i] << endl;
  cout << endl;

  cout << "----------------- SECTION 4 -----------------" << endl;
  cout << "Optimal policies for given beta" << endl;
  double betas[] = {0.1,0.3,0.5,0.7,0.9,0.99,0.999,0.9999,0.99999};
  for (double beta : betas) {
    best = find_j(beta);
    cout << beta << ": " << "j = " << best.first << " with max utility " << best.second << endl;
  }
  cout << endl;

  cout << "------------------- BONUS -------------------" << endl;
  cout << "Break even cost for beta = 0.9" << endl;
  cout << break_even(0.9) << endl;
  cout << endl;
  return 0;
}
