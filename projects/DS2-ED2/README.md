## 1. Purpose

This repository contains the two projects that I did for the discipline of "Data structures 2"$^{1}$.

## 2. Structures

### 2.1 Set data structure

Here I implemented a set datastructure using an AVL tree with C++. It permits you to make all the _CRUD_ operations, beyond the set operations, which are:

1. Union: $\{1,2,3\} \bigcup \{3,4,5\} = \{1,2,3,4,5\} $
2. Intersection: $\{1,2,3\} \bigcap \{3,4,5\}= \{3\}$ 
3. Difference: $\{1,2,3\} - \{3,4,5\}= \{1,2\}$

#### 2.1.1 Usage

Here are the CRUD functionalities:

```cpp
//creation and insertion
Set<string>* mySet = new Set<string>();
mySet->insert("Carl");
mySet->insert("Mary");
mySet->insert("Lucky");
//read
inOrder(mySet->root);
//update
mySet->update("Lucky", "Lucke")
//deletion
mySet->erase("Carl");
mySet->erase("Lucke");
```
for the set functionalities, suppose you have a `set1` and `set2` and they are equal, respectively, to : $\{Ane, Mary, Joseph\}$ and $\{Emanuel, Mary, John\}$.

```cpp
set1->intersection(set1,set2); //Mary
set1->difference(set1,set2); //empty
set1->union2(set1,set2); //Emanuel, Mary and John
```

It's a bit funny, but, since "union" was already a keyword in C++, I needed to use another name for the "union" operation😅.

#### 2.1.2 Compilation

In order to test the set data structure I created a menu that enables the user to test all the main functionalities. To compile it, everything that needs to be done is run the command `g++ main.cpp` in the same directory of the project.

If you are using linux or mac, to run the code after compilation just make `./a.out`, if you in windows, use `./a.exe`

### 2.2 Word frequency counter

The main purpose of this project was to empirically compare the performance of dictionaries implemented with different 4 data structures by using the metric of number of comparitions of keys needed to create a table of the frequency of the first 1024 words of a given book and the time spent to do so. For example, if the whole book consisted in just "cats are fun. I love cats" the output would be:

```txt
are 1
cats 2
fun 1
i 1
love 1
```

The datastructures used were:

1. AVL tree
2. Red-black tree
3. Hash table with open adressing
4. Hash table with separate chaining

#### 2.2.2 Dependencies

For treating special characters from other languages, such as russian, mandarin or portuguese, it was used the `icu` library. For this reason it must be installed system wide before using the program. Also, the program must be compiled using `g++` version 17 or superior.

### 2.2.3 Compilation and execution

To compile the program, you just need to run `g++ -std=c++17 main.cpp
-o <executable's name> -licuuc -licui18n` and, since this is a `CLI` program, you will have to use it just like if you were using some comamand in the terminal. The syntax is:

```
<executable name> <data structure choosed> <book name>.txt
```

For choosing the datastructure, use the following mnemonics:

1. AVL: AVL tree
2. RB: Red-black tree
3. hashOpen: Hash table with open adressing
4. hashExt: Hash table with separate chaining

For example, to execute the program using the `Pollyana` (which is already given) you can run it by using the following commands:

```
1. g++ -std=c++17 main.cpp -o freq -licuuc -licui18n
2. ./freq hashOpen pollyanaExample.txt
```

___
[1]: Actually the name of the subject was advanced data structures, but the name of the repository wouldn't be that cool if I had adopt the actual name.