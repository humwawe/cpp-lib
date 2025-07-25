#include<cpp-util.h>

template<class Info>
struct SegmentTree {
  int n;
  vector<Info> info;

  SegmentTree() : n(0) {
  }

  SegmentTree(int n_, Info v_ = Info()) {
    init(n_, v_);
  }

  template<class T>
  SegmentTree(vector<T> init_) {
    init(init_);
  }

  void init(int n_, Info v_ = Info()) {
    init(vector(n_, v_));
  }

  template<class T>
  void init(vector<T> init_) {
    n = init_.size();
    info.assign(4 << __lg(n), Info());
    function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        info[p] = init_[l];
        return;
      }
      int m = (l + r) / 2;
      build(2 * p, l, m);
      build(2 * p + 1, m, r);
      pull(p);
    };
    build(1, 0, n);
  }

  void pull(int p) {
    info[p] = info[2 * p] + info[2 * p + 1];
  }

  void modify(int p, int l, int r, int x, const Info &v) {
    if (r - l == 1) {
      info[p] = v;
      return;
    }
    int m = (l + r) / 2;
    if (x < m) {
      modify(2 * p, l, m, x, v);
    } else {
      modify(2 * p + 1, m, r, x, v);
    }
    pull(p);
  }

  void modify(int p, const Info &v) {
    modify(1, 0, n, p, v);
  }

  Info rangeQuery(int p, int l, int r, int x, int y) {
    // merge 注意有可能某一侧返回默认的 info()
    if (l >= y || r <= x) {
      return Info();
    }
    if (l >= x && r <= y) {
      return info[p];
    }
    int m = (l + r) / 2;
    return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
  }

  // [l,r)
  Info rangeQuery(int l, int r) {
    return rangeQuery(1, 0, n, l, r);
  }

  template<class F>
  int findFirst(int p, int l, int r, int x, int y, F &&pred) {
    if (l >= y || r <= x) {
      return -1;
    }
    if (l >= x && r <= y && !pred(info[p])) {
      return -1;
    }
    if (r - l == 1) {
      return l;
    }
    int m = (l + r) / 2;
    int res = findFirst(2 * p, l, m, x, y, pred);
    if (res == -1) {
      res = findFirst(2 * p + 1, m, r, x, y, pred);
    }
    return res;
  }

  template<class F>
  int findFirst(int l, int r, F &&pred) {
    return findFirst(1, 0, n, l, r, pred);
  }

  template<class F>
  int findLast(int p, int l, int r, int x, int y, F &&pred) {
    if (l >= y || r <= x) {
      return -1;
    }
    if (l >= x && r <= y && !pred(info[p])) {
      return -1;
    }
    if (r - l == 1) {
      return l;
    }
    int m = (l + r) / 2;
    int res = findLast(2 * p + 1, m, r, x, y, pred);
    if (res == -1) {
      res = findLast(2 * p, l, m, x, y, pred);
    }
    return res;
  }

  template<class F>
  int findLast(int l, int r, F &&pred) {
    return findLast(1, 0, n, l, r, pred);
  }
};

constexpr i64 inf = 1E18;

struct Info {
  i64 x;

  Info(i64 x = -inf) : x(x) {
  }
};

Info operator+(const Info &a, const Info &b) {
  Info c;
  c.x = max(a.x, b.x);
  return c;
}
