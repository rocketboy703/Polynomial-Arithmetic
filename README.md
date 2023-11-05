#Program Design

The program calculates the sum and product of up to 11 polynomials in one variable “x”. The polynomials must be entered in simplest form. Negative exponents and coefficients are allowed.

Procedural/Functional Decomposition

Problem is broken down into subtasks handled by different functions

Data and data structures passed around via parameters
No objects are included in the program
No library functions are included in the program.

Key Data Structures
•	Linked lists (Defined as type Polynomial) to organize and store each individual polynomial, where every node is a term
•	Arrays to group polynomials into sets, arrays of data type Polynomial are initialized
•	String variables for input validation, all user inputs are initially stored in a string and then manipulated to check for correct format and characters

Algorithm Design
•	Required Tasks
o	Storage of organized lists of numbers, letters, and operation signs that vary in length
o	Addition of lists (2 polynomials at a time) 
o	Multiplication of lists (2 polynomials at a time)
•	Solution
o	Store the characters of the polynomial in linked lists to accommodate for varying list sizes
o	Add polynomials by combining like terms in ascending order and storing the sum in a new linked list
o	Multiply polynomials by finding the product of each term in the two lists, handling varying sizes by adding the any remaining terms to the product which is stored in a new linked list

Time complexity of operations
•	Add Function: O(n)
•	Multiply Function: O(n^2)

Space complexity of operations
•	Add Function: O(n)
•	Multiply Function: O(n)

----------------------------------------------------------------------------------------------------

#Limitations of Current Works

Unable to handle large numeric values
•	Numbers that are larger than 8^11 are not displayed properly in the output console
•	This is likely due to storage limits within the integer variable type

Input must be in simplest form
•	The program does not combine like terms and sort the polynomial in descending powers
•	The solution may lie in searching for similar terms using binary search and sorting the result using merge sort

The only accepted variable to be operated on is “x”
•	The input validation will only allow variables of “x” to be entered
•	The linked list can store other characters in variable data type, however the arithmetic algorithms cannot produce accurate results
•	Modifications to both the addition and multiplication algorithms must be made to handle multiple variable types

Coefficients and other numeric values must be whole numbers
•	Numbers that contain decimal values are rejected by the input validation
•	This limitation has a simple solution of modifying the input validation to accept doubles and integers



