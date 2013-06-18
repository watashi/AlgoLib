import Data.Array (assocs, listArray, (!))
import Test.QuickCheck

palindrome :: Eq a => [a] -> [(Int, Int, Int)]
palindrome str = [(l, r, go l r) | l <- [1 .. n], r <- [l, l + 1], r <= n]
  where
    n = length str
    a = listArray (1, n) str
    go l r
      | l < 1 || r > n  = 0
      | a!l /= a!r      = 0
      | otherwise       = succ $ go (pred l) (succ r)

manacher :: Eq a => [a] -> [(Int, Int, Int)]
manacher str = [(div i 2, div (i + 1) 2, e) | (i, e) <- assocs b]
  where
    n = length str
    a = listArray (1, n) str
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

prob_palindrome_model :: Eq a => [a] -> Bool
prob_palindrome_model s = manacher s == palindrome s

data Color = Red | Green | Blue deriving (Eq, Show)
instance Arbitrary Color where
  arbitrary = elements $ concatMap (uncurry replicate) $
    [(100, Red), (10, Green), (1, Blue)]

main :: IO ()
main = do
  check (prob_palindrome_model :: [Bool] -> Bool)
  check (prob_palindrome_model :: [Color] -> Bool)
  check (prob_palindrome_model :: [Char] -> Bool)
  where
    check :: Testable prop => prop -> IO ()
    check = quickCheckWith stdArgs{maxSuccess=1000}
