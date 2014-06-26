#include <string>
#include <Rcpp.h>
using namespace Rcpp;
//[[Rcpp::export]]
SEXP constuct1() {
//  const char* p = "abcde";
//  const char p[] = {'a', 'b', 0x0, 'd', 'e', 0x0};
  std::string a(5, 'a');
  a.resize(10, 'b');
  Rcout << a.size() << std::endl;
  return wrap<std::string>(a);
}
/*** R
constuct1()
*/