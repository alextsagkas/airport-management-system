# Functionality

In the `airport_management.c` program the actions shown in the following numbered list are performed:

1. Create an index.

2. Import airports into the index from the `airports.txt` file. Also logs are stored about the following
   quantities and they are printed in the `output.txt` file:

   - Timing 2^N − 1 entries, where N = 9, 10, 11, 12.
   - Timing of the total amount of entries.
   - Total number of items inserted.

3. Update departures and arrivals from and to each airport from the data of the `routes.txt` file.
   When a route starts from one airport and has a destination for another, then the departures for
   the first and the arrivals for the second increment by one. Furthermore, logs are stored in the
   `output.txt` file about the following quantities:

   - The total number of airports that where search for all the routes stored in `routes.txt` file.
   - The total number of airports that where not found in the index.
   - The total time needed to process all the routes.
   - The average search time for each airport.

4. The airports are sorted in ascending order and printed in the `output.txt` file. In addition, the number
   of arrivals and departures corresponding to them are printed. The time it took to complete the print
   is also printed.

5. Delete index.

The above five actions are performed twice, once for random airport data and once for the sorted ones. In the
first case, the name of the airport data file is `airports_random.txt` and the output file `output_random_bst.txt`,
while in the second case it is `airport_sorted.txt` and `output_random_bst.txt`, respectively.
