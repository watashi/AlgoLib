template<int MAXN>
struct BridgeBlockTree {
  Tarjan<MAXN> bcc;
  DisjointSet<MAXN> ds;
  vector<int> e[MAXN];

  void init(int n) {
    bcc.init(n);
    ds.init(n);
  }

  void add(int a, int b) {
    bcc.add(a, b);
  }

  void gao() {
    bcc.gao();
    for (const auto& i: bcc.bcc) {
      if (i.size() > 1) {
        for (const auto& j: i) {
          ds.setp(j.first, j.second);
        }
      }
    }
    for (const auto& i: bcc.bridge) {
      int a = ds.getp(i.first);
      int b = ds.getp(i.second);
      e[a].push_back(b);
      e[b].push_back(a);
    }
  }

  int id(int v) {
    return ds.getp(v);
  }
};
