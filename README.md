# Huffman_Coding

# Introduction:

Huffman coding is a lossless data compression algorithm. The idea is to assign variable-length codes to
input characters, lengths of the assigned codes are based on the frequencies of corresponding characters.
The most frequent character gets the smallest code and the least frequent character gets the largest code.

# Data Structures used:
Binary Tree, Priority Queue

# Justification:
All the characters are stored using 8 bits i.e., 1 byte. Most recurring character are assigned a smaller code
compared to less frequent characters which reduces the file size thus implementing a lossless data
compression.

# List of functions/features with brief explanation


push(struct hufftree *,int) – This function is used to insert elements into the priority queue according to its
priority.


pop() – this Is to remove element with highest priority i.e. front most element.


tree_creator(int TheGivenList[128]) – enqueues all the unique characters with their frequencies in a queue.
And creates a frequency tree using it.


hufftree_parser(struct hufftree *root, char encode[16]) – traverses through the frequency tree and makes
code with 0’s and 1’s for leaf node(character to be encoded). 0 meaning go left and 1 meaning go right.


tobin(char*) – takes a string of length 8 containing 0’s and 1’s and converts it to a single character (1 byte).


void encodeFile(ofstream&,ifstream&) – reads data from source file one character at a time and then uses
code generated by hufftree_parser() converts it to one byte and writes it to destination file.


void decodeFile(ofstream&,ifstream&) – reads bytes from source and then uses the same tree to decode
the characters where 0 is go left and 1 is go right

# References
Geekforgeeks

Algorithms by Cormen, Lieserson, Rivet, Stien
