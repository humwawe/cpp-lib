#include <cpp-util.h>

//[0, n)
template<typename T>
struct Fenwick {
  int n{};
  vector<T> a;

  Fenwick(int n_ = 0) {
    init(n_);
  }

  void init(int n_) {
    n = n_;
    a.assign(n, T{});
  }

  void add(int p, const T v) {
    assert(0 <= p && p < n);

    for (int i = p + 1; i <= n; i += i & -i) {
      a[i - 1] = a[i - 1] + v;
    }
  }

  T _sum(int x) {
    T res{};
    for (int i = x; i > 0; i -= i & -i) {
      res = res + a[i - 1];
    }
    return res;
  }

  T rangeSum(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    return _sum(r) - _sum(l);
  }

  Fenwick(vector<T> _a) {
    init(_a.size());

    for (int i = 0; i < n; i++) {
      a[i] += _a[i];
      int j = i + ((i + 1) & -(i + 1));
      if (j < n) {
        a[j] += a[i];
      }
    }
  }

  void set(int i, T x) {
    add(i, x - get(i));
  }

  T get(int i) {
    return rangeSum(i, i + 1);
  }

  // 二分 类似在前缀和中求 lower_bound
  // 小于k的个数
  int lowerSelect(const T k) {
    int x = 0;
    T cur{};
    for (int i = 1 << std::__lg(n); i; i /= 2) {
      if (x + i <= n && cur + a[x + i - 1] < k) {
        x += i;
        cur = cur + a[x - 1];
      }
    }
    return x;
  }

  // 二分 类似在前缀和中求 upper_bound
  // 小于等于k的个数
  int upperSelect(const T k) {
    int x = 0;
    T cur{};
    for (int i = 1 << __lg(n); i; i /= 2) {
      if (x + i <= n && cur + a[x + i - 1] <= k) {
        x += i;
        cur = cur + a[x - 1];
      }
    }
    return x;
  }
};
