const int MAXN = 128;
const double EPS = 1e-10;

void LU(int n, double a[MAXN][MAXN], int r[MAXN], int c[MAXN]) {
  for (int i = 0; i < n; ++i) {
    r[i] = c[i] = i;
  }
  for (int k = 0; k < n; ++k) {
    int ii = k, jj = k;
    for (int i = k; i < n; ++i) {
      for (int j = k; j < n; ++j) {
        if (fabs(a[i][j]) > fabs(a[ii][jj])) {
          ii = i;
          jj = j;
        }
      }
    }
    swap(r[k], r[ii]);
    swap(c[k], c[jj]);
    for (int i = 0; i < n; ++i) {
      swap(a[i][k], a[i][jj]);
    }
    for (int j = 0; j < n; ++j) {
      swap(a[k][j], a[ii][j]);
    }
    if (fabs(a[k][k]) < EPS) {
      continue;
    }
    for (int i = k + 1; i < n; ++i) {
      a[i][k] = a[i][k] / a[k][k];
      for (int j = k + 1; j < n; ++j) {
        a[i][j] -= a[i][k] * a[k][j];
      }
    }
  }
}

void solve(int n, double a[MAXN][MAXN], int r[MAXN], int c[MAXN], double b[MAXN]) {
  static double x[MAXN];
  for (int i = 0; i < n; ++i) {
    x[i] = b[r[i]];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      x[i] -= a[i][j] * x[j];
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = n - 1; j > i; --j) {
      x[i] -= a[i][j] * x[j];
    }
    if (fabs(a[i][i]) >= EPS) {
      x[i] /= a[i][i];
    } // else assert(fabs(x[i]) < EPS);
  }
  for (int i = 0; i < n; ++i) {
    b[c[i]] = x[i];
  }
}

// LU(n - 1, a, r, c);
// solve(n - 1, a, r, c, b);
