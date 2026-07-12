#include <stddef.h>
#include "kernel.h"
#include "malloc.h"


typedef struct header {
    struct header *next;
    unsigned int size;
} __attribute__((aligned(4))) Header;


static unsigned char heaps[MAX_HEAPS];
static unsigned char *curr_pb = heaps;           // Program break

static Header base;             // empty list to get started
static Header *freep = NULL;    // start of free list (memory pool)


// On success, returns the previous program break.
// On error, (void *) -1 is returned and 'errno' is set to
// ENOMEM
void *sbrk(unsigned int nbytes)
{
    if ((curr_pb + nbytes >= heaps) && (curr_pb + nbytes < heaps + MAX_HEAPS)) {
        // The program break still in the range of heap
        unsigned char *prev_pb = curr_pb;
        curr_pb += nbytes;
        return (void *) prev_pb;
    }
    return (void *) -1;
}

/**
 * lower memory ─────────────────────────────────────────────────────────────► higher memory
 * ┌──────────────────────┐────────────────────────────────────────┐
 * │      Header (s)      │                                        │
 * ├──────────┬───────────┤        User can read/write             │
 * │  *next   │   size    │            (Payload segment)           │
 * └────┼─────┴───────────┴────────────────────────────────────────┘
 *      │
 *      └─► point to next Header
 */


// On success, malloc return a pointer to the allocated memory.
// On error, these functions return NULL and set 'errno'.
void *malloc(unsigned int nbytes)
{
    Header *p, *prevp;
    unsigned int nunits;
    void *cp;

    // Calculate the number of 'header block' required
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {
        // First time call malloc
        base.next = freep = prevp = &base;
        base.size = 0;
    }

    for (p = prevp->next; ; prevp = p, p = p->next) {
        if (p->size >= nunits) {
            // scan the cirtular linked list
            if (p->size == nunits) {
                // if the size if equal, use it
                prevp->next = p->next;
            } else {
                // if the size is larger than required, split and keep
                // the remain part in free list
                p->size -= nunits;
                p += p->size;
                p->size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }

		if (p == freep) {
			cp = sbrk(nunits * sizeof(Header));
			if (cp == (void *) -1) {
				return NULL;
			} else {
				p = (Header *) cp;
				p->size = nunits;
				free((void *) (p + 1));
				p = freep;
			}
		}
    }
}

void free(void *ap)
{
    Header *bp, *p;

    // When user invoke 'free', the 'ap' point to the Payload
    // segment, minus 1 to get the 'Header' address
    bp = (Header *) ap - 1;
    
    // Find the right position of 'bp' header in the free list
    for (p = freep; !(bp > p && bp < p->next); p = p->next) {
        if (p >= p->next && (bp > p || bp < p->next))
            break;
    }

    // Merge right side block
	if (bp + bp->size == p->next) {
		bp->size += p->next->size;
		bp->next = p->next->next;
	} else {
		bp->next = p->next;
	}

    // Merge left side block
	if (p + p->size == bp) {
		p->size += bp->size;
		p->next = bp->next;
	} else {
		p->next = bp;
	}

	freep = p;
}
