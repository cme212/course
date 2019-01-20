
# Lecture 5

## Abstraction Functions and Representation Invariants ##

Let’s begin to talk about programming with classes/structs. We’ve been using them up to
this point as function objects including comparators and predicates and a few iterator classes,
but have also been working with homework that involves writing more complicated objects
like `Graph`, `Node`, `Edge`, and a variety of iterators.

When we define classes in C/C++, we are really defining a new type. What is a type?
Earlier in this class, we argued that a type has the following properties:
- **Abstract value** – what the type is attempting to represent to the user.
- **Representation** – the implementation of the type. The “how” of the abstract value.
- **Behavior** – the set of operations and functions that act on the value.

We’ve talked about type concepts, which classify the behavior of types. We have
used these type concepts in our code generalizations in order to specify and
constrain the types that can be used for certain template parameters.
Now, let’s talk more about abstract values and representations.

**Abstract Values**
The abstract value of a type is everything that the user needs to know
in order to use that type. It is “how to think about this type” and is often expressed in
mathematical or pseudo-mathematical notation. If we define an abstract value and present
it to the user, we can actually use abstract values in our specifications. Here are a few
common type and how we might describe their abstract values:
- _AV_(`int`): An integer in the range [2<sup>-31</sup> , 2<sup>31</sup> - 1].
- _AV_(`float`): A floating point value in the range ±3.4 x 10<sup>±38</sup> with approximately 7
digits of accuracy.
- _AV_(`std::vector<int> a`): A sequence of `int`s [_v_<sub>0</sub>, _v_<sub>1</sub>, _v_<sub>2</sub>,..., _v_<sub>_n_-1</sub>], where _n_=`a.size()`
and _v<sub>i</sub>_=`a[i]`.
- _AV_(`Point`): A three-tuple of doubles: (_x_, _y_, _z_) with mathematical vector-like behavior.

The abstract value of a type can refer to the type’s public member functions, but only in
order to make clear how the type should be thought of.

**Representations**
The representation is the implementation of the abstract value. It describes how we are storing the type in memory.
- _R_(`int`): 32 bits, _b_<sub>0</sub> _b_<sub>1</sub> ··· _b_<sub>31</sub>, where _b<sub>i</sub>_ &isin; { 0 , 1 }.
- _R_(`float`): _b_<sub>0</sub> _b_<sub>1</sub> ··· _b_<sub>31</sub>, where _b<sub>i</sub>_ &isin; { 0 , 1 }.
- _R_(`std::vector<int>`): `int* a_`, `unsigned size_` or `int* begin_`, `int* end_`.
- _R_(`Point`): `double x, y, z`.

Public functions that use these types perform tasks meaningful for abstract values, but are
implemented in terms of representations. Clearly, representations are not unique.

**Abstraction Function**
An abstraction function, _AF_, maps the representation of a class
to the corresponding abstract value. Abstraction functions let us bridge between the more
abstract specifications provided by the comments and what actually happens in the code.
Abstraction functions go from representations to abstract values. For example:

- _AF_(`int`): (-1)<sup>b<sub>0</sub></sup> &sum;<sub>_i_=1</sub><sup>31</sup> _b<sub>i</sub>_ 2<sup>i-1</sup>
- _AF_(`float`): (-1)<sup>b<sub>0</sub></sup> 2<sup>_AF_(int(b<sub>1</sub> ···b<sub>8</sub> ))</sup> &sum;<sub>_i_=9</sub><sup>31</sup> _b<sub>i</sub>_ 2<sup>i-1</sup>
- _AF_(`std::vector<int>`): _v<sub>i</sub>_=`a[i]` or _v<sub>i</sub>_=`begin[i]`.
- _AF_(`Point`): (_x_, _y_, _z_)=`(x,y,z)`.

Again, there can be many abstraction functions for any given representation and abstract
value. For example, the _AF_(`int`) above is completely valid, but is not actually the abstraction
function for typical 32-bit `int`s. In fact, the abstraction function is wrong since there is no
way to produce an abstract value of 2<sup>-31</sup>. Instead, modern architectures, for a variety of
reasons, use the “twos compliment” abstraction function:

_AF_(`int`): -2 <sup>31</sup> + &sum;<sub>_i_=0</sub><sup>30</sup> _b<sub>i</sub>_ 2<sup>i</sup>

The interesting point of the _AF_ is that we often don’t think about it, or don’t need to.
When we think about `int`s, we almost always think about the abstract value rather than
the representation and the abstraction function.
Let’s try this for Graph now.

- _AV_(`Graph<V> g`): A pair of nodes and edges, (_N_, _E_):
    - _N_ = [_n_<sub>0</sub>, _n_<sub>1</sub>,..., _n_<sub>_m_-1</sub>] with _m_ = `g.numnodes()` and _n<sub>i</sub>_ = `g.node(i)` = (_p<sub>i</sub>_, _n<sub>i</sub>_, _i_),
    - _E_ = {{_n<sub>i</sub>_, _n<sub>j</sub>_} | _n<sub>i</sub>_, _n<sub>j</sub>_ &isin; _N_, and _i_ &ne; _j_}

This abstract value makes clear that we have a graph of a sequence nodes with data including
the point, _p<sub>i</sub>_, the node value _v<sub>i</sub>_, the index _i_, and a set of undirected
edges with no self-edges. We’ve actually defined some implicit abstract values here:
_AF_(`Node n`): (_p<sub>i</sub>_, _n<sub>i</sub>_, _i_) and
_AF_(`Edge e`): {_n<sub>i</sub>_, _n<sub>j</sub>_}. This makes no reference to the
representation or all the public
member functions, but it gives the user a way to think about what she is working with.
Now let’s consider one possible representation:

- _R_(`Graph`):

        struct nodeinfo {
          Point p_;
          node_value_type v_;
        }
        std::vector<nodeinfo> node_;
        std::vector<std::vector<uid_type> > adj_;

- _R_(`Node`):

        graph_type* g_;
        uid_type uid_;

- _R_(`Edge`):

        graph_type* g_;
        uid_type uid1_, uid2_;

The representation simply defines the member variables. We’ve let you choose your
representation for HW0 and HW1, so you may have something else. In order to show how this
representation allows us to represent the abstract value, we must define the abstraction
function. Each abstract value that appears in the _AF_ should have a definition in terms of the
representation.

- _AF_(`Graph`) = (_N_, _E_) where
    - _N_ = {_n<sub>i</sub>_ | 0 &le; _i_ < _m_ = `node_.size()`},
    - _E_ = {{ _n<sub>i</sub>_, _n<sub>i</sub>_} | 0 &le; i < j < _m_ and _i_ &isin; `adj_[j]`}.
- _AF_(`Node n`) = _n<sub>i<sub>_ = (_p<sub>i</sub>_, _v<sub>i</sub>_, _i_ = `uid_`) = (`g_->node[uid_].p_`, `g_->node[uid_].v_`, `uid_`).
- _AF_(`Edge e`) = {_n<sub>i</sub>_, _n<sub>j</sub>_} = {_n_<sub>`uid1_`</sub>, _n_<sub>`uid2_`</sub>} = {`g_->node(uid1_)`, `g_->node(uid2_)`}.

Inside the of the abstraction function for `Node` and `Edge`, we can use the `Graph`’s abstract
concept of the `Node`s, as we did.
These are nice specifications to define for any class that you write, especially when it gets
more complicated. The _AF_ can help you verify that your representation is sufficient to
implement your abstract value. There is one more concept though that is probably the most
powerful to define, the _representation invariant_.

**Representation Invariant**
A representation invariant defines whether a type representation is valid.
A data structure’s representation invariant (_RI_) is an invariant that should
always be true about its representations. Functionally, it maps representations to booleans.
Any valid representation _R_ has _RI_(_R_) = True. _RI_ is an implicit precondition for every
public member function (except constructors), and an implicit postcondition for every public
member function (except destructors). That is, constructors create valid representations;
destructors are only passed valid representations; and member functions preserve representation
validity. Private member functions do not have to preserve _RI_, but public member functions
must restore _RI_ before returning. Like precondition invariants and the behavior of functions,
the abstraction function is only valid for valid representations. Abstraction functions always
work on valid representations, so if _RI_(_x_) is false it’s OK for _AF_(_x_) to break
or return weird garbage. The purpose of a class is to enforce and defend these invariants.

We use representation invariants to help prove that data structure operations are correct:
every public data structure operation can assume that the data structure is valid on input,
and must provide a postcondition that the data structure is valid on output. (There’s an
exception for operations that destroy data structures, whose specifications say that they
invalidate their input. `remove_node` is an example.)

Representation invariants are functions that take representation objects and return boolean
values (true for valid, false for invalid).

For `std::vector<int>` and the representation above, the representation invariant might
look like:
- _RI_(`std::vector<int>`): Size of `a_` &ge; `size_`,

where `a_` is vector's private member data array.
That is, simply that the internal array has been allocated with enough elements to
appropriately represent the abstract vector.
A representation may contain parts that are not used in the abstraction function,
the representation invariant, or both. Often the _RI_ and _AF_ compliment each
other in some way. For example:
- _RI_(`int`): True.
- _RI_(`float`): True.
- _RI_(`Point`): True.

The `Point` class doesn’t care about the values of its member variables, it only exists to
group them and provide convenience operators. The _RI_ above is precisely why these member
variables can be provided publicly – there is no invariant to defend against users. Users cannot
break a `Point` object.
Users can break a `Graph`, `Node`, or `Edge` class though. Let’s consider the _RI_s given the
representation and abstraction functions above.
- _RI_(`Graph`): 
    - `node.size() == adj.size()`
    - &forall; _i_ such that 0 &le; i < `adj_.size()`, if _j_ &isin; `adj_[i]`, then _i_ &isin; `adj_[j]`.
- _RI_(`Node`): 
    - `g_ != nullptr`
    - 0 &le; `uid_` < `g->numnodes()`.
- _RI_(`Edge`):
    - `g_ != nullptr`
    - `uid1_` &isin; `g->adj_[uid2_]`

We’ve written this rather compactly and could write
```
std::find(g->adj_[uid1_].begin(), g->adj_[uid1_].end(), uid2_) != g_->adj_[uid1_].end()
```
instead of `uid1_` &isin; `g_->adj_[uid2_]`, but we find the latter smaller and easier to read.
Additionally, note that the `Graph` uses `std::vector`s, but doesn’t mention anything about
these objects themselves being valid. This is because `std::vector`s are already classes that
defend and uphold their representation invariants – we can assume they do this correctly
and are always valid. If we had used raw pointers and size member variables rather than
`std::vector`s, all of the _RI_s that the `std::vector`s are taking care of for us now would be
included in the _RI_s for `Graph`, complicating our invariants and implementations immensely!
More succinctly, the `Graph` is implemented using abstract vectors rather than raw arrays.
The _AF_ actually gives the _RI_ a lot of freedom here. For example, we could only store edges
{_n<sub>i</sub>_, _n<sub>j</sub>_} with _i_ < _j_ in the adjacency list. However, by storing both, the implementation
of incident iterator and has edge can be made more easily and more efficiently, so we
express the “double edge” invariant here. These two invariants mostly serve to simplify the
implementation of some of the methods. When we write classes like this, we often keep these
rules in our head, but writing them down to serve as preconditions and postconditions of all
public member functions can be very helpful. We will do a few examples of how we can use
_RI_s to aid implementations in the next lecture.
