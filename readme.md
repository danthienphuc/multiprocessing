# Multi-processing exercise

* Implement a program with 2 processes, socket connection, shared memory:

## Process 1 (Parent process)

* SetupRead data from import files (around 5 files)
* Import files with below structure, this is an email content need to be collected.

```m
From: sender 1
To: receiver 1
Content: Content of email. Write some thing here
```

* Send Monitor message (`is_alive`) to process 2 via socket (time out 1 second), this is a message check if process 2 still alive. Then wait for process 2 response alive message (`alive`).
* If process 2 still alive, save email data to shared memory.
* If process 2 is not alive, fork new process 2
* After process all files, send socket to Process 2 (`shutdown`), check alive of process 2, if not alive, shutdown process 1 also.

## Process 2 (Child process)

* After started, wait for (`is_alive`) message and keep processing shared memory in case of data exist.
* After receive (`is_alive`) message, response (`alive`) immediately.
* In case of shared memory having data, read it and log content to summary file (email_archive.csv) with below structure.
  `sender 1;receiver 1;Content of email. Write some thing here`
* If receive `shutdown` socket message, end process 2

## Sequence of program

1. Process 1 read one file
2. Process 1 check alive of Process 2
3. Process 2 response to Process 1
4. If process 2 is not alive, start again
5. If process 2 is alive, send data to shared memory
6. Process 2 detects shared memory is having data, read and process it
7. Process 2 Read `email_archive.csv`: if not exist->create one, if first line is not `From;To;Content`-> add into
8. Process 2 process data from shared memory: convert to structure as the example here `sender 1;receiver 1;Content of email. Write some thing here` and append it to `email_archive.csv`
9. Process 1 reads all files, sends a shutdown message to Process 2, and terminates the program.

## Require points

* Do not use multi-threading
* First line of email_archive.csv is: `From;To;Content`

## Coding convention 

* Do not write function over 80 lines 
* Do not keep line with over 80 characters. 
* Indent: 4 spaces 
* Variable name: camel case, ex: cencorName, inputValueName 
* Function name: use verd for processing function. Ex: calculateDataValue (ok) dataValueConculation (NG), Sum (OK) 
* Constant: UPPER CASE, ex: #define MAX_THREADS 10 
* Class name: camel case with upper the first character. Ex: CencorManager 
* Meaning variable name: int a, b = 0 (NG). 

 