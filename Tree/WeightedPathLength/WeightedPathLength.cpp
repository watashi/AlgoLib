#include <vector>

using namespace std;

/**
\brief Weighted path length from the root

The structure of tree must be fixed/static
The length of edge can be changed/dynamic
*/
template<int MAXN, typename T = int>
struct WeightedPathLength {
  int n, m, root;
  int id[MAXN][2];

  /// \see DataStructure/BinaryIndexedTree/BIT.cpp
  BIT<MAXN + MAXN, T> bit;

  const vector<int> *e;

  void dfs_(int v, int p) {
    for (vector<int>::const_iterator it = e[v].begin(); it != e[v].end(); ++it) {
      if (*it != p) {
        id[*it][0] = m++;
        dfs_(*it, v);
        id[*it][1] = m++;
      }
    }
  }

  void init(int n, const vector<int> e[MAXN], int root = 0) {
    this->n = n;
    this->m = 0;
    this->root = root;
    this->e = e;
    dfs_(root, root);
    bit.init(m);
  }

  /// change weight(\c v, parent(\c v)) to \c w
  void update(int v, T w) {
    bit.set(id[v][0], w);
    bit.set(id[v][1], -w);
  }

  /// return the path length from \c root to \c v
  T query(int v) {
    return v == root ? T() : bit.sum(id[v][0] + 1);
  }
};
