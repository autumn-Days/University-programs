## 1. Purpose

This repository contains the two projects that I did for the discipline of "Data structures 2"$^1$.

## 2. Structure

### 2. Set data structure

Here I implemented a set datastructure using an AVL tree with C++. It permits you to make all the _CRUD_ operations, beyond the set operations, which are:

1. Union: $\{1,2,3\} \bigcup \{3,4,5\} = \{1,2,3,4,5\} $
2. Intersection: $\{1,2,3\} \bigcap \{3,4,5\}= \{3\}$ 
3. Difference: $\{1,2,3\} - \{3,4,5\}= \{1,2\}$

#### 2.1 Usage

```cpp
//insertion
mySet->insert("Carl");
mySet->insert("Mary");
mySet->insert("Lucke");
//read
inOrder(mySet->root);
//deletion
mySet->erase("Carl");
mySet->erase("Lucke");
//
```

[1]: Actually the name of the subject was advanced data structures, but the name of the repository wouldn't be that cool if I had adopt the actual name.