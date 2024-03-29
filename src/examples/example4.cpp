/*
 * undirected graph
 *
 * trying to insert duplicated vertexs and edges
 */

#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

#include "cgt/graph.h"
using namespace cgt;

typedef graph<string, int, _Undirected> mygraph;

int main ()
{
  mygraph g;

  g.insert_vertex ("A");
  g.insert_vertex ("A");	// duplicated vertex, won't be added

  g.insert_vertex ("B");
  g.insert_vertex ("B");	// duplicated vertex, won't be added

  g.insert_vertex ("C");
  g.insert_vertex ("C");	// duplicated vertex, won't be added

  g.insert_edge (0, "A", "B");
  g.insert_edge (1, "A", "B");	// duplicated edge, won't be added

  g.insert_edge (2, "B", "C");
  g.insert_edge (3, "C", "B");	// duplicated edge, won't be added

  g.insert_edge (4, "C", "A");
  g.insert_edge (5, "A", "C");	// duplicated edge, won't be added

  cout << endl;
  cout << "directed graph: " << (g.is_directed () ? "true":"false") << endl;
  cout << endl;

  mygraph::const_iterator itn;
  mygraph::const_iterator itnEnd = g.end ();

  for (itn = g.begin (); itn != itnEnd; ++itn)
  {
    const mygraph::node&     n = *itn;
    const mygraph::vertex&  v = n.vertex ();

    cout << "vertex: " << v.value () << endl;

    const mygraph::adjlist &adjList = n.adjlist ();

    mygraph::adjlist::const_iterator itadj;
    mygraph::adjlist::const_iterator itadjEnd = adjList.end ();

    for (itadj = adjList.begin (); itadj != itadjEnd; ++itadj)
    {
      const mygraph::edge&     e   = itadj->edge ();
      const mygraph::vertex&  v1  = e.v1 ();
      const mygraph::vertex&  v2  = e.v2 ();

      cout << "  edge (" << e.value () << ", " << v1.value () << ", " << v2.value () << ")" << endl;
    }
  }

  return 0;
}
