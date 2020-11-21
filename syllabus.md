# CME 212 - Winter 2021
### Advanced Software Development for Scientists and Engineers

---

## Description
This course emphasizes the design of robust, performant, portable, 
and extensible code.

The course will work from the C++ programming language.
Students will work on a variety of programming projects, from small
data transformation utilities to more complex and scalable systems.
Along the way, students will learn to use a variety of practicable tools useful
for software design. Perhaps most importantly, students will get a clearer 
picture of how to piece together the right tools and approaches to solve
a given problem. 

Complexity will be managed through abstraction;
analytical tools will evaluate the efficiency of design choices.

### Format
The class has two lectures each week, in addition to weekly assignments.
The assignments alternate between short-answer Q/A and more involved
programming projects.  All lectures will be held virtually; please navigate through the Canvas course web page to access course lectures. Lectures will be held from 6:30 - 7:50 P.M. on Tuesdays and Thursdays.

You can expect to work hard and be challenged by this
course, but your effort can really pay off. Students anecdotally report
that CME 212 often greatly impacts what they are able to accomplish during 
their summer internships.

## Communication

This term we will be using Piazza for class discussion. We ask that you pose questions here such that other students may learn from the answers the TAs (or other students) post.
- We will use the [CME 212 Canvas page](https://canvas.stanford.edu/courses/130670) to share class-related files.

## Teaching Staff

Lecturer:
 - [Andreas Santucci](https://asantucci.github.io/) (santucci at stanford)

Teaching Assistants:
 - Guillermo Bescos Alapont (gbescos at stanford)
 - Maoguo Shi (smgyl at stanford)

## Office Hours
Office hours will be held virtually.
The hours will be announced after the first week of instruction.
Andreas will hold office hours at the end of each lecture for 50 minutes.

### How to utilize Office Hours effectively
The TAs know the homework assignments and exercise sets inside out. If you have questions there, you should ask them. On the other hand, I (Andreas) crafted the lecture notes and selected the practice interview problems, so if you have questions about *that* material, please utilize my office hours.

## Learning Objectives

Upon completion of this course, students should:

- Possess *mastery* of
  - writing performant C++ programs;
  - understanding of data representation, the lifetime of objects, 
    and complex use of memory and pointers;
  - applying design principles to the decomposition of software
    into reusable components.

- Achieve *competency* in 
  - identifying bottlenecks and improving runtime performance; 
  - writing portable programs.

- Have *exposure* to 
  - writing programs that respect the limitations of computer arithmetic;
  - the process of designing and implementing larger software systems;
  - how to approach an existing piece of software for maintenance, extension, and modification.
  - basic software development tools, including revision control, testing frameworks, and documentation tools;

In summary, we want to help you learn to *design scalable software to support
scientific experimentation*.

## Prerequisites

Students are expected to have programming experience at
the level of CME 211 or CS 106B. E.g. students should have understanding of
programming constructs such as loops, functions, 
standard data types, basic data structures, and classes; more colloquially,
students should already "know how to code".

In addition, we will be focused on Linux based tools, and to that 
end expect that you already possess some computing systems knowledge, 
e.g. basic underpinnings of the *compilation and linking* process of a C++ program.
This material is covered, for example, in
[Lecture 14](https://github.com/CME211/notes#contents) of CME 211.

### A note on style
You should have, or we hope to help you develop, an appreciation for the intrinsic value of good engineering and design.
We expect you to produce well-decomposed, readable code.
All graded coursework is focused on C++. You may find numerous examples
online of style guidelines, e.g. [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html#Formatting)

## Intended Audience

The course is aimed at students with a background in a scientific 
discipline who
will not typically have a traditional computer science background 
(though basic programming knowledge is assumed as a prerequisite). 
We hope to attract students from social sciences, medicine, and humanities.
Of course, computer science and engineering students alike are still welcome
and encouraged to take the course if it fits their needs.

## Course Content

### Exercise sets and Assignments
The class will be organized as a sequence of topic areas, each centered around a
set of tools and a motivating project. Students will complete a series of 5
programming assignments. On alternating weeks, students will tackle a series 
of 5 short-answer assignments. There will *not* be a final exam this year, due to the modified academic calendar: I wish to be compassionate and understand that all students will have a lot going on during the end of quarter period (including finishing programming assignments for this class).

### C++

- Pointers, arrays, strings
- Memory management
- Abstractions and naming
- Templates and STL
- Inheritance and polymorphism
- Operator overloading
- Encapsulation, classes, namespaces
- Constructors and destructors
- Tools: UNIX, Git, Make, C++

### Theory

- Specifications
- Complexity and correctness
- Program, loop, and representation invariants
- Type systems
- Abstract data types and abstract program values
- Consistency and replication
- Tools: Introduction to analysis and documentation, unit testing/verification

### Development

- Documentation and design
- Source code control
- Iterative development and code reviews (in the form of homework feedback)
- Documentation
- Tools: DOxygen

### Refinement and Topics

- Performance and optimization
- Parallelism, multithreaded applications and concurrency
- Regular expressions
- Tools: Introduction to GDB, valgrind, cachegrind (profiling optimization).

## Assessment

The course grade breakdown will be:

- 65% programming assignments (5 homeworks on 2 week intervals)
- 35% conceptual exercises (5 exercise sets throughout quarter)

Note that you must pass *each part* of the course in order to pass the course;
i.e. failing the programming assignments (when considered in union), *or* failing the
conceptual exercises (when considered in union) are considered grounds for not passing the course.

## Homework policies

### Late Days for homework assignments
- Each student is allowed 3 homework late days over the quarter on *homework assignments* (note this policy does not apply to exercise sets).
  Homework assignments are typically due Fridays at 4:30 P.M. P.S.T.,
  and exercise sets will typically be due on Tuesdays at 4:30 P.M. P.S.T.
  For homework assignments *only*, 
  students may use their late days on the subsequent
  Saturday, Sunday, and Monday. No late work will be accepted after 11:59pm on the Monday
  following the due date. Here's the way it works: if you submit your assignment anywhere between 4:31 P.M. P.S.T. on Friday and 11:59 P.M. P.S.T. on Saturday, that counts as 1 late day (yes you read that right, you get an extra couple hours leeway on your first late day); submitting anytime between 12:00 A.M. and 11:59 P.M. on Sunday counts as 2 late days used, and similarly for Monday. We emphasize that this rule does *not* apply to the exercise assignments
  (EX0, etc). Late exercises are not accepted. These policies are in place to ensure
  the TAs a chance to grade your homeworks in an efficient manner and to keep
  students from falling behind.

### Regrade requests
- Each student is granted 3 non-valid regrade requests. Unused regrade requests will be
  translated to a *small* amount of bonus points at the end of the quarter. A regrade request is only counted as used if the points were *not* awarded to the student. Regrade requests are
  made by submitting a GitHub issue in the homework submission repository and
  tagging or assigning the TA who graded the homework (not to be confused with the TA who *pushed* the homework feedback); you can find the TA who graded your feedback at the bottom of your homework feedback file.
  
### What do I do if I have an Emergency that requires an Accommodation?
If you have an emergency that requires both medical attention and a course accommodation, please get in touch with the [Office of Accessible Education](https://oae.stanford.edu/) as soon as possible to request a formal accommodation. If there is an emergency within your *family* that requires your attention and a course accommodation, please get in touch with the [Graduate Life Office](https://glo.stanford.edu/) as soon as possible to establish documentation. While pursuing these steps, please also get in touch with me (Andreas) as soon as possible; I aim to be compassionate and wish to work with you to facilitate a healthy learning experience. Although not all situations can be accommodated, many students have had success using these avenues in the past.

## Books

A great primer on C++ is available on the Stanford e-library, and would serve as a great
complement to course lecture notes: Lippman, Lajoie, Moo. ["C++ Primer, 5th edition"](http://proquest.safaribooksonline.com/9780133053043)

Another reference we will use in this course is an excellent book by Sutter and Alexandrescu
["C++ Coding Standards: 101 Rules, Guidelines, and Best Practices"](https://proquest-safaribooksonline-com.stanford.idm.oclc.org/0321113586),
also available on the Stanford e-library.

The lecture notes themselves will be largely based off Bjarne Stroustrup's fantastic text, 
["The C++ Programming Language", 4th edition](https://www.amazon.com/C-Programming-Language-Bjarne-Stroustrup-ebook/dp/B00DUW4BMS/ref=sr_1_2?ie=UTF8&qid=1515211070&sr=8-2&keywords=c%2B%2B+programming).

There are a myriad of resources that will become (more) accessible to you as you progress
through the course. Some additional references you may enjoy:
- Algorithms: Cormen, Leiserson, Rivest, Stein. *Introduction to Algorithms*
- Systems architecture: Bryant and O'Hallaron. *Computer Systems: A Programmer's Perspective*
- Design: Gamma, et. al. *Design Patterns: Elements of Reusable Object-Oriented Software*
- Pragmatic advice: Thomas Hunt. *The Pragmatic Programmer*
- Software engineering advice: Parnas. *Software Fundamentals*
- Human elements of software engineering: Broos. *The Mythical Man Month and The Design of Design.*
- Systems design: Waldo. *On System Design.*, and Lampson. *Hints on System Design.*

## Honor Code

You are welcome to discuss the course's material and homework with others in
order to better understand it, but **the work you turn in must be your own
unless collaboration is explicitly allowed**. You may not submit the same or
similar work to this course that you have submitted or will submit to another.

You must acknowledge any source code that was not written by you by mentioning
the original author(s) directly in your source code (comment or header). 
You can also acknowledge sources in a README.txt file if you used whole 
classes or libraries. Do not remove any original copyright notices 
and headers.

Making your work available for copy by other students is 
also prohibited (unless the assignment explicitly allows collaboration).  Violations of the
[*Stanford Honor Code and Fundamental Standard*](https://communitystandards.stanford.edu/student-conduct-process/honor-code-and-fundamental-standard) will
be forwarded to the Stanford University Office of Community Standards.

This computer science website has a good explanation of the honor code as it
relates to courses involving significant amounts of computer programming:

[*http://csmajor.stanford.edu/HonorCode.shtml*](http://csmajor.stanford.edu/HonorCode.shtml)

Note that we will use special computer software to assist us in detecting
plagiarism:

[*http://theory.stanford.edu/\~aiken/moss/*](http://theory.stanford.edu/~aiken/moss/)

If you are having difficulty completing an assignment please contact a TA or the
instructor so that we may help you. We would much rather spend time helping you
than dealing with honor code violations.

### Examples of "reasonable" actions
 - Speaking with peers about problem sets in English (or any spoken language  of your choice).
 - Whiteboarding solutions to problem sets with others using diagrams or pseudocode, but not actual code.

Since this is an advanced course in programming, we expect that you 
should be able to (learn to) debug programs on your own. 
E.g. asking another student
to directly look at your code and give suggestions for improvement starts
to get into murky waters.

### Examples of "unreasonable" actions
 - Accessing a solution to a problem prior to submitting your own. This includes solutions from prior years (staff/student) as well as this year (e.g. a fellow students finished program)
 - Failing to cite code that you borrow outside the course notes.
 - Showing your code to a student who is struggling with theirs.

## Students with Documented Different Learning Abilities

Students who may need an academic accommodation based on the impact of a different learning ability
must initiate the request with the Office of Accessible Education
(OAE). Professional staff will evaluate the request with required documentation,
recommend reasonable accommodations, and prepare an Accommodation Letter for
faculty dated in the current quarter in which the request is made. Students
should contact the OAE as soon as possible since timely notice is needed to
coordinate accommodations. Information about the OAE may be found
at:
[*http://studentaffairs.stanford.edu/oae*](http://studentaffairs.stanford.edu/oae).
