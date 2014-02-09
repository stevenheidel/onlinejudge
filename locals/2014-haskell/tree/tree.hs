import Control.Monad
import Text.Printf
import Data.List
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

maxPath :: (Int -> [Int]) -> Int -> (Int, Int)
maxPath children n = (path, height)
	where
		(path, height) = case (children n) of
			[] -> (0,0)
			[c] -> let (cpath, cheight) = maxPath children c
				in (cpath+1, cheight+1)
			cs -> let (paths, heights) = unzip $ map (maxPath children) cs
				  (m:(snd:rest)) = reverse $ sort heights
				in (max (maximum paths) (m+snd+2), m+1)

main = do 
	n <- getInt
	replicateM_ n readCase

listToFunc :: [a] -> (Int -> a)
listToFunc as = (arr!)
	where
		arr = array (0,length(as)-1) (zip [0..] as)

readCase = do
	ls <- readNof getInts
	let (p,_) = maxPath (listToFunc ls) 0
	putStrLn . show $ p
