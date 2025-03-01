Makefile doesnt seem to work correctly due to that same annoying tab error. :(

Questions:
1.
Phase 1 was modifed to provide a left skewed vine rather than a right skewed vine. This does not affect time complexity,
but this does affect the shape of the final tree. Some implementations may require this to be the case as this algorithm seems
quite felxible for it's use cases.

2.
Phase 2 implementation is not exact balance, but rather an apporximated balance of the tree. If only I could
get mine to work, I would have more to say about this.

3.
One tradeoff I notices was when we need to check the size of the subtree to make sure that a specific
rotation can occur, I had to create a recursive helper function for this so the code would not be so long
after making so many subtree checks.

4.
There might be a quicker way to fix these implementations by making hybrid trees. One thing I thought of
was the use of RB trees and the color encoding to make sorting the tree easeir than having to make a vine
and completely restructure the tree.