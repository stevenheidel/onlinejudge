import Control.Monad
import Text.Printf
import Data.List

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

comb :: Int -> [a] -> [[a]]
comb 0 _ = [[]]
comb m l = [x:ys | x:xs <- tails l, ys <- comb (m-1) xs]

isRectangle [(_, (x1, y1)), (_, (x2, y2)), (_, (x3, y3)), (_, (x4, y4))] =
	(y1 == y2) && (x2 == x3) && (y3 == y4) && (x4 == x1) && 
	(x1 < x2) && (y2 > y3) && (x3 > x4) && (y4 < y1)

answerString p4 = if null possibles then ""
		  else
			let
				a = head possibles
			in
				fst (a !! 0) ++ fst (a !! 1) ++ fst (a !! 2) ++ fst (a !! 3)
	where
		possibles = filter isRectangle perms
		perms = permutations p4

output pts = let
		coms = comb 4 pts
		res = map answerString coms
		out = sort $ filter (/= "") res
		groups = map ((" " ++).unwords) $ chop 10 out
		ls = unlines groups
	     in
		if null out then " No rectangles\n"
	     else
		"\n" ++ ls

chop n [] = []
chop n l = take n l : chop n (drop n l)

getPoint :: IO (String, (Int, Int))
getPoint = do
	str <- getLine
	let w = words str
	return (w !! 0, (read (w !! 1), read (w !! 2)))

main = recurse 1

recurse n = do
	i <- getInt
	if i == 0 then return ()
	else do
		pts <- replicateM i getPoint
		putStr ("Point set " ++ show n ++ ":")
		putStr (output pts)
		recurse (n+1)
