module Prim where
 
import Data.List
import Data.Array
 
--building the adjacency matrix -> creating az associative array
toGraph vertices graph =
    accumArray (\xs x -> x:xs)                                       -- accumulating function
                []                                                   -- start point
                vertices                                             -- limits
                ([(x1,(x2,w)) | (x1,x2,w) <- graph, x1 /= x2] ++     -- add each edge twice to the matrix
                [(x2,(x1,w)) | (x1,x2,w) <- graph, x1 /= x2])
 
 
edges graph = [(v1,v2,w) | v1 <- indices graph, (v2,w) <- graph!v1]     --vertices list -> edge list
 
prim graph = prim' [travelled] ns es []                  
    where 
        (travelled:ns) = indices graph                                --ns = list of vertices in crescending order, travelled = starting point
        es = edges graph                                              --es = list of edges


prim' _ [] _ ans = ans                                               --stopping point, ans = the minimal spanning tree
prim' travelled next es ans = let e@(c2,u2,v2) = minimum [(c,u,v) | (u,v,c) <- es, elem u travelled, elem v next]  
                in  prim' (v2:travelled) (delete v2 next) es (e:ans) 
                          
    
weightOf xs = sum[ a | ( a,_,_ ) <- xs]                               -- sum of the weights of the minimum spanning tree




graph1 = toGraph (1,7)                                                --creating a graph  (vertex, vertex, weight of the edge)
             [(1,2,12),(1,3,34),(1,5,78),(2,4,55),
              (2,5,32),(2,7,4),(3,4,61),(3,5,44),
              (4,5,93),(5,6,1),(6,7,8)]        

graph2 = toGraph (1,4)                                                --creating a graph  (vertex, vertex, weight of the edge)
             [(1,2,1011),(1,3,1000),(2,4,1000),(3,4,1)] 


graph3 = toGraph (1,9)                                                --creating a graph  (vertex, vertex, weight of the edge)
             [(1,2,12),(1,3,34),(1,5,78),(2,4,55),                    --no route -> error
              (2,5,32),(3,4,61),(3,5,44),(4,5,93),
              (1,6,11),(6,7,8),(2,7,4),(8,9,33)]        
