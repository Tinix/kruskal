#ifndef UNION_FIND
#define UNION_FIND

#include <stdbool.h>


typedef struct _union_find_t *union_find_t;
typedef unsigned int uint;

/* Union-Find: A set of disjoint sets.
 * Each set has an special element called the
 * 'representative' of the set. 
 * We write '[x]' when x is a representative.
 * All the functions assume the parameter 'uf' is not NULL, and the parameters
 * 'elem', 'elem1' and 'elem2' are in the correct range.
 */

union_find_t union_find_create(uint max_size);
/* Returns a newly created uf.
 * The result is a set of 'max_size' singletons:
 * {{0}, ..., {'max_size' - 1}}
 * The element of each singleton is its own representative.
 */

uint union_find_find(union_find_t uf, uint elem);
/* Returns the representative of the set that includes the element 'elem'.
 * Example: 
 * Suppose uf = {{0,[1],2}, {3,[4]}}. Then,
 * find(uf, 0) = 1
 * find(uf, 1) = 1
 * find(uf, 2) = 1
 * find(uf, 3) = 4
 * find(uf, 4) = 4
 */

void union_find_union(union_find_t uf, uint elem1, uint elem2);
/* Modifies the uf by joining the sets represented by 'elem1' and 'elem2' 
 * into a single set.
 * Both 'elem1' and 'elem2' must be representatives.
 * Example:
 * uf = {{0,[1],2}, {[3]}, {4,[5]}}
 * union(uf, 1, 5) = {{0,[1],2,4,5}, {[3]}}
 * Implementation note:
 * The new representative is [1] and not [5], since [1] represents 
 * more elements. 
 */

bool union_find_connected(union_find_t uf, uint elem1, uint elem2);
/* Returns true if 'elem1' and 'elem2' are in the same set, and false otherwise.
 * Example:
 * uf = {{0,[1],2}, {3}}
 * connected(0,2) = true
 * connected(0,3) = false
 */

uint union_find_count(union_find_t uf);
/* Returns how many sets are inside uf.
 * Example:
 * uf = {{0,[1]}, {[2]}, {3,[4]}}
 * count(uf) = 3
 */

union_find_t union_find_destroy(union_find_t uf);
/* Destroys the uf to free the memory resources */

#endif
