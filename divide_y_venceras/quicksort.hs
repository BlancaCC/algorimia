{-
ALGORITMO DE ORDENACIÓN QUICKSORT
  -}
quicksort :: Ord(a) => [a] -> [a]
quicksort [] = []
quicksort [a]= [a]
quicksort (x:xs) = quicksort [ y | y<-xs, y <= x] ++[x] ++ quicksort[ y| y<- xs, y>x ]

  
