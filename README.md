# CS-300
Data Structures and Algorithms

What was the problem you were solving in the projects for this course?
  The main problem I was solving was designing a system that could efficiently store, retrieve, and display course information and prerequisites. The program needed to read from a course data file allow hte user to search and sort courses easily through a command-line interface.

How did you approach the problem? Consider why data structures are important to understand.
  I approached the problem by first planning out how to represent the data. I used a hash table (unordered_map) to store course objects because it allows for fast lookup times. I knew a hash table would provide constant-time access on average, making it ideal for a program that needed to respond quickly to user searches.

How did you overcome any roadblocks you encountered while going through the activities or project?
  I encountered a few roadblocks, such as input buffer issues when mixing cin >> and getline(). This made following user searches get an error.

How has your work on this project expanded your approach to designing software and developing programs?
  Working on this project taught me the importance of algorithms and how different ones are better suited for different tasks. For example, I learned that hash tables offer fast average-case lookup times, making them ideal for searching course data by course number. This project helped me see how choosing the right algorithm is just as important as picking the right data structure. And that the combination of both can drastically improve performance, scalability, and user experience in software development.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
  This project taught me how using the right algorithms makes a big difference in writing efficient and adaptable code. I realized that using built-in sorting functions with custom comparators can simplify code and make it easier to read and maintain instead of writing complex logic from scratch.
