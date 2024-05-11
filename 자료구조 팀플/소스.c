#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//����ü ������ �̸� �����Ҵ��� �ȵ�
typedef struct stack_frame {

	char* char_stack;
	int* int_stack;
	struct stack_frame* link;
}stack_frame;


void show_current_state(stack_frame* new_frame) {



	for (stack_frame* p = new_frame; p != NULL; p = p->link) {
		printf("ù ������ to: %c", p->char_stack[0]);
		printf("  �ι�° ������ tmp: %c", p->char_stack[1]);
		printf("  ����° ������  from: %c", p->char_stack[2]);
		printf("  �׹�° ������  n: %d\n", p->int_stack[0]);
		printf("����� ���� ������ ->    ");
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

	//deleting_frame = deleting_frame->link; �� �κп��� ���ϴ� ����� ������ ����

	return deleting_frame->link;
}


stack_frame* new_stack_frame_and_push(stack_frame* previous_frame, int stack_number, char from, char tmp, char to) {

	stack_frame* new_stack_frame = (stack_frame*)malloc(sizeof(stack_frame));  //���ο� ���� ������ ����

	new_stack_frame->char_stack = (char*)malloc(sizeof(char) * 4);
	new_stack_frame->int_stack = (int*)malloc(sizeof(int) * 2);

	//���� �����Ͱ� ������ �׾ư�.
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

		

		frame = new_stack_frame_and_push(frame, n - 1, from, to, tmp);  //���� ������ ����

		to = frame->char_stack[0];  //�� �Լ� ������ from, tmp, to ����
		tmp = frame->char_stack[1];
		from = frame->char_stack[2];
		n = frame->int_stack[0];

		hanoi_stack_frame(frame, n, from, tmp, to);

		printf("���� %d�� %c���� %c�� �ű��.\n", n, from, to);
		
		to = frame->char_stack[0];  //�� �Լ� ������ from, tmp, to ����
		tmp = frame->char_stack[1];
		from = frame->char_stack[2];
		n = frame->int_stack[0];

		hanoi_stack_frame(frame, n, tmp, from, to);
		//hanoi_stack_frame(frame, n, from, tmp, to); //���� hanoi �ڵ��� ����Լ�(n-1, from, tmp, to)�� ����. n-1ó���� ���� �Ŀ� ����
													//�׷��� ������ �̹� ���� �ٲ� �� �����ؼ� ���� �״�� ��ߵ�      

		//to = frame->char_stack[0];  //�� �Լ� ������ from, tmp, to ����
		//tmp = frame->char_stack[1];
		//from = frame->char_stack[2];
		//n = frame->int_stack[0];

	}

	else  {  //n==1�� ��
		//frame = new_stack_frame_and_push(frame, n, from, tmp, to);

		to = frame->char_stack[0];  //�� �Լ� ������ from, tmp, to ����
		tmp = frame->char_stack[1];
		from = frame->char_stack[2];
		n = frame->int_stack[0];

		printf("���� 1�� %c ���� %c���� �ű��.\n", from, to);
		frame = stack_frame_pop(frame); //������ �������������� ���ƿ� 

		to = frame->char_stack[0];  //�� �Լ� ������ from, tmp, to ����
		tmp = frame->char_stack[1];
		from = frame->char_stack[2];
		n = frame->int_stack[0];
		printf("���� %d�� %c���� %c�� �ű��.\n", n, from, to);

		//hanoi_stack_frame(frame, n, from, tmp, to);
		//printf("���� %d�� %c���� %c�� �ű��.\n", n, from, to);
	}

	/***
	hanoi_stack_frame(frame, n, to, from, tmp);

	to = frame->char_stack[0];  //�� �Լ� ������ from, tmp, to ����
	tmp = frame->char_stack[1];
	from = frame->char_stack[2];
	n = frame->int_stack[0];


	frame = stack_frame_pop(frame); //���� �������� �������� ������ �׸�

	to = frame->char_stack[0];  //�� �Լ� ������ from, tmp, to ����
	tmp = frame->char_stack[1];
	from = frame->char_stack[2];
	n = frame->int_stack[0];
	****/
}
int main(void) {
	stack_frame* Top = NULL;
	hanoi_stack_frame(Top, 3, 'A', 'B', 'C');
}

