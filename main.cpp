#include <iostream>
using namespace std;

int const MAXNUMPOLY = 11;

struct ATerm 
{
  int coefficient; 
  int exponent;
  char variable;
  ATerm* next;
}; 
typedef ATerm* Polynomial;

bool isAlpha(char c);
bool isArrow(char c);
bool isEOS(char c);
bool isInt(char c);
bool isNewLine(char c);
bool isOp(char c);
bool isSpace(char c);
bool isValidPoly(string input);
int charToInt(char c);
int length(string s);
int numTerms(string input);
Polynomial add(Polynomial poly1, Polynomial poly2);
Polynomial createList(string &input, int numTerms);
Polynomial deleteZero(Polynomial head);
Polynomial multiply(Polynomial poly1, Polynomial poly2);
Polynomial storeTerm(string &input);
void printList(Polynomial head);

int main() 
{
  int numPoly;
  char c;
  string input;
  Polynomial set[MAXNUMPOLY];
  Polynomial sum;
  Polynomial product;
  
  cout << "This program returns the sum and the product of up to 11 polynomials." << endl;
  cout << "The each polynomial must be in standard form." << endl << endl;
  cout << "Enter 0 into the number of polynomials prompt to end the program." << endl;

  do
  {
    cout << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    cout << endl;
      
    cout << "Number of polynomials -> ";

    do 
    {
      cin >> input;
      numPoly = 0;
      
      for (int i = 0; i < length(input); i++)
      {
        numPoly = numPoly * 10 + charToInt(input[i]);
      }
        
      if (numPoly < 0 || numPoly > MAXNUMPOLY)
      {
        cout << "Invalid number of polynomials. Please try again -> ";
      }
      
    } while (numPoly < 0 || numPoly > MAXNUMPOLY);

    if (numPoly != 0)
    {
      for (int i = 0; i < numPoly; i++)
      {
        cout << "Input polynomial " << i + 1 << " -> ";
        
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
        
        set[i] = deleteZero(temp);
      }

      cout << endl;
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

      cout << endl << endl;;

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

      cout << endl;

      sum = NULL;
      product = NULL;
    }
  } while (numPoly != 0);
}

bool isSpace(char c)
{
  return (c == ' ');
}

bool isOp(char c)
{
  return (c == '+' || c == '-');
}

bool isInt(char c)
{
  return (c >= '0' && c <= '9');
}

bool isAlpha(char c) 
{
  return (c >= 'a' && c <= 'z' || c >='A' && c <= 'Z');
}

bool isArrow(char c)
{
  return (c == '^');
}

bool isEOS(char c)
{
  return (c == '\0');
}

bool isNewLine(char c)
{
  return (c == '\n');
}

char lowercase(char c)
{
  if (c >= 'A' && c <= 'Z')
  {
    return c + 'A';
  }
  return c;
}

int charToInt(char c)
{
  return (c - '0');
}

int length(string s)
{
  int i = 0;
  
  while (!isEOS(s[i]))
  {
    i++;
  }

  return i;
}

int numTerms(string input) 
{
  int numTerms = 1;
  
  for (int i = 1; i < length(input); i++)
  {
    
    if (isOp(input[i]) && !isArrow(input[i - 1]))
    {
      numTerms++;
    }
  }
  return numTerms;
}

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

  if (isArrow(input[i]) && input[i + 1] == '-' && !isEOS(input[i]))
  {
    eSign = '-';
    i += 2;
  } 
  
  if (isArrow(input[i]) && !isEOS(input[i]))
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

bool isValidPoly(string input)
{
  for (int i = 0; i < length(input); i++)
  {
     if (!isInt(input[i]) && lowercase(input[i]) != 'x' && !isArrow(input[i]) && !isOp(input[i]))
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

    if (i < length(input) - 1 && isAlpha(input[i]) && !isOp(input[i+1]) && !isArrow(input[i + 1]))
    {
      return false;
    }

    if (i < length(input) - 1 && isArrow(input[i]) && (!isInt(input[i + 1]) && !isAlpha(input[i + 1]) && input[i + 1] != '-'))
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
