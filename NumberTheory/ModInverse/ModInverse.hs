{-# LANGUAGE GeneralizedNewtypeDeriving #-}
{-# LANGUAGE TypeApplications #-}

import Data.Word
import Test.QuickCheck

-- a * x + b * y == gcd a b >= 0
extGcd :: Integral a => a -> a -> (a, a, a)
extGcd a 0
  | a >= 0 = (a, 1, 0)
  | otherwise = (negate a, -1, 0)
extGcd a b = (g, x, y - a `quot` b * x)
  where
  (g, y, x) = extGcd b (a `rem` b)

-- ASSUME: gcd a m == 1
-- a * x `mod` abs m == 1
modInv :: Integral a => a -> a -> a
modInv a m = x
  where
  (1, x, _) = extGcd a m

-- -----------------------------------------------------------------------------
prop_gcd :: Integral a => a -> a -> Bool
prop_gcd a b = gcd a b == g && a * x + b * y == g
  where
  (g, x, y) = extGcd a b

newtype I = I Integer
  deriving (Eq, Ord, Show, Enum, Num, Real, Integral)

instance Arbitrary I where
  arbitrary = I . product . map toInteger <$> arbitrary @[Large Int]
  shrink = shrinkIntegral

main :: IO ()
main = do
  check (prop_gcd @I)
  check (prop_gcd @(Small Int))
  check (prop_gcd @(Large Word64))
  where
  check :: Testable prop => prop -> IO ()
  check prop = quickCheckWith stdArgs{maxSuccess=1000, maxSize=50} prop
