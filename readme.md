# COL106 Project

This is a C++ project for COL106 (Data Structures and Algorithms).  
It implements custom data structures including a **Binary Heap**, a **HashMap**, and a **TreeNode-based versioning system**, with a test driver in `test.cpp`.

---

## Build Instructions

### Using the provided shell script
1. Make the script executable (only once):
   ```sh
   chmod +x shellscript.sh
   ```
2. Run the script:
   ```sh
   ./shellscript.sh
   ```
   This compiles all `.cpp` files and produces an executable named **`test.exe`**  

### Manual compilation
If you prefer, you can compile manually:
```sh
g++ -std=c++17 -Wall -Wextra -O2 test.cpp Binaryheap.cpp HashMap.cpp TreeNode.cpp -o test.exe
```

---

## Running the Program
After compilation, run:
```sh
./test.exe
```

The program reads commands from **standard input** (`cin`) line by line.  
To exit, type:
```
EXIT
```


---

## Features
- **Binary Heap** (`Binaryheap.cpp/.hpp`): Priority queue functionality. Generates a max_heap.
- **HashMap** (`HashMap.cpp/.hpp`): Custom hash map implementation.
- **TreeNode** (`TreeNode.cpp/.hpp`): Versioned tree with snapshot support.
- **Test Driver** (`test.cpp`): Entry point to run and test the data structures.

---

## Notes
- Error handling ensures invalid file operations don’t terminate the program; instead, an error message is displayed and the program continues.
- Time information for versions is stored using `std::time_t` (epoch seconds).

---

## Example Run
```text
> CREATE FILE1
> INSERT FILE1 Hello world
> SNAPSHOT FILE1 created version 1
> INSERT FILE1 Updated content
> READ FILE1
> SNAPSHOT FILE1 created version 2
> HISTORY FILE1
> ROLLBACK FILE1 0
> HISTORY FILE1
> EXIT
```

---

## Usage

The program works as an interactive command-line tool.  
It reads commands line by line from **standard input** and applies them to files stored in your data structures.

### Available Commands (examples)
- **Create a file**
  ```
  CREATE FILE1
  ```
  If file already exists, error is thrown and program moves to next command.

- **Insert into a file**  
  ```
  INSERT FILE1 CONTENT
  ```
  If file does not exist, error is thrown and program moves to next command. This is true for all functions which take file name as parameter.

- **Take a snapshot of a file**  
  ```
  SNAPSHOT FILE1 SNAPSHOT MESSAGE
  ```
  If the active version is already a snapshot, nothing will happend.

- **Update file content**  
  ```
  UPDATE FILE1 NEW CONTENT
  ```

- **Read content from file**  
  ```
  READ FILE1
  ```

- **Rollback to another version using its id**  
  ```
  ROLLBACK FILE1 2
  ```
  In case no ID is provided, it automatically rolls back to the parent.

- **Get the history of file**  
  ```
  HISTORY FILE1
  ```

  Returns a list of all snapshotted versions of the active version all the way upto the root, i.e., the original version.  

- **Display last modified file**  
  ```
  RECENT_FILES 2
  ```
  In case the number of files asked exceeds the number of existing files, it would return all the existing files in descending order of their modifies time.

- **Display largest files**  
  ```
  BIGGEST_TREES 2
  ```
  In case the number of files asked exceeds the number of existing files, it would return all the existing files in descending order of their vesrion count.

- **Exit the program**  
  ```
  EXIT
  ```


---

## Custom Data Structures Implementation

I have implemented a number of data structures in this project.
- **TreeNode**
  A simple object which represents one version of the file. It is uniquely identified in  the file tree by a version ID, which is an integer.

- **Tree**
  A tree is a representation of a file. It maintains a vector whose ith index contains the pointer to the version with ID i. It is a simple implementation of a hash map which makes look ups of a version by its ID O(1).

- **HashMap**
  I have implemented two different versions of a hashmap. Both hash a string to long long, and elements are stored in bucket arrays. One maps file name to int, which is used for maintaining the binary heaps for file size and modified time. The other maps file name to a pointer for that tree.

- **BinaryHeap**
  Uses vector to implement a MaxHeap, and HashMaps to look up elements in O(1) time. Updates dynamically as relevant commands are used.  

