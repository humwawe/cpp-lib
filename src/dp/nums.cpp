#include<cpp-util.h>


long long solve(int x) {
  vector<int> nums;
  while (x > 0) {
    nums.push_back(x % 10);
    x /= 10;
  }
  int n = nums.size();
  vector memo(n, vector(1 << n, -1ll));

  function<long long(int, int, bool, bool)> dfs = [&](int i, int st, bool limit, bool lead) {
    // 算到num的最后一位
    if (i == nums.size()) {
      // 考虑能否取 0
      return lead ? 0 : 1ll;
    }
    if (!limit && !lead && memo[i][st] != -1) {
      return memo[i][st];
    }

    long long res = 0;
    // 可以跳过当前数位
    if (lead) {
      res = dfs(i + 1, st, false, true);
    }

    int up = limit ? nums[i] : 9;
    // 根据前导0判断是否能取到0
    int low = lead ? 1 : 0;

    for (int j = low; j <= up; j++) {
      // 处理某种条件
      if ((st >> j & 1) == 0) {
        res += dfs(i + 1, st | (1 << j), limit && j == up, false);
      }
    }
    if (!limit && !lead) {
      memo[i][st] = res;
    }
    return res;
  };

  return dfs(0, 0, true, true);
}
