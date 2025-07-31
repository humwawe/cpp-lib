#include <cpp-util.h>

struct BigNum {
  static constexpr int base = 1e7;
  static constexpr int base_digits = 7;
  vector<int64_t> data;

  explicit BigNum(int x = 0) { data.push_back(x); }

  explicit BigNum(const string &s) {
    data.clear();
    for (int i = (int) s.length(); i > 0; i -= base_digits) {
      int start = max(0, i - base_digits);
      string part = s.substr(start, i - start);
      int64_t num = stoll(part);
      data.push_back(num);
    }
    fix();
  }

  void fix() {
    for (int i = 0; i < data.size(); i++) {
      if (data[i] >= base) {
        if (i + 1 == data.size()) data.push_back(0);
        data[i + 1] += data[i] / base;
        data[i] %= base;
      }
    }
    while ((!data.empty()) && (data.back() == 0)) data.pop_back();
  }

  BigNum operator+(const BigNum &other) const {
    BigNum res = (*this);
    if (data.size() < other.data.size()) res.data.resize(other.data.size(), 0);
    for (int i = 0; i < other.data.size(); i++) res.data[i] += other.data[i];
    res.fix();
    return res;
  }

  BigNum &operator+=(const BigNum &other) {
    if (data.size() < other.data.size()) data.resize(other.data.size(), 0);
    for (int i = 0; i < other.data.size(); i++) data[i] += other.data[i];
    fix();
    return *this;
  }

  BigNum operator*(const BigNum &other) const {
    BigNum res(0);
    res.data.clear();
    res.data.resize(data.size() + other.data.size(), 0);
    for (int i = 0; i < data.size(); i++)
      for (int j = 0; j < other.data.size(); j++) res.data[i + j] += data[i] * other.data[j];
    res.fix();
    return res;
  }

  bool operator<(const BigNum &other) const {
    if (data.size() != other.data.size()) return data.size() < other.data.size();
    for (int i = data.size() - 1; i >= 0; i--)
      if (data[i] != other.data[i]) return data[i] < other.data[i];
    return false;
  }

  friend ostream &operator<<(ostream &out, const BigNum &number) {
    cout << number.data.size() << endl;
    out << number.data.back();
    for (int i = int(number.data.size()) - 2; i >= 0; i--) {
      out << setw(7) << setfill('0') << number.data[i];
    }
    return out;
  }
};
