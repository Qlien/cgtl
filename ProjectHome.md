A graph template library for C++ under construction.

Here is simple example that explains how to create and iterate a graph by nodes using CGTL:

```
cgt::graph<string, int> g;

g.insert_vertex ("A");
g.insert_vertex ("B");
g.insert_vertex ("C");
g.insert_edge (1, "A", "B");
g.insert_edge (2, "A", "C");
g.insert_edge (3, "B", "C");

for (cgt::graph<string, int>::const_iterator it = g.begin (); it != g.end (); ++it)
{
    const cgt::graph<string, int>::node&     n    = *it;
    const cgt::graph<string, int>::vertex&   v    = n.vertex ();
    const cgt::graph<string, int>::adjlist&  adjs = n.adjlist ();

    cout << "vertex " << v.value () << " with " << adjs.size () << " edges" << endl;
}
```

You can iterate using breadth-first search too:

```
for (cgt::graph<string, int>::const_biterator it = g.bbegin (); it != g.bend (); ++it)
{
    const cgt::graph<string, int>::node&     n    = *it;
    const cgt::graph<string, int>::vertex&   v    = n.vertex ();
    const cgt::graph<string, int>::adjlist&  adjs = n.adjlist ();

    cout << "vertex " << v.value () << " with " << adjs.size () << " edges" << endl;
}
```

The breadth-first algorithm provides some information about each step of its execution, and you can access these informations as follows:

```
for (cgt::graph<string, int>::const_biterator it = g.bbegin (); it != g.bend (); ++it)
{
    const cgt::graph<string, int>::node&         n = *it;
    const cgt::graph<string, int>::vertex&       v = n.vertex ();
    const cgt::graph<string, int>::breadth_info* i = it.info (n);

    cout << "vertex " << v.value ()
         << ", parent: " << (i->parent () ? i->parent ()->vertex ().value ():"-")
         << ", discovery: " << setw (2) << i->discovery ()
         << ", finish: " << setw (2) << i->finish () << endl;
}
```

It's possible to do the same thing using depth-first search.

The class graph provides the following list of iterators:
  * node iterator;
  * vertex iterator;
  * edge iterator;
  * breadth-first search iterator;
  * depth-first search iterator;
  * dijkstra iterator;
  * strongly connected components iterator;
  * kruskal iterator;
  * prim iterator;
  * topological sort iterator.