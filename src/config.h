#include <cstdlib>
#include <iostream>

typedef long t_size;

typedef unsigned long ULONG;
typedef unsigned long t_bint;

const t_size BLOCK_SIZE = 8 * sizeof(t_bint); //64;
const t_size NUMBER_CAPACITY = (long)1 << 10; //384
const t_size BLOCKS_NUMBER = NUMBER_CAPACITY / BLOCK_SIZE;
const t_size ULONG_SIZE = sizeof(ULONG);

const t_bint BLOCK_MAX_VALUE = 0xFFFFFFFFFFFFFFFF;
const t_bint BLOCK_MAX_BIT = (long)1 << (BLOCK_SIZE - 1);

using namespace std;