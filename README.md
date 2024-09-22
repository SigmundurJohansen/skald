# Skald
 ```
docker build -t skald:latest .
 ```
 
### How to build
step 1
 ```
g++ --std=c++17 -o skald src/main.cpp src/file_system.cpp src/makefile.cpp external/yyjson.c src/json_reader.cpp src/default_project.cpp
 ```
or
 ```
clang++ --std=c++17 -o skald src/main.cpp src/file_system.cpp src/makefile.cpp external/yyjson.c src/json_reader.cpp src/default_project.cpp
 ```
step 2
 ```
sudo mv ./skald /usr/bin
 ```
 or
 ```
add skald folder to path 
 ```

### How to use

To get started you can generate a default template project in your project directory, easy if you've added skald to path, to startup a default project simply run
 ```
skald -default
 ```
Review the main.cpp, and add whatever you need.
Then run skald. This will setup the make file.
 ```
skald
 ```
Then to build execute.
 ```
make -j8
 ```
And to clean.
 ```
make clean
 ```

### How to configure project
you can add a settings.json file to your project folder, and include something like:
```
{
    "project_name": "new_project",
	"compiler_flag" : ["-g","-std=c++20","-Wall","-fstack-usage"]
}
```
here you can set project name.

### How to add dependencies
you first need to add a dependencies.json file, and include something like this:
```
{
    "vcpkg_path": "D:/tools/vcpkg/installed/x64-windows/",
	"dependencies" : ["fmt"],
	"includes" : []
}
```
and skald will add the dependencies and do the linking, not very smart, but works in simple cases.

### Add default format
To add a default .clang-format file
```
skald -format
```