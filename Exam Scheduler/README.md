Functionality:
This application efficiently organizes exam schedules for multiple students by ensuring that no student 
has overlapping exam times. It uses custom-implemented data structures like Binary Search Trees and AVL Trees 
to manage and optimize class assignments across available time slots.

I wrote the code and implemented my own version of binary and avl trees to track the classes in the scheduler. 

Description:
The program accepts an input file specified at the command line, detailing the number of classes, students, 
and available exam time slots. Following this, the file lists each student's name and the class numbers 
they are enrolled in. The software processes this information to produce an optimal exam schedule, 
distributing the classes across the provided time slots in such a way that no student has concurrent exams.
If it's not feasible to schedule the exams within the given slots without conflicts, the program outputs 
"No Valid Exam Schedule."

Example Input:
Command: ./examScheduler schedule.txt
Contents of schedule.txt:
8 5 4
Alice 201 301 401
Bob 301 501 601
Charlie 201 501
Diana 401 501 701 801
Evan 301 601 701

Example Output:
Section 1: 201, 601
Section 2: 301, 801
Section 3: 401, 701
Section 4: 501

Output Explanation:
The output shows that the classes have been assigned to four sections (or time slots) such that no student 
is scheduled to take more than one exam at the same time. The classes are grouped and allocated in a way 
that utilizes the available slots efficiently while adhering to the constraint of no overlapping exams for any student.






