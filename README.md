# B-Tree Implementation in C++

This contains a C++ code that implements a B-Tree data structure. A B-Tree is a self-balancing tree that can store and retrieve data efficiently. It is commonly used in databases and file systems

## Motivation

I created this code as a part of my <b>Advanced Data Structure Course</b>. I wanted to learn how to implement a B-Tree from scratch and understand its operations and applications. I also wanted to practice using templates and dynamic memory allocation in C++.

## Features

- The project defines a template class `BTree<T, Order>` that can store any type of data `T` with a given order `Order`.
- The project also defines a template struct `Node<T, Order>` that represents a node in the B-Tree. Each node has an array of keys, an array of child pointers, and some other attributes.
- The project provides methods for inserting, searching, splitting, and printing the B-Tree.

## Why B-Tree?

B-Tree is a powerful data structure that offers many advantages over other data structures. Here are some of the reasons why you should use B-Tree for your data:

- **Fast and Scalable**: B-Tree has a low height and a high branching factor, which means that it can store and access a large amount of data with a small number of disk I/Os. The time complexity for searching, inserting, and deleting a key in a B-Tree is O (log n), where n is the number of keys in the tree. This is much better than the linear or quadratic time complexity of other data structures such as arrays, linked lists, or hash tables.
- **Sorted and Sequential**: B-Tree maintains the data in sorted order, which makes it easy to traverse the data from the smallest to the largest key. This is useful for applications that require sequential access or range queries on the data. Moreover, B-Tree supports efficient operations on ordered data such as finding the minimum, maximum, predecessor, successor, or median key.
- **Flexible and Compact**: B-Tree allows each node to have a variable number of keys and child pointers, as long as they satisfy the minimum and maximum constraints. This means that the B-Tree can adapt to the changes in the data and avoid wasting space or creating fragmentation. Moreover, B-Tree has efficient algorithms for splitting and merging nodes when they become too full or too empty, which ensures that the tree remains balanced and compact.

## Installation

To install this project, you need to have a C++ compiler that supports templates. You can clone or download this repository to your local machine and compile the main program using the following command:

```bash
g++ main.cpp -o main
```

This will create an executable file named main in the same directory. You can run it by typing:

```
./main
```

## Usage

To use this project, you can compile and run the C++ file main.cpp that contains the header and implementation of the BTree class. For example:

```
int main()
{
    // Create a B-Tree of order 3 that stores integers
    BTree<int, 3> t1;
    // Insert some values
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);
    // Print the B-Tree
    t1.Print();
    // Output:
    /*
    1,4
      0
      2,3
      5
    */
    
    // Create a B-Tree of order 5 that stores characters
    BTree<char, 5> t2;
    // Insert some values
    t2.Insert('G');
    t2.Insert('I');
    t2.Insert('B');
    t2.Insert('J');
    t2.Insert('C');
    t2.Insert('A');
    t2.Insert('K');
    t2.Insert('E');
    t2.Insert('D');
    t2.Insert('S');
    t2.Insert('T');
    t2.Insert('R');
    t2.Insert('L');
    t2.Insert('F');
    t2.Insert('H');
    t2.Insert('M');
    t2.Insert('N');
    t2.Insert('P');
    t2.Insert('Q');
    // Print the B-Tree
    t2.Print();
    // Output:
    /*
     K
      C,G
        A,B
        D,E,F
        H,I,J
      N,R
        L,M
        P,Q
        S,T
     */
    
     return 0;
}
```

## Contributing

I welcome any contributions to this code. If you want to contribute, please follow these steps:

- Fork this repository and clone it to your local machine.
- Create a new branch with a descriptive name for your feature or bug fix.
- Make your changes and commit them with clear and concise messages.
- Push your branch to your forked repository and create a pull request to the master branch of this repository.
- Wait for me to review your pull request and provide feedback or suggestions.
- If everything is fine, I will merge your pull request and thank you for your contribution.

## License

This code is licensed under the MIT License. You can use, modify, and distribute this project for any purpose, as long as you include the original license notice and disclaimer.

## References

For more information about B-Trees, you can check out these resources:

- [B-Tree - Wikipedia](https://en.wikipedia.org/wiki/B-tree)
- [B-Trees Visualization](https://www.cs.usfca.edu/~galles/visualization/BTree.html)
