# Week 1 - Introduction

18 nisan Salı 11.30 Database Midterm

Final projesi seçimi?

Database App Ex.

- enterprise info
- manufacturing
- banking-finance
- universities
- airlines
- telecommunication
- web-based service
- document database
- navigation system

### Purpose of Db Systems

- File systems had data redundancy and inconsistency: data is stored in multiple formats
- Difficulty in accessing data : need to write a new program to carry out each task
- Data isolation : multiple files and formats
- Integrity problems : hard to add new constraints or exchange existing ones
- Atomicity of updates : failures may leave database in an inconsistent state with partial updates carried out
- Concurrent access by multiple users : needed for performance, uncontrolled concurrent accesses can lead to inconsistincies.
- Security problems

### Data Models

A collection of tools describing

- data
- data relationships
- data semantics (requirements vs)
- data constraints (rules)

- Relational model
- Entity Relationship model

![Untitled](Week%201%20-%20Introduction%20a1ec43afab984d2fa795e2e5e27fdecc/Untitled.png)

### Relational Model

All the data is stored in various tables

![Untitled](Week%201%20-%20Introduction%20a1ec43afab984d2fa795e2e5e27fdecc/Untitled%201.png)

### View of Data

An arch of db system : 

![Untitled](Week%201%20-%20Introduction%20a1ec43afab984d2fa795e2e5e27fdecc/Untitled%202.png)

- View Level : artifical tables
    
    system gives access to this view so that we can see it
    
    so that we cannot see other peoples information, not others
    

- Logical Level : we just define the logical tables. Age column, name column should be number or name etc.
- Physical Level : define coding info, how to save into db and os that info.

Tables : Schemas

- Logical Schema : overall logical structure of db
- Physical Schema : overall physical structure of db
- Instance : the actual content of the db at a particular point in time

### Physical Data Independence

Ability to modify the physical schema without changing the logical schema. In general the interfaces between various levels and components should be well defined so that changes in some parts do not seriously influence others

### Data Definition Language  - DDL

Specification notation for defining the database schema

![Untitled](Week%201%20-%20Introduction%20a1ec43afab984d2fa795e2e5e27fdecc/Untitled%203.png)

DDL compiler generates a set of table templates stored in a data dictionary

- Data dictionary contains metadata → data about data
    - database schema
    - integrity constraints
        - primary key - unique id
    - authorization

### Data Manipulation Language - DML

- Language for accessing and updating the data organized by the appropriate data model
    - DML also known as query language
- Two types of data manipulation language
    - Procedural DML — require a user to specify what data are needed and how to get those data
    - Declarative DML — require a user to specify what data are needed without specifying how to get those data
- Declarative DMLs are easier to learn
- Declarative DMLs is called also non procedural DMLs
- Portion of DML that involves information retrieval is called a query language

SQL is declarative DML

### SQL Query Language

SQL query language is nonprocedural. A query takes as input several tables and always returns a single table.

![Untitled](Week%201%20-%20Introduction%20a1ec43afab984d2fa795e2e5e27fdecc/Untitled%204.png)

- App programs generally access db through :
    - Language extensions to allow embedded SQL
    - App program interface which allow SQL queries to be sent to a db

### Database Design

- Logical Design - Deciding database schema. Database design requires that we find a good collection of relation schemas
    - Business decision - what attiributes should be recorded
    - Computer Science decision - what relation schemas should we have and how should the attributes be distributed ampng the varios relation schemas
    - Physical Design - Deciding on the physical layout of db

### Database Engine

Database system is partitioned into modules that deal with each of the responsibilites of the overall system

The function components of a database system can be divided into 3

- the storage manager
- the query processor component
- the transaction management component

### Storage Manager

A program module that provides the interface between the low level data stored in the db and app programs and queries submitted to system

Main tasks:

- Interaction with the OS file manager
- Efficient storing retrieving and updating of data

Storage manager components include

- Authorization and integrity manager
- Transaction manager
- File manager
- Buffer manager

Storage manager implements several data structures as part of the physical system implementation:

- Data files — store db itself
- Data dictionary — stores metadata about structure of db, schema of db
- Indices — provide fast access to items, provide pointers to those items that hold a particular value

### Query Processor

- DDL interpreter — interprets DDL statements and records the definitions in the data dictionary
- DML compiler — translates DML statements in a query language into an evaluation plan consisting of low level instructions that the query evaluation engine understands
    - DML compiler performs query optimization, it picks the lowest cost evaluation plan from among the various alternatives
- Query evaluation engine — executes low level instructions generated by the DML compiler

![Untitled](Week%201%20-%20Introduction%20a1ec43afab984d2fa795e2e5e27fdecc/Untitled%205.png)

### Transaction Management

A transaction is a collection of operations that performs a single logical function in a db app

Transaction management component ensures that the db remains in a consistent state despite system failures and transaction failures

Concurrency control manager controls the interaction among the concurrent transactions to ensure the consistincy of the db