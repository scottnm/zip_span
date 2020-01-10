# span_zip

**What is this?**
- a utility which allows for simultaneously iterating over multiple differently sized collections without copies. 
- a fun exercise to do some really gross things with template metaprogramming

**What is this not?**
- a good example of template metaprogramming

What have I learned?
- Trying to use templates and metaprogramming to generate variations of classes that handle different numbers of parameters is a bit of a rat's nest
- Sometimes it's just better to copy and paste, rather than to build something more generic with template metaprogramming. If I only needed a zip-span helper for tuples of size 2 and 3, the extra complexity to write template code to generate both helpers from the same skeleton is wildly more complicated and less maintainable than just manually generating those variations. Often times you likely won't want or need more than a few variations and if the utility is simple enough you likely won't need to make sweeping changes too often
- fence post problems with metaprogramming SUCK. I knew they sucked before but this really hammered it home. If you are trying to write a macro to generate something that repeats N times but some portion of that repetition repeats only N-1 times it's going to look gross (e.g. "1,2,3,4" has 4 digits and only 3 commas. It's super easy to generate "1,2,3,4," but dropping that extra comma leads to some grossness)
- c++ template error messages are terrible and it upsets me to no end that I've wasted enough time reading them that I'm starting to figure them out.

What is there left to do?
- update the zip_span helper so that it can take any arrangement of parameters which can convert to gsl::span. Right now it can take a list of spans or a list of array literal references but that's it.
