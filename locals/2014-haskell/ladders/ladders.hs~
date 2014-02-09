import Control.Monad
import Text.Printf
import Data.List
import Debug.Trace

getInt :: IO Int
getInt = fmap read $ getLine

getInts :: IO [Int]
getInts = fmap (map read . words) $ getLine

getStrs :: IO [String]
getStrs = fmap words $ getLine

getPair :: IO (Int, Int)
getPair = do
	[i1, i2] <- getInts
	return (i1, i2)

readNof :: IO a -> IO [a]
readNof io = do
	n <- getInt
	replicateM n io

oneStep :: String -> String -> Bool
oneStep s1 s2 = 
	let
		p = commonPrefix s1 s2
		s = commonSuffix (drop p s1) (drop p s2)
		commonPrefix s1 s2 = length . takeWhile id $ zipWith (==) s1 s2
		commonSuffix s1 s2 = commonPrefix (reverse s1) (reverse s2)
		a = p + s
	in
		abs(a - (length s1)) <= 1 && abs(a - (length s2)) <= 1

bfs current unused n target 
	| target `elem` current = n
	| null current = -1
	| otherwise = let
			nextLayer = filter accessible unused
			accessible :: String -> Bool
			accessible a = or (map (oneStep a) current)
		      in
			--trace (show current ++ " " ++ show unused) $
			bfs nextLayer (unused \\ nextLayer) (n+1) target 

query strs s1 s2 = bfs [s1] (strs \\ [s1]) 0 s2

main = do
	strs <- readNof getLine
	recurse strs

recurse strs = do
	[s1, s2] <- getStrs
	if s1 == "END" && s2 == "END" then return () else do
		let ans = query strs s1 s2
		let prin = if ans == -1 then "no ladder" else show ans
		putStrLn prin
		recurse strs 
