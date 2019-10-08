
#' Enumerate all connected subgraphs of a graph
#' @param g a (possibly sparse) adjacency matrix of an undirected, unweighted graph.
#' @details the matrix \code{g} should be the adjacency matrix of an undirected, unweighted graph.
#' Its values should be either 0 or 1. It should be symmetric and have only zeroes on the diagonal. It can be a sparse matrix as
#' created by the package \code{Matrix}. This function uses the Depth-First-Search Enumeration algorithm of Skibski et al. (2018).
#' @return a list where each element is a vector of the ids of the vertices forming a connected subgraph.
#' @references
#' O. Skibski, T. Rahwan, T. Michalak, M. Wooldridge (2019).
#' "Enumerating Connected Subgraphs and Computing the Myerson and Shapley Values in Graph-restricted Games”.
#' \emph{ ACM Transactions on Intelligent Systems and Technology}. 10(2), 15. Publisher: ACM (Association for Computing Machinery).
#' @examples
#' g <- matrix(c(
#' 0,1,0,
#' 1,0,1,
#' 0,1,0
#' ), nrow = 3, ncol = 3)
#' subgraphs(g)
#' @export

subgraphs <- function(g) {
  g <- tryCatch(
    Matrix::Matrix(g, sparse = T),
    error = function(e) {
      stop("g cannot be coerced to a Matrix.")
    }
  )
  if(!Matrix::isSymmetric(g)) stop("g is not a symmetric matrix")
  if(any(Matrix::diag(g) != 0)) stop("g has non-zero diagonal elements")
  if(anyNA(g)) stop("g has NA values")
  if(any(g@x != 1)) stop("g has values that are neither 1 or 0")

  deg <- Matrix::rowSums(g)
  ord <- order(deg, decreasing = T)
  g <- g[ord, ord]
  m <- apply(g, 1, function(v) which(v != 0)-1)

  table <- mapply(
    function(v, i) {
      if(length(v) > 0) {
        cbind(i-1, v, (1:length(v))-1)  
      } else {
        matrix(0, 0, 3)
      }
      
    },
    m, 1:length(m)
  )
  table <- do.call(rbind, table)

  DFSE(m, table, ord)
}

