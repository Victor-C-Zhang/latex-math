#include <cmath>
#include <iostream>

#define int long long int
#define f(x) ((x)*(x)+1)
// #define f(x) ((x)*(x)+2)
// #define f(x) ((x)*(x)+n-2)


int gcd (int a, int b) {
  return b ? gcd (b, a % b) : a;
}

signed main() {
  std::cout << "N: ";
  int n; std::cin >> n;
  int x = 0, y = 0;
  int cnt = 0;
  do {
    x = f(x);
    x %= n;
    y = f(y);
    y %= n;
    y = f(y);
    y %= n;
    ++cnt;
  } while (gcd(std::abs(x-y),n) == 1);
  std::cout << "k = " << cnt << std::endl;
  std::cout << "k/sqrtN = " << (double)cnt/std::sqrt(n) << std::endl;
}