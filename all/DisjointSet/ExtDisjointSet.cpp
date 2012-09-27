struct DisjointSet {
    int p[MAXN];

    static inline int RE(int i) { return -1 - i; }

    void init(int n) {
        for (int i = 0; i < n; ++i) {
            p[i] = i;
        }
    }

    int getp(int i) {
        if (i < 0) {
            return RE(getp(RE(i)));
        } else if (i == p[i]) {
            return i;
        } else {
            return p[i] = getp(p[i]);
        }
    }

    int setp(int i, int j) {
        i = getp(i);
        j = getp(j);
        if (i == j) {
            return 0;
        } else if (i == RE(j)) {
            return -1;
        } else {
            if (i < 0) {
                i = RE(i);
                j = RE(j);
            }
            p[i] = j;
            return 1;
        }
    }
} ds;
