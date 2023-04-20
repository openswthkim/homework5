/* postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>


#define MAX_STACK_SIZE 10   
#define MAX_EXPRESSION_SIZE 20  

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
   lparen = 0,  /* ( 왼쪽 괄호 */
   rparen = 9,  /* ) 오른쪽 괄호*/
   times = 7,   /* * 곱셈 */
   divide = 6,  /* / 나눗셈 */
   plus = 5,    /* + 덧셈 */
   minus = 4,   /* - 뺄셈 */
   operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE]; 
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE]; // 배열 선언

int postfixStackTop = -1; // 정수형 변수 선언 후 -1로 초기화
int evalStackTop = -1;
int evalResult = 0;

void postfixpush(char x); 
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();


int main()
{
   
   char command;

   printf("[----- [Taehyung Kim] [2020039024] -----]");

   do {
        printf("----------------------------------------------------------------\n");
        printf("               Infix to Postfix, then Evaluation               \n");
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'i': case 'I': // i일 경우
         getInfix(); // getInfix 함수 호출
         break;
      case 'p': case 'P': // p일 경우
         toPostfix();
         break;
      case 'e': case 'E': // e일 경우
         evaluation(); // evaluation 함수 호출
         break;
      case 'd': case 'D': // d일 경우
         debug(); // debug 함수 호출
         break;
      case 'r': case 'R': // r일 경우
         reset(); // reset 함수 호출
         break;
      case 'q': case 'Q': // q일 경우
         break; // 종료
      default:
         printf("\n       >>>>>   Concentration!!   <<<<<     \n");
         break;
      }

   } while (command != 'q' && command != 'Q');

   return 1;
}

void postfixPush(char x)
{
   postfixStack[++postfixStackTop] = x; //x값을 배열을 증가시킨 위치에 저장
}

char postfixPop()
{
   char x;
   if (postfixStackTop == -1) // postfixStackTop이 공백일 때
      return '\0';
   else {
      x = postfixStack[postfixStackTop--]; // x값을 배열을 감소시킨 위치에 저장
   }
   return x;
}

void evalPush(int x)
{
   evalStack[++evalStackTop] = x; // evalStack 배열을 증가시킨 위치에 x값 저장
}

int evalPop()
{
   if (evalStackTop == -1) // evalStackTop이 -1이면
      return -1; // -1값 반환
   else
      return evalStack[evalStackTop--]; // 배열에 저장된 값 반환
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
   printf("Type the expression >>> ");
   scanf("%s", infixExp); // 값 입력받기
}

precedence getToken(char symbol)
{
   switch (symbol) { // 우선순위반환하는 switch 조건문
   case '(': return lparen;
   case ')': return rparen;
   case '+': return plus;
   case '-': return minus;
   case '/': return divide;
   case '*': return times;
   default: return operand;
   }
}

precedence getPriority(char x)
{
        return getToken(x); // getToken값 반환
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
   if (postfixExp == '\0') // postfixExp값이 NULL이면
      strncpy(postfixExp, c, 1); // postfixExp에 문자열 1개 복사
   else
      strncat(postfixExp, c, 1); // postfixExp에 문자열 붙여넣기
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
   char* exp = infixExp; // 포인터에 infixExp 저장
   char x; // 임시로 값 저장할 변수 선언

   /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
   while (*exp != '\0')
   {
      if (getPriority(*exp) == operand) // getPriority의 반환값이 operand 일 경우
      {
         x = *exp; // x에 *exp를 저장
         charCat(&x); // chatCat 함수 호출
      }

      else if (getPriority(*exp) == lparen)
      {
         postfixPush(*exp); // postfixPush 함수 호출
      }

      else if (getPriority(*exp) == rparen)
      {
         while ((x = postfixPop()) != '(') // postfixPop의 반환값을 저장하고 x가 (가 아닐동안 반복
        {
            charCat(&x);
        }
      }
      else
      {
         while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) // postfix의 우선순위가 *exp의 우선순위보다 높을동안
         {
            x = postfixPop(); // x에 postfixPop함수값 저장
            charCat(&x); // charCat 함수 호출
         }
         postfixPush(*exp); // *exp를 postfixStack에 push함
      }
      exp++; // exp값 증가
   }

   while (postfixStackTop != -1) // postfixStackTop이 -1이 아닐 동안
   {
      x = postfixPop(); // x에 postfixPop값 저장
      charCat(&x);
   }
}

//infixExp,postfixExp,eavl result,postfixStack 출력하는 함수
void debug()
{
   printf("\n---DEBUG\n");
   printf("infixExp =  %s\n", infixExp);
   printf("postExp =  %s\n", postfixExp);
   printf("eval result = %d\n", evalResult);

   printf("postfixStack : ");
   for (int i = 0; i < MAX_STACK_SIZE; i++) // 스택의 크기만큼 반복
   {
      printf("%c  ", postfixStack[i]);
   }
   printf("\n");
}

void reset()
{
   infixExp[0] = '\0';
   postfixExp[0] = '\0';

   for (int i = 0; i < MAX_STACK_SIZE; i++) // 배열의 크기만큼 반복
   {
      postfixStack[i] = '\0'; // postfixStack에 NULL 저장
   }

   postfixStackTop = -1; // 초기값 저장
   evalStackTop = -1; // 초기값 저장
   evalResult = 0; // 초기값 저장
}


void evaluation()
{
   int opr1, opr2, i; // 정수형 변수 선언

   int length = strlen(postfixExp); // 정수형 변수에 postfixExp 길이 저장
   char symbol;
   evalStackTop = -1; // 변수값 초기화

   for (i = 0; i < length; i++) // postfixExp의 길이만큼 반복
   {
      symbol = postfixExp[i]; // 값 대입
      if (getToken(symbol) == operand) // 지정된 연산자 외 다른 값이 입력되면
      {
         evalPush(symbol - '0'); // 연산자 값을 push
      }

      else
      {

        opr2 = evalPop(); // evalStack Pop하여 opr2에 저장
		opr1 = evalPop(); // evalStack Pop하여 opr1에 저장
		switch(getToken(symbol)) { //getToken의 반환값에 따른 switch 조건문
		case plus: evalPush(opr1 + opr2); break; 
		case minus: evalPush(opr1 - opr2); break;
		case times: evalPush(opr1 * opr2); break;
		case divide: evalPush(opr1 / opr2); break;
        default: break;
         }
      }
   }


   evalResult = evalPop();
}