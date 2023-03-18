#include <string>
#include <iostream>
#include <exception>
#include"myexceptions.h" //exceptions 
#include"stack.h" //pdf.stack imp
#include"ArrayStack.h"//my Stack
#include"QueueArray.h"// my queue
#include"queue.h"//pdf.queue imp

bool checkBalanceBrackets(const std::string& text, const int maxDeep); 

void testStack();
void testQueue();
void testBrackets()
{
    std::cout << "Brackets Test--------------------\n";
    std::cout << "Correct:\n";
    std::cout << checkBalanceBrackets("()[]{}({[]}[{}])", 10) << '\n';
    std::cout << checkBalanceBrackets("()", 10) << '\n';
    std::cout << checkBalanceBrackets("(8)*{5/[8-9*(2-a)]}", 10) << '\n';
    std::cout << "Incorrect:\n";
    std::cout << checkBalanceBrackets("(()", 10) << '\n';
    std::cout << checkBalanceBrackets("()}", 10) << '\n';
    std::cout << checkBalanceBrackets("({[])}", 10) << '\n';
    std::cout << checkBalanceBrackets("({[()]})", 2) << '\n';
}


int main()
{
    testStack();
    testQueue();
    testBrackets();

    return 0;
}


bool checkBalanceBrackets(const std::string& text, const int maxDeep) {
 // StackArray<char> stack(text.size());//size()!!!
StackArray<char> stack(text.size());
  int countRound{0}, countSquare{0}, countCurly{0};
   
  for (const char& c : text) {
    switch (c) {
      case '(':
        if (countRound == maxDeep)
         {
          return false;
        }
        stack.push(c);
        countRound++;
        break;

      case '[':
        if (countSquare == maxDeep) 
        {
          return false;
        }
        stack.push(c);
        countSquare++;
        break;

      case '{':
        if (countCurly == maxDeep) 
         {
          return false;
        }
        stack.push(c);
        countCurly++;
        break;

      case ')':

        if (stack.isEmpty() || stack.pop() != '(') 
        
        {
          return false;
        }
        countRound--;
        break;

      case ']':

        if (stack.isEmpty() || stack.pop() != '[') 
        {
          return false;
        }
        countSquare--;
        break;

      case '}':
        if (stack.isEmpty() || stack.pop() != '{')
        {
          return false;
        }
        countCurly--;
        break;

      default:// ıgnore  characters
        break;
    }
  }

  return stack.isEmpty() && countRound == 0 && countSquare == 0 && countCurly == 0;  //  brackets  match

}

void testStack()
{
    std::cout << "Stack Test--------------------\n";

    Stack<int>* intStack = new StackArray<int>(5);

    std::cout << "Stack is empty: " << intStack->isEmpty() << '\n';

    intStack->push(1);
    intStack->push(2);
    intStack->push(3);
    intStack->push(4);
    intStack->push(5);

    try
    {
        intStack->push(6);
    }
    catch (const StackOverFlow& e)
    {
        std::cout << e.what() << '\n';
    }

    std::cout << intStack->pop() << '\n';
    std::cout << intStack->pop() << '\n';

    intStack->push(7);
    intStack->push(8);

    std::cout << "Stack is empty: " << intStack->isEmpty() << '\n';

    std::cout << intStack->pop() << '\n';
    std::cout << intStack->pop() << '\n';
    std::cout << intStack->pop() << '\n';
    std::cout << intStack->pop() << '\n';
    std::cout << intStack->pop() << '\n';

    std::cout << "Stack is empty: " << intStack->isEmpty() << '\n';

    try
    {
        std::cout << intStack->pop() << '\n';
    }
    catch (const StackUnderFlow& e)
    {
        std::cout << e.what() << '\n';
    }

    delete intStack;
}

void testQueue()
{
    std::cout << "Queue Test--------------------\n";

    Queue<std::string>* strQueue = new QueueArray<std::string>(5);
	
	std::cout << "Queue is empty: " << strQueue->isEmpty() << '\n';

    strQueue->enQueue("ab");
    strQueue->enQueue("cd");
    strQueue->enQueue("ef");
    strQueue->enQueue("gh");
    strQueue->enQueue("ij");

    try
    {
        strQueue->enQueue("lm");
    }
    catch (const QueueOverFlow& e)
    {
        std::cout << e.what() << '\n';
    }

    std::cout << strQueue->deQueue() << '\n';
    std::cout << strQueue->deQueue() << '\n';

    strQueue->enQueue("lm");
    strQueue->enQueue("no");

    std::cout << "Queue is empty: " << strQueue->isEmpty() << '\n';

    std::cout << strQueue->deQueue() << '\n';
    std::cout << strQueue->deQueue() << '\n';
    std::cout << strQueue->deQueue() << '\n';
    std::cout << strQueue->deQueue() << '\n';
    std::cout << strQueue->deQueue() << '\n';

    std::cout << "Queue is empty: " << strQueue->isEmpty() << '\n';

    try
    {
        std::cout << strQueue->deQueue() << '\n';
    }
    catch (const QueueUnderFlow& e)
    {
        std::cout << e.what() << '\n';
    }

    delete strQueue;
}