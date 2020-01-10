# span_zip

**What is this?**
- a C++ utility to perform iterable zipping: mapping the similar index of multiple containers so that they can be used just using as single entity. Another way to think about it is that it allows for simultaneously iterating over multiple differently sized collections.
- A zipping utility that doesn't require any copies or heap allocations.
- syntactic sugar over something that's relatively simple to do in plain ole c-style code
- a fun exercise to do some really gross things with template metaprogramming
- a hodge podge of poor naming decisions and duct tape style. Usually I would take better care, but with some personal projects/exercises, I get so wrapped up in style and engineering principles that I never do anything. I didn't intend to do anything meaningful with this so I just haven't bothered. Maybe I'll make it more usable in the future.

```cpp
// Both the following loops will print:
// (1, '1', 1.00)
// (2, '2', 2.00)
// (3, '3', 3.00)

int ints[] = {1, 2, 3};
char chars[] = {'1', '2', '3', '4'};
char floats[] = {1.f, 2.f, 3.f, 4.f};

// a no-frills zip would look like...
for (int i = 0; i < MIN(MIN(ARRAYSIZE(ints), ARRAYSIZE(chars)), ARRAYSIZE(floats)); ++i)
{
    printf("(%i, '%c', %.2f)\n", ints[i], chars[i], floats[i]);
}

// with my frill-full zip utility you could write this...
for (auto nextTuple : zip_span(ints, chars, floats)) // <--- visually I think this reads well
{
    printf("(%i, '%c', %.2f)\n",
        std::get<0>(nextTuple), // <-- I think this part is a mess though.
        std::get<1>(nextTuple),
        std::get<2>(nextTuple)); 
}
```

**What is this not?**
- a good example of template metaprogramming
- something I meaningfully intend to use in its current state in ANY sort of production code
- a good use of my time to write (but it was fun :) )

What have I learned?
- Trying to use templates and metaprogramming to generate variations of classes that handle different numbers of parameters is a bit of a rat's nest
- Sometimes it's just better to copy and paste, rather than to build something more generic with template metaprogramming. If I only needed a zip-span helper for tuples of size 2 and 3, the extra complexity to write template code to generate both helpers from the same skeleton is wildly more complicated and less maintainable than just manually generating those variations. Often times you likely won't want or need more than a few variations and if the utility is simple enough you likely won't need to make sweeping changes too often
- fence post problems with metaprogramming SUCK. I knew they sucked before but this really hammered it home. If you are trying to write a macro to generate something that repeats N times but some portion of that repetition repeats only N-1 times it's going to look gross (e.g. "1,2,3,4" has 4 digits and only 3 commas. It's super easy to generate "1,2,3,4," but dropping that extra comma leads to some grossness)
- c++ template error messages are terrible and it upsets me to no end that I've wasted enough time reading them that I'm starting to figure them out.

What is there left to do?
- update the zip_span helper so that it can take any arrangement of parameters which can convert to gsl::span. Right now it can take a list of spans or a list of array literal references but that's it.
- write a variant of zip_span that asserts/requires all zipped iterables to be of the same size
- Find a better return interface than std::tuple. Having to use std::get utilty sucks
