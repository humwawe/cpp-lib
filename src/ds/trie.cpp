#include <cpp-util.h>

struct Trie {
  int N;
  int idx{};
  vector<array<int, 26>> son;
  vector<int> cnt;

  Trie(int n) {
    init(n);
  }

  // n个字符串中 字符的总长度
  void init(int n_) {
    N = n_ + 5;
    son.assign(N, array<int, 26>{});
    cnt.assign(N, 0);
  }

  void insert(string s) {
    int p{0};
    for (char c: s) {
      int u = c - 'a';
      if (son[p][u] == 0) {
        son[p][u] = ++idx;
      }
      p = son[p][u];
    }
    cnt[p]++;
  }

  int query(string s) {
    int p{};
    for (char c: s) {
      int u = c - 'a';
      if (son[p][u] == 0) {
        return 0;
      }
      p = son[p][u];
    }
    return cnt[p];
  }
};
