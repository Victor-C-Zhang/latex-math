#include <cmath>
#include <iostream>
#include <optional>
#include <unordered_map>

typedef long long int ll;

ll powmod(ll base, ll exp, ll mod) {
  ll res = 1;
  ll b = base % mod;
  while (exp > 0) {
    if (exp % 2)
      res = (res*b)%mod;
    exp >>= 1;
    b = (b*b)%mod;
  }
  return res;
}

std::optional<ll> shanks(ll g, ll h, ll p) {
  ll n = static_cast<ll>(std::ceil(std::sqrt(p)));
  auto table = std::unordered_map<ll, ll>{};
  ll val = 1;
  for (ll i = 0; i < n; ++i) {
    table[val] = i;
    val = (val*g)%p;
  }
  ll gn_inv = powmod(g, p-1-n, p);
  val = h;
  for (ll i = 0; i < n; ++i) {
    if (table.find(val) != table.end()) {
      return {i*n + table[val]};
    }
    val = (val*gn_inv)%p;
  }
  return {};
}

int main() {
  ll g, h, p;
  std::cout << "g: ";
  std::cin >> g;
  std::cout << "h: ";
  std::cin >> h;
  std::cout << "p: ";
  std::cin >> p;

  auto ans = shanks(g, h, p);
  if (!ans.has_value())
    std::cout << "Could not find log_" << g << "(" << h
    << ") mod " << p << std::endl;
  else
    std::cout << "log_" << g << "(" << h << ") = "
    << ans.value() << " mod " << p << std::endl;
  return 0;
}