#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>


/*
 * Returns a pair (V_0, \Delta_0).
 */
std::pair<double, double> pricer(int N, double S_0, double u, double d,
double r, double (*f)(double))
{
  std::vector<std::vector<double>> V(N + 1, std::vector<double>(N + 1));
  for (int i = 0; i <= N; ++i) {
    V[N][i] = f(S_0 * pow(u, N - i) * pow(d, i));
  }

  double p_tilde = (1.0 + r - d) / (u - d);
  double q_tilde = 1.0 - p_tilde;
  for (int n = N - 1; n >= 0; --n) {
    for (int i = 0; i <= n; ++i) {
      V[n][i] = 1.0 / (1.0 + r) * (p_tilde*V[n+1][i] + q_tilde*V[n+1][i+1]);
    }
  }

  return {V[0][0], (V[1][0] - V[1][1]) / (S_0 * (u - d))};
}

double call_5(double s) {
  return std::max(s - 5, 0.0);
}

double rebate_148(double s) {
  return (s >= 148.0) ? 1.0 : 0.0;
}

double put_110(double s) {
  return std::max(110 - s, 0.0);
}

int main() {
  std::cout << "5a: V_0 = ";
  std::cout << pricer(2, 4.0, 2, 0.5, 0.25, call_5).first << "\n";

  std::cout << "5b: V_0 = ";
  std::cout << pricer(20, 100.0, 1.02, 0.98, 0.01, rebate_148).first << "\n";
  
  auto res = pricer(20, 100.0, 1.02, 0.98, 0.01, put_110);
  std::cout << "5c: V_0 = " << res.first << "\n";
  std::cout << "5d: \\Delta_0 = " << res.second << std::endl;
}