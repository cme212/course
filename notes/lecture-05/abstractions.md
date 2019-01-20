
# Lecture 5

## Abstraction Functions and Representation Invariants ##

Let’s begin to talk about programming with classes/structs. We’ve been using them up to
this point as function objects including comparators and predicates and a few iterator classes,
but have also been working with homework that involves writing more complicated objects
like `Graph`, `Node`, `Edge`, and a variety of iterators.

When we define classes in C/C++, we are really defining a new type. What is a type?
Earlier in this class, we argued that a type has the following properties:
- An abstract value – what the type is attempting to represent to the user.
- A representation – the implementation of the type. The “how” of the abstract value.
- Behavior – the set of operations and functions that act on the value.

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
- AV(`int`): An integer in the range [2<sup>-31</sup> , 2<sup>31</sup> - 1].
- AV(`float`): A floating point value in the range ±3.4 x 10<sup>±38</sup> with approximately 7
digits of accuracy.
- AV(`std::vector<int> a`): A sequence of `int`s [_v_<sub>0</sub>, _v_<sub>1</sub>, _v_<sub>2</sub>,..., _v_<sub>_n_-1</sub>], where _n_=`a.size()`
and _v<sub>i</sub>_=`a[i]`.
- AV(`Point`): A three-tuple of doubles: (_x_, _y_, _z_) with mathematical vector-like behavior.

The abstract value of a type can refer to the type’s public member functions, but only in
order to make clear how the type should be thought of.

**Representations**
The representation is the implementation of the abstract value. It de-
scribes how we are storing the type in memory.
- R(`int`): 32 bits, _b_<sub>0</sub>_b_<sub>1</sub> ··· _b_<sub>31</sub>, where _b<sub>i</sub>_ is in { 0 , 1 }.
- R(`float`): _b_<sub>0</sub>_b_<sub>1</sub> ··· _b_<sub>31</sub>, where _b<sub>i</sub>_ is in { 0 , 1 }.
- R(`std::vector<int>`): `int* a`, `unsigned size` or `int* begin`, `int* end`.
- R(`Point`): `double x, y, z`.

Public functions that use these types perform tasks meaningful for abstract values, but are
implemented in terms of representations. Clearly, representations are not unique.

**Abstraction Function**
An abstraction function, AF, maps the representation of a class
to the corresponding abstract value. Abstraction functions let us bridge between the more
abstract specifications provided by the comments and what actually happens in the code.
Abstraction functions go from representations to abstract values. For example:

- AF(`int`): 1 b^0
P 31
i=1bi·^2
i (^1).
- AF(float): 1 b^02 AF(int(b^1 ···b^8 ))
P 31
i=9bi·^2
(i9)
- AF(`std::vector<int>`): _v<sub>i</sub>_=`a[i]` or _v<sub>i</sub>_=`begin[i]`.
- AF(`Point`): (_x_, _y_, _z_)=`(x,y,z)`.

Again, there can be many abstraction functions for any given representation and abstract
value. For example, the AF(`int`) above is completely valid, but is not actually the abstraction
function for typical 32-bit `int`s. In fact, the abstraction function is wrong since there is no
way to produce an abstract value of 2<sup>-31</sup>. Instead, modern architectures, for a variety of
reasons, use the “twos compliment” abstraction function:

AF(`int`): b 31 · 2 31+X^30 i=0bi· 2 i

The interesting point of the AF is that we often don’t think about it, or don’t need to.
When we think about `int`s, we almost always think about the abstract value rather than
the representation and the abstraction function.
Let’s try this for Graph now.

- AV(`Graph<V> g`): A pair of nodes and edges, (_N_, _E_):
    - _N_ = [_n_<sub>0</sub>, _n_<sub>1</sub>,..., _n_<sub>_m_-1</sub>] with _m_ = `g.numnodes()` and _n<sub>i</sub>_ = `g.node(i)` = (_p<sub>i</sub>_, _n<sub>i</sub>_, _i_),
    - _E_ = {{_n<sub>i</sub>_, _n<sub>j</sub>_} | _n<sub>i</sub>_, _n<sub>j</sub>_ is in _N_, and _i_ != _j_}

This abstract value makes clear that we have a graph of a sequence nodes with data including
the point, pi,thenodevaluevi,theindexi,andasetofundirectededgeswithnoself-
edges. We’ve actually defined some implicit abstract values here: AF(Nodeni):(_p<sub>i</sub>_, _n<sub>i</sub>_, _i_)
and AF(Edgee):{_n<sub>i</sub>_, _n<sub>j</sub>_}. This makes no reference to the representation or all the public
member functions, but it gives the user a way to think about what she is working with.
Now let’s consider one possible representation:

- R(`Graph`):

        struct nodeinfo {
          Point p_;
          node_value_type v_;
        }
        std::vector<nodeinfo> node_;
        std::vector<std::vector<uid_type>> adj_;

- R(`Node`):

        graph_type* g_;
        uid_type uid_;

- R(`Edge`):

        graph_type* g_;
        uid_type uid1_, uid2_;

The representation simply defines the member variables. We’ve let you choose your repre-
sentation for HW0 and HW1, so you may have something else. In order to show how this
representation allows us to represent the abstract value, we must define the abstraction func-
tion. Each abstract value that appears in the AF should have a definition in terms of the
representation.

- AF(Graph)=(N, E)whereN=[ni| 0 i<m=node.size()].
E={{ni,nj}| 0 i<j<mandi 2 adj[j]}.
- AF(Noden)=nuid =(pi,vi,uid)=(g->node[uid].p,g->node[uid].v,uid).
- AF(Edgee)={ni,nj}={nuid1,nuid2}={g->node(uid1),g->node(uid2)}.

Inside the of the abstraction function forNodeandEdge,wecanusetheGraph’s abstract
concept of theNodes, as we did.
These are nice specifications to define for any class that you write, especially when it gets
more complicated. The AF can help you verify that your representation is sufficient to
implement your abstract value. There is one more concept though that is probably the most
powerful to define, therepresentation invariant.

**Representation Invariant**
A representation invariant defines whether a type representation is valid. 
A data structure’s representation invariant (RI) is an invariant that should
always be true about its representations. Functionally, it maps representations to booleans.
Any valid representation R has RI(R)=true. RI is an implicit precondition for every
public member function (except constructors), and an implicit postcondition for every public
member function (except destructors). That is, constructors create valid representations;
destructors are only passed valid representations; and member functions preserve representation
validity. Private member functions do not have to preserve RI, but public member functions
must restore RI before returning. Like precondition invariants and the behavior of functions,
the abstraction function is only valid for valid representations. Abstraction functions always
work on valid representations, so if RI(x) is false it’s OK for AF(x) to break
or return weird garbage. The purpose of a class is to enforce and defend these invariants.

We use representation invariants to help prove that data structure operations are correct:
every public data structure operation can assume that the data structure is valid on input,
and must provide a postcondition that the data structure is valid on output. (There’s an
exception for operations that destroy data structures, whose specifications say that they
invalidate their input. removenode is an example.)

Representation invariants are functions that take representation objects and return boolean
values (true for valid, false for invalid).

For std::vector<int> and the representation above, the representation invariant might
look like:
- RI(std::vector<int>): Size ofa size.
That is, simply that the internal array has been allocated with enough elements to appro-
priately represent the abstract vector.
Arepresentationmaycontainpartsthataren’tusedintheabstractionfunction,therepre-
sentation invariant, or both. Often the RI and AF compliment each other in some way. For
example:
- RI(int): True.
- RI(float): True.
- RI(Point): True.
        
ThePoint class doesn’t care about the values of its member variables, it only exists to
group them and provide convenience operators. The RI above is precisely why these member
variables can be provided publicly – there is no invariant to defend against users. Users cannot
break a `Point` object.
Users can break a Graph, Node, or Edge class though. Let’s consider the RIs given the
representation and abstraction functions above.
- RI(Graph):node.size() == adj.size()
8 iwith 0 i<adj.size(),ifj 2 adj[i], theni 2 adj[j].
- RI(Node):g != nullptr
0 uid <g->numnodes().
- RI(Edge):g != nullptr
uid1 2 g->adj[uid2]

We’ve written this rather compactly and could write
```
std::find(g->adj[uid1].begin(), g->adj[uid1].end(), uid2) != g->adj[uid1].end()
```
instead of `uid1 2 g->adj[uid2]`, but we find the latter smaller and easier to read.

Additionally, note that the Graph uses std::vectors, but doesn’t mention anything about
these objects themselves being valid. This is because std::vectors are already classes that
defend and uphold their representation invariants – we can assume they do this correctly
and are always valid. If we had used raw pointers and size member variables rather than
std::vectors, all of the RIs that the std::vectors are taking care of for us now would be
included in the RIs for Graph, complicating our invariants and implementations immensely!
More succinctly, the Graphis implemented using abstract vectors rather than raw arrays.
The AF actually gives the RI a lot of freedom here. For example, we could only store edges
{_n<sub>i</sub>_, _n<sub>j</sub>_} with _i_ < _j_ in the adjacency list. However, by storing both, the implementation
of incident iterator and has edge can be made more easily and more efficiently, so we
express the “double edge” invariant here. These two invariants mostly serve to simplify the
implementation of some of the methods. When we write classes like this, we often keep these
rules in our head, but writing them down to serve as preconditions and postconditions of all
public member functions can be very helpful. We will do a few examples of how we can use
RIs to aid implementations in the next lecture.
