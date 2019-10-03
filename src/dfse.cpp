#include <Rcpp.h>
using namespace Rcpp;


List subgraphs = List::create();


int getIndex(IntegerMatrix& table, int& a, int& b) {
  for(int i = 0; i < table.nrow(); i++) {
    if(table(i,0) == a && table(i,1) == b) {
      return table(i,2);
    }
  }
  return 0;
}

IntegerVector newToOldIndex(IntegerVector& v0, IntegerVector& v1) {
  IntegerVector sto(v0.length());
  for(int i=0; i < v0.length(); i++) {
    sto[i] = v1[v0[i]];
  }
  return sto;
}

void expandSubgraph(
    IntegerVector path,
    IntegerVector s,
    IntegerVector forbidden,
    int index,
    List& m,
    IntegerMatrix& table,
    IntegerVector& reference
) {
  int v = path[path.length()-1];
  IntegerVector mv = m[v];
  IntegerVector newS;
  IntegerVector newPath;
  for(int i=index; i < mv.length(); i++) {
    int u = mv[i];
    bool uInForbidden = is_true(any(forbidden == u));
    bool uInS = is_true(any(s == u));
    if(! (uInForbidden || uInS)) {
      newS = s;
      newS.push_back(u);
      newPath = path;
      newPath.push_back(u);
      expandSubgraph(newPath, newS, forbidden, 0, m, table, reference);
      forbidden.push_back(u);
    }
  }
  path.erase(path.length()-1);
  if(path.length() > 0) {
    int w = path[path.length()-1];
    index = getIndex(table, w, v) + 1;
    expandSubgraph(path, s, forbidden, index, m, table, reference);
  } else {
    IntegerVector sOld = newToOldIndex(s, reference);
    if(sOld.length() == 1) {
      subgraphs.push_back(sOld[0]);
    } else {
      subgraphs.push_back(sOld);
    }
  }
}


// [[Rcpp::export]]
List DFSE(List& m, IntegerMatrix& table, IntegerVector& reference) {
  subgraphs = List::create();
  IntegerVector forbidden(0);
  IntegerVector path(1);
  IntegerVector s(1);
  for (int i = 0; i < m.length(); i++) {
    if(i > 0) {
      forbidden.push_back(i-1);
    }
    path[0] = i;
    s[0] = i;
    expandSubgraph(path, s, forbidden, 0, m, table, reference);
  }
  return subgraphs;
}

