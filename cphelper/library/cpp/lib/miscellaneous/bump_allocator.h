#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Bump Allocator
 * Description:
 *    Dynamically allocate many objects without freeing them. "new X" otherwise
 *    has an overhead.
 * Time Complexity: N/A
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/cses/1737/pseg.cpp
 */

static char buf[450 << 20];
void* operator new(size_t s) {
    static size_t i = sizeof buf;
    assert(s < i);
    return (void*) & buf[i -= s];
}
void operator delete(void*) noexcept {}
void operator delete(void*, size_t) noexcept {}
