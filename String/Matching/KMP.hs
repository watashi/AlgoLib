{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE RecordWildCards #-}

import Prelude hiding (fail)
import Data.Array

import Data.List
import Test.QuickCheck

data KMP a = KMP
  { pat :: Array Int a
  , fail :: Array Int Int
  } deriving (Show)

newKMP :: Eq a => [a] -> KMP a
newKMP a = KMP{..}
  where
  n = length a
  pat = listArray (0, n-1) a
  fail = listArray (0, n-1) $ (-1):
    [ if pat!(k+1) == e then k+1 else -1
    | (i, e) <- tail $ assocs pat
    , let k = until (\j -> j < 0 || pat!(j+1) == e) (fail!) (fail!(i-1))
    ]

runKMP :: Eq a => KMP a -> [a] -> [Int]
runKMP KMP{..} = go 0
  where
  go _ [] = []
  go k b@(h:t)
    | k <= snd (bounds pat) && h == pat!k = let k' = k + 1 in k': go k' t
    | k > 0                               = let k' = fail!(k-1) + 1 in go k' b
    | otherwise                           = 0: go 0 t

prop_fail_model :: Eq a => [a] -> Bool
prop_fail_model s = (elems . fail . newKMP $ s) == (map f . tail . inits $ s)
  where
  f t = head [length i - 1 | i <- tail . tails $ t, i `isPrefixOf` s]

main :: IO ()
main = do
  check (prop_fail_model :: [Bool] -> Bool)
  check (prop_fail_model :: [Ordering] -> Bool)
  check (prop_fail_model :: [Char] -> Bool)
  where
  check :: Testable prop => prop -> IO ()
  check = quickCheckWith stdArgs{maxSuccess=1000}
