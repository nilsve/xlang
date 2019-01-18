# xlang

### My first attempt at designing a programming language, and writing a compiler.

The intent for this project was to build a compiler & custom language that would generate a completely different output each time you compile.
The idea was that this would bypass signature detection in Anti Cheat's in games. There are much better ways to achieve this than writing a custom compiler. But I wanted to gain the experience.
It has been fun writing this project, but there is still quite a bit of work to do for this project to become useful.

### This project still has a long way to go. At the moment it's capable of
  - Parsing code
    - Modules
    - Functions
    - Scopes
    - Variable declarations
    - Variable assignment
    - Mathmetic operations
    - Function calls (With argument type checking
  - Building an abstract syntax tree
  - Generating x86 NASM
    - Function's are assembled
    - Scopes work (Variable's declared in a scope, nested scopes are allowed, get cleaned up after exiting the scope)
    - Function calls with arguments
    - Variable assignment
   
What still needs the be done
  - Parsing struct declarations
  - Emitting assembly code for the mathmetic operations (I think only add operations work atm)
  - Pointers
  - Probably a ton more that I haven't foreseen 
