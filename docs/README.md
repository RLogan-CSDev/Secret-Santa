# Secret Santa Application
**Developer**: Robert Logan

---

## Project Overview
Imagine you are playing a game of Secret Santa with some friends and/or family. Everyone
writes their name down on a piece of paper with a couple of gift ideas for something they
would like their *secret Santa* to get for them. The first person draws and gets their
assigned person, and this pattern repeats until the last person gets their assignment.
#### Scenario
What happens when the second to last person, let's call him `Bob`, draws himself? Bob would
have to put his name back into the hat and be forced to draw the last available person in
the hat, let's call her `Alice`. Then, the very last person, let's call him `Charlie`,
would be default assigned to `Bob`. Since `Bob` had to put his name back into the hat,
everyone knew that he drew himself, leaving everyone aware that `Charlie` will be assigned
to `Bob`. The drawing gets more complicated when you add partner constraints, such as
`Bob` cannot draw his partner, `Alice`, either.


This is the exact conundrum that my Secret Santa application resolves.
### Problems Solved
1. Randomized secret santa assignment.
2. Partner and self-drawing constraints.
3. Dynamic counter for identifying remaining draws.

---

## Tech Stack
- **Language**: C++17
- **Libraries**: `std::vector`, `std::random`
- **IDE**: Qt Creator
- **Version Control**: GitHub

### Design Patterns
- *Encapsulation*: Packaged all of the attributes and methods specific to a `Player`
instance, and a `SantaBag` instance into separate classes, preventing unprivileged access
to that particular instance's resources.
- *Composition*: The **has-a** relationship in which the `SantaBag` class **has a** `Player`
object as part of it's class definition.
- *Function Overloading*: A single identifier to `add` players to the bag has diverse
meanings by creating functions with the same name, different parameter lists. This is an
example of ***compile-time polymorphism***.