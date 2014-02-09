import Control.Monad
import Text.Printf
import Data.Array
import Debug.Trace

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

ways a _ 0 = 1
ways a 5 _ = 0
ways a typ val
	| val < 0 = 0
	| otherwise = ways a (typ+1) val + more
		where
			index = val-(coinValue!!typ)
			more = if index >= 0 then a!(index, typ) else 0
			coinValue = [1,5,10,25,50]

arr :: Array (Int,Int) Integer
arr = array ((0,0), (100000,4)) [((j, i), ways arr i j) | j <- [0..100000], i <- [4,3..0]]

ans x = arr!(x,0)

main = do
	n <- getInt
	res <- replicateM n getInt
	let a = unlines . map show $ map ans res
	putStr a
