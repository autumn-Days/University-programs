# List of exercises

## 5° exercise

Write a load test code for both types of TCP servers:

-  **Multithreaded**: Handles multiple concurrent clients.  
 -  **Single-threaded**: Handles one client at a time. The connection opening (`accept()`) is in the same thread that processes the request (the main thread).  

The test code should generate **100 simultaneous clients** (threads). Each client will make a single request to the server and then terminate. Perform one round for the multithreaded server and another for the single-threaded server. Compare the execution times.

Do not require user interaction on the client (e.g., keyboard input). All requests can be predefined in the code itself, for example: `"ADD;10;11"`.  

Since the calculator does not provide enough load for a thread to lose the CPU before completing its execution, add a pause in the code. In Java, for example: `Thread.sleep(100)` (the thread will suspend for 100 milliseconds). This ensures that the single-threaded server will take at least **100 x 100 milliseconds** to handle all 100 requests.

### Tips:
1. Avoid sending output messages to the console as it may become a bottleneck for concurrent threads (e.g., avoid `println()`, `print()`, `System.out.println()`).
2. The end time should only be recorded when **all threads have completed**. Use `join()` to synchronize the main thread of the load test with the other threads making requests, e.g., `threads[i].join();`.