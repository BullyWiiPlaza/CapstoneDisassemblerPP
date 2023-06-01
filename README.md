# CapstoneDisassemblerPP

A very basic wrapper around the [Capstone C API](https://www.capstone-engine.org/lang_c.html) for more convenient usage.

## Compiling

Load the `.sln` file in Visual Studio and build your project (the dependencies from the [vcpkg](https://vcpkg.io) manifest file `vcpkg.json` will be installed locally in this project automatically if you ran `vcpkg integrate install` before).
You can now reference this project from another one by specifying the folder of this project in the `Include Directories` of your Visual Studio C++ project.
Include the `*.hpp` file(s) in your code to start using code from this project and make sure to add the `*.cpp` file(s) as `Add` -> `Existing Item` to your code to avoid getting linker error(s) after attempting to build your code.
Note that for using this library from another project you should install the dependencies globally using e.g. `vcpkg install capstone[x86]:x86-windows` (or `vcpkg install capstone[x86]:x86-windows-static` when building statically), otherwise `capstone/capstone.h` won't be found when compiling the parent project.