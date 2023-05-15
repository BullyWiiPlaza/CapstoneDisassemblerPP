# CapstoneDisassemblerPP

A very basic wrapper around the [Capstone C API](https://www.capstone-engine.org/lang_c.html) for more convenient usage.

## Compiling

Load the `.sln` file in Visual Studio and make sure that `Capstone[x86]` is installed via e.g. `vcpkg`.
You can now reference this project from another one by specifying the folder of this project in the `Include Directories` of your Visual Studio C++ project.
Include the `*.hpp` file(s) in your code to start using this project and make sure to add the `*.cpp` file(s) as `Add` -> `Existing Item` to your code to avoid getting linker error(s).