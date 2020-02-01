# CME 212: Lecture 9

## Graph `remove*`

In Homework 2, we ask you to implement `remove_node` and `remove_edge` in a variety of different ways; the use case is to allow us to 
simulate tearing a hole in fabric! As part of the process, 
you are allowed to invalidate `Node`s and `Edge`s, 
but doing so might result in more complex invariants and 
more work to be performed within the `remove*` methods. 
In order to accomplish this feat, 
the concepts of `Node` `uid` and `idx` need to be separated:
there will be a _user facing_ `idx` which tracks nodes in a way that users 
care about (i.e. there are never gaps between valid `idx`s and the maximum 
`idx` is one less than the number of nodes); then there will also be an
_internal_ `uid` that is used to track _all_ information entered into the
program.
We expanded the data members of graph to include an additional field
```c++
struct nodeinfo
{
  Point p_
  node_value_type v_;
  size_type idx_;  // New member attribute! This is what our users care about.
  ...
};

// Used to store nodeinfo for any node added, even if later removed.
std::vector<nodeinfo> nodes_; // Indexed by node uid
// Store the currently "active" set of nodes.
std::vector<uid_type> i2u_;   // Indexed by node idx
```
so that we can map back and forth between node indices and node unique identifiers. 
When we remove a node, we won't delete the internal information
(doing so would require that we move things around in memory), instead we simply
ensure
the user cannot access that information by removing the `uid` from the `i2u`
vector; we can remove an arbitrary element from `i2u` in constant time by first
swapping the position with the tail element of the array then popping off the
last element.

All of this has impact on our abstraction functions and representation invariants. Stating these explicitly
can aid in our implementation.

The additional `idx_` member in the `nodeinfo` data structure will 
certainly be useful when calling `node.index()`. The new, additional data structure `i2u_` will certainly be needed when looking nodes up by _index_ via `graph.node(i)`.


### Abstraction functions ###

The abstraction function, now looks like this:

- _AF_(`Graph`) = (_N_, _E_) where
    - _N_ = { _n<sub>i</sub>_ | 0 &le; _i_ < _m_ = `i2u_.size()`},
    - _E_ = { {_n<sub>i</sub>_, _n<sub>j</sub>_} | 0 &le; i < j < _m_ and `i2u_[i]` &isin; `adj_[i2u_[j]]`}.
    - _n<sub>i</sub>_ = (`nodes_[i2u[i]].p`, `nodes_[i2u[i]].v`, _i_)

Note that the total number of nodes is now defined by the `i2u_` structure rather than the `nodes_` structure: `i2u` stores our currently active set of nodes versus the `nodes_` structure which keeps track of all nodes that were ever a part of the graph; recall that we are applying our "swap and pop" operation to our `i2u` vector and in this way we maintain our representation invariant about the size of the graph. 
Further, we now convert abstract indices in 
the _AF_ to `uid`s where required, and we will
have to do the same in the implementation. It's also no accident that we are retreiving a node's data attributes (position, value, and index) using the
`nodes_` vector, which stores data with permanence.

One key thing to note is that the particular values of `i2u_` do not occur in the abstract value
(the output of the abstraction function), i.e. we are never exposing the internal node `uid` to the user; this is important, and common. Good data
structures often include helper members that don't match directly to parts of the corresponding abstract value. We use these helper members to make the 
data structure better -- either faster or,
as in our example, less likely to cause problems for users -- 
it would be very difficult to use a `Graph`
whose `Node` objects all got invalidated by a sequence of `remove_node` operations, and this is what we want! 
Thus, many graph representations with different `uid` values will map to the same abstract graph; put differently, we can end up with the same Graph by different sequences of adding and deleting nodes, and although the Graph's abstract value would remain the same the `uid`s behind them might differ.
In this way, we can say that the _AF_ is invariant 
under changes in values within `i2u_`.


### Representation invariants ###

For Graph, the representation invariant needs to check that
the `nodes_` and `i2u_` arrays are _synchronized_. We translate the specification in Homework 2 that
`graph.node(i).index() == i` into the Graph _RI_:

_RI_(`Graph`) For every _i_ with 0 &le; i < `i2u_.size()`, the following holds:`nodes_[i2u_[i]].idx_ == i`.

Several other useful consistency requirements are actually implicitly expressed by this invariant:

- For each _i_ with 0 &le; _i_ < `i2u.size()`, it holds 0 &le; `i2u_[i]` < `nodes_.size()`.
Realize that this is implied since otherwise the element access `nodes_[i2u[i]]` would fail. To see it another way: if we never remove nodes/data from `nodes_` vector which stores node data with permanence, then of course the size of the set of "active nodes" is within range of the number of nodes ever added to the graph.

- The unique identifiers in `i2u_` are disjoint: If 0 &le; i < j < `i2u.size()`, then `i2u_[i]` &ne; `i2u_[j]`. That is, if we have two different indices that are in range of the size of our graph, these two indices will correspond to nodes with different unique identifiers; this is implied since `nodes_[i].idx_` can take only one value.

It's usually good to express the invariant as compactly as possible, since that makes it easier
to understand and prove. Again, these conditions are relatively easy to prove and/or check
via assertion in your member functions.

Our representation invariant doesn't mention `position_` or `value_` because there are no
internal consistency requirements on those fields. The abstraction function and representation
invariant serve different purposes and can be quite independent.

<!-- The key thing to note here is that values not listed in the abstract concept --> <!-- appear in the -->
<!-- representation invariant. This is again important, and common. We add helper --> <!-- members -->
<!-- to improve the data structure, but they have to be correct to help! And --> Here, the basic
correctness requirement on our nodes is that the `idx_` member is right and that the unique identification numbers are unique.

Abstraction functions always work on valid representations, so if _RI_(_x_) is false it is OK for
_AF_(_x_) to break or return weird garbage.


### Node abstraction function and representation invariants ###

The `Node` sub-object has its own abstraction function and representation
invariant that are useful to write down. The abstract value of a node is a sub-value of that
of a graph.

_AF_(`Node`) = _n<sub>i</sub>_ = (`g_->nodes_[uid_].p_`, `g_->nodes_[uid_].v_`, `g_->nodes_[uid_].idx_`)

_RI_(`Node`) = 0 &le; uid_ < `g_->nodes_.size()`.

Do you think this is complete, though? Think about it for a minute.
It is not complete, because removed nodes are invalid, but their uids are still in range by
design, since we've decided to store the data with permanence in `nodes_`! We can improve the representation invariant to catch removed nodes this way:

_RI_(`Node`) = `g_->i2u_[g_->nodes_[uid_].idx_] == uid_`.

Again we can elide some implied requirements, such as that uid and `g_->nodes[uid_].idx_`
are in range for their respective arrays, since if the node's index is out-of-range or `i2u_` and `uid_`
don't match, this signifies the node has been deleted. This is very cool: we can add a complexity _O_(1) function `valid()`
to the class `Node` that verifies a node is valid, and then use that function in assertions!

```c++
class Node
{
  ...
private:
  bool valid() const
  {
    return uid_>= 0 && uid_< g_->nodes_.size()         // uid in range.
           && g_->nodes_[uid_].idx_ < g_->i2u_.size()  // idx in range.
           && g_->i2u_[g_->nodes_[uid_].idx_] == uid_; // uid in sync.
  }
public:
  Point& position()
  {
    assert(valid());
    return g_->nodes_[uid_].p_;
  }
  ...
};
```
Note how `valid()` actually contains the implied requirements from the representation invariant, not just the main requirement. This is important. The purpose of `valid()` is to detect
invalid nodes, so unlike most other operations, it doesn't assume its input is totally valid, i,.e. that the representation invariant is true. The carefully written out checks avoid crashing when a node is invalid and (say) has `idx_` that's out of range for `i2u_`. 
