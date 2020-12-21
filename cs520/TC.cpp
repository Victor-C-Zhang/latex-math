#include <iostream>
#include <tuple>
#include <vector>
#include <climits>
#include <cassert>

using namespace std;

#define endl '\n'
#define int long long int

const int dim = 7;
typedef pair<int,int> Square;
typedef tuple<Square,Square,Square> Config;

pair<int,int> operator+(const pair<int,int>& lhs, const pair<int,int>& rhs) {
  return {lhs.first+rhs.first, lhs.second+rhs.second};
}

/** 
 * Finds the reachable configurations of a given configuration.
 * @param config the given configuration.
 * @return a set of configurations grouped by s'.
 */
vector<vector<Config>> neighbors(Config config) {
  Square scards[4] = {{-1,0},{1,0},{0,-1},{0,1}};
  Square cards[5] = {{-1,0},{1,0},{0,0},{0,-1},{0,1}};
  vector<vector<Config>> retval;
  vector<Config> temp;
  Square s, d1, d2;
  bool modified;
  bool trapped = true;
  for (auto & scard : scards) {
    s = get<2>(config) + scard;
    if (s.first < 0 || s.first >= dim || s.second < 0 || s.second >= dim) continue;
    if (s == get<0>(config) || s == get<1>(config)) continue;
    temp.clear();
    modified = false;
    for (auto & card : cards) {
      d1 = get<0>(config) + card;
      if (d1.first < 0 || d1.first >= dim || d1.second < 0 || d1.second >= dim) continue;
      if (d1 == s) continue;
      for (auto & card2 : cards) {
        d2 = get<1>(config) + card2;
        if (d2.first < 0 || d2.first >= dim || d2.second < 0 || d2.second >= dim) continue;
        if (d2 == s || d2 == d1) continue;
        temp.emplace_back(d1,d2,s);
        modified = true;
      }
    }
    if (modified) {
      retval.push_back(temp);
      trapped = false;
    }
  }
  if (!trapped) return retval;

  // otherwise, s has nowhere to go
  s = get<2>(config);
  vector<vector<Config>> altret;
  for (auto & card : cards) {
    d1 = get<0>(config) + card;
    if (d1.first < 0 || d1.first >= dim || d1.second < 0 || d1.second >= dim) continue;
    if (d1 == s) continue;
    for (auto & card2 : cards) {
      d2 = get<1>(config) + card2;
      if (d2.first < 0 || d2.first >= dim || d2.second < 0 || d2.second >= dim) continue;
      if (d2 == s || d2 == d1) continue;
      temp.emplace_back(d1,d2,s);
    }
  }
  altret.push_back(temp);
  return altret;
}

signed main(){
  double C[2][dim][dim][dim][dim][dim][dim]; // d1, d2, s
  // init first matrix
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      for (int k = 0; k < dim; ++k) {
        for (int l = 0; l < dim; ++l) {
          for (int m = 0; m < dim; ++m) {
            for (int p = 0; p < dim; ++p) {
              C[0][i][j][k][l][m][p] = INT_MAX;
            }
          }
        }
      }
    }
  }
  for (int i = 1; i < dim; ++i) {
    for (int j = 1; j < dim; ++j) {
      C[0][i-1][j][i][j-1][i][j] = C[0][i][j-1][i-1][j][i][j] = 2*(dim-1) -
            i - j;
    }
  }

  // value iteration
  int which;
  double tempval;
  for (int epoch = 0; epoch < 50; ++epoch) {
    which = (epoch+1)%2;
    // s
    for (int i = dim-1; i >= 0; --i) {
      for (int j = dim-1; j >= 0; --j) {
        // d1
        for (int k = dim-1; k >= 0; --k) {
          for (int l = dim-1; l >= 0; --l) {
            if (i==k && j==l) continue;
            // d2
            for (int m = dim-1; m >= 0; --m) {
              for (int p = dim-1; p >= 0; --p) {
                if ((i==m && j==p) || (k==m && l==p)) continue;
                if ((i == 6 && j == 6 && k == 5 && l == 6 && m == 6 && p == 5)
                      || (i == 6 && j == 6 && k == 6 && l == 5 && m == 5 && p ==6)) {
                  C[which][k][l][m][p][i][j] = 0;
                  continue;
                }
                tempval = 0;
                auto neighs = neighbors({{k,l},{m,p},{i,j}});
                for (const auto& vec : neighs) {
                  double minval = INT_MAX;
                  for (const Config& cfg : vec) {
                    minval = min(minval, C[epoch%2][get<0>(cfg).first][get<0>(cfg).second]
                    [get<1>(cfg).first][get<1>(cfg).second]
                    [get<2>(cfg).first][get<2>(cfg).second]);
                  }
                  tempval += minval;
                }
                C[which][k][l][m][p][i][j] = 1 + tempval/neighs.size();

              }
            }
          }
        }
      }
    }
  }

  // verify no values are "infinite"
  int verifier = 0;
  int num_combos = 110544;
  // find the emiprically worst starting config
  double mostbad = -1;
  int mostbadidx = 0;
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      for (int k = 0; k < dim; ++k) {
        for (int l = 0; l < dim; ++l) {
          for (int m = 0; m < dim; ++m) {
            for (int p = 0; p < dim; ++p) {
              if (C[0][i][j][k][l][m][p] != INT_MAX) {
                cout << C[0][i][j][k][l][m][p] << endl;
                ++verifier;
                if (C[0][i][j][k][l][m][p] > mostbad) {
                  mostbad = C[0][i][j][k][l][m][p];
                  mostbadidx = p+m*10+l*100+k*1000+j*10000+i*100000;
                }
              }
            }
          }
        }
      }
    }
  }
  assert(verifier == num_combos);
  cout << "Example initial state: " << C[1][0][6][6][3][4][0] << endl;
  cout << "Empirically worst initial state: " << mostbadidx << " with T(C) = " << mostbad << endl;
  return 0;
}
