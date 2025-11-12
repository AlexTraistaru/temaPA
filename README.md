The implementation demonstrates the use of data structures such as linked lists, queues, stacks, binary search trees (BST), and AVL trees.

# Features

Reads team and player data from an input file (.in) and writes results to an output file (.out).

Uses a linked list to store team information.

Eliminates the weakest team in each round based on total score.

Organizes matches using queues and separates winners and losers into stacks.

Inserts the top 8 teams into a BST, balancing it into an AVL tree.

Displays elements from a specific level of the AVL tree.

# Data Structures Used

Linked List – for team management and elimination logic.

Queue – for organizing tournament matches.

Stack – for managing winners and losers between rounds.

Binary Search Tree (BST) – for storing the final eight teams.

AVL Tree – for balancing and structured output of top teams.

# Technologies

Language: C

Concepts: Dynamic memory allocation, pointers, linked lists, trees, queues, stacks, recursion.

# Task Breakdown 
## Task 1

I started by reading team data from the input file — team names, player names, and their scores.
Then I created a linked list by adding data at the beginning and displayed the team names in the output file.

## Task 2

I determined the lowest score and removed the corresponding team in each step.
If two teams had the same score, the first one found was eliminated.

## Task 3

I created a queue containing the matches between teams, written to the output file.
Then I used two stacks — one for winners and one for losers. The losers’ stack was cleared, and the winners’ stack was reinserted into the queue for the next round.
When only 8 teams remained, I placed them into a stack.

## Task 4

Using the list of the final 8 teams, I built a Binary Search Tree (BST).
When inserting nodes, I handled the case where two teams had equal scores by sorting them alphabetically.

## Task 5

I transformed the BST into an AVL Tree through balancing operations.
Finally, I printed the elements from level 2 of the tree.
