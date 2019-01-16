# CME 212 - Winter 2019
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
programming projects. 

You can expect to work hard and be challenged by this
course, but your effort can really pay off. Students anecdotally report
that CME 212 often greatly impacts what they are able to accomplish during 
their summer internships.

## Communication

This term we will be using Piazza for class discussion.  The [CME 212 Piazza page](https://piazza.com/stanford/winter2019/cme212/home) has been made available to all Stanford students.  We will also use Piazza for announcements, so please enroll yourself as a student to receive notifications.  
- Please ask questions related to course material on Piazza, placing your question in the appropriate folder (e.g. 'hw0').
- Questions should be posted to "Instructors" *only* when the question is personal in nature; else it should be visible to the "Entire Class" such that other students may benefit from the QA.  While we do have a staff mailing list (<cme212-staff-19@lists.stanford.edu>), I encourage you to post your questions on Piazza.
- We will still use the [CME 212 Canvas page](https://canvas.stanford.edu/courses/94167) to share class-related files.

## Teaching Staff

Lecturers:
 - [Slaven Peles](https://icme.stanford.edu/people/slaven-peles) (peles at stanford)
 - [Andreas Santucci](https://asantucci.github.io/) (santucci at stanford)

Teaching Assistants:
 - Remmelt Ammerlaan (remmelt at stanford)
 - Brett Harvey (rbharvey at stanford)
 - Youkow Homma (youkow.homma at stanford)
 - Jessica Wetstone (wetstone at stanford)

## Office Hours
Office hours will be held in [Huang
basement](https://campus-map.stanford.edu/) 
outside of ICME (with exception to Slaven's).
The hours will be announced after the first week of instruction. 
Andreas will hold office hours by appointment.

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
e.g. basic underpinnings of the compilation and linking process of a C++ program.
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

The class will be organized as a sequence of topic areas, each centered around a
set of tools and a motivating project. Students will complete a series of 5
programming assignments. On alternating weeks, students will tackle a series 
of 5 short-answer assignments. There will be a final exam.

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

- 50% programming assignments (5 homeworks on 2 week intervals)
- 25% conceptual exercises (5 exercise sets throughout quarter)
- 25% final exam

## Homework policies

- Each student is allowed 2 homework late days over the quarter.
  Homework assignments are typically due Friday at 4:30 P.M. P.S.T.
  Students may use their late days on the subsequent
  Saturday and Sunday. No late work will be accepted after 11:59pm on the Sunday
  following the due date. This rule does not apply to the exercise assignments
  (EX0, etc). Late exercises are not accepted. These policies are in place to ensure
  the TAs a chance to grade your homeworks in an efficient manner and to keep
  students from falling behind.

- Each student is granted 3 regrade requests. Unused regrade requests will be
  translated to bonus points at the end of the quarter. Regrade requests are
  made by submitting a GitHub issue in the homework submission repository and
  assigning the TA who graded the homework.

## Final Exam
We anticipate that the final exam will be take-home. Students will be able to access
the exam through the course-website on Canvas. We will provide a 72-hour window
for students to take the exam, but we only anticipate the exam to take students
approximately 3 hours.
Students will be expected to use revision control (Git) for their project,
and we will grade the latest commit which is pushed to the master branch
of a student's repository no later than the final exam deadline set by the
registrar.

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
- Design: Gamma, et. al. *Design Patterns: Elements of Reusable Object-Oriented Software*
- Pragmatic advice: Thomas Hunt. *The Pragmatic Programmer*
- Software engineering advice: Parnas. *Software Fundamentals*
- Human elements of software engineering: Broos. *The Mythical Man Month and The Design of Design.*
- Systems architecture: Bryant and O'Hallaron. *Computer Systems: A Programmer's Perspective*
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

## Students with Documented Disabilities

Students who may need an academic accommodation based on the impact of a
disability must initiate the request with the Office of Accessible Education
(OAE). Professional staff will evaluate the request with required documentation,
recommend reasonable accommodations, and prepare an Accommodation Letter for
faculty dated in the current quarter in which the request is made. Students
should contact the OAE as soon as possible since timely notice is needed to
coordinate accommodations. Information about the OAE may be found
at:
[*http://studentaffairs.stanford.edu/oae*](http://studentaffairs.stanford.edu/oae).
