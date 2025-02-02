#include <cpp-util.h>

// 枚举子集,可以取到 0
void subst0(int st) {
  int sub = st;
  do {
    // use sub do something
    cout << sub << endl;
    sub = (sub - 1) & st;
  } while (sub != st);
}

// 枚举子集
// sub变为 0 后，
// (sub - 1) & st
// => -1 & st
// => st
void subst(int st) {
  for (int sub = st; sub > 0; sub = (sub - 1) & st) {
    // use sub do something
    cout << sub << endl;
  }
}

/** 枚举从n个物品中选k个
 最小的子集是(1<<k)-1，用它作为初始值N
 1.求出最低位的1开始连续的1的区间，x&-x的值就是将最低位的1独立出来的值
 2.将这一区间全部变为0，并将区间最左侧的0变为1
 3.将第1步取出的区间右移，知道剩下的1的个数少了1个
 4.将第2步和第3步的结果按位取或 **/
void sub_comb(int n, int k) {
  assert(k <= n);
  int sub = (1 << k) - 1;
  while (sub < 1 << n) {
    // use sub do something
    cout << sub << endl;
    int x = sub & -sub;
    int y = sub + x;
    sub = ((sub & ~y) / x >> 1) | y;
  }
}
