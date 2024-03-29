#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "cgt/graph.h"
using namespace cgt;

#include "util.h"

typedef graph<string, int> mygraph;

int main ()
{
  mygraph g;

  cout << "=== creating graph ===" << endl << endl;
  create_graph_1<string, int> (g);

  cout << "=== dijkstra from vertex E ===" << endl << endl;

  mygraph::djiterator itd;
  mygraph::djiterator itdEnd = g.djend ();

  for (itd = g.djbegin (g.find ("E")); itd != itdEnd; ++itd)
  {
    const mygraph::node&       n = *itd;
    const mygraph::vertex&     v = n.vertex ();

    const mygraph::dijkstra_info* i = itd.info (n);

    cout << "vertex: " << v.value () << ", distance: " << i->distance () << endl;
  /*

    cout << "itd: " << v.value () <<  ", discovery: " << setw (2) << i->discovery () << ", parent: " << (i->parent () ? i->parent ()->vertex ().value ():"-") << endl;
    */
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

    if (i)
      cout << "vertex: " << v.value () << ", distance: " << i->distance () << endl;
//    cout << "node: " << v.value () << ", parent: " << (i->parent () ? i->parent ()->vertex ().value ():"-") << ", discovery: " << setw (2) << i->discovery () << ", finish: " << setw (2) << i->finish () << endl;
  }

  cout << endl;
  cout << "=== show the same using dijkstra info iterator ===" << endl << endl;

  mygraph::const_djiiterator it;
  mygraph::const_djiiterator itEnd = g.djiend (itd);

  for (it = g.djibegin (itd); it != itEnd; ++it)
  {
    const mygraph::dijkstra_info& i = *it;

    cout << "vertex: " << i.node ().vertex ().value () << ", distance: " << i.distance () << endl;
//    cout << "node: " << i.node ().vertex ().value () << ", parent: " << (i.parent () ? i.parent ()->vertex ().value ():"-") << ", discovery: " << setw (2) << i.discovery () << ", finish: " << setw (2) << i.finish () << endl;
  }

  cout << endl;

  return 0;
}
