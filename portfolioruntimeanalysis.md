# Project One: ABCU Advising Program — Run-Time and Memory Analysis

*Donald Champagne | CS 300*

This analysis covers `loadCourses` — reading the file, building the course objects, inserting them, and validating that every prerequisite listed actually exists as its own course — since that's the operation the assignment asks about, not the menu or print functions. *n* is the number of courses, and I'm assuming a roughly constant number of prerequisites per course.

## Run-Time Analysis

| Structure | Read + Parse | Insert (n times) | Validate Prereqs (n times) | Total |
|---|---|---|---|---|
| Vector | O(n) | O(1) each → O(n) | O(n) each → O(n²) | **O(n²)** |
| Hash Table | O(n) | O(1) avg each → O(n) | O(1) avg each → O(n) | **O(n) avg** |
| Tree | O(n) | O(log n) avg each → O(n log n) | O(log n) avg each → O(n log n) | **O(n log n) avg** |

For the vector, there's no fast way to look anything up, so validating each prerequisite means scanning the whole thing, which is what pushes it to O(n²) overall. The hash table's O(1) average insert and search keeps both loading and validation linear, so it comes out to O(n) overall. The tree's O(log n) average insert and search gets it to O(n log n) overall, but since the course numbers are already close to sorted order coming out of the file, the tree can end up unbalanced, which would push it toward O(n) per operation and O(n²) overall in the worst case.

## Memory (Space) Analysis

Run-time isn't the whole picture, so it's worth looking at how much memory each structure actually uses to hold *n* courses:

- **Vector**: the most memory-efficient of the three. It's a single contiguous block holding exactly the `Course` objects themselves, with no per-element pointer overhead. The only inefficiency is that a vector occasionally over-allocates when it grows (doubling its capacity), so it can briefly hold a bit more memory than it strictly needs — but that's a small, temporary cost. Total space is O(n).
- **Hash Table**: needs a fixed-size bucket array allocated up front — 179 buckets in this implementation — regardless of how many courses actually get loaded. For a course catalog with a few dozen entries, that means a chunk of allocated-but-empty buckets, which is minor waste but real. On top of that, every course also carries a "next" pointer for chaining, even when no collision ever occurs at that bucket. Total space is O(tableSize + n).
- **Tree (BST)**: has no fixed pre-allocated structure like the hash table's bucket array — it only ever allocates exactly one node per course, so there's no "empty slot" waste. However, each node needs two pointers (left and right) instead of the hash table's one, so its per-course overhead is a bit higher than the hash table's per-node cost. Total space is O(n).

None of these differences are large in absolute terms at this catalog's size (a few dozen CS/Math courses), but the pattern holds at scale: the vector is the leanest, the tree adds one extra pointer's worth of overhead per course, and the hash table trades a bit of pre-allocated bucket-array space for its speed advantage.

## Advantages and Disadvantages

**Vector**: simple to set up and it keeps courses in the order they were inserted. The downside is there's no fast lookup at all, so every search and every prerequisite check is O(n), which makes it the slowest option overall, and it also needs to be sorted separately before printing the list.

**Hash Table**: O(1) average insert and search, which makes it the fastest option for looking up an individual course, and that's what advisors will be doing most often. The downside is it has no natural order, so the full course list has to be pulled out and sorted separately, and its performance depends on having a decent table size and hash function.

**Binary Search Tree**: naturally stays sorted, so printing the full list is just a traversal with no separate sort needed, and it has O(log n) average insert and search. The downside is it isn't self-balancing, so if course numbers come in close to sorted order, which they do here, it can degrade toward O(n) per operation.

## Recommendation

I'd go with the hash table. Advisors are going to be looking up individual courses most often, and the hash table's O(1) average search handles that the fastest, while still keeping the initial load and prerequisite validation at O(n) overall, which is the best combined result out of the three. Printing the sorted list does need one extra O(n log n) sort, but that only happens when option 2 is picked, and it's still cheaper than what the vector costs just to validate prerequisites. The tree is a reasonable second choice since it stays sorted on its own, but its O(log n) average performance isn't guaranteed here — this data set's course numbers come in close to sorted order already, which is exactly the situation that unbalances a plain binary search tree toward O(n) per operation. Memory-wise, none of the three is meaningfully worse than the others at this catalog's size, so run-time — specifically, optimizing for the lookup operation advisors will perform most often — was the deciding factor. The hash table is just the more dependable option for what advisors will actually be doing with this program.
