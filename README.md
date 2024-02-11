# Skald

### How to build

 ```
g++ --std=c++17 -o skald main.cpp src/file_system.cpp src/makefile.cpp external/yyjson.c src/json_reader.cpp
or
clang++ --std=c++17 -o skald main.cpp src/file_system.cpp src/makefile.cpp external/yyjson.c src/json_reader.cpp
 ```

only works on windows at the moment

### How to use

Run it in project folder, easy if you've added skald to path.
 ```
skald
 ```
This will setup the make file, then just build.
 ```
make -j8
 ```
And to clean just
 ```
make clean
 ```

### How to configure project
you can add a settings.json file to your project folder, and include something like:
```
{
    "project_name": "Skald",
    "debug": "true"
}
```
here you can set project name.

### How to add dependencies
you first need to add a dependencies.json file, and include something like this:
```
{
    "vcpkg_path": "D:/tools/vcpkg/installed/x64-windows/",
    "dependencies":["example_one", "example_two"]    
}
```
and skald will add the dependencies and do the linking, not very smart, but works in simple cases.