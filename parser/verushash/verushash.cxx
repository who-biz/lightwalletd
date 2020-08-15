/* File : verushash.cxx */

#include "verushash.h"

#include <stdint.h>
#include <vector>

#include "include/verus_hash.h"
#include "solutiondata.h"

#include <sstream>

bool initialized = false;


void Verushash::initialize() {
    if (!initialized)
    {
        CVerusHash::init();
        CVerusHashV2::init();
        sodium_init();
    }
    initialized = true;
}


void Verushash::verushash(const char * bytes, int length, char * ptrResult) {
    char *result = new char[32];
    
    if (initialized == false) {
        initialize();
    }
    verus_hash(result, bytes, length);
    memcpy(ptrResult, result, 32);
}

void Verushash::verushash_v2(const unsigned char * bytes, int length, char * ptrResult) {
    CVerusHashV2 vh2(SOLUTION_VERUSHHASH_V2);
    unsigned char *result = new unsigned char[32];
    
    if (initialized == false) {
        initialize();
    }

    vh2.Reset();
    vh2.Write(bytes, length);
    vh2.Finalize(result);
    memcpy(ptrResult, result, 32);
}

void Verushash::verushash_v2b(const unsigned char * bytes, int length, char * ptrResult) {
    CVerusHashV2 vh2(SOLUTION_VERUSHHASH_V2);
    unsigned char *result = new unsigned char[32];
    
    if (initialized == false) {
        initialize();
    }

    vh2.Reset();
    vh2.Write(bytes, length);
    vh2.Finalize2b(result);
    memcpy(ptrResult, result, 32);
}

void Verushash::verushash_v2b1(std::string const bytes, int length, char * ptrResult) {
    CVerusHashV2 vh2b1(SOLUTION_VERUSHHASH_V2_1);
    unsigned char *result = new unsigned char[32];
    
    if (initialized == false) {
        initialize();
    }

    vh2b1.Reset();
    vh2b1.Write((unsigned char *) &bytes[0], length);
    vh2b1.Finalize2b(result);
    memcpy(ptrResult, result, 32);
}

void Verushash::verushash_v2b2(const std::string bytes, char * ptrResult)
{
    uint256 result;


    if (initialized == false) {
        initialize();
    }

    CBlockHeader bh;
    CDataStream s(bytes.data(), bytes.data() + bytes.size(), SER_GETHASH, 0);

    try
    {
        s >> bh;
        result = bh.GetVerusV2Hash();
    }
    catch(const std::exception& e)
    {
    }

    memcpy(ptrResult, &result, 32);
}
