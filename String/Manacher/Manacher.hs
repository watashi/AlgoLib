import Data.Array (assocs, listArray, (!))
import qualified Data.ByteString as C

palindrome :: C.ByteString -> [(Int, Int, Int)]
palindrome str = [(l, r, go l r) | l <- [1 .. n], r <- [l, l + 1], r <= n]
  where
    n = C.length str
    a = listArray (1, n) $ C.unpack str
    go l r
      | l < 1 || r > n  = 0
      | a!l /= a!r      = 0
      | otherwise       = succ $ go (pred l) (succ r)

manacher :: C.ByteString -> [(Int, Int, Int)]
manacher str = [(div i 2, div (i + 1) 2, e) | (i, e) <- assocs b]
  where
    n = C.length str
    a = listArray (1, n) $ C.unpack str
    pal l r
      | l < 1 || r > n = 0
      | a!l /= a!r     = 0
      | otherwise      = succ $ pal (pred l) (succ r)
    b = listArray (2, 2*n) $ go 2 (0, 0)
    go k (e, c) = if l > n then [] else t: go (k + 1) (e', c')
      where
        l = div k 2
        r = k - l
        s = if k <= e then min (b!(2*c-k)) $ 1 + div (e-k) 2 else 0
        t = s + pal (l - s) (r + s)
        (e', c') = max (e, c) (2 * (r + t - 1), k)

