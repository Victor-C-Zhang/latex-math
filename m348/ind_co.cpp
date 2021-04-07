#include <string>
#include <iostream>

// determines equality of s.substr(idx_s,len) and t.substr(idx_t,len).
// does no error-checking.
bool _substr_eq(const std::string& s, const std::string& t, int idx_s, int idx_t, int len) {
  for (int i=0;i<len;++i) {
    if (s[idx_s+i] != t[idx_t+i]) return false;
  }
  return true;
}

// implements index of coincidence
double _index_coincidence(std::string s, int gram) {
  int coincidences = 0;
  for (int i = 0; i < s.size()+1-gram; ++i) {
    for (int j = i+1; j < s.size()+1-gram; ++j) {
      if (_substr_eq(s,s,i,j,gram)) ++coincidences;
    }
  }
  return (double)coincidences / (double)((s.size()+1-gram)*(s.size()-gram)/2);
}

// implements mutual index of coincidence
double _mut_index_coincidence(std::string s, std::string t, int gram) {
  int coincidences = 0;
  for (int i = 0; i < s.size()+1-gram; ++i) {
    for (int j = 0; j < t.size()+1-gram; ++j) {
      if (_substr_eq(s,t,i,j,gram)) ++coincidences;
    }
  }
  return (double) coincidences / (double)((s.size()+1-gram)*(t.size()+1-gram));
}

/**
 * General function to calculate indices of coincidence.
 * @param s       the first string.
 * @param t       (optional) second string.
 * @param gram    (optional) the length to match. 1 for normal index of
 *                coincidence, 2 for bi-grams, etc.
 * @param mutual  (optional) whether to calculate mutual index of coincidence.
 */
double index_coincidence(std::string s, std::string t, int gram, bool mutual) {
  return (mutual) ? _mut_index_coincidence(s,t,gram) : _index_coincidence(s,gram);
}

int main() {
  std::string s,t;
  int gram;
  std::string yn;
  bool mutual;

  std::cout << "s: ";
  std::cin >> s;
  getline(std::cin,t);
  std::cout << "t (optional): ";
  getline(std::cin,t);
  std::cout << "gram length: ";
  std::cin >> gram;
  std::cout << "mutual (y/n): ";
  std::cin >> yn;
  mutual = (yn[0] == 'Y' || yn[0] == 'y');
  if (mutual) std::cout << "Mutual ";
  std::cout << "Index of Coincidence: " << index_coincidence(s,t,gram,mutual) << std::endl;
}
