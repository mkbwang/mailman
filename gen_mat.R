binarymat=matrix(0,3,8)
for (i in 1:3){
  element = rep(seq(0,1), each=8/(2^i))
  binarymat[i,]=rep(element, 2^(i-1))
}

# 
set.seed(1)
randomvec=runif(n = 8, min = 1, max = 10)
binarymat %*% randomvec
  #