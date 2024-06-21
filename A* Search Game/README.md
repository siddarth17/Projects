
This project features a custom MinHeap implementation utilized in solving Doublet (or Word Ladder) game. 
In this game, players start with two command-line input words of the same length. The challenge is to convert the 
first word into the second by altering one letter at a time, each change resulting in a valid word, and using the 
minimum number of steps possible. The third command-line argument is a dictionary file containing valid words that 
can be used for transformations.

Below is an example of how the file can be structured: 
6
leet
leek
lead
leap
leak
lean

Example output: 

Command: ./doublet clip clop dictionary.txt

**Output Description:**
The program outputs the shortest path from the starting word to the target word, detailing each intermediate word 
in the sequence. It also reports the number of steps in the quickest solution and the total number of configurations 
tried during the solution process.

**Output Example:**
Path: CLOP CLOD COLD COLE COPE COPI CLIP
Steps for Fastest Path: 7
Total Steps Tried: 7

This output indicates that the program transformed "clip" to "clop" in 7 steps, exploring a total of 7 different 
configurations to achieve this result, thereby finding the most efficient sequence possible.
