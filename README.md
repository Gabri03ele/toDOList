# TODO List Project

A basic project for managing and organizing your tasks. 
Add, complete, modify and remove tasks to keep track of your to-do list easily.

### Features

- Add tasks with descriptions.
- Complete existing tasks.
- Modify description of existing tasks.
- Remove tasks when completed.

### Compile the file

From within the parent directory create a build directory if it doesn't exist:

$ mkdir build
$ make

Move into the build directory:
$ cd build.

For a "debug" build, do this instead:

$ make debug

To use compile sanitizers:

$ make sanitizers

### Run the code

After compilation, from within the parent directory:

$ ./build/todo_list

Replace todo_list with the actual name of your executable if it differs.
