import Control.Monad
import Text.Printf
import Data.Set (member, union, (\\), fromList, toList, empty, null, singleton)
import Data.Array

getInt :: IO Int
getInt = fmap read $ getLine

getInts :: IO [Int]
getInts = fmap (map read . words) $ getLine

getPair :: IO (Int, Int)
getPair = do
	[i1, i2] <- getInts
	return (i1, i2)

readNof :: IO a -> IO [a]
readNof io = do
	n <- getInt
	replicateM n io

toArray l = listArray (1,length l) l

type State = Array Int Int

pour :: State -> State -> (Int, Int) -> State
pour cap state (src, dest) = 
	let
		srca = state!src
		desta = state!dest
		amount = min (srca) ((cap!dest)-desta)
	in
		state // [(src, srca-amount), (dest, desta+amount)]

pairs = [(a,b) | a <- [1,2,3], b <- [1,2,3], a /= b]

next cap state = map (pour cap state) pairs

bfs cap visited current target n
	| Data.Set.null current = -1
	| target `member` current = n
	| otherwise = bfs cap (union visited nextLayer) nextLayer target (n+1)
		where
			nextLayer = fromList (concatMap (next cap) (toList current)) \\ visited

chop n [] = []
chop n l = take n l : chop n (drop n l)

main = do
	n <- getInt
	replicateM_ n processCase

processCase = do
	ints <- getInts
	let [cap, init, f] = map(toArray) . chop 3 $ ints
	let ans = bfs cap Data.Set.empty (Data.Set.singleton init) f 0
	putStrLn $ prin ans

prin (-1) = "IMPOSSIBLE"
prin n = show n
