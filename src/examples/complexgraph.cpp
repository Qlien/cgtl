#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "cgt/graph.h"
using namespace cgt;

#include "util.h"

class Vertex
{
  public:
    Vertex () : mV (0) { }
    Vertex (const unsigned int& v) : mV (v) { }

  public:
    const bool operator==(const Vertex& other) const { return (mV == other.mV); }
    const unsigned int& operator()() const { return mV; }

  public:
    unsigned int mV;
};

class Edge
{
  public:
    Edge () : mE (0) { }
    Edge (const double& e) : mE (e) { }

  public:
    const double& operator()() const { return mE; }
    const bool operator<(const Edge& other) const { return (mE < other.mE); }
    const bool operator<=(const Edge& other) const { return (mE <= other.mE); }
    const bool operator>(const Edge& other) const { return ! operator<=(other); }
    const bool operator>=(const Edge& other) const { return ! operator<(other); }
    Edge operator+(const Edge& other) const { return Edge (mE + other.mE); }

  public:
    double mE;
};

typedef graph<Vertex, Edge, _Undirected> mygraph;

int main ()
{
  mygraph g;

  cout << "=== creating graph ===" << endl << endl;
  add_vertex<Vertex, Edge, _Undirected>(g, Vertex (1));
  add_vertex<Vertex, Edge, _Undirected>(g, Vertex (2));
  add_vertex<Vertex, Edge, _Undirected>(g, Vertex (3));
  cout << endl;
  add_edge<Vertex, Edge, _Undirected>(g, Edge (0.01), Vertex (1), Vertex (2));
  add_edge<Vertex, Edge, _Undirected>(g, Edge (9.27), Vertex (1), Vertex (3));
  add_edge<Vertex, Edge, _Undirected>(g, Edge (3.14), Vertex (2), Vertex (3));
  cout << endl;


  cout << "=== dijkstra from vertex 1 ===" << endl << endl;

  mygraph::djiterator itd;
  mygraph::djiterator itdEnd = g.djend ();

  for (itd = g.djbegin (g.find (1)); itd != itdEnd; ++itd)
  {
    const mygraph::node&       n = *itd;
    const mygraph::vertex&     v = n.vertex ();

    const mygraph::dijkstra_info* i = itd.info (n);

    cout << "vertex: " << v.value ()() << ", distance: " << i->distance ()() << ", previous: " << (i->previous () ? i->previous ()->vertex ().value () ():0) << endl;
  }

  cout << endl;
  cout << "=== show dijkstra info for all vertices ===" << endl << endl;

  mygraph::const_iterator itn;
  mygraph::const_iterator itnEnd = g.end ();

  for (itn = g.begin (); itn != itnEnd; ++itn)
  {
    const mygraph::node&   n = *itn;
    const mygraph::vertex& v = n.vertex ();
    const mygraph::dijkstra_info* i = itd.info (n);

    cout << "vertex: " << v.value ()() << ", distance: " << i->distance ()() << ", previous: " << (i->previous () ? i->previous ()->vertex ().value () ():0) << endl;
  }

  cout << endl;
  cout << "=== show the same using dijkstra info iterator ===" << endl << endl;

  mygraph::const_djiiterator it;
  mygraph::const_djiiterator itEnd = g.djiend (itd);

  for (it = g.djibegin (itd); it != itEnd; ++it)
  {
    const mygraph::dijkstra_info& i = *it;

    cout << "vertex: " << i.node ().vertex ().value ()() << ", distance: " << i.distance ()() << ", previous: " << (i.previous () ? i.previous ()->vertex ().value () ():0) << endl;
  }

  cout << endl;

  return 0;
}
