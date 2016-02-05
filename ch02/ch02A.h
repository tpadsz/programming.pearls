#ifndef CH02A_H_INCLUDED
#define CH02A_H_INCLUDED

// As defined in the problem, we will search 4 billion
// numbers for at least one missing. 0xEE6B2800 literally
// is the hex representation for 4 billion.
#define NUMBERS 0xEE6B2800
#define HIHEST_U32b_BIT 0x80000000
#define CH02A_4B_FILE_NAME "numbers.txt"

#if __WIN32__
#define stat64 _stat64
#endif

#endif // CH02A_H_INCLUDED
