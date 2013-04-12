// Modular Linear Equations
import java.math.BigInteger;

public class ModLinear {
  // a * g[1] + b * g[2] = g[0]
  static BigInteger[] extGcd(BigInteger a, BigInteger b) {
    if (b.signum() == 0) {
      return new BigInteger[]{a, BigInteger.ONE, BigInteger.ZERO};
    } else {
      BigInteger[] g = extGcd(b, a.mod(b));
      return new BigInteger[]{g[0], g[2], g[1].subtract(a.divide(b).multiply(g[2]))};
    }
  }

  // x % u[1] = u[0] && x % v[1] = v[0] => x % ret[1] == ret[0]
  static BigInteger[] modLinearSys(BigInteger[] u, BigInteger[] v) throws Exception {
    BigInteger[] g = extGcd(u[1], v[1]);
    BigInteger z = u[0].subtract(v[0]);
    if (z.mod(g[0]).signum() != 0) {
      throw new Exception("No Solution");
    } else {
      z = g[2].multiply(z.divide(g[0]));
      BigInteger[] ret = new BigInteger[]{
        v[0].add(v[1].multiply(z)),
        u[1].divide(g[0]).multiply(v[1])
      };
      ret[0] = ret[0].mod(ret[1]);
      return ret;
    }
  }
}
