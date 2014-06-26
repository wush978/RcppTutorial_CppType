---
title       : Rcpp / C++ 線上講座 -- R 和 C++的形態轉換(簡介C++的形態)
subtitle    : 
author      : 
job         : 
framework   : io2012        # {io2012, html5slides, shower, dzslides, ...}
highlighter : highlight.js  # {highlight.js, prettify, highlight}
hitheme     : zenburn      # 
widgets     : [mathjax, quiz]            # {mathjax, quiz, bootstrap}
mode        : selfcontained # {standalone, draft}
knit        : slidify::knit2slides
--- .segue .dark




## 原子形態

--- &vcenter .large

<!-- html table generated in R 3.0.3 by xtable 1.7-3 package -->
<!-- Thu Jun 26 21:23:36 2014 -->
<TABLE border=1>
<TR> <TH>  </TH> <TH> C原子形態 </TH> <TH> 意義 </TH> <TH> 對應的R原子形態 </TH> <TH> 大小.位元組. </TH>  </TR>
  <TR> <TD align="right"> 1 </TD> <TD> bool </TD> <TD> 布林 </TD> <TD> logical(註) </TD> <TD align="right">  </TD> </TR>
  <TR> <TD align="right"> 2 </TD> <TD> char </TD> <TD> 字元 </TD> <TD> character(註) </TD> <TD align="right">   1 </TD> </TR>
  <TR> <TD align="right"> 3 </TD> <TD> short </TD> <TD> 短整數 </TD> <TD>  </TD> <TD align="right">   2 </TD> </TR>
  <TR> <TD align="right"> 4 </TD> <TD> int </TD> <TD> 整數 </TD> <TD> integer </TD> <TD align="right">   4 </TD> </TR>
  <TR> <TD align="right"> 5 </TD> <TD> long </TD> <TD> 長整數 </TD> <TD> POSIXct(註) </TD> <TD align="right">   8 </TD> </TR>
  <TR> <TD align="right"> 6 </TD> <TD> float </TD> <TD> 浮點數 </TD> <TD>  </TD> <TD align="right">   4 </TD> </TR>
  <TR> <TD align="right"> 7 </TD> <TD> double </TD> <TD> 雙精確服點數 </TD> <TD> double </TD> <TD align="right">   8 </TD> </TR>
   </TABLE>


--- &twocol

## 查詢物件的記憶體大小

`sizeof` 可以印出物件需要的記憶體大小(位元組)

*** =left


```cpp
#include <Rcpp.h>
using namespace Rcpp;
//[[Rcpp::export]]
void showSize() {
  Rcout << sizeof(bool) << std::endl;
  Rcout << sizeof(char) << std::endl;
  Rcout << sizeof(short) << std::endl;
  Rcout << sizeof(int) << std::endl;
  Rcout << sizeof(long) << std::endl;
  Rcout << sizeof(float) << std::endl;
  Rcout << sizeof(double) << std::endl;
}
```


*** =right

<br/><br/><br/>

```
## 1
## 1
## 2
## 4
## 8
## 4
## 8
```


--- &radio

## 小挑戰

資料出處: [wiki人類基因組](http://zh.wikipedia.org/wiki/%E4%BA%BA%E9%A1%9E%E5%9F%BA%E5%9B%A0%E7%B5%84)

人類基因組含有約30億個DNA鹼基對，鹼基對是以氫鍵相結合的兩個含氮鹼基，以胸腺嘧啶（T）、腺嘌呤（A）、胞嘧啶（C）和鳥嘌呤（G）四種鹼基排列成鹼基序列。

如果我們以一個位元組(`char`)來儲存一個人的基因組，大約需要多大的記憶體？

提示: 1KB約表示1000位元組, 以此類推

1. 約 3KB
2. 約 3MB
3. _約 3GB_
4. 約 3TB

*** =pnotes

30億為$3 \times 10^9$

$3$ GB = $3 \times 2^10$ MB = $3 \times 2^20$ KB = $3 \times 2^30$ 位元組

--- &vcenter .large

面對大量資料

可估計需要的記憶體

--- &twocolvcenter .large

## 指針, 記憶體的住址

*** =left


```cpp
#include <Rcpp.h>
using namespace Rcpp;
//[[Rcpp::export]]
void showAddress(SEXP a) {
  Rprintf("%p\n", a);
}
```


*** =right


```r
showAddress(iris)
```

```
## 0x384cd98
```


--- &vcenter 

## 32位元與64位元


```r
showAddress(iris)
```

```
## 0x384cd98
```


HexCode: 0 ~ F, 兩個字母表示一個位元組

所以可以用$2^6 = 64$個bit表示記憶體的住址。

32位元的電腦僅用$2^5 = 32$個bit表示記憶體的住址，

$2^32個$個位元組約為4GB

--- &radio

## 小挑戰

64位元的電腦，記憶體大概為多少?

1. 小於TB($2^{40}$ 位元組)
1. 小於PB($2^{50}$ 位元組)
1. 小於EB($2^{60}$ 位元組)
1. _小於ZB($2^{70}$ 位元組)_

--- &vcenter .large

取住址的運算子: `&`

取值的運算子: `*`


```cpp
#include <Rcpp.h>
using namespace Rcpp;
//[[Rcpp::export]]
int getInt() {
  int a = 1;
  int* pa = &a; // pa 是 a 的住址
  return (*pa); // 把住在pa的人拿出來
}
```


*** =pnotes

[1] 1


--- &twocolvcenter 

## 字串的本質: char*, char[]

*** =left


```cpp
#include <Rcpp.h>
using namespace Rcpp;
//[[Rcpp::export]]
void getChar(CharacterVector src) {
  const char* ps = CHAR(src[0]);
  char tmp;
  for(int i = 0;i < 7;i++) {
    tmp = ps[i];
    Rcout << tmp << std::endl;
  }
}
/*** R
getChar("setosa")
*/
```


*** =right

`{'s', 'e', 't', 'o', 's', 'a', 0x00}`

陣列住標運算子:`[`


```
## s
## e
## t
## o
## s
## a
```


--- &twocolvcenter 

## 字串的本質: char*, char[]

*** =left


```cpp
#include <Rcpp.h>
using namespace Rcpp;
//[[Rcpp::export]]
void changeChar(CharacterVector src) {
  char* ps =
    const_cast<char*>(CHAR(src[0]));
  ps[0] = 'z';
}
/*** R
a <- "setosa"
tracemem(a)
changeChar(a)
a
*/
```


*** =right


```
## [1] "zetosa"
```


`{'s', 'e', 't', 'o', 's', 'a', 0x00}` $\Rightarrow$ `{'z', 'e', 't', 'o', 's', 'a', 0x00}`

--- &vcenter .large

運用指標就可以避免記憶體的拷貝

--- &vcenter .large

指標的形態非常重要

--- &twocolvcenter

*** =left


```cpp
#include <Rcpp.h>
using namespace Rcpp;
//[[Rcpp::export]]
int changePtr() {
  char* ps = "setosa";
  int* pi = (int*) ps;
  return *pi;
}
/*** R
changePtr()
*/
```


*** =right


```
## [1] 1869899123
```


- s: 0x73
- e: 0x65
- t: 0x74
- o: 0x6f

0x7365746f

0x6f746573

--- &vcenter

## 為什麼bool的轉形會變成0 or 1?


```r
as.character(TRUE)
```

```
## [1] "TRUE"
```



```cpp
#include<Rcpp.h>
using namespace Rcpp;
//[[Rcpp::export]]
void bool2char() {
  bool b = true;
  Rprintf("%hhX", (char) true);
}
/*** R
bool2char()
*/
```



```
## 1
```


--- &twocolvcenter

## R 的字串結尾一定是 0x00

*** =left


```r
a <- c("a", "setosa", "我是中文", "xxas;")
nchar(a, type = "bytes")
```

```
## [1]  1  6 12  5
```



```cpp
#include<Rcpp.h>
using namespace Rcpp;
//[[Rcpp::export]]
void showTail(CharacterVector src, IntegerVector len) {
  for(int i = 0;i < src.size();i++) {
    const char* ps = CHAR(src[i]);
    Rprintf("%hhX\n", ps[len[i]]);
  }
}
/*** R
showTail(a, nchar(a, type="bytes"))
*/
```


*** =right


```
## 0
## 0
## 0
## 0
```


--- &vcenter .large

C++ 處理字串有很方便的物件:

`std::string`

--- &vcenter .large

`std::string`是一個C++ 類別(class)

類別有:

- 建構子(constructor)
- 解構子(destructor)
- 成員函數(member function)
- 資料成員(data member)

--- &twocol

## [建構子](http://www.cplusplus.com/reference/string/string/string/)




--- &vcenter .large

今天沒講到的有:

- const
- const char*
