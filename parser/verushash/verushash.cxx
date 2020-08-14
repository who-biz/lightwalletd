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


void * Verushash::verushash(const char * bytes, size_t length) {
    char *result = new char[32];
    
    if (initialized == false) {
        initialize();
    }
    verus_hash(result, bytes, length);
    return result;
}

void * Verushash::verushash_v2(const unsigned char * bytes, size_t length) {
    CVerusHashV2 vh2(SOLUTION_VERUSHHASH_V2);
    unsigned char *result = new unsigned char[32];
    
    if (initialized == false) {
        initialize();
    }

    vh2.Reset();
    vh2.Write(bytes, length);
    vh2.Finalize(result);
    return result;
}

void * Verushash::verushash_v2b(const unsigned char * bytes, size_t length) {
    CVerusHashV2 vh2(SOLUTION_VERUSHHASH_V2);
    unsigned char *result = new unsigned char[32];
    
    if (initialized == false) {
        initialize();
    }

    vh2.Reset();
    vh2.Write(bytes, length);
    vh2.Finalize2b(result);
    return result;
}

void * Verushash::verushash_v2b1(const unsigned char * bytes, size_t length) {
    CVerusHashV2 vh2b1(SOLUTION_VERUSHHASH_V2_1);
    unsigned char *result = new unsigned char[32];
    
    if (initialized == false) {
        initialize();
    }

    vh2b1.Reset();
    vh2b1.Write(bytes, length);
    vh2b1.Finalize2b(result);
    return result;
}

void * Verushash::verushash_v2b2(const std::string bytes)
{
    uint256 result;
    uint256 *results = new uint256[1];

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

    results[0] = result;
    return results;
}
