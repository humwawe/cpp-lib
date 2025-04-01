#include <cpp-util.h>

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(long long x, long long y) {
  return uniform_int_distribution<>(x, y)(rng);
}

long long MOD = 1e18 + rnd(0, 1e9);
int BASE = 233 + rnd(0, 1e3);

struct HashSeq {
  vector<__int128> P, H;
  int n;

  HashSeq(string s = "") {
    init(s);
    add(s);
  }

  void init(string s) {
    n = 0;
    P.resize(n + 1);
    P[0] = 1;
    H.resize(n + 1);
    H[0] = 0;
    add(s);
  }

  // [l, r)
  long long query(int l, int r) {
    return (H[r] - H[l] * P[r - l] % MOD + MOD) % MOD;
  }

  void add(string s) {
    int len = s.size();
    P.resize(n + len + 1);
    for (int i = 1; i <= len; i++) {
      P[n + i] = P[n + i - 1] * BASE % MOD;
    }
    H.resize(n + len + 1);
    for (int i = 1; i <= len; i++) {
      H[n + i] = (H[n + i - 1] * BASE + (s[i - 1] ^ 7)) % MOD;
    }

    n += len;
  }

  void del(int len) {
    n -= len;
    P.resize(n + 1);
    H.resize(n + 1);
  }
};
