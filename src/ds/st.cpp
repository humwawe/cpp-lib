#include<cpp-util.h>


template<typename Iterator, typename Merge>
class SparseTable {
  using Tp = typename iterator_traits<Iterator>::value_type;
  vector<vector<Tp>> m_data;
  Merge m_merge;

public:
  // SparseTable st(v.begin(), v.end(), max);
  SparseTable(Iterator _first, Iterator _last, Merge _merge) : m_data(1), m_merge(_merge) {
    int n = distance(_first, _last);
    m_data.resize(__lg(n | 1) + 1, vector<Tp>(n));
    m_data[0].assign(_first, _last);
    for (int k = 0; k + 1 < m_data.size(); ++k) {
      for (int i = 0; i + (1 << k) < n; ++i) {
        m_data[k + 1][i] = m_merge(m_data[k][i], m_data[k][i + (1 << k)]);
      }
    }
  }

  // [l, r]
  Tp get(int lPos, int rPos) {
    if (lPos > rPos)
      return 0;
    int k = __lg(rPos - lPos + 1);
    return m_merge(m_data[k][lPos], m_data[k][rPos - (1 << k) + 1]);
  }
};


template<typename Iterator, typename Tp = typename iterator_traits<Iterator>::value_type>
SparseTable(Iterator, Iterator, const Tp &(*)(const Tp &, const Tp &))
  -> SparseTable<Iterator, const Tp &(*)(const Tp &, const Tp &)>;
