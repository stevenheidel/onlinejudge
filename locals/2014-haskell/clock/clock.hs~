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

output :: [Char] -> String
output arr =
	replicate 8 ' ' ++ [arr !! 0] ++ "\n" ++
	replicate 4 ' ' ++ [arr !! 11] ++ replicate 7 ' ' ++ [arr !! 1] ++ "\n\n" ++
	replicate 1 ' ' ++ [arr !! 10] ++ replicate 13 ' ' ++ [arr !! 2] ++ "\n\n" ++
	[arr !! 9] ++ replicate 15 ' ' ++ [arr !! 3] ++ "\n\n" ++
	replicate 1 ' ' ++ [arr !! 8] ++ replicate 13 ' ' ++ [arr !! 4] ++ "\n\n" ++
	replicate 4 ' ' ++ [arr !! 7] ++ replicate 7 ' ' ++ [arr !! 5] ++ "\n" ++
	replicate 8 ' ' ++ [arr !! 6] ++ "\n"

make :: (Int, Int) -> String
make (h, m) = 
	let
		hour = if h < 12 then h else h-12
		minute = m `div` 5
		arr = replicate 12 'o'
		arr' = take hour arr ++ "h" ++ drop (hour+1) arr
		arr'' = take minute arr' ++ "m" ++ drop (minute+1) arr'
		arr''' = if minute == hour then take hour arr'' ++ "x" ++ drop (hour+1) arr'' else arr''
	in
		output arr'''

parse :: String -> (Int, Int)
parse str = (read(take 2 str), read(drop 3 str))

main = do
	str <- getContents
	let ls = lines str 
	let ns = map parse ls
	let ans = map make ns
	putStr (intercalate (replicate 17 '-' ++ "\n") ans)
