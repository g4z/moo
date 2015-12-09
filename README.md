
## MOO Interpreter

    This is the code from *http://www.mayukhbose.com/freebies/c-code.php*

This is the relavent text from Mayukh Bose website about his code...

    So what is MOO, you ask? Well, MOO is an interpreter I wrote one fine day, just because I felt like writing some code. Why the funny name, you ask? Well, I decided to write it in C++ to keep my Object Oriented skills up. MOO stands for Mayukh's Objectionally Oriented Language. It should have been called MOOL, but I lost the L somewhere early on. Before you ask, the language itself is not object oriented at all. However, it is a weird mixture of pascal, python and C and is the product of my fertile (and somewhat warped!) imagination. The code has been tested on the following compilers/environments:

        gcc 2.9.5 on FreeBSD 4.8, FreeBSD 4.9, OpenBSD 3.2, OpenBSD 3.3, OpenBSD 3.4 and Red Hat 7.1
        gcc 3.2.2 on Red Hat 9
        Visual C++ 6.0 on Windows 2000. 

    DOCUMENTATION / FEATURES
    Haven't yet got the time to write anything formally as yet, but there are a couple of sample moo programs included and you should have no trouble figuring out the language. Some of the features are:

        Two data types (integer and string).
        The language is weakly typed, so variable types are not explicitly specified. It is actually possible to declare an integer and a string variable with the same name!
        First line of any MOO program is always ignored. This allows you to use the first line to document what the program is about!.
        Expressions are evaluated right-to-left and there's NO other operator precedence!
        The language has no comments!
        As of Jan 25th 2005, I broke down and implemented a WHILE and INPUT constructs as well. 

    CHECK IT OUT
    Click here to download the MOO source code. To compile the source, do the following:
    tar -zxvf moo.tar.gz
    cd moo-interpreter
    make

    You can then run a moo program like this:
    ./moo test.moo

    Two sample moo programs are included with the source code, so that you can study them and get a feel for the language syntax.

    BUGS / IMPROVEMENTS
    There are NO bugs :). Anything you see that may be buggy, is actually A FEATURE!! However, there are some improvements that are planned for the future.

        Comprehensive Documentation.
        Better error handling. 