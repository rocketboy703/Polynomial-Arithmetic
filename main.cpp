#include <iostream>
using namespace std;

int const MAXNUMPOLY = 11;
int const MAXDIGIT = 2;

struct ATerm
{
  int coefficient; 
  int exponent;
  char variable;
  ATerm* next;
}; 
typedef ATerm* Polynomial;

bool isAlpha(char c);
bool isCaret(char c);
bool isEOS(char c);
bool isInt(char c);
bool isNewLine(char c);
bool isOp(char c);
bool isSpace(char c);
bool isValidPoly(string input);
char lowercase(char c);
int charToInt(char c);
int getNumPoly();
int length(string s);
int numTerms(string input);
Polynomial add(Polynomial poly1, Polynomial poly2);
Polynomial createList(string &input, int numTerms);
Polynomial deleteZero(Polynomial head);
Polynomial getPoly();
Polynomial multiply(Polynomial poly1, Polynomial poly2);
Polynomial storeTerm(string &input);
void introMessage();
void printList(Polynomial head);
void printProduct(Polynomial set[], int numPoly);
void printSum(Polynomial set[], int numPoly); 

/*---------------------------------------------------------
Calculates the sum and product of up to 11 simplified
polynomials in one variable “x”
---------------------------------------------------------*/
int main() 
{
  int numPoly;
  Polynomial set[MAXNUMPOLY];

  introMessage();

  do
  {
    cout << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    cout << endl;

    numPoly = getNumPoly();

    if (numPoly != 0)
    {
      for (int i = 0; i < numPoly; i++)
      {
        cout << "Input polynomial " << i + 1 << " -> ";
        set[i] = getPoly();
      }

      cout << endl;
      printSum(set, numPoly);
      cout << endl << endl;
      printProduct(set, numPoly);
      cout << endl;
    }
  } while (numPoly != 0);
}

/*---------------------------------------------------------
Given a character, returns true if the character is a space 
and false otherwise
---------------------------------------------------------*/
bool isSpace(char c)
{
  return (c == ' ');
}

/*---------------------------------------------------------
Given a character, returns true if the character is an 
integer and false otherwise
---------------------------------------------------------*/
bool isOp(char c)
{
  return (c == '+' || c == '-');
}

/*---------------------------------------------------------
Given a character, returns true if the character is an 
integer and false otherwise
---------------------------------------------------------*/
bool isInt(char c)
{
  return (c >= '0' && c <= '9');
}

/*---------------------------------------------------------
Given a character, returns true if the character is 
alphabetical and false otherwise
---------------------------------------------------------*/
bool isAlpha(char c) 
{
  return (c >= 'a' && c <= 'z' || c >='A' && c <= 'Z');
}

/*---------------------------------------------------------
Given a character, returns true if the character is a caret 
and false otherwise
---------------------------------------------------------*/
bool isCaret(char c)
{
  return (c == '^');
}

/*---------------------------------------------------------
Given a character, returns true if the character is the 
end-of-string marker false otherwise
---------------------------------------------------------*/
bool isEOS(char c)
{
  return (c == '\0');
}

/*---------------------------------------------------------
Given a character, returns true if the character is the 
new-line marker and false otherwise
---------------------------------------------------------*/
bool isNewLine(char c)
{
  return (c == '\n');
}

/*---------------------------------------------------------
Takes an alphebetical character and returns it in
lowercase
---------------------------------------------------------*/
char lowercase(char c)
{
  if (c >= 'A' && c <= 'Z')
  {
    return c + 'A';
  }
  return c;
}

/*---------------------------------------------------------
Takes an integer stored as a char and returns the integer 
equivalent
---------------------------------------------------------*/
int charToInt(char c)
{
  return (c - '0');
}

/*---------------------------------------------------------
Takes a string and returns the length of the string
---------------------------------------------------------*/
int length(string s)
{
  int i = 0;

  while (!isEOS(s[i]))
  {
    i++;
  }
  return i;
}

/*---------------------------------------------------------
Prints out the program introduction message
---------------------------------------------------------*/
void introMessage()
{
  cout << "This program returns the sum and the product of up to 11 polynomials." << endl;
  cout << "The each polynomial must be in standard form." << endl << endl;
  cout << "Enter 0 into the number of polynomials prompt to end the program." << endl;
}

/*---------------------------------------------------------
Asks the user for the number of polynomials to be operated 
on and validates the input
---------------------------------------------------------*/
int getNumPoly()
{
  int numPoly;
  string input;
  bool valid;

  cout << "Number of polynomials -> ";

  do 
  {
    numPoly = 0;
    cin >> input;
    valid = true;

    if (length(input) == 0 || length(input) > MAXDIGIT)
    {
      valid = false;
    }
    else
    {
      for (int i = 0; i < length(input); i++)
      {
        if (!isInt(input[i]))
        {
          valid = false;
        }
        else
        {
          numPoly = numPoly * 10 + charToInt(input[i]);
        }
      }
    }

    if (numPoly < 0 || numPoly > MAXNUMPOLY)
    {
      valid = false;
    }
    
    if (!valid)
    {
      cout << "Invalid number of polynomials. Please try again -> ";
    }

  } while (!valid);

  return numPoly;
}

/*---------------------------------------------------------
Asks the user to input a polynomial into a string variable 
and returns the polynomial stored in a linked list
---------------------------------------------------------*/
Polynomial getPoly()
{
  char c;
  string input;

  do
  {
    cin >> input;

    if (!isValidPoly(input))
    {
      cout << "Invalid polynomial. Please try again -> ";
    }
  } while (!isValidPoly(input));

  cin.get(c);

  while (!isNewLine(c))
  {
    if (!isSpace(c))
    {
      input += c;
    }
    cin.get(c);
  }

  Polynomial temp = createList(input, numTerms(input));

  return deleteZero(temp);
}

/*---------------------------------------------------------
Determines the number of terms in the polynomial inputted 
by the user
---------------------------------------------------------*/
int numTerms(string input) 
{
  int numTerms = 1;

  for (int i = 1; i < length(input); i++)
  {

    if (isOp(input[i]) && !isCaret(input[i - 1]))
    {
      numTerms++;
    }
  }
  return numTerms;
}

/*---------------------------------------------------------
Takes a polynomial stored in a string, removes the first 
term from the string, and returns the term in the form of a
linked list node
---------------------------------------------------------*/
Polynomial storeTerm(string &input)
{
  Polynomial term = new ATerm;
  int i = 0;
  int coefficient = 0;
  int exponent = 0;
  char cSign = '+'; 
  char eSign = '+';

  if (input[0] == '-')
  {
    cSign = '-';
    i++;
  } 
  else if(input[0] == '+')
  {
    i++;
  }

  while (isInt(input[i]) && !isEOS(input[i]))
  {
    coefficient = coefficient * 10 + charToInt(input[i]);
    i++;
  }

  term->coefficient = coefficient;

  if (isAlpha(input[i]) && !isEOS(input[i]))
  {
    term->variable = input[i];
    i++;
  }

  if (isCaret(input[i]) && input[i + 1] == '-' && !isEOS(input[i]))
  {
    eSign = '-';
    i += 2;
  } 

  if (isCaret(input[i]) && !isEOS(input[i]))
  {
    i++;
  }

  while (isInt(input[i]) && !isEOS(input[i]))
  {
    exponent = exponent * 10 + charToInt(input[i]);
    i++;
  }

  term->exponent = exponent;

  if (coefficient == 0 && isAlpha(term->variable))
  {
    term->coefficient = 1;
  }

  if (exponent == 0 && isAlpha(term->variable))
  {
    term->exponent = 1;
  }

  if (isAlpha(term->variable))
  {
    term->variable = lowercase(term->variable);
  }

  if (cSign == '-')
  {
    term->coefficient *= -1;
  }

  if (eSign == '-')
  {
    term->exponent *= -1;
  }

  input.erase(0, i);

  return term;
}

/*---------------------------------------------------------
Takes a polynomial stored in a string and the number of 
terms in the polynomial and returns the polynomial in a 
linked list
---------------------------------------------------------*/
Polynomial createList(string &input, int numTerms)
{
  Polynomial head = storeTerm(input);
  Polynomial temp = head;

  for (int i = 1; i < numTerms; i++)
  {
    temp->next = storeTerm(input);
    temp = temp->next;
  }

  temp->next = NULL;

  return head;
}

/*---------------------------------------------------------
Takes a polynomial and prints it out in the console
---------------------------------------------------------*/
void printList(Polynomial head)
{
  Polynomial temp = head;

  while (temp != NULL)
  {
    cout << '[';

    if (temp->coefficient != 1 || !isAlpha(temp->variable))
    {
    cout << temp->coefficient;
    }

    cout << temp->variable;

    if (temp->exponent != 0 && temp->exponent != 1)
    {
      cout << '^';
      cout << temp->exponent;
    }

    cout << ']';

    if (temp->next != NULL)
    {
      cout << " + ";
    }

    temp = temp->next;
  }
}

/*---------------------------------------------------------
Takes a set of polynomials, calculates the sum, and 
prints it out in the console 
---------------------------------------------------------*/
void printSum(Polynomial set[], int numPoly)
{
  Polynomial sum;

  cout << "Sum = ";

  for (int i = 0; i < numPoly; i++)
  {
    cout << "(";
    printList(set[i]);
    cout << ")";

    if (i != numPoly - 1)
    {
      cout << " + ";
    }
  }

  cout << endl;
  cout << "    = ";

  sum = set[0];

  for (int i = 1; i < numPoly; i++)
  {
    sum = add(sum, set[i]);
    sum = deleteZero(sum);
  }

  printList(sum);

  sum = NULL;
}

/*---------------------------------------------------------
Takes a set of polynomials, calculates the product, and 
prints it out in the console 
---------------------------------------------------------*/
void printProduct(Polynomial set[], int numPoly)
{
  Polynomial product;

  cout << "Product = ";

  for (int i = 0; i < numPoly; i++)
  {
    cout << "(";
    printList(set[i]);
    cout << ")";

    if (i != numPoly - 1)
    {
      cout << " * ";
    }
  }

  cout << endl;
  cout << "        = ";

  product = set[0];

  for (int i = 1; i < numPoly; i++)
  {
    product = multiply(product, set[i]);
  }

  printList(product);

  product = NULL;
}

/*---------------------------------------------------------
Takes a polynomial and removes and terms that simplify to 
0, returns the simplified polynomial
---------------------------------------------------------*/
Polynomial deleteZero(Polynomial head)
{
  Polynomial temp = head;
  Polynomial toDelete = temp;

  if (head->coefficient == 0 && head->next == NULL)
  {
    return head;
  }

  if (head->coefficient == 0)
  {
    toDelete = head;
    head = toDelete->next;
    delete toDelete;
  }

  toDelete = temp;

  while (toDelete->next != NULL)
  {
    temp = toDelete;
    toDelete = toDelete->next;

    if (toDelete->coefficient == 0)
    {
      temp->next = toDelete->next;
      delete toDelete;
      toDelete = temp->next;
    }
  }

  if (toDelete->coefficient == 0)
  {
    temp->next = NULL;
    delete toDelete->next;
  }

  return head;
}

/*---------------------------------------------------------
Takes two polynomials stored in separate linked lists and 
returns the sum stored in a new linked list
---------------------------------------------------------*/
Polynomial add(Polynomial poly1, Polynomial poly2)
{
  Polynomial head = new ATerm;
  Polynomial temp = head;
  Polynomial temp1 = poly1;
  Polynomial temp2 = poly2;

  while (temp1 != NULL && temp2 != NULL)
  {
    if (temp1->exponent > temp2->exponent)
    {
      temp->coefficient = temp1->coefficient;
      temp->exponent = temp1->exponent;
      temp->variable = temp1->variable;

      temp1= temp1->next;
    }
    else if (temp1->exponent < temp2->exponent)
    {
      temp->coefficient = temp2->coefficient;
      temp->exponent = temp2->exponent;
      temp->variable = temp2->variable;

      temp2= temp2->next;
    }
    else if (temp1->exponent == temp2->exponent)
    {
      temp->coefficient = (temp1->coefficient + temp2->coefficient);
      temp->exponent = temp1->exponent;
      temp->variable = temp1->variable;

      temp1 = temp1->next;  
      temp2 = temp2->next;
    }

    if (temp1 != NULL || temp2 != NULL)
    {
      temp->next = new ATerm;
      temp = temp->next;
    }
  }

  while (temp1 != NULL)
  {
    temp->coefficient = temp1->coefficient;
    temp->exponent = temp1->exponent;
    temp->variable = temp1->variable;

    temp1= temp1->next;

    if (temp1 != NULL)
    {
      temp->next = new ATerm;
      temp = temp->next;
    }
  }

  while (temp2 != NULL)
  {
    temp->coefficient = temp2->coefficient;
    temp->exponent = temp2->exponent;
    temp->variable = temp2->variable;

    temp2= temp2->next;

    if (temp2 != NULL)
    {
      temp->next = new ATerm;
      temp = temp->next;
    }
  }

  temp->next = NULL;

  return head;
}

/*---------------------------------------------------------
Takes two polynomials stored in separate linked lists and 
returns the product stored in a new linked list
---------------------------------------------------------*/
Polynomial multiply(Polynomial poly1, Polynomial poly2)
{
  Polynomial product = NULL;
  Polynomial temp;
  Polynomial temp1 = poly1;
  Polynomial temp2;

  while (temp1 != NULL)
  {
    Polynomial head = new ATerm;
    temp = head;

    temp2 = poly2;

    while (temp2 != NULL)
    {
      temp->coefficient = (temp1->coefficient * temp2->coefficient);

      temp->exponent = (temp1->exponent + temp2->exponent);

      if (isAlpha(temp1->variable) && temp->exponent != 0)
      {
        temp->variable = temp1->variable;
      }

      if (isAlpha(temp2->variable) && temp->exponent != 0)
      {
        temp->variable = temp2->variable;
      }

      if (temp2->next != NULL)
      {
        temp->next = new ATerm;
        temp = temp->next;
      }

      temp2 = temp2->next;
    }

    temp->next = NULL;
    temp1 = temp1->next;

    product = add(product, head);
  }

  return product;
}

/*---------------------------------------------------------
Given a string, returns true if the string consists of a 
properly formatted polynomial in simplest form and returns 
false otherwise
---------------------------------------------------------*/
bool isValidPoly(string input)
{
  if (length(input) == 0)
  {
    return false;
  }
  
  for (int i = 0; i < length(input); i++)
  {
     if (!isInt(input[i]) && lowercase(input[i]) != 'x' && !isCaret(input[i]) && !isOp(input[i]))
     {
       return false;
     }
  }

  for (int i = 0; i < length(input); i++)
  { 
    if (input[0] != '-' && !isInt(input[0]) && !isAlpha(input[0]))
    {
      return false;
    }

    if (i < length(input) - 1 && isAlpha(input[i]) && !isOp(input[i+1]) && !isCaret(input[i + 1]))
    {
      return false;
    }

    if (i < length(input) - 1 && isCaret(input[i]) && (!isInt(input[i + 1]) && !isAlpha(input[i + 1]) && input[i + 1] != '-'))
    {
      return false;
    }

    if (i < length(input) - 1 && isOp(input[i]) && !isInt(input[i + 1]) && !isAlpha(input[i + 1]))
    {
      return false;
    }

    if (i == length(input) - 1 && !isInt(input[i]) && !isAlpha(input[i]))
    {
      return false;
    }
  }
  return true;
}

//Don't get stuck on one problem when programming. Skip it and come back to it.
