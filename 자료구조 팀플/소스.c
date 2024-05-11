#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//구조체 내에서 미리 동적할당이 안됨
typedef struct stack_frame {

	char* char_stack;
	int* int_stack;
	struct stack_frame* link;
}stack_frame;


void show_current_state(stack_frame* new_frame) {



	for (stack_frame* p = new_frame; p != NULL; p = p->link) {
		printf("첫 데이터 to: %c", p->char_stack[0]);
		printf("  두번째 데이터 tmp: %c", p->char_stack[1]);
		printf("  세번째 데이터  from: %c", p->char_stack[2]);
		printf("  네번째 데이터  n: %d\n", p->int_stack[0]);
		printf("연결된 스택 프레임 ->    ");
	}
	printf("NULL\n");

}


stack_frame* stack_frame_pop(stack_frame* deleting_frame) {

	//deleting_frame->int_stack[0] = 0;
	free(deleting_frame->int_stack);
	deleting_frame->char_stack[2] = ' ';
	deleting_frame->char_stack[1] = ' ';
	deleting_frame->char_stack[0] = ' ';
	free(deleting_frame->char_stack);

	//deleting_frame = deleting_frame->link; 이 부분에서 원하는 결과가 나오지 않음

	return deleting_frame->link;
}


stack_frame* new_stack_frame_and_push(stack_frame* previous_frame, int stack_number, char from, char tmp, char to) {

	stack_frame* new_stack_frame = (stack_frame*)malloc(sizeof(stack_frame));  //새로운 스택 프레임 형성

	new_stack_frame->char_stack = (char*)malloc(sizeof(char) * 4);
	new_stack_frame->int_stack = (int*)malloc(sizeof(int) * 2);

	//스택 포인터가 스택을 쌓아감.
	new_stack_frame->char_stack[0] = to;
	new_stack_frame->char_stack[1] = tmp;
	new_stack_frame->char_stack[2] = from;
	new_stack_frame->int_stack[0] = stack_number;

	new_stack_frame->link = previous_frame;

	show_current_state(new_stack_frame);

	return new_stack_frame;
}



void hanoi_stack_frame(stack_frame* frame, int n, char from, char tmp, char to)
{
	if (n > 1) {

		

		frame = new_stack_frame_and_push(frame, n - 1, from, to, tmp);  //스택 프레임 생성

		to = frame->char_stack[0];  //이 함수 내에서 from, tmp, to 갱신
		tmp = frame->char_stack[1];
		from = frame->char_stack[2];
		n = frame->int_stack[0];

		hanoi_stack_frame(frame, n, from, tmp, to);

		printf("원판 %d를 %c에서 %c로 옮긴다.\n", n, from, to);
		
		to = frame->char_stack[0];  //이 함수 내에서 from, tmp, to 갱신
		tmp = frame->char_stack[1];
		from = frame->char_stack[2];
		n = frame->int_stack[0];

		hanoi_stack_frame(frame, n, tmp, from, to);
		//hanoi_stack_frame(frame, n, from, tmp, to); //원래 hanoi 코드의 재귀함수(n-1, from, tmp, to)와 같음. n-1처리는 위의 식에 있음
													//그런데 위에서 이미 변수 바뀐 걸 갱신해서 원판 그대로 써야됨      

		//to = frame->char_stack[0];  //이 함수 내에서 from, tmp, to 갱신
		//tmp = frame->char_stack[1];
		//from = frame->char_stack[2];
		//n = frame->int_stack[0];

	}

	else  {  //n==1일 때
		//frame = new_stack_frame_and_push(frame, n, from, tmp, to);

		to = frame->char_stack[0];  //이 함수 내에서 from, tmp, to 갱신
		tmp = frame->char_stack[1];
		from = frame->char_stack[2];
		n = frame->int_stack[0];

		printf("원판 1을 %c 에서 %c으로 옮긴다.\n", from, to);
		frame = stack_frame_pop(frame); //이전의 스택프레임으로 돌아옴 

		to = frame->char_stack[0];  //이 함수 내에서 from, tmp, to 갱신
		tmp = frame->char_stack[1];
		from = frame->char_stack[2];
		n = frame->int_stack[0];
		printf("원판 %d를 %c에서 %c로 옮긴다.\n", n, from, to);

		//hanoi_stack_frame(frame, n, from, tmp, to);
		//printf("원판 %d를 %c에서 %c로 옮긴다.\n", n, from, to);
	}

	/***
	hanoi_stack_frame(frame, n, to, from, tmp);

	to = frame->char_stack[0];  //이 함수 내에서 from, tmp, to 갱신
	tmp = frame->char_stack[1];
	from = frame->char_stack[2];
	n = frame->int_stack[0];


	frame = stack_frame_pop(frame); //스택 프레임이 없어지는 과정을 그림

	to = frame->char_stack[0];  //이 함수 내에서 from, tmp, to 갱신
	tmp = frame->char_stack[1];
	from = frame->char_stack[2];
	n = frame->int_stack[0];
	****/
}
int main(void) {
	stack_frame* Top = NULL;
	hanoi_stack_frame(Top, 3, 'A', 'B', 'C');
}

