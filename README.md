rescue-asset-allocator
======================

A small program written in C used to allocate rescue assets to a ship in peril.

The program works in the following manner:

1. Read three separate files specified by the user: one that contains details of a mayday call; one containing details of rescue assets in the area and one containing information about ships in the area.

2. Store the informaion in linked-list data structures.

3. Carry out calculations on the stored data to calculate which rescue assets can get to the ship in peril the quickest.

4. Print the result out to the command line and write it to a log file.
