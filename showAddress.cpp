#include <Rcpp.h>
using namespace Rcpp;
//[[Rcpp::export]]
void showAddress(SEXP a) {
  Rprintf("%p\n", a);
}