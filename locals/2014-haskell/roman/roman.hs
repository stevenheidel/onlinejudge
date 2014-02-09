import Control.Monad
import Text.Printf

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

data Roman = I | V | X | L | C | D | M deriving (Eq, Ord, Show, Read)

value I = 1
value V = 5
value X = 10
value L = 50
value C = 100
value D = 500
value M = 1000

sub M = C
sub D = C
sub C = X
sub L = X
sub X = I
sub V = I
sub I = error "Don't do this 1" 

next M = D
next D = C
next C = L
next L = X
next X = V
next V = I
next I = error "Don't do this 2"

maxnum I = 3
maxnum V = 1
maxnum X = 3
maxnum L = 1
maxnum C = 3
maxnum D = 1
maxnum M = 3

parse :: Roman -> Int -> [Roman] -> Maybe Int
parse mode num str
	| null str = Just 0
	| head str == mode = if num == maxnum mode then Nothing 
			     else fmap (value mode +) (parse mode (num+1) (tail str))
	| mode == I = Nothing
	| value (head str) > value mode = Nothing
	| length str >= 2 && head str == sub mode && str!!1 == mode = 
		fmap ((value mode - value (sub mode)) +) (parse (sub mode) (maxnum (sub mode)) (drop 2 str))
	| otherwise = parse (next mode) 0 str

strToRomans :: String -> [Roman]
strToRomans [] = []
strToRomans (s:ss) = ch s : strToRomans ss 

ch 'I' = I
ch 'V' = V
ch 'X' = X
ch 'L' = L
ch 'C' = C
ch 'D' = D
ch 'M' = M

convert :: String -> Int
convert s = case parse mode num str of
		Just i -> i
		Nothing -> -1
	where
		str = strToRomans s
		mode = M
		num = 0

unconvert :: Int -> String
unconvert 0 = "invalid"
unconvert n = unparse n

unparse n = 
	let ms = replicate (div n 1000) M
	in
		concatMap show (ms ++ 
		unparseDigit (digitOf n 100) 3 ++
		unparseDigit (digitOf n 10) 2 ++
		unparseDigit (digitOf n 1) 1)

ten 1 = X
ten 2 = C
ten 3 = M

five 1 = V
five 2 = L
five 3 = D

one 1 = I
one 2 = X
one 3 = C

unparseDigit digit level
	| digit == 9 = [one level, ten level]
	| digit >= 5 = [five level] ++ replicate (digit-5) (one level)
	| digit == 4 = [one level, five level]
	| otherwise = replicate digit (one level)

digitOf n x = div (mod n (x*10)) x

main = do
	n <- getInt
	vals <- replicateM n getLine
	let ms = map convert vals
	let ns = map (\x -> x+1) ms
	putStr (unlines (map unconvert ns))
