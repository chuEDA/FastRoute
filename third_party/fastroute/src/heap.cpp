////////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (c) 2018, Iowa State University All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software
// without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
// USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////////

/* Binary heap routines for use in Prim's algorithm, with points are numbered from 0 to n-1 */

#include <stdlib.h>
#include "heap.h"

namespace FastRoute {

Heap* _heap = (Heap*)NULL;
long _max_heap_size = 0;
long _heap_size = 0;

void allocate_heap(long n) {
        if (_max_heap_size < n) {
                _heap = (Heap*)realloc((void*)_heap, (size_t)(n + 1) * sizeof(Heap));
                if (!_heap) {
                        printf("Cannot reallocate memory in allocate_heap!\n");
                        exit(1);
                }
                _max_heap_size = n;
        }
}

void deallocate_heap() {
        _max_heap_size = 0;
        if (_heap) {
                free((void*)_heap);
                _heap = (Heap*)NULL;
        }
}

void heap_init(long n) {
        long p;

        allocate_heap(n);
        _heap_size = 0;
        for (p = 0; p < n; p++) {
                heap_idx(p) = 0;
        }

}

void heap_insert(
    long p,
    long key) {
        long k; /* hole in the heap     */
        long j; /* parent of the hole   */
        long q; /* heap_elt(j)          */

        heap_key(p) = key;

        if (_heap_size == 0) {
                _heap_size = 1;
                heap_elt(1) = p;
                heap_idx(p) = 1;
                return;
        }

        k = ++_heap_size;
        j = k >> 1; /* k/2 */

        while ((j > 0) && (heap_key(q = heap_elt(j)) > key)) {
                heap_elt(k) = q;
                heap_idx(q) = k;
                k = j;
                j = k >> 1; /* k/2 */
        }

        /* store p in the position of the hole */
        heap_elt(k) = p;
        heap_idx(p) = k;

} /* END heap_insert() */

/****************************************************************************/

void heap_decrease_key(
    long p,
    long new_key) {
        long k; /* hole in the heap     */
        long j; /* parent of the hole   */
        long q; /* heap_elt(j)          */

        heap_key(p) = new_key;
        k = heap_idx(p);
        j = k >> 1; /* k/2 */

        if ((j > 0) && (heap_key(q = heap_elt(j)) > new_key)) { /* change is needed */
                do {
                        heap_elt(k) = q;
                        heap_idx(q) = k;
                        k = j;
                        j = k >> 1; /* k/2 */

                } while ((j > 0) && (heap_key(q = heap_elt(j)) > new_key));

                /* store p in the position of the hole */
                heap_elt(k) = p;
                heap_idx(p) = k;
        }

} /* END heap_decrease_key() */

/****************************************************************************/

long heap_delete_min() {
        long min, last;
        long k;     /* hole in the heap     */
        long j;     /* child of the hole    */
        long l_key; /* key of last point    */

        if (_heap_size == 0) /* heap is empty */
                return (-1);

        min = heap_elt(1);
        last = heap_elt(_heap_size--);
        l_key = heap_key(last);

        k = 1;
        j = 2;
        while (j <= _heap_size) {
                if (heap_key(heap_elt(j)) > heap_key(heap_elt(j + 1)))
                        j++;

                if (heap_key(heap_elt(j)) >= l_key)
                        break; /* found a position to insert 'last' */

                /* else, sift hole down */
                heap_elt(k) = heap_elt(j); /* Note that j <= _heap_size */
                heap_idx(heap_elt(k)) = k;
                k = j;
                j = k << 1;
        }

        heap_elt(k) = last;
        heap_idx(last) = k;

        heap_idx(min) = -1; /* mark the point visited */
        return (min);

} /* END heap_delete_min() */

/****************************************************************************/
}  // namespace FastRoute
