# CME 212: Lecture 9

## Graph `remove*` ##

In lecture, we addressed the case where no outstanding `Node`s or `Edge`s are invalidated by
the `remove*` methods of `Graph`, though this is not technically required by Homework 2. In Homework 2,
you are allowed to invalidate `Node`s and `Edge`s, but doing so might result in more complex
invariants and more work to be performed within the `remove*` methods. We argued that in
order to accomplish this feat, the concepts of `Node` `uid` and `idx` needed to be separated. We
expanded the data members of graph to include
```c++
struct nodeinfo
{
  size_type idx_;
  ...

};

std::vector<nodeinfo> nodes_; // Indexed by node uid
std::vector<uid_type> i2u_;   // Indexed by node idx
```
so that we can map back and forth between node indices and node unique identifiers. This has
impact on our abstraction functions and representation invariants. Stating these explicitly
can aid in our implementation.

The additional `idx_` member in the `nodeinfo` data structure will clearly be useful when
calling `node.index()`. The new, additional data structure `i2u_` will certainly be needed
when looking nodes up by index via `graph.node(i)`.


### Abstraction functions ###

The abstraction function, now looks like this:

- _AF_(`Graph`) = (_N_, _E_) where
    - _N_ = { _n<sub>i</sub>_ | 0 &le; _i_ < _m_ = `i2u_.size()`},
    - _E_ = { {_n<sub>i</sub>_, _n<sub>j</sub>_} | 0 &le; i < j < _m_ and `i2u_[i]` &isin; `adj_[j]`}.
    - _n<sub>i</sub>_ = (`nodes_[i2u[i]].p`, `nodes_[i2u[i]].v`, _i_)

Note that the total number of nodes is now defined by the `i2u_` structure rather than the
`nodes_` structure. We now convert abstract indices in the _AF_ to `uid`s where required and will
have to do the same in the implementation.

One key thing to note is that the particular values of `i2u_` do not occur in the abstract value
(the output of the abstraction function). This is important, and common. Good data
structures often include helper members that don't match directly to parts of the corresponding
abstract value. We use those members to make the data structure better -- either faster or,
as here, less likely to cause problems for users -- it could be very difficult to use a `Graph`
whose `Node` objects all got invalidated by every `remove_node` operation. Thus, many graph
representations with different `uid` values will map to the same abstract graph. Therefore,
the _AF_ is invariant under changes in values within `i2u_`.


### Representation invariants ###

For Graph, the representation invariant needs to check that
the nodes and i2u arrays are synchronized. We translate the specification in Homework 2 that
`graph.node(i).index() == i` into the Graph _RI_:

_RI_(`Graph`) For every _i_ with 0 &le; i < `i2u_.size()`, the following holds:`nodes_[i2u_[i]].idx_ == i`.

Several other useful consistency requirements are actually implicitly expressed by this invariant:

- For each _i_ with 0 &le; _i_ < `i2u.size()`, it holds 0 &le; `i2u_[i]` < `nodes.size()`.
(This is implied since otherwise the element access `nodes_[i2u[i]]` would fail.)

- The unique identifiers in `i2u_` are disjoint: If 0 &le; i < j < `i2u.size()`, then `i2u_[i]` &ne; `i2u_[j]`.
(This is implied since `nodes[i].idx` can take only one value.)

It's usually good to express the invariant as compactly as possible, since that makes it easier
to understand and prove. Again, these conditions are relatively easy to prove and/or check
via assertion in your member functions.

Our representation invariant doesn't mention `position_` or `value_` because there are no
internal consistency requirements on those fields. The abstraction function and representation
invariant serve different purposes and can be quite independent.

The key thing to note here is that values not listed in the abstract concept appear in the
representation invariant. This is again important, and common. We add helper members
to improve the data structure, but they have to be correct to help! And here, the basic
correctness requirement on nodes is that the `idx_` member is right and that the unique
identification numbers are, well, unique.

Abstraction functions always work on valid representations, so if _RI_(_x_) is false it is OK for
_AF_(_x_) to break or return weird garbage.


### Node abstraction function and representation invariants ###

The `Node` subobject has its own abstraction function and representation
invariant that are useful to write down. The abstract value of a node is a subvalue of that
of a graph.

_AF_(`Node`) = _n<sub>i</sub>_ = (`g_->nodes_[uid_].p_`, `g_->nodes_[uid_].v_`, `g_->nodes_[uid_].idx_`)

_RI_(`Node`) = 0 &le; uid_ < `g_->nodes_.size()`.

Do you think this is complete, though? Think about it for a minute.
It is not complete, because removed nodes are invalid, but their uids are still in range by
design! We can improve the representation invariant to catch removed nodes this way:

_RI_(`Node`) = `g_->i2u_[g_->nodes[uid_].idx_] == uid_`.

Again we can elide some implied requirements, such as that uid and `g_->nodes[uid_].idx_`
are in range for their respective arrays. If the node's index is out-of-range or `i2u_` and `uid_`
don't match, the node has been deleted. This is very cool: we can add a complexity _O_(1) function `valid()`
to the class `Node` that verifies a node is valid, and then use that function in assertions!

```c++
class Node
{
  ...
private:
  bool valid() const
  {
    return uid_>= 0 && uid_< graph_->nodes_.size()
           && graph_->nodes_[uid_].index_ < graph_->i2u_.size()
           && graph_->i2u_[graph_->nodes_[uid_].index_] == uid_;
  }
public:
  Point& position()
  {
    assert(valid());
    return graph_->nodes_[uid_].position_;
  }
  ...
};
```
Note how `valid()` actually contains the implied requirements from the representation
invariant, not just the main requirement. This is important. The purpose of `valid()` is to detect
invalid nodes, so unlike most other operations, it doesn't assume its input is totally valid
(that the representation invariant is true). The carefully written out checks avoid crashing
when a node is invalid and (say) has `idx_` that's out of range for `i2u_`.
