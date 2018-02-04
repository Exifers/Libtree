=== Tiger Compiler Project ===

== About ==
This project is about programming a compiler in C++ for the Tiger programming
language (https://www.lrde.epita.fr/~tiger/tiger.html), ie outputting assembly
from a source file. Making this project involves parsing, building an abstract
syntax tree, checking the syntax, evaluating the tree, etc. All of that is done
in that program.

== Prerequisites ==
- Linux
- flex, version 1.2.6
- bison
- autotools

Autotools may ask for various modules.

== How to compile this project ? ==

  ./bootstrap
  export CXX=g++
  ./configure
  make

This should produce the 'tc' binary in the 'src/' folder.

== How to use Tiger Compiler ? ==
The binary 'tc' reads Tiger source code on a file given as argument. For now
it just checks the syntax.

Ouput value :
  - O : syntax is correct
  - 1 : parser error
  - 2 : lexer error

In case of an error it should display a message.

== Testsuite ==
This project comports a testsuite. It is not linked to the build system yet.

== Licence ==
You're free to copy, share, reuse this code the way you want.

== Authors ==
Emmanuel Meric de Bellefon
Arnaud Lehuby
Clément Shi

Epita ing1, promo 2020
Jan 2018 - Apr 2018
