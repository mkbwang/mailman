#include <math.h> 
#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;

using arma::mat;
using arma::colvec;
using arma::rowvec;
using arma::vec;
using namespace std;

// [[Rcpp::export]]
colvec mailman_multiply(colvec& myvec, int rownum, int colnum){
    // do the matrix multiplication from bottom up
    // resize the vector sum up columns/rows
    // dot product with corresponding "building blocks"
    colvec result = arma::zeros<colvec>(rownum); 
    for (int i=0; i<rownum; i++){
      mat newmat(myvec);
      int matrow = colnum/pow(3,i);
      newmat.set_size(matrow, pow(3,i));
      colvec colsum= arma::sum(newmat, 1);
      result(i) = arma::sum(colsum.subvec(int(matrow/3), int(matrow*2/3 - 1))) +
        arma::sum(colsum.tail(matrow/3)) * 2;
    }
    return result;
    //mat newmat = myvec;
    //newmat.set_size(3,9);
    //cout << newmat << endl;
    // cout << myvec << endl;
    //cout << myvec.subvec(0,5) << endl;
}


/*** R
library(RcppArmadillo)
# binarymat=matrix(0,3,8)
# for (i in 1:3){
#   element = rep(seq(0,1), each=8/(2^i))
#   binarymat[i,]=rep(element, 2^(i-1))
# }
toy_mailman = function(rownum){
  # generate the matrix that contains only 0, 1 and 2
  colnum = 3^rownum
  trimat = matrix(0,rownum, colnum)
  for (i in 1:rownum){
    element = rep(seq(0,2), each=colnum/(3^i))
    trimat[i,] = rep(element, 3^(i-1))
  }
  randomvec = runif(n = colnum, min = 1, max = 10) # vector to multiply with
  ptm <- proc.time()
  product = trimat %*%randomvec # regular multiplication
  Rtime = proc.time() - ptm
  # next is the mailman algorithm
  ptm <- proc.time()
  mailman_product = mailman_multiply(randomvec, rownum, colnum)
  mailmantime = proc.time() - ptm
  # check if the result is the same
  print(paste(c("Are they the same? ",all(product==mailman_product)), collapse = ""))
  print(t(product))
  print(t(mailman_product))
  print(paste(c("R time: ", Rtime[[1]]), collapse = ""))
  print(paste(c("Mailman time: ", mailmantime[[1]]), collapse = ""))
}


toy_mailman(14)

*/