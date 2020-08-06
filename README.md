# Library project

## Index
### Documentation
1. [Introduction](#Introduction)
  * [Content of the documentation](#Content-of-the-documentation)
    * [Developer manual](#Info-developer-manual)
    * [User Manual](#Info-user-Manual)
  * [Commissioned project](#Commissioned-project)
  
### Developer manual
1. [Composition](#Composition)
  * [Use of a single main structure](#AUse-of-a-single-main-structure)
  * [Double pointers](#Double-pointers)
  * [No redundant information](#No-redundant-information)
  * [Stop scanf](#Stop-scanf)
  * [Printouts and errors](#Printouts-and-errors) 
  * [Deadlock](#Deadlock)
2. [Data structures](#Data-structures)    
  * [Main structure](#Main-structure)
  * [Search binary trees](#Search-binary-trees)
  * [Linked lists](#Linked-lists)

### User Manual
1. [Overview](#Overview)
  * [Data entry](#Data-entry)
  * [Interfaces](#Interfaces)
  * [Automatic populating books](#Automatic-populating-books)


# Introduction
## Content of the documentation

The following documentation is divided into two parts.  
The first part is intended for developers and those who are willing to understand how the program works at the project level.

On the other hand, is intended for the end user and for those who want to access the correct use of the program, taking advantage of all its features.  
It is possible to separate the two manuals according to the type of reader to which it should be destined, or consider the use of the entire documentation.


### Info developer manual

The developer manual refers to those who intend to examine the mechanisms and systems that revolve around the commissioned project.

The analysis takes into consideration the files that make up the program, giving a description of their content and underlining certain implementation details adopted.

The use of all data structures and their interactions with the rest of the program are then shown.


### Info user Manual

The user manual includes the analysis from the functional point of view of the program.

The correct compilation and execution of the program is shown. We then move on to the interfaces and their correct use in more detail.


## Commissioned project
Design a program to manage a student library. The main actors are:
* The library, a collection of books identified by a unique title.
* The students, identified by a unique freshman.

Each student can make a request, which can be of two types:
* Borrow a book.
* Return a book (previously borrowed).

Requests must be met in the order in which they are carried out. It is required to appropriately choose the data structures to organize both the library and student requests. Before starting the program, it is required to populate the library with 15 books.  
When the program starts, the user is required to perform the following operations:
* Add a student request.
* Take charge of a request, i.e .:
    * Satisfy the request.
    * Suspend the request (if the requested book is temporarily unavailable).
* Terminate, only if all requests have been met.

Furthermore, implement a criterion to avoid deadlocks due to suspended requests, which cannot be effectively fulfilled.

# Developer manual
## Composition
The program consists of the union of eight source files with as many headers. Each of these plays a fundamental role in the overall operation of the application.

## Use of a single main structure
It was decided to structure the entire functioning of the library using a single main structure. It is therefore possible to have all the information on which one operates in a single operational block.

All the procedures operate by entering this structure and based on their purpose, they proceed to use the information they need.

This choice has some advantages such as:
* **Reliability**: it is not necessary to de ﬁ ne functions and/or procedures that take different types as inputs. If in the future some parameters were to change this would lead to having to modify the procedure and all the calls that are made to it to pass the new parameter. With a main structure these modifications are almost nil, only the function/procedure will have to be modified to operate on the new parameters. Obviously the procedures in libraries such as *Abr* or *Coda*, being "independent" libraries provide for input parameters that are appropriate to their functionality, for example the allocation of a node of a tree does not take the entire structure but only the node to be allocated.
* **Maintainability**: the modification of a piece of the program is almost reduced to the minimum as new functions or modifications can be built separately and then linked to the main structure.

## Double pointers
Most of the procedures and functions present have been managed with the use of the double pointer technique even if these do not operate on multiple structures at the same time.

## No redundant information
The information on the students (matriculation, name and surname) and on the books (title, author, copies) are allocated in their respective trees.

All the operations that can be performed by the application do not allocate any copy of this data but build a pointer to them.

For example, if a student delivers a book, instead of looking for the book inside the tree to update its number of copies, you can directly access the copies of the book by changing the value and making it available to the whole structure.

## Stop scanf
The use of the scanf can lead to various problems from a simple "dirty buﬀer" to a complete overﬂow.

The entire library is free of scanf, ﬄush or similar but is limited to managing the entry of numeric values and strings by analyzing them character by character through the use of the getchar functionality.

If the value taken as input agrees with the context, then we proceed to allocate a suitable structure for containing the value. For example, for strings it is allowed to enter a total of *forty* characters, if this value is exceeded, the string is truncated, if less then a structure of the same size is allocated to contain the string.

## Printouts and errors
The use of the scanf can lead to various problems from a simple "dirty buﬀer" to a complete overﬂow.

The entire library is free of scanf, ﬄush or similar but is limited to managing the entry of numeric values and strings by analyzing them character by character through the use of the getchar functionality.

If the value taken as input agrees with the context, then we proceed to allocate a suitable structure for containing the value. For example, for strings it is allowed to enter a total of *forty* characters, if this value is exceeded, the string is truncated, if less then a structure of the same size is allocated to contain the string.

## Deadlock
To prevent deadlock situations, the Prompt for delivery functionality has been implemented. We consider a deadlock situation when any of the three queues: book delivery requests, book return requests and the queue for delivered books; is not empty.

The delivery request provides for the delivery of all the books borrowed by the students to the library and for canceling the requests that have been received.

# Data structures
Two main types of data structures are used to manage the library:
1. Binary search trees (abr).
2. Linked lists.

## Main structure
The operation of the entire program is based on the use of a main *struttura_gestione _biblioteca* structure within which all other structures are stored for data storage.
```c
struct struttura_gestione_biblioteca{
    struct struttura_nodo_albero_studente *strutturaStudentiPtr;
    struct struttura_nodo_albero_libro *strutturaLibriPtr;
    struct struttura_elemento_coda *codaRichiestePtr;
    struct struttura_elemento_coda *codaRestituzioniPtr;
    struct struttura_elemento_coda *codaLibriPresiInPrestitoPtr;
};
```
We have:
* **strutturaStudentiPtr**: pointer to the root of the tree containing all students who are registered in the library.
* **strutturaLibriPtr**: pointer to the root of the tree containing all the books that are present in the library.
* **codaRichiestePtr**: pointer to the head of the list containing all requests from students who want to take a book.
* **codaRestituzioniPtr**: pointer to the head of the list containing all requests from students who want to return a book.
* **codaLibriPresiInPrestitoPtr**: pointer to the head of the list containing all the students who have borrowed a book from the library.
Please refer to the source code for more details on the other structures used.

## Search binary trees
Abr's are used to hold information:
* Students enrolled in the library.
* Books that make up the entire library catalog.

The choice to use abr as makes it effective and eﬃcient because the search for an element on *average* has *log2n* complexity where n is the number of nodes in the tree.

In this case, it was decided to use the serial number and the title of the book as a discriminating element for the positioning of the element within the tree.

## Linked lists
Linked lists are used to hold the student-book information pair. Used for: student inquiries, returns and loans.

It was decided to take advantage of the lists implemented as structures rather than one based on an array as the lists allow greater ﬂexibility.

Through arrays, a significant gain is obtained in times of direct access to the individual fields, but the space for the allocation and the possible re-allocations to contain all the information play a disadvantage in the context in which we find ourselves.  
The lists, on the other hand, occupy the space necessary to contain the requested information and are allocated only when necessary.


# User Manual
## Overview
The following manual aims to facilitate the use of the application by means of a simple and quick overview of all the features available.

## Data entry
For correct use of the application it is important to consider:
**The student registration number is a sequence of only numerical values.**  
In order to carry out the functions, the system requests the insertion of the student's serial number. If this is not present then the student is registered providing the name and surname. If the student is already registered, the system shows his registration data.

**The research of the books and all the operations involved on them are case sensitive.**  
If a student wants to take the book "Steve Jobs" he will have to write it respecting upper and lower case letters, insertions such as "sTeve JOBS", "steve Jobs" or others are not considered.

**At the end of the manual there is a list of the predefined books** inserted when the automatic population operation is carried out.

## Interfaces
Once the executable is started, you will find yourself in the main screen. In each of the proposed screens, it is possible to move through the insertion of the numerical value associated with the functionality to be performed.  
There are a total of **five** interfaces:

There are a total of *six* interfaces:
1. **Gestione biblioteca - Popolamento**. It is presented when the program starts. There are two options:
* *Popolamento dei libri tramite terminale*: the library is populated with the books entered by the user.
* *Popolamento dei libri automatico*: the library is automatically populated by *fifteen* books.
2. **Gestione biblioteca - Menu principale**. Shown after populating and when returning from other screens. There are two options:
* *Aggiungi richiesta studente*: open *Gestione biblioteca - Richiesta studente*.
* *Prendi in carico una richiesta*: open *Gestione biblioteca - Operazione richieste*.
3. **Gestione biblioteca - Operazione richieste.**. There are two options:
* *Soddisfa una richiesta*: open *Gestione biblioteca - Soddisfa richiesta*.
* *Sollecita la consegna*: urges the immediate delivery of all books by students.
4. **Gestione biblioteca - Richiesta studente**. There are two options:
* *Richiesta prestito libro*: allows you to add requests from students for loaning a book or delivering a book.
* *Richiesta restituzione libro*: allows you to add requests from students for the return of a borrowed book.
5. **Gestione biblioteca - Soddisfa richiestae**.Here the operations are queued "physically" at the end of the requests made. There are two options:
* *Consegna libro*: takes a request made in *Richiesta prestito libro* and if possible delivers the book to the student.
* *Restituzione libro*: takes a request made in *Richiesta restituzione libro* and if possible the student returns the book.

## Automatic populating books
When automatic population is carried out, the following books are added to the library:
"Halo" (Copies: 2)  
"Il Piccolo Principe" (Copies: 2)  
"Blockchain" (Copies: 1)   
"Vegan" (Copies: 3)  
"Lego" (Copies: 2)  
"Teoria dei graﬁ" (Copies: 4)  
"Algebra" (Copies: 2)  
"Tredici" (Copies: 3)   
"Thinking in java" (Copies: 2)  
"Steve Jobs" (Copies: 2)  
"Elon Musk" (Copies: 3)  
"Essential" (Copies: 2)  
"L’arte dell’inganno" (Copies: 1)   
"Cronache del mondo emerso" (Copies: 1)   
"Il linguaggio C" (Copies: 2)





