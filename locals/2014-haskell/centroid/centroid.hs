import Control.Monad
import Text.Printf
import Data.Array
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

main = do
	str <- getLine
	let (h:t) = words str
	if null t then return ()
	else do
		putStrLn (printPT . centroid . map parse $ t)
		main

toArray l = listArray (0,(length l)) (0:l)

parse :: String -> (Int, Int)
parse str = 
	let [n1, n2] = split str
	in (read n1, read n2)

centroid :: [(Int, Int)] -> (Double, Double)
centroid pts =
	let 
		(xs, ys) = unzip pts
		x = toArray xs
		y = toArray ys
		a' = sum ( map (\i -> x!i * y!(i+1) - x!(i+1) * y!i) [0..(n-1)] )
		a = 0.5 * fromIntegral a'
		n = length pts
		xc' = sum ( map (\i -> (x!i + x!(i+1)) * (x!i*y!(i+1)-x!(i+1)*y!i)) [0..n-1])
		xc = 1 / (6*a) * fromIntegral xc'
		yc' = sum ( map (\i -> (y!i + y!(i+1)) * (x!i*y!(i+1)-x!(i+1)*y!i)) [0..n-1])
		yc = 1 / (6*a) * fromIntegral yc'
	in
		(xc, yc)

split str = filter (/= ",") (groupBy (\x y -> x /= ',' && y /= ',') str)

printPT (x,y) = printf "%.3f,%.3f" x y
