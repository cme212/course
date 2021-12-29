# CME 212 Grading Guidelines

We want to see functioning, clear, elegant code that is readable, cleanly
designed, well-decomposed, and commented appropriately.

## Broad categories
 
* [65%] Functionality: "Does your code run well"
* [30%] Design/style:  "Implementation decisions, data structures, Readability, variable names."
* [5%] Documentation / Write-up

In each category, overall feedback will be summarized with:

* `++`: truly exceptional work, rarely granted,
* `+`: work meets all expectations, without flaw(s),
* `ok`: major functionality present, small details missed or
  an anticipated error was made,
* `-`: functionality impeded by a fundamental correctness error,
  which requires multiple modifications to rectified,
* `--`: multiple key components impeded by fundamental correctness errors,
  *each of which* requires *multiple* modifications to be rectified.

Students who do not submit their assignment at all will earn an
entirely separate category of points, called "0". At the end of the quarter, 
we will map categories to scalar values, e.g.

`{"++" : 1.05, "+" : 1", "ok" : 0.85, "-" : 0.75, "--" : 0.6}`.

E.g. your feedback from an assignment might be something like, `"Functionality" : "+", "code-quality" : "ok", "documentation" : "-"}` then if you were really eager to squash this multidimensional, rich feedback into a single scalar value you could compute `0.65 * 1.0 + 0.25 * 0.85 + 0.10 * 0.75 = 0.9375`.

### Functionality

High priority
 - Correct functionality on test cases
 - Performance is in reasonable bounds on all test cases

Medium priority
 - Output conforms to spec
 - Clean compile: no warnings under strict compiler flags 
 - Clean run: no segfaults under any cases, and valgrind runs cleanly.

Low priority
- Correct files present
- Clean repo (according to hw specs)

### Write up
- The problem is stated clearly
- The results are explained in sufficient detail
- The format is easy to read
- Answers to questions asked in assignment specification are correct
- Language is mostly correct and easy to follow

### Design/Style
 - Modular code, decomposed into appropriate logical units (functions/classes)
 - Use of proper data structures
 - Efficient algorithm implementation
 - Cleanliness and readability
 - Language conventions

Cleanliness/readability
* code is free of clutter: remove all dead code and unused vars/fns
* use of whitespace/indentation is tidy and consistent
  * split long lines if necessary (screenwidth ~80 chars)
  * 2-4 spaces per indent level (use spaces to indent instead of tabs to avoid editor inconsistency)
  * whitespace used to visually support logical separation
* variable/function names are consistent and descriptive
  * good naming conventions help avoid need for additional commentary
  * use consistent scheme for capitalization/underscores
* use constants/#define'd/sizeof/variables instead of hardcoded numbers
* comments are present where warranted, prose is correct and helpful
  * overview comments (per-function, per-module) with summary highlights
  * inline comments used sparingly where needed to decipher dense/complex lines
  * no excess verbiage that reiterates what code itself already says

Language conventions
* choose the most clean, direct, conventional syntax available to you
* avoid unnecessary use of obscure constructs
* use standard language features appropriately, e.g. `bool` instead of `int` for true-false scenarios

Program design
* program flow decomposed into manageable, logical pieces
* function interfaces are clean and well-encapsulated
* appropriate algorithms used, coded cleanly
* common code is unified, not duplicated. (don't copy paste -- unify!)
* use standard library functions rather than re-implement that functionality, e.g. 
  string manipulation, formatted I/O, sort/search, type conversion, etc.

Data structures
* data structures are well-chosen and appropriate
* no redundant storage/copying of data
* no global variables
