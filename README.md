cache size in bytes
block size in bytes
type of cache alloction "D":1 "T":2 "F":3
write through:1 or write allocation:2 
Array i size
Array j size 


print out two tables that have a hit and miss map 


what the code does: 

first sets up the map of source and destination this will  be set up initally as a int ** so i can have the ability to turn it into a bit ** because i really only need a hit marker or a miss marker. 

second I will create the input for the file this will go as follows. ./simulate <cache size(in bytes)> , <block size (in bytes)>, <type of allocation 1-3>, <write type>, <src i>, <src j>
