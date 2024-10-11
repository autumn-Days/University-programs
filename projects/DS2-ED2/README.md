## 1. Purpose

This repository contains the two projects that I did for the discipline of "Data structures 2"$^1$.

## 2. Structure

### 2. Set data structure

Here I implemented a set datastructure using an AVL tree with C++. It permits you to make all the _CRUD_ operations, beyond the set operations, which are:

1. Union: $\{1,2,3\} \bigcup \{3,4,5\} = \{1,2,3,4,5\} $
2. Intersection: $\{1,2,3\} \bigcap \{3,4,5\}= \{3\}$ 
3. Difference: $\{1,2,3\} - \{3,4,5\}= \{1,2\}$

#### 2.1 Usage

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


[1]: Actually the name of the subject was advanced data structures, but the name of the repository wouldn't be that cool if I had adopt the actual name.