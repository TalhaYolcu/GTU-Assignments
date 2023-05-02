# Midterm Notes

## Week 1 Summary

### Purpose of the db systems :

- **Decrease data redundancy and inconsistency**
- **Decrase difficulty to access data**
- **Data isolation**
- **Integrity problems**
- **Atomicity updates**
- **Security**

### What is Relational Model

Powerful and flexible way of organizing and managing data. Ensures that database system is consistent, reliable and accurate. These properties includes atomicity, consistency, isolation and durability. Key idea is that data is organized into tables with tables and rows, and the relationships between tables are defined by common fields or attributes. Each row represents a record, each column represents a field or attribute.

### What is relation?

Math term for a set of values that are related to each other.

### What is a view?

A view is a virtual table that is created by defining a specific subset of data from one or more tables in the database. It provides a way to access and manipulate data from existing tables.

Views are often used to simplify the complexity of a database providing a customized view of data to a specific user.

### What are Logical Schema and Physical Schema

They represent two views

**Logical schema :** Conceptual representation of a database. Describes the organization of data in terms of entities, attributes.

**Physical schema :**  Represents actual storage of data on a physical storage device. Defines how data is stored on a device including details as file organziation, indexing etc.

### What is instance?

The actual content of the database at a particular point in time - variable

### What is Physical Data Independence?

Ability to modify the physical schema without changing the logical schema. Interfaces between various levels should be well defined so that changes in some part does not influence others.

### What is DDL?

Data Definiton Language, used to define database schema. DDL statements are used to create, modify or delete database objects. Commands:

- **CREATE TABLE**
- **ALTER TABLE**
- **DROP TABLE**
- **CREATE INDEX**
- **CREATE VIEW**

DDL compiler generates a set of table templates stored in a data dictionary.

### What is DML?

Data Manipulation Language, used to manipulate or modify data stored in a database. DML statements are used to insert, update, delete data from tables in a database. Commands:

- **INSERT**
- **UPDATE**
- **DELETE**
- **SEARCH**

**Procedural DML :** Requires the user to have detailed knowledge of the underlying database.

**Declarative DML :** Focuses on what the user wants to achieve and allows the database system to figure out the best way to execute the query.

Declarative one is easier to learn. In some complex queries, procedural one might be needed.

### What is data dictionary?

Centralized repository that stores metadata about the data in a database system. Provides description of structure, relationships and properties of the data elements plus their data types, constraints.

### What is query?

The portion of a DML that involves information retrieval.

### What is SQL Query Language?

Standart programming language used to manage relational databases. Used to retrieve data from a database. Commands: select,insert,update,delete

### What is Logical Database Design?

Deciding database schema.

### What is Physical Database Design?

Deciding on the physical layout of the database.

### What is Database Engine?

Database system is partitioned into modules that deal with each of the responsibilies of the system.

- **Storage Manager**
- **Query Processor**
- **Transaction Manager**

### What is transaction?

Transaction is a logical unit of work that consists one or more database operations. A way to group a set of related database operations together into a single atomic unit of work. Essentail properties : ACID

- **Atomicity**
- **Consistency**
- **Isolation**
- **Durability**

## Week 2 Summary

### What is an attribute?

A characteristic or property that is used to describe a data entity. Can be thought as a column in database table.

### What is Database Schema

Logical structure of the database

### What is database instance?

Snapshot of the data in the database at a given instant time

### What are keys?

A key is a field or set of fields that uniquely identifies a record or entity in a database table.

- **Primary key :** Unique identifier for each record in a table. Cannot contain null values and must be unique across all records in a table. Used as a reference point for relationships between tables.
- **Foreign key :** A field in a table that refers to the primary key of another table. Used to establish a relationship between two tables. Using a single query, we can retrieve data from both tables.
- **Candidate key :** Field that could potentially be used as a primary key for a table. It must be unique and cannot contain null values.
- **Alternate key :** Field that is unique and can be used to identify a record, but not the primary key
- **Composite key :** Combination of two or more fields that together uniquely identify a record in a table

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled.png)

ID is primary key for student and instructor

dept_name is foreign key for student and instructor

dept_name is unique key for department

for advisor relation, student id should be primary key because each student has one advisor but each advisor has many students

### What is Relational Algebra?

A procedural language consists of set of operations that take one or two relations as input and produce a new relation as result.

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%201.png)

**Select operation**

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%202.png)

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%203.png)

**Project operation**

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%204.png)

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%205.png)

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%206.png)

**Cartesian Product operation**

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%207.png)

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%208.png)

**Join operation**

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%209.png)

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2010.png)

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2011.png)

**Union operation**

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2012.png)

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2013.png)

**Set intersection operation**

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2014.png)

Set difference opration

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2015.png)

**Assignment operation**

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2016.png)

**Rename operation**

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2017.png)

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2018.png)

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2019.png)

### Intro to SQL - SQL Parts

- **DML** → provides the ability to query data from the database
- **Integrity** → DDL includes commands for specifiying integrity constaints
- **View definition** → DDL includes command for defining views
- **Transaction control** → DDL includes commands for specifiying the beginning and ending of transactions
- **Embedded and Dynamic SQL** → define how SQL statements can be embedded withing a PL
- **Authorization** → DDL includes commands for specifiying access rights to views

### What is DDL?

Data Definition Language allow specifiaction of information about relations including:

- **Schema for each relation**
- **Type of values associated with each attribute**
- **Integrity constraints**
- **Security and authorization**
- **Physical storage structure of each relation**

### Types in SQL

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2020.png)

in numeric, p is for precision and d is for scale. for ex : 10000000,00

**Create table command**

```sql
CREATE TABLE instructor (
    ID CHAR(5),
    name VARCHAR(20),
    dept_name VARCHAR(20),
    salary NUMERIC(8,2)
);
```

**Creating table with integrity constraints**

```sql
create table instructor(
	ID char(5),
	name varchar(20) not null,
	dept_name varchar(20),
	salary numeric(8,2),
	primary key (ID),
	foreign key (dept_name) references department
);
```

**More examples**

```sql
create table student(
	ID varchar(5),
	name varchar(20) not null,
	dept_name varchar(20),
	tot_cred numeric(3,0),
	primary key (ID),
	foreign key (dept_name) references department
);
```

```sql
create table takes(
	ID varchar(5),
	course_id varchar(8),
	sec_id varchar(8),
	semester varchar(6),
	year numeric(4,0),
	grade varchar(2),
	primary key (ID, course_id, sec_id, semester, year),
	foreign key (ID) references student,
	foreign key (course_id, sec_id, semester, year) references section
);
```

```sql
create table course(
	course_id varchar(8),
	title varchar(50),
	dept_name varchar(20),
	credits numeric(2,0),
	primary key (course_id),
	foreign key (dept_name) references department
);
```

**Insertion into a table**

```sql
insert into instructor values ('10211', 'Smith', 'Biology', 66000);
```

**Delete all tuples from the student relation - delete contents, not the table**

```sql
delete from student
```

**Drop table - delete table with its contents**

```sql
drop table r
```

**Add a new column - all data will be null**

```sql
ALTER TABLE students
ADD COLUMN email VARCHAR(50);
```

**Modifiy existing column**

```sql
ALTER TABLE students
ALTER COLUMN grade NUMERIC(3, 2);
```

### What is Select Clause?

Lists the attributes desired in the result of a query

**Find the names of all instructors**

```sql
select name from instructor
```

**Force the elimination of duplicates : insert the keyword “distinct” after select**

**Find the department names of all instructors, remove duplicates**

```sql
select distinct dept_name from instructor
```

**Keyword all specifies that duplicates should not be removed**

```sql
select all dept_name from instructor
```

**Get all attirbutes from instructor**

```sql
select * from instructor
```

**could contain math op.**

```sql
select ID, name, salary/12 from instructor
select ID,name, salary/12 as monthly_salary from instructor
```

### What is where clause?

Specifies conditions that result must satisfy

**Find all instructors in Comp. Sci**

```sql
select name from instructor where dept_name='Comp. Sci.'
```

and - or - not allowed, math allowed

**Find all instructors in Comp. Sci. dept with salary > 80000**

```sql
select name from instructor where dept_name='Comp. Sci.' and salary > 80000
```

### What is from clause?

Lists the relations involved in the query.

**Find the cartesian product instructor x teaches**

```sql
select * from instructor,teaches
```

**Find the names of all instructors who have taught some course and the course_id**

```sql
select name,course_id from instructor,teaches where instructor.ID=teaches.ID
```

**Find the names of all instructors in the Art department who have taught some course and the course_id**

```sql
select name, course_id from instructor , teaches where instructor.ID = teaches.ID and instructor.dept_name = 'Art'
```

### What is rename operation?

rename with as clause. usage : old-name as new-name

**Find the names of all instructors who have a higher salary than some instructor in 'Comp. Sci'.**

```sql
select distinct T.name from instructor as T,instructor as S where T.salary>S.salary and S.dept_name='Comp. Sci.'
```

instructor as T = instructor T

**Find the names of all instructors whose name includes the substring “dar”.**

```sql
select name from instructor where name like '%dar%'
```

**List in alphabetic order the names of all instructors**

```sql
select distinct name from instructor order by name
```

**Find the names of all instructors with salary between $90,000 and $100,000 (that is, ≥$90,000 and ≤$100,000)**

```sql
select name from instructor where salary between 90000 and 100000
```

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2021.png)

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2022.png)

## Week 3 Summary

### What are Aggregate Functions?

Operate on the mulitset of values of a column of a relation and return a value

avg,min,max,sum,count

**Find the average salary of instructors in the Computer Science department**

```sql
select avg(salary) from instructor where dept_name='Comp. Sci.'
```

**Find the total number of instructors who teach a course in the Spring 2018 semester**

```sql
select count(distinct ID) from teaches where semester='Spring' and year=2018
```

Grouping in agg.functions

**Find the average salary of instructors in each department**

```sql
select dept_name, avg(salary) as avg_salary from instructor group by dept_name
```

**Having Clause**

**Find the names and average salaries of all departments whose average salary is greater than 42000**

```sql
select name, avg(salary) as avg_salary from instructor group by dept_name having avg(salary)>42000
```

### What are Nested Subqueries?

Select-from-where expression that is nested within another query

**Find courses offered in Fall 2017 and in Spring 2018**

```sql
select distinct course_id from section where semester='Fall' and year=2017 and course_id in (select course_id from section where semester='Spring' and year=2018)
```

**Find courses offered in Fall 2017 but not in Spring 2018**

```sql
select distinct course_id from section where semester='Fall' and year=2017 and course_id not in (select course_id from section where semester='Spring' and year=2018)
```

**Name all instructors whose name is neither Mozart nor Eintein**

```sql
select distinct name from instructor where name not in ('Mozart','Einstein')
```

**Find the total number of (distinct) students who have taken course sections taught by the instructor with ID 10101**

```sql
select count (distinct ID) from takes where (course_id,sec_id,semester,year) in (select course_id,sec_id,semester,year from teaches where teaches.ID=10101)
```

## Week 4 Summary

Design is seperated into 3 phases

### Initial Phase

Identifiying requirements and understanding the data needs to be stored. Also identifiying the types of data, relationships between data etc.

### Second Phase - choosing a data model

Often relational. Depend on complexity, needs of users, requirements.

### Final Phase - **Moving from an abstract data model to the implementation of the database**

Includes defining tables, columnds, constraints. Logical and Physical design is here.

We should avoid from two:

**Redundancy :** redundant representation of info may lead data inconsistency.

**Incompleteness** : some expected or required data is missing.

### Design Approaches

### Entity Relationship Model

Conceptual data model that represents the relations between entities in database. Consists of entities, relationships and attributes

### What is an entity?

Real word object that can be identified in database.

### What is an entity set?

A set of entities that share the same type and properties.

### What is an attribute?

An attribute is a characteristic or property of an entity.

### What is relationship

Represents the association or connection between two or more entities in the database.

### What is a role?

Named collection of privileges or permissions that can be assigned to one or more users.

### What is a degree of a relationship?

Number of entites involved in that relationship

Binary relationship : two entities are involved

Ternary relationship : three entities

### What is simple attribute?

Cannot be broken down into smalle components → age, gender

### What is composite attribute?

Can be broken down into smaller components. → address,name

### What is derived attribute?

Not stored directly but derived from other stored attributes.

Age can be derived from birthdate.

### What is domain?

A set of values that can be assigned to an attribute.

### What are Cardinality Constraints?

Expressing the number of entities to which another entity can be associated with a relation

- One to one → 1 employee, 1 office
- One to many → 1 customer, n order
- Many to one → n order, 1 customer
- Many to many → n student, n course

### What is Total Participation?

Every instance of an entity must participate in a relationship. - Mandatory participation - Existence dependency  - Department and employee. If every employee mustbe associated with a department, then the participation of the employee in the relationship with department is total

### What is Partial Participation?

Some instances of an entity may not participate in a relationship. - Optional participation - non-existence dependency - Department and project. If some projects may not be associated with any department, the participation of the project in the relationship is partial.

0..* → 0 or more

1..1 → must have 1

- A minimum value of 1 indicates total pariticipation
- A maximum value of 1 indicates entity can participate at most one relationship
- A maximum value of * indicates no limit

### Primary keys for entity sets

Attributes that uniquely identify each entity in the set

### Primary keys for relationship sets

A set of attributes that when taken together, uniquely identify each relationship between entities in relationship set

### What is weak entity set?

Cannot be uniquely identified by its attributes alone. Depends on the existence of antoher related entity set.

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2023.png)

### What is specialization?

Process of defining new entity sets based on existing entity set where the new entity sets have attributes that specific to them and not shared with other entity sets.

### What is attribute inheritence?

Lower level entity set inherits all the attributes.

## Week 5 Summary

### What is View?

Provides mechanism to hide certain data from the view of certain users.

A view of instructors without their salary

```sql
create view faculty as select ID,name,dept_name from instructor
```

Find all instructors in the biology department

```sql
select name from faculty where dept_name='Biology'
```

Create view of department salary totals

```sql
create view dep_tot_salary(dept_name,total_salary) as select dept_name, sum(salary) from instructor group by dept_name;
```

### What is View Expansion

A way to define the meaning of views defined in terms of other views.

### What is materialized view?

Contains the results of a precomputed query, stored in a physical form as a table.

**Insertion operation**

```sql
insert into faculty values ('30765', 'Green','Music');
```

### What is a transaction?

Consists of a sequence of query and/or update statements and is a unit of work

Transaction must end with one of the following statements

- **Commit work : Updated performed by the transaction become permanent**
- **Rollback work : All updates performed by SQL statements are undone**

### What are integrity constraints?

Guard againts accidental damage to the database. Ensures authorized changes.

- not null
- primary key
- unique
- check : define a condition that must be satisfied for a row to be valid and inserted into a table. salary cannot be less than 0

### Referantial Integrity

A value that appears in one relation for a given set of attributes also appears for a certain set of attributes in another relation. For ex: If biology is a department name in one of tuples in instructor relation, there should exist a tuple in the department relation for biology

### What are Assertions?

Predicate expressing a condition that we wish the database always to satisfy.

**create assertion assertion_name check (cond)**

```sql
CREATE ASSERTION salary_constraint CHECK (
    NOT EXISTS (
        SELECT * FROM employees e1
        WHERE EXISTS (
            SELECT * FROM employees e2
            WHERE e2.supervisor_id = e1.employee_id
            AND e2.salary < e1.salary
        )
    )
);
```

**creating a type**

```sql
create type Dollars as numeric (12,2) final
```

**final : subtype cannot be derived from the object type**

**blob : binary large object, store binary data as a single entity**

**clob : character large object, store large amounts of char data as a single entity**

**creating domain:**

```sql
create domain person_name char (20) not null
```

Domains can have constraints like not null

### What is an index?

Index on an attribute of a relation is a data structure that allows the system to find those tuples in the relation that have a specified value for that attribute efficiently.

```sql
create index studentID_index on student (ID)
```

### Authorization

- read
- insert
- update
- delete
- index
- resources : allow create new relation
- alternation : allow add delete attribute
- drop
- select : allow read access
- all privileges : all

```sql
grant select on department to Amit,Satoshi
```

```sql
revoke select on department from Amit
```

### What is a Role?

A way to distinguish among various users.

```sql
create role instructor
grant instructor to Amit,Ulric
```

references privelege allows a user to create a foreign key that references another table in the database.

```sql
grant references on department to username
```

## Week 6 Summary

### What is decomposition?

Process of breaking down a large table into smaller tables to improve database design.

### What is lossy decomposition?

Decomposition of a relation that results in the loss of information or functional dependencies.

### What is Normalization?

Process of organizing data in a database to minimize redundancy and dependency, by decomposing it.

### What is functional dependency?

Relationship between two attributes in a relation, where the value of one attribute determines the value of other attribute. If we know one, we can determine the other one. There are constraints like student and instructors are uniquely identified bu id. We can extract functional dependencies from that constraints.

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2024.png)

iki farklı entity, aynı attribute une bak, eğer iki farklı entity nin bir attribute ü eşitse, diğer attribute üde eşit olmalıdır. Bu örnekte tutmuyor

ters düşünelim, 4 - 5 - 7 hepsi farklı, o yüzden bu case sağlanmış oluyor. Tüm B→A ‘lar tutuyor.

### What is Closure of a Set of Functional Dependencies?

Refers to the of all functional dependencies that can be inferred from the given set of functional dependencies.

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2025.png)

### Keys and Functional Dependencies

Keys play an important role in determining functional dependencies. Any attribute that depends on the primary key must be functionally dependent on it.

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2026.png)

**superkey : K is a superkey if and only if k has a functional dependency to r**

**candidate key : K is a candidate key if and only if** 

- K has  a functional dependendency to R
- alfa won’t be k’s subset, alfa will not have a functional dependency to R

### What is trivial functional dependency?

A functional dependency is trivial if it is satisfied by all instances of a relation

ID,name → ID

name → name

beta is a subset of alfa

alfa → beta

### Lossless Decomposition

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2027.png)

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2028.png)

### What is dependency preservation?

Property of a decomposition of a relation that ensures that the functional dependencies that hold in the original relation also hold in the decomposed relations.

### Boyce-Codd Normal Form

BCNF → A relation is in BCNF if and only if every determinant (candidate key) is a candidate key. In a BCNF relation, every nontrivial functional dependency involves superkey.

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2029.png)

Sure, here is an example:

Consider a relation R(A, B, C, D) with functional dependencies:

- A → B
- B → C
- C → D

This relation is not in BCNF because the determinant of the third functional dependency, C, is not a superkey of R.

To bring the relation to BCNF, we need to decompose it into two relations, R1 and R2:

- R1(A, B, C)
- R2(C, D)

Here, R1 has the candidate keys {A} and {B}, and R2 has the candidate key {C}. The dependency A → B is preserved in R1, and the dependency C → D is preserved in R2. Therefore, this decomposition satisfies the BCNF.

### Decomposing a schema into BCNF

To decompose a schema into BCNF, we need to follow these steps:

1. Start with a set of functional dependencies and determine the candidate keys for the relation schema.
2. Check whether the relation schema is in BCNF or not. If not, proceed to the next step.
3. For each functional dependency that violates BCNF, create a new relation schema by removing the attributes on the right-hand side of the dependency and including the candidate key for the original relation schema.
4. Repeat step 2 and step 3 until all relation schemas are in BCNF.

Here's an example of decomposing a relation schema into BCNF:

Consider a relation schema R(A, B, C, D) with the following functional dependencies:

- A → B
- B → C
- C → D

The candidate keys for the relation schema are {A} and {B}.

The dependency A → B violates BCNF, as A is not a superkey for the relation schema. To decompose the relation schema into BCNF, we create a new relation schema R1(A, B) with A as the primary key and a second relation schema R2(B, C, D) with B as the primary key.

The resulting relation schemas are:

R1(A, B) with A as the primary key and the functional dependency A → B.

R2(B, C, D) with B as the primary key and the functional dependencies B → C and C → D.

Both relation schemas are now in BCNF.

### Dependency preservation and BCNF

Consider a relation R(A, B, C, D) with functional dependencies:

- A → B
- B → C
- C → D

R is not in BCNF because the determinant of each dependency is not a superkey. We can decompose R into two relations:

R1(A, B) with functional dependency A → B
and
R2(B, C, D) with functional dependencies B → C and C → D

The decomposition is BCNF because each relation has a single candidate key that includes all of its attributes, and all functional dependencies are preserved:

- A → B is preserved in R1
- B → C is preserved in R2 because B is the only attribute in R2 that determines C
- C → D is preserved in R2

### Third Normal Form

Ensures that each non-key attribute of a table is functionally dependent on the primary key, as well as on no other nonkey attributes

3NF requires that for any nonkey attribute A in a table, either A must be a part of the primary key or A must be dependent on the primary key and on nothing else.

For example, consider a table named "Order_Details" that stores information about customer orders, with columns for "Order_ID", "Product_ID", "Product_Name", "Product_Price", and "Customer_ID". In this table, "Product_Name" and "Product_Price" are dependent on "Product_ID", which is dependent on "Order_ID", making it a transitive dependency. To make the table 3NF, it would be decomposed into two tables: "Order_Details" and "Products", with "Product_ID" as the primary key in the latter, and "Product_Name" and "Product_Price" as attributes in the "Products" table

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2030.png)

![Untitled](Midterm%20Notes%20bec9cc36bc61441282f1d863b02f0a02/Untitled%2031.png)