Overview

This repository holds portfolio work from CS 300 — Data Structures and Algorithms: Analysis and Design, part of SNHU's Computer Science program.

The course project was building advising software for a fictional university (ABCU). The academic advisors needed a program that could do two things: print every course in the Computer Science department in alphanumeric order, and look up any single course to see its title and prerequisites.

The project had two phases. First, a design phase, where I wrote pseudocode for three different data structures — a vector, a hash table, and a binary search tree — and analyzed how each one would perform, in order to decide which one to actually build with. Second, an implementation phase, where I took that design and wrote a full working C++ program around it.

What's in this repo
portfolio-runtime-analysis.md — the design-phase analysis: run-time and memory comparison of the vector, hash table, and binary search tree, ending in a recommendation for which one to use.
CourseListSortAndPrint.cpp — a piece of the finished program: the code that sorts and prints the full course list in alphanumeric order.
Reflection

What was the problem you were solving in the projects for this course?

Building software an academic advisor could actually use to look up course information — specifically, printing a sorted list of every CS course and looking up any one course's title and prerequisites. The challenge wasn't really "can this be done," it was deciding how the course data should be stored and organized so both of those operations work well.

How did you approach the problem? Consider why data structures are important to understand.

Before writing any real code, I wrote pseudocode for three different ways of storing the data — a vector, a hash table, and a binary search tree — and compared how fast each one would be at loading the data and looking things up. That comparison is really the point of learning data structures: there's no single "best" one, it depends on what you're going to do with the data most often. Since advisors would be looking up individual courses more than printing the full list, I picked the hash table for its fast average lookup speed, even though that meant it wouldn't keep the courses in order automatically the way a tree would.

How did you overcome any roadblocks you encountered while going through the activities or project?

The trickiest part wasn't actually the code — it was getting my development environment set up correctly. I ran into a file that had silently saved with the wrong extension, an attempt to edit code in Microsoft Word that would have broken it (Word automatically converts straight quotes into "smart" curly quotes, which breaks quoted strings in code), and some confusion figuring out where a downloaded file had actually landed on my computer. Working through those slowly and checking things like file size and file type at each step got everything sorted out.

How has your work on this project expanded your approach to designing software and developing programs?

It made me design before I build. Comparing three working solutions to the same problem side by side, based on actual performance trade-offs, made my final choice something I could explain and justify — not just a guess. It also showed me that a data structure's weak point isn't automatically a dealbreaker; the hash table doesn't keep things sorted on its own, but that's a small problem to solve on top of it, not a reason to pick a different structure altogether.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

I got more disciplined about validating input instead of assuming it will be well-formed — bad lines in the data file get skipped with a clear message instead of crashing the program, and every prerequisite gets double-checked against the actual course list after loading. I also kept the data structure's internal details hidden behind a small, clear set of functions (load, search, get-all), so the rest of the program only ever talks to that interface. That means the underlying structure could be swapped out later without having to rewrite everything else around it.
