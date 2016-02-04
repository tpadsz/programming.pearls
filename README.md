# **Programming Pearls**


## Column 1: **Cracking the Oyster**
### **Precise Problem Statement**
*Input:*    A file containing at most *n* positive integers, each less than *n*, where n = 10<sup>7</sup>. It is a fatal error if any integer occurs twice in the input. No other data is associated with the integer.

*Output:*   A sorted list in increasing order of the input integers.

*Constraints:*  At most (roughly) a megabyte of storage is available in main memory; ample disk storage is available. The run time can be at most several minutes; a run time of ten seconds need not be decreased.

### **Implementation Sketch**
  Viewed in this light, the *bitmap* or *bit vector* representation of a set screams out to be used. We can represent a toy set of nonnegative integers less than 20 by a string of 20 bits. For instance, we can store the set {1, 2, 3, 5, 8, 13} in this string:
    0 1 1 1 0 1 0 0 1 0 0 0 0 1 0 0 0 0 0 0
  The bits representing numbers in the set are 1, and all other bits are 0.
  In the real problem, the seven decimal digits of each integer denote a number less than ten million. We'll represent the file by a string of ten million bits in which the *i<sup>th</sup>* bit is on if and only if the integer *i* is in the file.(The programmer found two million spare bits; Problem 5 investigates what happens when a megabyte is a firm limit.) This representation uses three attributes of this problem not usually found in sorting problems: the input is from a relatively small range, it contains no duplicates, and no data is associated with each record beyond the single integer.

### **TPAD's Practice**
  As we focus on the bitmap section, I ignore the merge sort stuffs and implement only the `bitmap` algorithm along with its corresponding `input file`. So the core function of ch01.c is this:

```c
/**
*   parameters:
*   void* bitmap, the bitmap buffer which contains all the numbers as individual bits.
*   int bitmapSize, the size of the bitmap.
*   int number, the number to mark. If the number is larger the buffer can hold, returns ERR_OUT_OF_BUFFER.
*   return: <0 if an error occurs. >=0 if the bit is set.
*/
int markNumber(U8b* bitmap, int bitmapSize, int number);
```

  Note that I changed the rule defined in `Precise Problem Statement` as the first step to deal with duplicate numbers which may require a little trick.

  Also note that I allocate 1MB memory and produce exactly the same quantity of numbers (i.d. `#define NUMBERS (1*1024*1024*8)` in ch01.h). Thus the output looks like this: `Number <integer>: 255` because all bits are set.



