# jnp1-4

Repository contains a program that manages bakery. It was written for advanced C++ classes. The intresting thing is that it uses 
C++17 compile-time features.

There is Pi and Ln(2) calculated at compilation time. There are template types that have 
some complex requirements for template types. For example Bakery checks, if all Products 
have unique types at compile time, otherwise compilation error is raised. It requires a lot of not-obvious tricks.

