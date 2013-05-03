import Data.Array
import Data.Complex
import Data.Int
import Test.QuickCheck

-- DITFFT
-- radix-2 ONLY!!
fft, ifft :: RealFloat a => [Complex a] -> [Complex a]
fft x = fft' (-1) x
ifft x = map (/fromIntegral n) y
  where
    y = fft' 1 x
    n = length y

fft' :: RealFloat a => a -> [Complex a] -> [Complex a]
fft' _ [] = []
fft' _ [x] = [x]
fft' d x = zipWith3 (\i j k -> i + j * k) (ye ++ ye) (yo ++ yo) $ iterate (*w) 1
  where
    split [] = ([], [])
    split [a] = ([a], [0])
    split (a:b:c) = let (ce, co) = split c in (a:ce, b:co)
    (xe, xo) = split x
    (ye, yo) = (fft' d xe, fft' d xo)
    n = length xe + length xo
    w = cis $ 2 * d * pi / fromIntegral n

-- DFT
dft, idft :: RealFloat a => [Complex a] -> [Complex a]
dft x = dft' (-1) x
idft x = map (/fromIntegral n) y
  where
    y = dft' 1 x
    n = length y

dft' :: RealFloat a => a -> [Complex a] -> [Complex a]
dft' d x = [sum $ zipWith (\i j -> i * e (j * k)) x [0 ..] | k <- [0 .. n - 1]]
  where
    n = length x
    e i = cis $ 2 * d * pi * fromIntegral i / fromIntegral n

-- Convolution
convolve :: Integral a => [a] -> [a] -> [a]
convolve a b = map (round . realPart) $ ifft $ zipWith (*) (fft $ pad0 a) (fft $ pad0 b)
  where
    n = let m = length a + length b in until (>=m) (*2) 1
    pad0 x = take n $ map fromIntegral x ++ repeat (0 :: Complex Double)

-- test
eps :: Double
eps = 1e-6

(~~) :: [Complex Double] -> [Complex Double] -> Bool
(~~) a b = length a == length b && maximum (map magnitude $ zipWith (-) a b) < eps

pad :: [Complex Double] -> [Complex Double]
pad x = take n $ x ++ repeat 0
  where
    n = until (>=length x) (*2) 1

prop_invertible :: [Complex Double] -> Bool
prop_invertible x = let x' = pad x in (~~ x') $ ifft $ fft x'

prop_equality :: [Complex Double] -> Bool
prop_equality x = let x' = pad x in fft x' ~~ dft x'

prop_convolution :: ([Int16], [Int16]) -> Property
prop_convolution (a, b) =
  not (null a || null b) ==>
    f c' == f (convolve (elems a') (elems b'))
  where
    da = length a - 1
    db = length b - 1
    a' = listArray (0, da) $ map toInteger a
    b' = listArray (0, db) $ map toInteger b
    c' = elems $ accumArray (+) 0 (0, da + db) $
      [(i + j, a'!i * b'!j) | i <- [0 .. da], j <- [0 .. db]]
    f = dropWhile (==0) . reverse

main :: IO ()
main = do
  quickCheckWith stdArgs{maxSuccess=500} prop_invertible
  quickCheckWith stdArgs{maxSuccess=300} prop_invertible
  quickCheckWith stdArgs{maxSuccess=200} prop_convolution
