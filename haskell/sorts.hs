module Main where

qsort :: (Ord a) => [a] -> [a]
qsort [] = []
qsort (pv:t) = (qsort small) ++ [pv] ++ (qsort big)
    where small = [y | y <- t, y <= pv]
          big   = [z | z <- t, z >  pv]

sortWith :: (Num a, Ord a, Ord b) => (b -> b -> a) -> [b] -> [b]
sortWith f [] = []
sortWith f (pv:t) = (sortWith f small) ++ [pv] ++ (sortWith f big)
    where small = [y | y <- t, y `f` pv <= 0]
          big   = [z | z <- t, z `f` pv >  0]

reverseAcc :: [a] -> [a] -> [a]
reverseAcc [x]   acc = x:acc
reverseAcc (h:t) acc = reverseAcc t (h:acc)

myReverse :: [a] -> [a]
myReverse [] = []
myReverse x  = reverseAcc x []

parsenum :: (Fractional a) => a -> a -> [Char] -> a
parsenum d n [] = n
parsenum d n (h:t)
    | h == ','  = parsenum d n t
    | h == '.'  = parsenum d n t
    | h == '1'  = parsenum (d*10) (n+d)   t
    | h == '2'  = parsenum (d*10) (n+d*2) t
    | h == '3'  = parsenum (d*10) (n+d*3) t
    | h == '4'  = parsenum (d*10) (n+d*4) t
    | h == '5'  = parsenum (d*10) (n+d*5) t
    | h == '6'  = parsenum (d*10) (n+d*6) t
    | h == '7'  = parsenum (d*10) (n+d*7) t
    | h == '8'  = parsenum (d*10) (n+d*8) t
    | h == '9'  = parsenum (d*10) (n+d*9) t
    | h == '0'  = parsenum (d*10) n       t
    | otherwise = n

atof :: (Fractional a) => [Char] -> a
atof x = parsenum 0.01 0 (reverse x)

each3 x = [x,x+3..]
each5 x = [x,x+5..]
each8 x y = zipWith (+) (each3 x) (each5 y)

half = (/ 2)
finstr = (++ "\n")

myGcd :: Integer -> Integer -> Integer
myGcd a 0 = a
myGcd a b
    | a < 0     = gcd (-a) b
    | b < 0     = gcd a    (-b)
    | b > a     = gcd b    a
    | otherwise = gcd b    (a `mod` b)

prime :: Integer -> Bool
prime x
    | x <= 1 = False
    | even x = if 2 == x then True else False
    | otherwise = and $ map ((1 ==) . (gcd x)) [1..(x `div` 2)]

primes :: [Integer]
primes = filter prime [1..]

allSpaces :: [Char] -> [Char]
allSpaces [] = []
allSpaces (h:t)
    | h == '\t' = ' ' : allSpaces t
    | h == '\n' = ' ' : allSpaces t
    | otherwise =  h  : allSpaces t

oneSpace :: [Char] -> [Char]
oneSpace [] = []
oneSpace [x] | x == ' '  = []
             | otherwise = [x]
oneSpace (x:y:t) | and [(x == ' '),(y == ' ')] = oneSpace $ ' ':t
                 | otherwise                   = x : (oneSpace $ y:t)

prstr :: [Char] -> [Char]
prstr = oneSpace . allSpaces

breakLine :: Integral a => a -> [[Char]] -> [Char] -> [[Char]] -> [[Char]]
breakLine l []    []  macc = macc
breakLine l []    acc macc = macc ++ [acc]
breakLine l (w:t) []  macc
    | lw <  len = breakLine l t                w  macc
    | lw == len = breakLine l t                [] (macc ++ [w])
    | otherwise = breakLine l ((drop len w):t) [] (macc ++ [take len w])
    where lw  = fromIntegral $ length w
          len = fromIntegral l
breakLine l (w:t) acc macc
    | 0  == lr  = breakLine l (w:t)       []         (macc ++ [acc])
    | lw >  len = breakLine l ((dlr w):t) []         (macc ++ [aw acc (tlr w)])
    | lw >  lr  = breakLine l (w:t)       []         (macc ++ [acc])
    | lw == lr  = breakLine l t           []         (macc ++ [aw acc w])
    | otherwise = breakLine l t           (aw acc w) macc
    where len    = fromIntegral l
          lw     = fromIntegral $ length w
          lr     = len - (length acc) - 1
          aw a w = a ++ " " ++ w
          dlr    = drop lr
          tlr    = take lr

brl :: Integral a => [Char] -> a -> [[Char]]
brl str l | 0 >= l    = []
          | otherwise = breakLine l (words str) [] []

digitsAcc :: Integral a => a -> a -> a -> a
digitsAcc n base acc | n >= base  = digitsAcc (n `div` base) base (acc+1)
                     | otherwise = acc

digits :: Integral a => a -> a
digits n = digitsAcc n 10 1

writenum :: Integral a => a -> a -> [Char] -> [Char]
writenum 0 base [] = "0"
writenum 0 base acc = acc
writenum n base acc
    | r == 1 = writenum q base $ '1':acc
    | r == 2 = writenum q base $ '2':acc
    | r == 3 = writenum q base $ '3':acc
    | r == 4 = writenum q base $ '4':acc
    | r == 5 = writenum q base $ '5':acc
    | r == 6 = writenum q base $ '6':acc
    | r == 7 = writenum q base $ '7':acc
    | r == 8 = writenum q base $ '8':acc
    | r == 9 = writenum q base $ '9':acc
    | r == 0 = writenum q base $ '0':acc
    where q = n `div` base
          r = n `mod` base

itoa :: Integral a => a -> [Char]
itoa x = writenum x 10 ""

mean :: Fractional a => [a] -> a
mean [] = 0
mean x  = (sum x) / (fromIntegral $ length x)

median :: (Ord a, Fractional a) => [a] -> a
median [] = 0
median x  = mean [s !! (floor hli) , s !! (ceiling hli)]
    where hli = (fromIntegral $ length x - 1) / 2
          s   = qsort x

estLines :: Integral a => a -> [[b]] -> a
estLines l w
    | mw < (l `div` 4) = lw
    | mw < (l `div` 2) = lw*2
    | mw < l           = lw*4
    | otherwise        = lw*8
    where mw = ceiling $ median $ map (fromIntegral . length) w
          lw = fromIntegral $ length w

brLinenum :: Integral a => [Char] -> a -> [(a,[Char])]
brLinenum str l = zip [1..(fromIntegral $ length lines)] lines
    where lines = brl str $ l - (digits $ estLines l $ words str) - 1

rcrop :: Integral a => a -> [Char] -> [Char]
rcrop len (h:t)
    | 0 > len = []
    | len == ll = h:t
    | len >  ll = rcrop len (' ':h:t)
    | len <  ll = rcrop len t
    where ll = fromIntegral $ length (h:t)

brln :: Integral a => [Char] -> a -> [[Char]]
brln str l = map (\(x,y) -> (rcrop nl $ itoa x) ++ " " ++ y) $ brLinenum str l
    where nl = digits $ estLines l $ words str

nSpaces :: Integral a => a -> a -> [[Char]]
nSpaces n l = take (fromIntegral n) $ repeat $
              take (fromIntegral l) $ repeat ' '

extraSpaces :: Integral a => a -> [[Char]] -> [[Char]] -> [[Char]]
extraSpaces n acc    []  = acc
extraSpaces 0 acc    sp  = acc ++ sp
extraSpaces n acc (s:sp) = extraSpaces (n-1) (acc ++ [' ':s]) sp

genSpaces :: Integral a => a -> a -> [[Char]]
genSpaces l lw = extraSpaces (l `mod` lw) [] (nSpaces lw $ l `div` lw + 1)

justify :: Integral a => [Char] -> a -> [Char]
justify str l
    | lw <= 0   = rcrop l str
    | l  <  ls  = rcrop l str
    | l  == ls  = str
    | otherwise = foldl (++) [] $
                  zipWith (++) w $ (genSpaces (l-ls) lw) ++ [""]
    where ls = fromIntegral $ length str
          w  = words str
          lw = (fromIntegral $ length w) - 1

teststr = "apple jack, pinkie pie, twilight sparkle, rarity, rainbow " ++
          "dash, fluttershy, lyra, bon bon, trixie, celestia, luna"

marmite = "I make a haddock and artichoke chowder. I've tried it with Marmite and without Marmite. The chowder, if you get the quantity of Marmite right, is great. You can't taste the Marmite, but the haddock and the artichoke become much bigger flavours. It is completely delicious. Now Unilever suggests there is a perfect way to make a classic Marmite on toast. Toast a slice of freshly baked white bread until golden brown, they say. Apply a tasty covering of real butter (about 10g), allowing it to melt while the toast is still hot. Top your creation with about four grams of Marmite, from the tip of a knife and eat immediately, while still warm.  Again, the big corporation seems to have missed the mark. The point, if there is a point to be gleaned from the hundreds of Marmite missives the newspaper has received, is that there is no one way of doing anything with Marmite.  Marmite people spread the love in their own, unique fashion. The only thing that should never change is the thing itself, the pot-bellied, heavy, British, stolid, mucky, stubborn, salty, delicious, perfect little jar of Marmite."

