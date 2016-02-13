#include<math.h>
#include "bloom.h"

// Multiplication method 1
index_t hash1(bloom_filter_t *B, key_t k)
{
  const long double A = 0.333*(sqrt(47) -1);
  const long m = pow(2,50);
  long double s;
  index_t h1;

  s = k*k*A;
  s = s - floor(s);

  return ((index_t) floor(m*s) % B->size);
}

// Multiplication method 2
index_t hash2(bloom_filter_t *B, key_t k)
{
  const long double A = 0.5*(sqrt(5) -1);
  const long m = pow(2,30);
  long double s;
  index_t h1;

  s = k*A;
  s = s - floor(s);

  return ((index_t) floor(m*s) % B->size);
}

// Identity
index_t hash3(bloom_filter_t *B, key_t k)
{

  return ((index_t) k*2654435761 % B->size);
}

void printHash(int num,index_t hashValue)
{
  printf("The hash of %d is %llu\n",num,hashValue);
  return ;
}

void testHash()
{
  bloom_filter_t *B;
  int arrTest[6] = {0,1,2,3,13,97};
  int i;

  B->size = 100;

  for(i=0;i<6;i++)
  {
    printHash(arrTest[i],hash1(B,arrTest[i]));
    printHash(arrTest[i],hash2(B,arrTest[i]));
  }
}

void testShift()
{
  uint64_t x = 1;
  int i;

  for(i = 0;i<65;i++)
  {
    printf("%llu\n", x);
    x <<= 1;
  }
  return;
}

void set_bit(bloom_filter_t *B, index_t i)
{
  int j = i / 64, k = i % 64; // get the positions
  index_t word_k; // get the word in the table
  word_k = 1 << k;

  B->table[j] = B->table[j] | word_k;

  return;
}

int get_bit(bloom_filter_t *B, index_t i)
{
  int j = i / 64, k = i % 64; // get the positions
  index_t word = B->table[j], word_k; // get the word in the table
  word_k = 1 << k;

  return (int)((word & word_k) >> k);
}

bloom_filter_t* bloom_init(index_t size_in_bits)
{
  int j = size_in_bits/64,i;
  bloom_filter_t* B = (bloom_filter_t*) malloc(sizeof(bloom_filter_t));

  B->size = size_in_bits;
  B->count = 0;

  B->table = (index_t *) malloc(j * sizeof(index_t));
  for(i=0;i<j;i++)
  {
    B->table[i] = 0;
  }

  return B;
}

void bloom_destroy(bloom_filter_t *B)
{
  free(B->table);
  free(B);
  return;
}

int bloom_check(bloom_filter_t *B, key_t k)
{
  int i,tr = 1;
  index_t hashVal;

  for(i=0;i<N_HASHES;i++)
  {
    hashVal = (hash1(B,k) + i*hash2(B,k)) % B->size;
    tr &= get_bit(B,hashVal);
  }

  return tr;

}
void bloom_add(bloom_filter_t *B, key_t k)
{
  int i;
  index_t hashVal;

  // update the table
  for(i=0;i<N_HASHES;i++)
  {
    //printf("Calling set bit with key= %llu, hash1=%llu, hash2=%llu\n",k,hash1(B,k),hash2(B,k));
    hashVal = (hash1(B,k) + i*hash2(B,k)) % B->size;
    set_bit(B,hashVal);
  }

  // update the count
  B->count++;
  return;

}

int main(int argc, char const *argv[]) {

  int i,total=0;
  //testHash();
  //testShift();

  //initialize the filter
  bloom_filter_t *B = bloom_init(1000);

  // add some numbers to the filter
  for(i=0;i<70;i++)
  {
    bloom_add(B,i);
  }

  // check how many bits are set
  for(i=0;i<B->size;i++)
  {
    total += get_bit(B,i);
  }
  printf("Total number of bits set %d\n",total );

  bloom_destroy(B);

  return 0;
}
