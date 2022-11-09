/**
 * All of the following code is from Yi Yang's implementation of xChaCha20 encryption
 * algorithms.
 * From http://github.com/2042third/pdm-crypt-module
 * 
 * */
#define __STDC_FORMAT_MACROS 1
#include <inttypes.h>
#include <iostream>
using namespace std;
#include <memory>
#include <iostream>
#include <map>
#include <random>
#include <stdio.h>
#include <string.h>

#define POLY_SIZE 16

#define U32T8_S(p, v)    \
  {                            \
    (p)[0] = (v >> 0) & 0xff;  \
    (p)[1] = (v >> 8) & 0xff;  \
    (p)[2] = (v >> 16) & 0xff; \
    (p)[3] = (v >> 24) & 0xff; \
  }

#define U8T32_S(p)                              \
  (((uint32_t)((p)[0])) | ((uint32_t)((p)[1]) << 8) | \
   ((uint32_t)((p)[2]) << 16) | ((uint32_t)((p)[3]) << 24))

class crypto{

public:
  uint32_t cy[17];
  uint32_t folow[17];
  uint8_t  bk[65];
  uint64_t ctr = 0;

  uint32_t upper(uint64_t a){
    uint32_t b;
    a&= 0xffffffff00000000ull;
    b=a>>32;
    return b;
  }

  uint32_t lower(uint64_t a){
    uint32_t b;
    a&= 0x00000000ffffffffull;
    a=a<<32;
    b=a>>32;
    return (uint32_t)b;
  }

  uint64_t cast(uint32_t u, uint32_t l){
    uint64_t c = 0;
    uint64_t d = u;
    d = d<<32;
    // d = d>>32; // Shift clean up
    // d = d<<32;
    c += d;
    c += l;
    return c;
  }

  void endicha(uint8_t * a, uint32_t * b) {
    for (unsigned int i = 0; i < POLY_SIZE; i++) {
      U32T8_S(a + 4 * i, b[i]);
    }
  }

  void expan(uint32_t * ot, unsigned int off, const uint8_t* in, unsigned int n) {
    for(unsigned int i=0;i<n;i++){
      ot[off+i] = U8T32_S(in+4*i);
    }
  }

  // Addition operation
  template<typename NU>
  void set_conc(NU* s1,NU* s2,unsigned int n){
    for(unsigned int i=0;i<n;i++)s1[i]+=s2[i];
  }

  void init_byte_rand_cc20 (uint8_t* a, int n){
    for (int i=0;i<n;i++) {
      std::random_device rd;   // non-deterministic generator
      std::mt19937 gen(rd());
      a[i]=gen();
    }
  }

  void one_block( uint64_t xcount) {
    cy[12] = upper(xcount);
    cy[13] = lower(xcount);
    memcpy(folow, cy, sizeof(uint32_t) * 16);
    // for (unsigned int i = 0; i < 10; i++) tworounds(folow); // 20 rounds
    for (unsigned int i = 0; i < 1; i++) tworounds(folow); // 2 rounds
    set_conc(cy, folow, 16);
    endicha(bk, cy);
  }

  static inline uint32_t rotl32(uint32_t x, int n)
  {
    // http://blog.regehr.org/archives/1063
    return x << n | (x >> (-n & 31));
  }

  // Operate a quarter-round chacha state on total of 16 bytes or 4 32-bit numbers at a time.
  void quarteround(uint32_t * x, uint32_t a, uint32_t b, uint32_t c, uint32_t d){

    x[a] += x[b];
    x[d] = rotl32(x[d] ^ x[a], 16);
    x[c] += x[d];
    x[b] = rotl32(x[b] ^ x[c], 12);
    x[a] += x[b];
    x[d] = rotl32(x[d] ^ x[a], 8);
    x[c] += x[d];
    x[b] = rotl32(x[b] ^ x[c], 7);
  }

  void tworounds(uint32_t * state){
    quarteround(state, 0, 4, 8, 12) ;
    quarteround(state, 1, 5, 9, 13) ;
    quarteround(state, 2, 6, 10, 14);
    quarteround(state, 3, 7, 11, 15);
    quarteround(state, 0, 5, 10, 15);
    quarteround(state, 1, 6, 11, 12);
    quarteround(state, 2, 7, 8, 13) ;
    quarteround(state, 3, 4, 9, 14) ;
  }
  /**
   * Assume block, bk[], has 64 bytes of random data.
   * Initializes the cypher block, cy[], using the block.
   * All operations are based on Yi Yang's implementation of
   * xchacha20 stream cypher.
   *
   * */
  void init () {
    this -> cy[0] = 0xbcd45678;
    this -> cy[1] = 0x9a123e0f;
    this -> cy[2] = 0xbc3e0678;
    this -> cy[3] = 0x9cd4a12f;

    expan(this -> cy, 14, bk+46, 2); // XCHACHA20 difference
    expan(this -> cy, 12, bk, 4);
    expan(this -> cy, 4 , bk+16, 8);
    ctr++;
    one_block(ctr);
  }

  crypto(){
    init_byte_rand_cc20(bk,64);
    init();
  }

  double next () {
    ctr++;
    if(ctr%16 == 0)
      one_block(ctr);
    return (double)((double)cy[ctr%16]/(double)UINT32_MAX);
  }

}; // crypto