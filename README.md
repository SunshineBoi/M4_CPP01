*This project has been created as part of the 42 curriculum by kong.*

## Description

This repository contains my solutions to **C++ Module 01** of the 42 Common Core.
This module follows on from Module 00's introduction to classes, and focuses on:

- The distinction between allocating objects on the **stack** vs. the **heap**, and
  when to prefer one over the other.
- Manual memory management with `new` / `delete`, including allocating an array of
  objects in a single block and constructing them individually with **placement new**
  (needed when the class has no default constructor).
- **Pointers and references** as two syntaxes for the same underlying idea: address
  manipulation.
- **Composition via member objects**, and choosing between a reference member
  (mandatory, fixed for the object's life) and a pointer member (optional,
  re-seatable) based on those exact constraints.
- The **Orthodox Canonical Form** (default/copy constructor, `operator=`,
  destructor) and the shallow-vs-deep-copy distinction it forces you to make
  explicit for any non-trivial member.
- **`std::string` manipulation and file I/O** with `std::ifstream`/`std::ofstream`,
  without relying on C's `fopen`/`fread` family.
- **Pointers to member functions**, used to dispatch behaviour without a chain of
  `if`/`else if`.
- The `switch` statement.

All code complies with the **C++98** standard and compiles cleanly with
`-Wall -Wextra -Werror`.

## Exercises

| Ex | Name | Topic |
|----|------|-------|
| 00 | BraiiiiiiinnnzzzZ | `Zombie` class, stack vs. heap allocation, destructors |
| 01 | Moar brainz! | Allocating an array of objects with `new`/placement `new` |
| 02 | HI THIS IS BRAIN | Pointers vs. references |
| 03 | Unnecessary violence | Composition, pointer vs. reference members |
| 04 | Sed is for losers | `std::string` manipulation, file I/O |
| 05 | Harl 2.0 | Pointers to member functions |
| 06 | Harl filter (optional) | `switch` statement |

## Instructions

Each exercise lives in its own `exXX/` directory and ships with its own `Makefile`.

```sh
cd exXX
make        # build the exercise, produces an executable named `zombie` (or as specified)
./zombie    # run it
make clean  # remove object files
make fclean # remove object files and the executable
make re     # fclean + all
```

All exercises are compiled with:

```sh
c++ -Wall -Wextra -Werror -std=c++98
```

No external dependencies are required beyond a C++98-capable compiler (`c++`/`g++`)
and `make`.

### ex00 — BraiiiiiiinnnzzzZ

Builds a `Zombie` class plus two free functions, `newZombie` (heap-allocated,
you own the `delete`) and `randomChump` (stack-allocated, destroyed automatically
at end of scope). `main.cpp` exercises both paths, plus the copy constructor and
copy assignment operator.

**Key concepts / notes:**

- **Class member.** Any variable or function declared inside a class body,
  regardless of access specifier. `public`/`private`/`protected` only control
  *who may call or access it from outside* — they play no part in deciding
  whether something counts as a member in the first place.
  ```cpp
  class Zombie
  {
  private:
      std::string name;      // data member
  public:
      void announce(void);   // member function — declared here, defined below
  };
  ```

- **Defining a member outside the class (`ClassName::`).** A member function
  can be *declared* inside the class and *defined* elsewhere, but the
  definition must be qualified with the class name and the scope resolution
  operator. Omit the qualifier and the compiler doesn't treat it as an error —
  it silently defines an unrelated free function that happens to share a
  name, which has no access to the class's private members and leaves the
  real declared member undefined (a link error, wherever it's actually
  called). This is exactly the bug hit while implementing `announce()`:
  ```cpp
  // Zombie.cpp — WRONG: this is a new, unrelated free function
  void announce(void)
  {
      std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
  }
  // error: 'name' was not declared in this scope
  // (and Zombie::announce is still undefined — link error wherever it's called)

  // RIGHT: qualified with the class name
  void Zombie::announce(void)
  {
      std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
  }
  ```

- **Free function vs. member function.** A free function isn't attached to
  any class and is called on its own; a member function is called *on* an
  object and has implicit access to that object's members via `this`.
  | | Free function | Member function |
  |---|---|---|
  | Call syntax | `f(x)` | `x.f()` |
  | Access to private members | No (unless `friend`) | Yes |
  | Typically defined | Its own file/header | Alongside the rest of the class |

  In this exercise, `newZombie` and `randomChump` are asked for in their own
  files (`newZombie.cpp`, `randomChump.cpp`), separate from `Zombie.cpp` —
  that's the signal they're meant to be free functions, not members. One
  consequence: free functions can't reach `private` members, so `announce()`
  had to be `public` for `randomChump` to call it.

- **Object storage duration and destructor triggers.** An object's destructor
  runs automatically whenever its lifetime ends, and *what ends it* depends on
  where the object lives:
  | Storage duration | What ends the lifetime |
  |---|---|
  | Automatic (stack) — `T x(args);` | End of the enclosing scope (`{ }`), automatically. |
  | Dynamic (heap) — `T* x = new T(args);` | An explicit `delete x;`. Omitting it leaks; calling `delete` on a stack object is undefined behaviour. |
  | Static / global | Program exit. |
  | Member subobject | Right after the owning object's own destructor body finishes. |
  | Temporary | End of the full expression it appears in. |

  `newZombie`/`randomChump` are the heap/stack sides of this table in one
  exercise:
  ```cpp
  Zombie* heapZombie = newZombie("Heap Harry");
  heapZombie->announce();
  delete heapZombie;              // dtor fires here, on demand

  randomChump("Stack Sally");     // dtor fires automatically when this returns
  ```

- **Object construction as two steps.** Constructing an object is really
  "allocate storage" followed by "run a constructor on that storage" — two
  separate operations ordinary code bundles together. For a stack variable,
  storage is reserved implicitly just by entering scope; for a heap object,
  `new` performs the allocation explicitly and returns a pointer to it.
  Either way, *where* the storage comes from is independent of *which*
  constructor initializes it.
  ```cpp
  Zombie zb(za);
  // step 1: reserve sizeof(Zombie) bytes for zb on the stack (implicit)
  // step 2: call Zombie(const Zombie&) on that storage, with za as the argument
  ```

- **Constructor overload resolution.** When a class has multiple
  constructors, the compiler picks one via ordinary overload resolution on
  the argument types — not by the literal spelling of the initialization:
  | Form | Kind | Constructor selected |
  |---|---|---|
  | `Zombie zb(za);` | direct-initialization | `Zombie(const Zombie&)` — directly, no temporary |
  | `Zombie zb = za;` | copy-initialization | `Zombie(const Zombie&)` — same result |
  | `Zombie zb = Zombie(za);` | copy-init from a temporary | `Zombie(const Zombie&)` builds the temporary, then (typically elided) again for `zb` |

  All three end up calling the same constructor; `Zombie zb(za);` is just the
  most direct way to say it.

- **Self-assignment guard: identity vs. equality.** Inside `operator=`,
  `this` is a pointer to the object being assigned *to*; the parameter is a
  reference to the object being assigned *from*. A guard against
  self-assignment (`a = a;`) should compare **identity** — are these the same
  object in memory — which is an address comparison, not a content
  comparison:
  ```cpp
  // WRONG — doesn't even compile: no operator!= defined for Zombie
  Zombie& Zombie::operator=(const Zombie& other)
  {
      if (*this != other)   // error: no match for 'operator!=' (Zombie, const Zombie)
          name = other.name;
      return (*this);
  }

  // RIGHT — compares addresses (identity), not values (content)
  Zombie& Zombie::operator=(const Zombie& other)
  {
      if (this != &other)
          name = other.name;
      return (*this);
  }
  ```
  Even with a working `operator!=`, comparing content would be the wrong
  check regardless: two distinct `Zombie`s can share the same `name` without
  being the same instance.

### ex01 — Moar brainz!

Builds `zombieHorde(int N, std::string name)`, which allocates `N` zombies in a
**single** heap allocation and constructs each one in place with placement `new`
(a plain `new Zombie[N]` isn't possible here since `Zombie` has no default
constructor). `main.cpp` creates a horde, makes each zombie announce itself, then
tears the horde down by calling each destructor manually before releasing the
raw block — the exact mirror of how it was built.

**Key concepts / notes:**

- **Variable-length arrays (VLAs).** An array declared with a size that's only
  known at runtime, e.g. `T arr[n];` where `n` is a variable. Standard C++
  requires array sizes to be compile-time constants — VLAs are a GNU
  extension, not portable C++:
  ```cpp
  int     N = 4;
  Zombie  horde[N];   // non-standard VLA — and see the next point, it's worse than that
  ```

- **Why array construction needs a default constructor.** Declaring an array
  of class-typed elements — `T arr[N];`, or its heap equivalent `new
  T[N]` — must initialize every element immediately, and does so by calling
  that class's **default constructor** (taking no arguments) on each one.
  `Zombie` only has `Zombie(std::string)`, no default constructor, so *both*
  forms are dead ends here — not just the VLA:
  ```cpp
  Zombie  horde[N];        // error: no matching function for call to 'Zombie::Zombie()'
  Zombie* horde = new Zombie[N];  // same problem — new[] default-constructs every element too
  ```
  This is the actual point of the exercise: there is no way to pass
  per-element constructor arguments through array syntax, so allocation and
  construction have to be pulled apart and done separately.

- **`operator new` as a raw allocator.** `operator new(size_t)`, called
  directly as a function (not via a `new`-expression), allocates that many
  raw, uninitialized bytes and returns `void*` — no constructor runs. It's
  the C++ counterpart to `malloc`, except it throws `std::bad_alloc` on
  failure instead of returning null, and pairs with `operator delete`.
  Four related spellings, only one of which fits this exercise:
  | Syntax | Allocates | Constructs | Notes |
  |---|---|---|---|
  | `new Type(args)` | Yes | Yes | ordinary new-expression |
  | `::new Type(args)` | Yes, global only | Yes | forces the global `operator new`, skipping any class-specific overload |
  | `operator new(n)` | Yes, `n` raw bytes | No | direct function call, no `new`-expression involved |
  | `::operator new(n)` | Yes, `n` raw bytes, global only | No | **used in `zombieHorde`** |

- **Placement new.** A form of `new`-expression that constructs an object at
  a **specific, pre-existing address**, performing no allocation of its own:
  `new (address) Type(args);`. It's not special grammar — the parentheses
  after `new` pass extra arguments to whichever `operator new` overload
  matches, and the standard library provides exactly one such overload for
  this in `<new>`: `void* operator new(size_t, void* p) { return p; }`, which
  allocates nothing and just hands back the address it was given. Full
  pattern used in `zombieHorde`:
  ```cpp
  void*   raw   = ::operator new(N * sizeof(Zombie));   // 1. raw bytes, no objects yet
  Zombie* horde = static_cast<Zombie*>(raw);

  for (int i = 0; i < N; i++)
      new (&horde[i]) Zombie(name);                     // 2. construct in place, per slot
  ```
  The expression still evaluates to a `Type*`, but it's always equal to the
  address supplied — capturing it (`Zombie* p = new (&horde[i]) Zombie(name);`)
  is legal but redundant, since `&horde[i]` already gives the same pointer.

- **`<new>` header.** The single-argument global `operator new(size_t)` /
  `operator delete(void*)` are implicitly available in any translation unit,
  no include required. The two-argument **placement** overload is not — it
  needs `#include <new>`. Confirmed by testing both ways:
  ```cpp
  // WITHOUT #include <new>:
  Foo* f = new (raw) Foo();
  // error: no matching function for call to 'operator new(sizetype, void*&)'
  //   candidate: 'void* operator new(long unsigned int)'   <- only the 1-arg built-in exists

  // WITH #include <new>: compiles fine.
  ```
  `<iostream>`/`<string>` often pull `<new>` in transitively on a given
  implementation, but that's not guaranteed — code using placement new
  should include `<new>` explicitly.

- **Manual destruction.** An object constructed with placement new was never
  tied to an allocation `delete`/`delete[]` can find and free correctly, so
  it has to be destroyed explicitly — `obj.~Type();`, one of the few
  legitimate uses of that syntax — before the raw block itself is released.
  Construction and destruction must stay symmetric: whatever obtained the raw
  memory (`::operator new`) is what should free it (`::operator delete`),
  only *after* every object inside it has been destroyed individually:
  ```cpp
  for (int i = 0; i < N; i++)
      horde[i].~Zombie();      // destroy each object first
  ::operator delete(horde);     // then free the raw block — NOT delete[]
  ```
  Verified leak-free with Valgrind:
  ```
  HEAP SUMMARY:
      in use at exit: 0 bytes in 0 blocks
      total heap usage: 3 allocs, 3 frees, 77,952 bytes allocated
  All heap blocks were freed -- no leaks are possible
  ```

Memory correctness for `ex00`/`ex01` was checked with:

```sh
valgrind --leak-check=full ./zombie
```

### ex03 — Unnecessary violence

Builds `Weapon`, plus two humans that hold one by composition: `HumanA` (always
armed — the weapon is mandatory) and `HumanB` (may start unarmed, weapon attached
later via `setWeapon`). `main.cpp` mutates a `Weapon`'s type *after* handing it to
each human and re-attacks, to prove the humans are observing the live object
rather than a snapshot of it.

**Key concepts / notes:**

- **Members without a default constructor.** Any member not listed in a
  constructor's initializer list is **default-constructed before the
  constructor body runs**, using that member's own default constructor. If
  the member's type doesn't have one, this fails to compile — assigning to
  it inside the body is too late, since default construction was already
  attempted before the body starts. `Weapon` only declares
  `Weapon(std::string)`, no `Weapon()`, so this is exactly the wall
  `HumanA`'s copy constructor hit:
  ```cpp
  // WRONG — tries to default-construct `weapon` before the body runs
  HumanA::HumanA(const HumanA& other)
  {
      weapon = other.weapon;
      // error: no matching function for call to 'Weapon::Weapon()'
  }

  // RIGHT — construct directly in the initializer list, via Weapon's copy ctor
  HumanA::HumanA(const HumanA& other)
      : name(other.name), weapon(other.weapon) {}
  ```

- **Reference vs. pointer members.** The choice comes down to two
  independent properties: whether the relationship can be *absent*
  (nullable), and whether it can be *reassigned* to a different object after
  construction (rebindable). A reference has neither property; a pointer has
  both:
  | | Reference (`Weapon&`) | Pointer (`Weapon*`) |
  |---|---|---|
  | Must be bound at construction | Yes | No — can start `NULL` |
  | Can be null | No | Yes |
  | Can be re-pointed later | No, never | Yes, any time |

  `HumanA` is always armed — the weapon is mandatory and fixed for the
  object's whole life, so it holds a `Weapon&`. `HumanB` may start unarmed
  and have a weapon attached (or swapped) later via `setWeapon`, so it needs
  both properties a reference lacks — hence `Weapon*`.

- **Binding a reference to a temporary (lvalue vs. rvalue).** An lvalue is
  anything with a persistent identity — a named variable, `*ptr`, an array
  element — that you could take the address of and refer to again later. An
  rvalue is a temporary with no name, destroyed at the end of the full
  expression it appears in. A **non-const** reference cannot bind to an
  rvalue; only a `const` reference is granted that, via a lifetime-extension
  rule that applies to `const` references specifically:
  ```cpp
  Weapon& w = Weapon("WATER GUN");
  // error: invalid initialization of non-const reference from an rvalue

  Weapon  w("WATER GUN");   // w is a named lvalue — safe for a Weapon& to bind to
  ```

- **Shallow copy vs. deep copy.** A shallow copy duplicates a handle
  (pointer or reference) without touching what it refers to — both copies
  end up sharing the same underlying object. A deep copy instead allocates a
  new instance and copies the referred-to object's *contents* into it,
  giving each copy independent ownership. `HumanB`'s copy constructor,
  `weapon(other.weapon)`, is shallow — it copies the pointer *value*, so both
  `HumanB`s end up pointing at the same `Weapon`. That's correct here, since
  `HumanB` never owns the weapon, only borrows a reference to one that lives
  elsewhere. The deep alternative, if `HumanB` were meant to own it instead:
  ```cpp
  HumanB::HumanB(const HumanB& other)
      : weapon(other.weapon ? new Weapon(*other.weapon) : NULL), name(other.name) {}
  // now also requires `delete weapon;` in ~HumanB() — this HumanB owns its Weapon
  ```
  `HumanA`'s reference member is shallow in the same sense, even without a
  pointer involved: binding a reference in the copy constructor copies
  nothing, it just makes the new object refer to the exact same `Weapon` as
  the original.

- **`operator=` on a reference member.** A reference can never be re-bound
  after it's initialized, so assigning through it doesn't repoint it to a
  different object — it mutates the object it already refers to, via that
  type's own `operator=`. `HumanA::operator=`'s naive `weapon = other.weapon;`
  therefore doesn't make `this` refer to `other`'s weapon; it calls
  `Weapon::operator=` and overwrites the type of whatever `Weapon`
  `this->weapon` already refers to — a side effect on a third object that
  might be shared elsewhere in the program:
  ```cpp
  HumanA& HumanA::operator=(const HumanA& other)
  {
      if (this != &other)
          name = other.name;   // weapon is intentionally left alone — see above
      return (*this);
  }
  ```
  `HumanB::operator=` has no such problem: `weapon = other.weapon;` on a
  `Weapon*` just reseats the pointer, which is exactly the shallow-copy
  behaviour wanted, with no mutation of shared state.

### ex04 — Sed is for losers

Reads `<filename>`, replaces every occurrence of `s1` with `s2`, and writes the
result to `<filename>.replace`. No C file functions (`fopen`/`fread`/etc.), and
`std::string::replace` itself is off-limits — every other `std::string` member
function is fair game. Logic lives in `find_and_replace.{hpp,cpp}` (`read_file`,
`replace_all`, `write_file`); `main.cpp` only handles argv and orchestration.
Correctness is checked with `tests.sh`, a black-box test script that builds the
binary and drives it purely through argv + files on disk, the same way the
grader will.

**Key concepts / notes:**

- **`std::istreambuf_iterator<T>`** — an input iterator that reads raw
  characters directly out of a stream's buffer, one at a time, with no
  formatting or whitespace-skipping (unlike `>>`). A default-constructed
  instance, with no stream argument, is the standard's designated
  end-of-stream sentinel — comparing any `istreambuf_iterator` to it answers
  "have I run out of stream?" Paired with `std::string`'s range constructor,
  this reads a whole file byte-for-byte in one line, including every
  embedded newline — no need to reassemble the file line-by-line (which
  would need extra bookkeeping to know whether the original had a trailing
  newline):

  ```cpp
  std::istreambuf_iterator<char> begin(file);
  std::istreambuf_iterator<char> end;
  std::string content(begin, end);
  ```

- **The "most vexing parse"** — a standing C++ grammar rule: wherever a line
  of code could be parsed *either* as a declaration *or* as an expression,
  the compiler always picks the declaration reading. This becomes a trap the
  moment a constructor argument is itself written as `Type(x)`, because that
  shape is *also* valid syntax for "a parameter named `x` of type `Type`."
  It hit this exercise directly:

  ```cpp
  // Looks like: define a std::string named `content`, initialized from
  // two iterators.
  // Actually parsed as: declare a function named `content`, returning
  // std::string, taking a `std::istreambuf_iterator<char>` parameter named
  // `file` and one unnamed function-pointer parameter.
  std::string content(
      std::istreambuf_iterator<char>(file),
      std::istreambuf_iterator<char>());
  ```

  The compiler doesn't error on this line — it's valid as a declaration, just
  not the one intended. The error only surfaces later, wherever `content` is
  actually *used* as an object. Fix: give the iterators their own named
  variables first (as in the snippet above) — named variables aren't
  parenthesized `Type(x)` expressions, so the ambiguity never arises.

- **`std::string::substr(pos, len)` takes a length, not an end index.** The
  replace loop tracks `pos` (the resume point in the original string) and,
  on each match, needs to copy the *distance* between `pos` and the match —
  `found - pos` — not `found` itself.

  | Call | Meaning |
  |---|---|
  | `content.substr(pos, found - pos)` | correct — copy `found - pos` characters starting at `pos` |
  | `content.substr(pos, found)` | wrong — copy `found` characters starting at `pos` |

  Passing `found` directly only looked correct on the very first match
  (where `pos == 0`, so the two happen to be numerically equal); from the
  second match onward it copied extra characters, including the match text
  itself that was supposed to be replaced.

- **`std::string::npos`** — a `static const size_t` sentinel value, defined
  as the largest possible `size_t` (effectively "no valid position"). It
  plays two different roles depending on which function it's used with:

  | Used as... | Meaning |
  |---|---|
  | `find`'s return value | "no match was found" |
  | `substr`'s length argument | "copy through to the end of the string" |

  So `content.substr(pos, std::string::npos)` is a normal, correct way to
  copy the remaining tail of a string once the replace loop has run out of
  matches — not a misuse of the not-found sentinel.

- **Empty `s1` is a real infinite-loop hazard, not just an edge case.**
  `find("", pos)` "matches" (returns `pos`) at every position, with zero
  length — so `pos = found + s1.length()` never advances, and the loop spins
  forever:

  ```cpp
  size_t pos = 0;
  while (true)
  {
      size_t found = content.find("", pos); // always == pos
      // ...
      pos = found + 0;                      // pos never changes → infinite loop
  }
  ```

  Guarded against with an early `s1.empty()` check *before* the loop starts,
  rather than trying to special-case it inside the loop body.

- **A default-constructed `std::string` is empty, never garbage.** Unlike a
  built-in type (`int x;` leaves indeterminate bits), `std::string` is a
  class type, so declaring one with no initializer still invokes a
  constructor — its default constructor, whose job is specifically to
  produce a valid, empty (`size() == 0`) string. `std::string result;` is
  safe to `+=` onto immediately, with no explicit `= ""` needed first.

- **C++98 stream constructors only accept `const char*`, never
  `std::string`.** The `std::string`-argument overloads of
  `ifstream`/`ofstream`'s constructors were added in C++11.

  | Standard | `std::ofstream(std::string)` | `std::ofstream(const char*)` |
  |---|---|---|
  | C++98 (this module's target) | ✗ does not exist | ✓ |
  | C++11 and later | ✓ | ✓ |

  Under `-std=c++98`, passing a `std::string` (e.g. `filename + ".replace"`)
  straight to `std::ofstream(...)` fails to compile. `.c_str()` bridges the
  gap — a `std::string` member function that hands back a `const char*` view
  of the string's own internal, null-terminated buffer, with no copying.

- **Streams are non-copyable — which rules out copy-initialization for
  them.** Two ways to build an object, and under C++98 they aren't
  interchangeable:

  | Form | What it does | Needs an accessible copy ctor? |
  |---|---|---|
  | `Type var(args);` (direct-init) | Constructs `var` in place, once. | No |
  | `Type var = Type(args);` (copy-init) | Constructs a temporary, then copies it into `var` (even though real compilers usually elide the copy, C++98 still requires it to be *legal*). | Yes |

  `std::ifstream`'s copy constructor is `private` — deliberately, since only
  one object may own a given open file handle at a time. So
  `std::ifstream file = std::ifstream(filename.c_str());` fails to compile
  under C++98, while `std::ifstream file(filename.c_str());` (direct-init)
  works fine, since it never goes through a copy step at all. This is a
  C++98-specific trap: C++11 move semantics, and C++17's mandatory copy
  elision for prvalues, both make the copy-init form work fine for streams
  in modern C++ — just not under the standard this module targets.

- **Brace-init (`Type var{args};`) is a C++11 feature, not available in
  C++98.** `std::ifstream file{ av[1] };` fails with `extended initializer
  lists only available with -std=c++11` — parens (`Type var(args);`) are the
  only valid construction syntax here.

- **`std::ifstream`/`std::ofstream` vs. C's `FILE*`** — same underlying job,
  different safety guarantees:

  | | C (`FILE*`) | C++ (`ifstream`/`ofstream`) |
  |---|---|---|
  | Open | `fopen(path, "r"/"w")` | Constructor, or `.open(path)` |
  | Read/write | `fread`/`fwrite`/`fgets`/`fprintf` (format strings) | `<<`, `>>`, `.get()`, `.read()`, `.write()` (type-checked) |
  | Error reporting | Return value / `errno`, checked per call | `.is_open()`, `.fail()`, `.bad()`, or `if (!stream)` |
  | Resource cleanup | Manual `fclose` — forgetting it leaks the handle | Destructor auto-closes on scope exit (RAII) |

### ex05 — Harl 2.0

Builds `Harl`, with four private methods (`debug`/`info`/`warning`/`error`) that
each print one of Harl's canned rants, and a public `complain(std::string level)`
that dispatches to the right one. The subject explicitly bans a chain of
`if`/`else if` for the dispatch — it has to go through pointers to member
functions instead. `main.cpp` calls `complain()` with all four valid levels plus
an invalid one, to prove both the dispatch and the fallback work.

**Key concepts / notes:**

- **Pointer to member function.** A pointer-to-member-function is a distinct
  pointer type that refers to a non-static member function *belonging to a
  specific class*, rather than to a fixed code address. It cannot be called
  on its own the way an ordinary function pointer can — a member function
  implicitly needs an object to run against (see the next point), and the
  pointer alone carries no object with it.

  | | Ordinary function pointer | Pointer to member function |
  |---|---|---|
  | Declared as | `void (*fp)(void);` | `void (Harl::*mp)(void);` |
  | Refers to | A fixed address in code | A member "slot" defined on a class |
  | Needs an object to call | No | Yes, always |
  | Call syntax | `fp();` | `(obj.*mp)();` or `(objPtr->*mp)();` — **never** `mp()` |

- **Why an ordinary function pointer can't hold a member function.** Every
  non-static member function implicitly receives the calling object as a
  hidden first parameter — conventionally accessed inside the function as
  `this`. The function's compiled code is shared across every instance (there
  is exactly one copy of `Harl::debug`'s machine code, not one per `Harl`
  object); `this` is what tells a given call *which* object's data to use.
  A plain `void(*)(void)` has no slot to carry that object, so the language
  defines a structurally different pointer type for members —
  `void (Harl::*)(void)` — precisely so the compiler can force an object to
  be supplied before the pointer can ever be called.

- **`ClassName::` — compile-time scope resolution, not object binding.** The
  scope resolution operator (`::`) tells the compiler *where to look up a
  name* — inside which class, namespace, or enclosing scope — and nothing
  more. `&Harl::debug` never touches any `Harl` object: it resolves the name
  `debug` specifically within `Harl`'s scope (distinguishing it from an
  unrelated `debug()` some other class might declare) and produces a typed
  value. Binding that value to an actual instance happens later, and
  separately, at the point the pointer is *called*.

  ```cpp
  class Harl  { void debug(void); /* prints a bacon rant */ };
  class Robot { void debug(void); /* prints a diagnostic */ };

  &Harl::debug;   // resolves to Harl's debug — the qualifier disambiguates
                  // which of the two same-named functions is meant
  ```

- **`.*` and `->*` — the operators that actually supply the instance.** A
  member pointer stored in a variable can't be invoked with plain `()`;
  calling it needs one of two dedicated operators, which pair an object with
  a member-pointer *value* the same way `.`/`->` pair an object with a member
  *name* known at compile time:

  | Operator | Left operand | Right operand | Used for |
  |---|---|---|---|
  | `.` | an object | a member name (fixed at compile time) | ordinary member access, e.g. `harl.complain(...)` |
  | `->` | a pointer to an object | a member name | ordinary member access through a pointer |
  | `.*` | an object | a member-pointer **value** (only known at runtime) | calling/accessing a member whose identity lives in a variable |
  | `->*` | a pointer to an object | a member-pointer **value** | same, through a pointer to the object |

  Inside `complain()`, `this` is already a `Harl*`, so dispatch goes through
  `->*`:

  ```cpp
  (this->*levels_fn[i])();
  // 1. levels_fn[i]  -> a stored pointer-to-member VALUE
  // 2. this->*        -> pair it with the current object, supplying `this`
  // 3. (...)()         -> now call the result
  ```

- **Deriving the array-of-member-pointers syntax, instead of memorizing it.**
  C++ declarations follow one consistent rule: to turn any declared entity
  into an array of N, insert `[N]` directly next to its *name*, leaving the
  rest of the declaration's shape untouched. Starting from a single pointer
  and applying that rule mechanically:

  ```cpp
  void (Harl::*debug_ptr)(void);          // one pointer to a Harl member
  void (Harl::*levels_fn[4])(void);       // same shape, [4] slotted next to the name
  ```

  A `typedef` up front avoids re-deriving (or re-reading) the dense form more
  than once — both lines below declare the same array type:

  | Form | Declaration |
  |---|---|
  | Direct | `void (Harl::*levels_fn[4])(void) = {...};` |
  | Via `typedef` | `typedef void (Harl::*FnPtr)(void); FnPtr levels_fn[4] = {...};` |

- **Declaring the canonical form obligates you to define it — a link-time
  trap.** A *declaration* just promises a name and signature exist somewhere;
  a *definition* is what actually provides the body/address the linker needs.
  `Harl.hpp` explicitly declares a default constructor, copy constructor,
  `operator=`, and destructor — once declared explicitly, the compiler stops
  generating implicit defaults for them, so every one of those four now needs
  a real definition in `Harl.cpp`.

  | Stage | What it checks | What skipping the definitions looks like |
  |---|---|---|
  | Compile | Every *name used* has a visible declaration | Passes silently — a declaration is all the compiler asked for |
  | Link | Every *function called* has exactly one definition | `undefined reference to Harl::Harl()`, the moment `main.cpp` writes `Harl harl;` |

- **`switch` was never an option here regardless.** C++98's `switch` requires
  an integral or enum controlling expression — `std::string` doesn't qualify,
  so even ignoring the "no if/else forest" rule, dispatching on `level` with
  a `switch` wouldn't compile. `switch` becomes usable again only once the
  level is represented as an `enum` — the approach ex06 takes.

### ex06 — Harl filter

Reworks `Harl::complain` to take a severity level from `argv[1]` and print every
message **at or above** that severity (`DEBUG` → all four, `ERROR` → just error),
using a `switch` on an `enum Level`. Logic lives entirely in `Harl.cpp`; `main.cpp`
just validates `argc` and forwards `argv[1]`.

**Key concepts / notes:**

- **`enum` — a named type with a fixed set of integer constants.** An `enum`
  declaration introduces both a new type and a set of named constants, each
  backed by an integer value (by default, `0, 1, 2, ...` in declaration
  order). Unlike a `std::string`, an enum value *is* an integral type under
  the hood — which is exactly what `switch` needs to work at all:

  ```cpp
  enum Level { DEBUG, INFO, WARNING, ERROR };
  // DEBUG == 0, INFO == 1, WARNING == 2, ERROR == 3
  ```

- **Bridging `std::string` to an `enum` — the adapter step.** The program
  still receives the level as text (`argv[1]`), so something has to convert
  that string into one of the four `Level` values before a `switch` can use
  it. The fix is a parallel array of the level names, searched linearly, with
  the resulting index doubling as the matching enum value:

  ```cpp
  std::string levelNames[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
  int         ilevel       = -1;             // sentinel: "no match yet"

  for (int i = 0; i < 4; i++)
      if (levelNames[i] == level)
          ilevel = i;
  ```

  The `-1` sentinel matters: a local `int` left uninitialized holds an
  indeterminate value, and switching on it when no name matches would be
  undefined behaviour — not reliably reaching `default`. Initializing to a
  value outside `0`–`3` guarantees an unrecognized level falls through to
  `default` every time.

- **How `switch`/`case`/`break` actually execute.** A `case` label is not a
  boundary that stops execution — it's just a named jump target, like a
  bookmark. `switch (x)` computes `x` once, jumps to whichever `case` label
  matches, and then execution proceeds **straight down, line by line**,
  exactly as if the labels weren't there, until it hits a `break` (which
  exits the whole `switch`) or runs off the end of the block. `break` is the
  only thing that stops it — without one, control just keeps running into
  whatever code sits below, `case` label or not:

  | `x` | Jumps to | Then executes (no `break` in the way) | Output |
  |---|---|---|---|
  | `0` | `case 0:` | `case 0:`'s code, then falls into `case 1:`'s code, stops at its `break` | `"zero"`, `"one"` |
  | `1` | `case 1:` (skips `case 0:`'s code entirely — jumping to a label never runs what's above it) | `case 1:`'s code, stops at its `break` | `"one"` |

  ```cpp
  switch (x)
  {
      case 0: std::cout << "zero" << std::endl;   // no break
      case 1: std::cout << "one"  << std::endl; break;
      case 2: std::cout << "two"  << std::endl; break;
  }
  ```

- **Fallthrough as a deliberate technique, not a bug.** "Falling through" is
  the name for exactly the behaviour above: a case with no `break` runs into
  the next one. It's normally a beginner mistake, but it's the natural way to
  express "this severity and everything worse" — each case only needs to
  print *its own* message before continuing into the next, instead of every
  case re-listing every message at or above it:

  ```cpp
  switch (ilevel)
  {
      case DEBUG:
          (this->*harl_fn[0])();
          // fallthrough
      case INFO:
          (this->*harl_fn[1])();
          // fallthrough
      case WARNING:
          (this->*harl_fn[2])();
          // fallthrough
      case ERROR:
          (this->*harl_fn[3])();
          break ;
      default:
          // unrecognized level
  }
  ```

  `ilevel == INFO` jumps straight to `case INFO:` (never touching `case
  DEBUG:`'s line), then cascades through `WARNING` and `ERROR` — three
  messages, correctly skipping `debug`.

- **`-Wimplicit-fallthrough` under `-Werror`.** Because a missing `break` is
  such a common accidental bug, modern GCC's `-Wextra` warns on any case that
  falls into the next one — and under this project's `-Werror`, that warning
  becomes a hard compile error, even though the fallthrough above is
  intentional. Verified directly against this repo's build flags:

  | Code | Result under `-Wall -Wextra -Werror -std=c++98` |
  |---|---|
  | Fallthrough with no comment | `error: this statement may fall through [-Werror=implicit-fallthrough=]` |
  | Fallthrough with a `// fallthrough` comment immediately before the next `case` | Compiles clean |

  GCC specifically recognizes a comment containing the word "fallthrough" as
  an explicit "yes, I meant this" marker — it's a real requirement for this
  build, not decoration.

## Resources

Classic references consulted while working through this module:

- [cppreference.com](https://en.cppreference.com/) — `std::string`, `new`/`delete` expressions, placement `new`, pointers to members.
- [isocpp.org FAQ](https://isocpp.org/faq) — Orthodox Canonical Form, copy constructors/assignment operators, general C++ idioms.
- Bjarne Stroustrup, *The C++ Programming Language* — background on object lifetime, memory allocation, and references.
- Scott Meyers, *Effective C++* — guidance on the canonical form and resource management.
- The 42 CPP Module 01 subject PDF (`resource/en.subject.pdf` in this repo).
