/**
 * circularQ.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 // 스택 사이즈를 정의

typedef char element; // char 변수 element 선언
typedef struct {
	element queue[MAX_QUEUE_SIZE]; // 구조체 배열 선언
	int front, rear;
}QueueType; // QueueType 


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();


int main(void)
{
	QueueType *cQ = createQueue(); // 구조체를 가리키는 포인터 변수 선언
	element data;

	char command;
   		printf("[----- [Taehyung Kim] [2020039024] -----]");
	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement(); // 요소 추가할 값 입력 받고 큐에 요소 추가
			enQueue(cQ, data); 
			break;
		case 'd': case 'D': 
			deQueue(cQ,&data); // 큐에서 요소 삭제
			break;
		case 'p': case 'P':
			printQ(cQ); // 큐에서 요소 출력
			break;
		case 'b': case 'B': // 큐에서 디버그 후 정보 출력
			debugQ(cQ);
			break;
		case 'q': case 'Q': // 종료하는 명령
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ; 
	cQ = (QueueType *)malloc(sizeof(QueueType)); // 구조체 동적 할당
	cQ->front = 0; // front 값 0으로 초기화
	cQ->rear = 0; // rear 값 0으로 초기화
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; // cQ가 NULL이면 1 반환
    free(cQ); // cQ 메모리 해제
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item); // 요소 추가할 값 입력 받음
	return item;
}


int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){  // front와 rear값이 같다면
		printf("Circular Queue is empty!"); // 출력
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ)
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) { // 증가시킨 rear이 front와 같으면
		printf(" Circular Queue is full!"); // 출력
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // 포인터 값을 1 증가
		cQ->queue[cQ->rear] = item;  // 큐에 데이터 삽입
	}
}

void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; // 포인터 값을 1 증가
		*item = cQ->queue[cQ->front]; // item의 주소에 front위치의 값 대입
		return;
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last; 

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; // first 증가시키기
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; // last 증가시키기

	printf("Circular Queue : [");

	i = first;
	while(i != last){ // i가 last가 아닐 동안
		printf("%3c", cQ->queue[i]); // queue[i] 값 출력
		i = (i+1)%MAX_QUEUE_SIZE; // i값을 증가시킨다

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) // 큐의 개수만큼 반복한다
	{
		if(i == cQ->front) { // i가 front와 같으면 
			printf("  [%d] = front\n", i); // i 출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // front, rear 출력
}