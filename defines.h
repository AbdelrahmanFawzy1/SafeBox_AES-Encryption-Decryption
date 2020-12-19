#ifndef DEFINES_H
#define DEFINES_H
//#include"includes.h"
//#include"AVLTree.hpp"
typedef unsigned __int128 uint128_t;
#include<iostream>
#include<string>
#define COMMAND_LINE_ARGUMENT_MAX_SIZE 128
#define ERROR_STRING_MAX_SIZE 128



/*      UINT64_MAX 18446744073709551615ULL */
#define P10_UINT64 10000000000000000000ULL   /* 19 zeroes */
#define E10_UINT64 19

#define STRINGIZER(x)   # x
#define TO_STRING(x)    STRINGIZER(x)

#define PHASE1     1
#define PHASE2     2

namespace CryptoPP{
    typedef unsigned char byte;
};

typedef struct AVL_Node {
  public: 
        std::string filename;
        long blocksize;
        long size_in_blocks;
        long size_in_bytes;
        long shreds;
        std::string hidden_name;
        bool flag ;

       
        friend std::ostream & operator << (std::ostream & os, AVL_Node* n) {
            os << n->filename << "," << n->blocksize << ","<<n->size_in_blocks << ","<< n->size_in_bytes << "," << n->shreds << "," << n->hidden_name << std::endl; 
            
            return os;
        }
        bool operator == (AVL_Node str){
             if (filename == str.filename) return true;
             else return false;
        }
        bool operator > (AVL_Node str){
             if (filename > str.filename) return true;
             else return false;
        }
        bool operator < (AVL_Node str){
             if (filename < str.filename) return true;
             else return false;
        }
        bool operator != (AVL_Node str){
             if (filename != str.filename) return true;
             else return false;
        }


}AVL_Node_index_t;

typedef struct sb_block_index{ 
    long block;
    long shred_block;
    char shred;
} sb_block_index_t;



#endif
