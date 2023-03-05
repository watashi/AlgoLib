import GHC.Integer.GMP.Internals (powModInteger)

millerRabin :: Integer -> Bool
millerRabin n
  | n < 3 = n == 2
  | even n = False
  | otherwise = all check [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]	-- https://oeis.org/A014233
  where
    (s, d) = until (odd . snd) (\(i, j) -> (i + 1, j `quot` 2)) (0, n - 1)
    check a
      | x == 1 = True
      | otherwise = any (== n - 1) $ take s $ iterate (\i -> i * i `rem` n) x
      where
        x = powModInteger a d n
