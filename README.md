# Time-Travel File System (TTFS)
xoxoxoo
## Project Overview
This project implements a **Time-Travel File System (TTFS)** in C++ that supports versioning, snapshots, branching, rollback, and analytics on files. It maintains the history of file contents over multiple versions, allowing users to explore and revert to previous versions of files. The system also provides commands to track the biggest files (by versions) and the most recently modified files.

The project has been designed to handle **complex histories**, **branching**, **high-volume versioning**, and **extreme edge cases**.

---

## Modules

* **`main.cpp`**
    * CLI interface for the Time-Travel File System.
    * Supports commands like `CREATE`, `READ`, `INSERT`, `UPDATE`, `SNAPSHOT`, `ROLLBACK`, `HISTORY`, `BIGGEST TREES`, `RECENT FILES`, `EXIT`.

* **`File.hpp` / `File_definition.tpp`**
    * Represents a file with versioning support.
    * Each file maintains a **tree of TreeNodes**, where each node is a version of the file. 
    * Supports operations: `insert`, `update`, `snapshot`, `rollback`, `history`.
    * Destructor cleans up all dynamically allocated TreeNodes to avoid memory leaks.

* **`Version.hpp`**
    * Defines **`TreeNode`**, representing a single version of a file.
    * Each `TreeNode` stores `version_id`, `content`, `snapshot message`, `timestamps`, `parent pointer`, and `children pointers`.

* **`types.hpp`**
    * Defines structures:
        * `big_tree`: for keeping track of number of versions per file.
        * `recent_file`: for tracking recent modifications.
        * `return_snapshot`: for storing snapshot history.

* **`Heap.hpp` / `Heap_definition.tpp`**
    * Template **`Heap`** class with custom comparator.
    * Used to maintain:
        * Max heap of biggest trees by version count.
        * Max heap of most recently modified files.
    * Destructor clears vector memory.

* **`Map.hpp` / `Map_definition.tpp`**
    * Implements a **custom HashMap** with linked list buckets (no STL `unordered_map` used).
    * Supports `insert`, `get`, and `contains` operations for mapping filenames to `File` objects.

* **`System.hpp` / `System_definition.tpp`**
    * The main system controller.
    * Holds `HashMap<File>` as the file system.
    * Maintains two heaps:
        * `heap_biggestTrees`
        * `heap_recentFiles`
    * Provides all the file system operations as a high-level API.
    * Destructor ensures heaps are cleared, files are destroyed.

---

## Compilation Instructions
1. Ensure all files are in the same directory:
    ```
    main.cpp
    File.hpp
    File_definition.tpp
    Version.hpp
    types.hpp
    Heap.hpp
    Heap_definition.tpp
    Map.hpp
    Map_definition.tpp
    System.hpp
    System_definition.tpp
    ```

2. Compile with:
    ```bash
    g++ -std=c++17 main.cpp -o ttfs
    ```

3. Run the program:
    ```bash
    ./ttfs
    ```

---

## Supported Commands

| Command | Description | Example |
| :--- | :--- | :--- |
| **`CREATE <filename>`** | Create a new file with an initial empty version. | `CREATE my_doc.txt` |
| **`READ <filename>`** | Print the content of the active version. | `READ my_doc.txt` |
| **`INSERT <filename> <content>`** | Append content as a new version if the active version is a snapshot. | `INSERT my_doc.txt "More text"` |
| **`UPDATE <filename> <content>`** | Replace content in a new version. | `UPDATE my_doc.txt "New content"` |
| **`SNAPSHOT <filename> <message>`** | Create a snapshot of the active version with a message. | `SNAPSHOT my_doc.txt "Initial draft"` |
| **`ROLLBACK <filename> [versionID]`** | Revert file to parent version or a specific version ID. | `ROLLBACK my_doc.txt` or `ROLLBACK my_doc.txt 5` |
| **`HISTORY <filename>`** | Display all snapshots of the file along with timestamps and messages. | `HISTORY my_doc.txt` |
| **`BIGGEST TREES <num>`** | Show top `<num>` files with the most versions. | `BIGGEST TREES 5` |
| **`RECENT FILES <num>`** | Show top `<num>` files most recently modified. | `RECENT FILES 3` |
| **`EXIT`** | Exit the system. | `EXIT` |

---

## Error Handling
* Invalid commands, missing filenames, missing content, or invalid version IDs do **not crash the system**. Errors are printed and the program continues.
* Duplicate `CREATE` commands are ignored with an error message.
* Accessing non-existent files is handled gracefully.

## Memory Management
* `TreeNodes` are dynamically allocated per version.
* `File::~File()` deletes all versions.
* Heaps are properly cleared in `System::~System()`.
* **No memory leaks** in extreme test cases.

## Extreme Test Case Support
* Supports **branching**, **rollback**, and multiple snapshot histories per file.
* Handles high-volume files (like datasets with many versions).
* Tracks recent modifications and largest version trees.
* Handles edge cases like invalid rollback, inserting into non-existent files, or updating snapshot versions.

---

**Author**
Arittra Malhotra

**Date**
2025
