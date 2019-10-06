
<!-- README.md is generated from README.Rmd. Please edit that file -->

# subgraphs

<!-- badges: start -->

<!-- badges: end -->

The goal of subgraphs is to enumerate efficiently all connected
subgraphs of a graph. I use the algorithm of Skibski et al (2019),
implemented in C++. Because I hope that this package will be someday
integrated into the main `R` packages for network analysis
(i.e. `igraph` and `network`), I purposely do not rely on their formats
to store graphs, and instead just use (sparse) adjacency matrices. To
convert a graph to an adjacency matrix, use `igraph::as_ajd` or
`network::as.matrix`.

## Installation

You can install the released version of subgraphs from
[CRAN](https://CRAN.R-project.org) with:

``` r
install.packages("subgraphs")
```

And the development version from [GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("rferrali/subgraphs")
```

## Example

This is a basic example which shows you how to enumerate subgraphs for a
line graph where 1 is connected to 2 who is connected to 3:

``` r
library(subgraphs)
## create a simple graph
g <- matrix(c(
  0,1,0, 
  1,0,1,
  0,1,0
), nrow = 3, ncol = 3)
## enumerate the subgraphs
subgraphs(g)
#> [[1]]
#> [1] 2 1 3
#> 
#> [[2]]
#> [1] 2 1
#> 
#> [[3]]
#> [1] 2 3
#> 
#> [[4]]
#> [1] 2
#> 
#> [[5]]
#> [1] 1
#> 
#> [[6]]
#> [1] 3
```
