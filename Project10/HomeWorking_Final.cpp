#include <stdio.h>
#include <Windows.h>
#include <malloc.h>
#include <time.h>

struct d_Node {  //typedef -> 별칭을 지정해 준것 struct d_node 대신 Node 만 써줘도 됨
	int num;
	struct d_Node *prev; // 자기 자신을 가리키는 주소를 가진다.
	struct d_Node *next; // 그래서 prev,next를 사용해서 다른 구조체의 주소를 가리킬수 있도록 만든다
};

struct d_list {
	struct d_Node *head;
	struct d_Node *tail;
	int NumofData;
};

d_list *memo;

void init();
int list_cnt();
void list_insert_head(int);
void list_insert_tail(int);
void list_insert_index(int, int);
void list_delete_head();
void list_delete_tail();
void list_delete_data(int);
void list_delete_index(int);
void list_search_index(int);
void list_search_data(int);
void list_clear();
int* list_copy();
void display();
void list_sort_asc();
void list_sort_dsc();
void merge_asc(int, int, int);
void merge_sort_asc(int, int);
void merge_dsc();
void quick_sort_asc(int, int);
void quick_sort_dsc(int, int);
int partition(int, int);
int partition_dsc(int, int);

int main() {
	clock_t t1;
	clock_t t2;
	clock_t t3;
	clock_t t4;
	clock_t t5;
	clock_t t6;
	init();
	list_insert_tail(1);
	list_insert_head(0);
	list_insert_index(1, 3);
	list_insert_index(1, 5);
	list_insert_index(2, 6);
	list_delete_index(1);
	list_delete_index(1);
	list_delete_head();
	list_delete_tail();
	list_insert_head(1);
	list_insert_tail(1);
	list_delete_data(3);
	list_delete_data(1);
	list_insert_head(1);
	list_insert_tail(0);
	list_insert_head(1);
	list_insert_tail(1);
	list_search_index(1);
	list_insert_head(2);
	list_search_data(2);
	list_insert_index(1, 2);
	display();
	printf("\n");
	
	t1 = clock();
	list_sort_asc();
	t1 = clock() - t1;
	display();
	printf("Exchange sort_asc: ");
	printf("%f 초 걸렸습니다\n", ((float)t1) / (float)CLOCKS_PER_SEC);

	t2 = clock();
	list_sort_dsc();
	t2 = clock() - t2;
	display();
	printf("Exchange sort_dsc: ");
	printf("%f 초 걸렸습니다\n", ((float)t2) / (float)CLOCKS_PER_SEC);

	t3 = clock();
	merge_sort_asc(0, (memo->NumofData - 1));
	t3 = clock() - t3;
	display();
	printf("Merge sort_asc: ");
	printf("%f 초 걸렸습니다\n", ((float)t2) / (float)CLOCKS_PER_SEC);

	t4 = clock();
	merge_dsc();
	t4 = clock() - t4;
	display();
	printf("Merge sort_dsc: ");
	printf("%f 초 걸렸습니다\n", ((float)t4) / CLOCKS_PER_SEC);

	t5 = clock();
	quick_sort_asc(0, memo->NumofData - 1);
	t5 = clock() - t5;
	display();
	printf("Quick sort_asc: ");
	printf("%f 초 걸렸습니다\n", ((float)t5)/ CLOCKS_PER_SEC);

	t6 = clock();
	quick_sort_dsc(0, memo->NumofData - 1);
	t6 = clock() - t6;
	display();
	printf("Quick sort_dsc: ");
	printf("%f 초 걸렸습니다\n", ((float)t6) / CLOCKS_PER_SEC);

	system("pause");
	return 0;
}

void init() {
	memo = (d_list*)malloc(sizeof(d_list));
	memo->head = NULL;
	memo->tail = NULL;
	memo->NumofData = 0;
}

int list_cnt() {
	return memo->NumofData;
}

void list_insert_head(int data) {
	d_Node * prenode = memo->head;
	d_Node * newnode = (d_Node*)malloc(sizeof(d_Node));
	if (memo->NumofData == 0) {
		newnode->next = newnode;
		newnode->prev = newnode;
		memo->head = newnode;
		newnode->num = data;
	}
	else {
		if (prenode != NULL && memo->tail != NULL) {
			newnode->next = prenode;
			prenode->prev = newnode;
			memo->tail->next = newnode;
			newnode->prev = memo->tail;
			memo->head = newnode;
			newnode->num = data;
		}
		else if (prenode != NULL && memo->tail == NULL) {
			memo->tail = memo->head;
			memo->head = newnode;
			newnode->next = prenode;
			prenode->prev = newnode;
			prenode->next = newnode;
			newnode->prev = prenode;
			newnode->num = data;
		}
		else {
			newnode->next = memo->tail;
			newnode->prev = memo->tail;
			memo->tail->prev = newnode;
			memo->tail->next = newnode;
			memo->head = newnode;
			newnode->num = data;
		}
	}
	memo->NumofData++;
}

void list_insert_tail(int data) {
	d_Node * prenode = memo->tail;
	d_Node * newnode = (d_Node*)malloc(sizeof(d_Node));
	if (memo->NumofData == 0) {
		newnode->next = newnode;
		newnode->prev = newnode;
		memo->tail = newnode;
		newnode->num = data;
	}
	else {
		if (prenode != NULL && memo->head != NULL) {
			newnode->prev = prenode;
			newnode->next = memo->head;
			prenode->next = newnode;
			memo->head->prev = newnode;
			memo->tail = newnode;
			newnode->num = data;
		}
		else if (prenode != 0 && memo->head == NULL) {
			memo->head = prenode;
			newnode->prev = prenode;
			newnode->next = prenode;
			prenode->next = newnode;
			prenode->prev = newnode;
			memo->tail = newnode;
			newnode->num = data;
		}
		else {
			memo->head->next = newnode;
			memo->head->prev = newnode;
			newnode->prev = memo->head;
			newnode->next = memo->head;
			memo->tail = newnode;
			newnode->num = data;
		}
	}
	memo->NumofData++;
}

void list_insert_index(int position, int data) {
	d_Node * prenode = memo->tail;
	d_Node * newnode = (d_Node*)malloc(sizeof(d_Node));
	if (memo->NumofData == 0) {
		newnode->next = newnode;
		newnode->prev = newnode;
		memo->tail = newnode;
		newnode->num = data;
	}
	else {
		for (int i = 0; i < position; i++) { prenode = prenode->next; }
		newnode->next = prenode->next;
		newnode->prev = prenode;
		newnode->next->prev = newnode;
		prenode->next = newnode;
		newnode->num = data;
		if (position == memo->NumofData) {
			memo->tail = newnode; newnode->num = data;
		}
	}
	memo->NumofData++;
}

void list_delete_head()
{
	d_Node * prenode;
	d_Node * delnode = memo->head;
	if (memo->NumofData == 0) { printf("Error\n"); memo->head = NULL; }
	else {
		if (memo->head != NULL && memo->head != NULL) {
			if (memo->NumofData == 2) { prenode = memo->tail; prenode->next = prenode; prenode->prev = prenode; memo->head = memo->head; free(delnode); }
			else {
				memo->tail->next = delnode->next;
				delnode->next->prev = memo->tail;
				memo->head = delnode->next;
				free(delnode);
			}
		}
	}
	memo->NumofData--;
	if (memo->NumofData == 0) { memo->head = NULL; memo->tail = NULL; }
}

void list_delete_tail() {
	d_Node * prenode;
	d_Node * delnode = memo->tail;
	if (memo->NumofData == 0) { printf("Error\n"); memo->tail = NULL; }
	else {
		if (memo->head != NULL && memo->head != NULL) {
			if (memo->NumofData == 2) { prenode = memo->head; prenode->next = prenode; prenode->prev = prenode; memo->tail = memo->head; free(delnode); }
			else {
				memo->head = delnode->prev;
				delnode->prev->next = memo->head;
				memo->tail = delnode->prev;
				free(delnode);
			}
		}
	}
	memo->NumofData--;
	if (memo->NumofData == 0) { memo->head = NULL; memo->tail = NULL; }
}

void list_delete_data(int data) {
	int count = 0;
	d_Node * delnode = memo->head;
	d_Node * prenode = memo->head;
	if (memo->NumofData == 0) { printf("Error\n"); }
	else
	{
		for (int i = 0; i <= memo->NumofData; i++)
		{
			if (delnode->num == data) {
				prenode = delnode->prev;
				prenode->next = delnode->next;
				delnode->next->prev = prenode;
				count += 1;
				memo->NumofData--;
			}
			delnode = delnode->next;
		}
		if (count == 0) { printf("No Data\n"); }
	}
	if (memo->NumofData == 0) { memo->head = NULL; memo->tail = NULL; }
}

void list_delete_index(int num) {
	d_Node * delnode = memo->tail;
	d_Node * prenode = memo->tail;
	if (memo->NumofData == 0) { printf("Error\n"); }
	else
	{
		for (int i = 0; i < num; i++)
		{
			prenode = prenode->next;
		}
		delnode = prenode->next;
		prenode->next = delnode->next;
		delnode->next->prev = prenode;
		free(delnode);
		if (num == memo->NumofData - 1)
		{
			memo->tail = prenode;
		}
	}
	memo->NumofData--;
	if (memo->NumofData == 0) { memo->head = NULL; memo->tail = NULL; }
}

void display() {
	int i;
	d_Node *node;
	if (memo->NumofData == 0) { printf("NULL LIST\n"); return; }
	for (node = memo->tail->next, i = 0; i < memo->NumofData; node = node->next, i++)
	{
		printf("%d  ", node->num);
	}
	printf("\n");
}

void list_search_index(int index) {
	d_Node* prenode = memo->tail;
	if (memo->NumofData == 0) { printf("Error\n"); }
	else
	{
		if (index <= memo->NumofData) {
			for (int i = 0; i < index; i++) { prenode = prenode->next; }
			printf("Searching Index Number : %d\n", prenode->next->num);
		}
		else { printf("There is No your index\n"); }
	}
}

void list_search_data(int data) {
	int count = 0;
	d_Node* prenode = memo->tail;
	if (memo->NumofData == 0) { printf("Error\n"); }
	else
	{
		for (int i = 0; i < memo->NumofData; i++)
		{
			if (prenode->next->num == data) { printf("%d번째\n", i); count += 1; }
			prenode = prenode->next;
		}
	}
	printf("%d개 보유중\n", count);
}

int* list_copy() {
	int num = memo->NumofData;
	int *arr = (int*)malloc(sizeof(int)*(memo->NumofData));
	d_Node *prenode = memo->head;
	printf("Copy : ");
	if (memo->NumofData != 0) {
		for (int i = 0; i < memo->NumofData; i++) {
			arr[i] = prenode->num;
			printf("arr[%d]=%d ", i, arr[i]);
			prenode = prenode->next;
		}
	}
	else { printf("복사할 데이터가 존재하지 않습니다.\n"); return NULL; }
	printf("\n");
	return arr;
}

void list_clear() {
	int count = 0;;
	d_Node*delnode = memo->head;

	for (int i = 0; i < memo->NumofData; i++) {
		d_Node* next = delnode->next;
		free(delnode);
		delnode = next;
		count += 1;
	}
	if ((memo->NumofData) - count == 0) { printf("ALL CLEAR\n"); memo->head = NULL; memo->tail = NULL; memo->NumofData = 0; }
}

void list_sort_asc() {
	d_Node * prenode = memo->head;
	d_Node * nextnode = memo->head;
	d_Node * tempnode = (d_Node*)malloc(sizeof(d_Node));
	for (int i = 0; i < memo->NumofData; i++) {
		for (int j = 0; j < memo->NumofData - 1; j++) {
			nextnode = nextnode->next;
			if (nextnode->num >= prenode->num) {
				tempnode->num = prenode->num;
				prenode->num = nextnode->num;
				nextnode->num = tempnode->num;
			}
		}
		prenode = prenode->next;
		nextnode = prenode;
	}
}

void list_sort_dsc() {
	d_Node * prenode = memo->head;
	d_Node * nextnode = memo->head;
	d_Node * tempnode = (d_Node*)malloc(sizeof(d_Node));
	for (int i = 0; i < memo->NumofData; i++) {
		for (int j = 0; j < memo->NumofData - 1; j++) {
			nextnode = nextnode->next;
			if (nextnode->num <= prenode->num) {
				tempnode->num = prenode->num;
				prenode->num = nextnode->num;
				nextnode->num = tempnode->num;
			}
		}
		prenode = prenode->next;
		nextnode = prenode;
	}

}

void merge_asc(int left, int mid, int right) {
	int *arr = (int*)malloc(sizeof(int)*memo->NumofData);
	d_Node * prenode = memo->head;
	d_Node * nextnode = memo->head;
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	for (int cri = 0; cri < i; cri++) {
		prenode = prenode->next;
	}
	for (int cri = 0; cri < j; cri++) {
		nextnode = nextnode->next;
	}
	while (i <= mid && j <= right) {
		if (prenode->num <= nextnode->num) {
			arr[k++] = prenode->num;
			prenode = prenode->next;
			i++;
		}
		else {
			arr[k++] = nextnode->num;
			nextnode = nextnode->next;
			j++;
		}
	}
	if (i > mid) {
		prenode = memo->head;
		for (int cri = 0; cri < j; cri++) { prenode = prenode->next; }
		for (l = j; l <= right; l++) { arr[k++] = prenode->num; prenode = prenode->next; }
	}
	else {
		prenode = memo->head;
		for (int cri = 0; cri < i; cri++) { prenode = prenode->next; }
		for (l = i; l <= mid; l++) { arr[k++] = prenode->num; prenode = prenode->next; }
	}
	prenode = memo->head;
	for (int cri = 0; cri < left; cri++) { prenode = prenode->next; }
	for (l = left; l <= right; l++) {
		prenode->num = arr[l];
		prenode = prenode->next;
	}
}

void merge_sort_asc(int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort_asc(left, mid);
		merge_sort_asc(mid + 1, right);
		merge_asc(left, mid, right);
	}
}

void merge_dsc() {
	int num;
	d_Node*tail = memo->tail;
	d_Node*head = memo->head;
	merge_sort_asc(0, memo->NumofData - 1);

	for (int i = 0; i <= (memo->NumofData) / 2; i++) {
		num = head->num;
		head->num = tail->num;
		tail->num = num;
		head = head->next;
		tail = tail->prev;
	}
}

void quick_sort_asc(int left, int right) {
	if (left < right) {
		int part = partition(left, right);
		quick_sort_asc(left, part - 1);
		quick_sort_asc(part + 1, right);
	}
}

int partition(int left, int right) {
	d_Node* prenode = memo->head;
	d_Node*nextnode = memo->head;
	d_Node*pivotnode = memo->head;
	int first = left;
	int pivot = first;
	int temp;
	left++;
	for (int i = 0; i < left; i++) { prenode = prenode->next; }
	for (int i = 0; i < right; i++) { nextnode = nextnode->next; }
	for (int i = 0; i < pivot; i++) { pivotnode = pivotnode->next; }
	while (left <= right) {
		while (prenode->num <= pivotnode->num && left < right) { left++; prenode = prenode->next; }
		while (nextnode->num > pivotnode->num && left <= right) { right--; nextnode = nextnode->prev; }

		if (left < right) {
			prenode = memo->head; nextnode = memo->head;
			for (int i = 0; i < left; i++) { prenode = prenode->next; }
			for (int i = 0; i < right; i++) { nextnode = nextnode->next; }
			temp = prenode->num; prenode->num = nextnode->num; nextnode->num = temp;
		}
		else break;
	}
	prenode = memo->head;
	nextnode = memo->head;

	for (int i = 0; i < first; i++) { prenode = prenode->next; }
	for (int i = 0; i < right; i++) { nextnode = nextnode->next; }
	temp = prenode->num; prenode->num = nextnode->num; nextnode->num = temp;
	return right;
}

void quick_sort_dsc(int left, int right) {
	if (left < right) {
		int part = partition_dsc(left, right);
		quick_sort_dsc(left, part - 1);
		quick_sort_dsc(part + 1, right);
	}
}

int partition_dsc(int left, int right) {
	d_Node* prenode = memo->head;
	d_Node*nextnode = memo->head;
	d_Node*pivotnode = memo->head;
	int first = left;
	int pivot = first;
	int temp;
	left++;
	for (int i = 0; i < left; i++) { prenode = prenode->next; }
	for (int i = 0; i < right; i++) { nextnode = nextnode->next; }
	for (int i = 0; i < pivot; i++) { pivotnode = pivotnode->next; }
	while (left <= right) {
		while (prenode->num >= pivotnode->num && left < right) { left++; prenode = prenode->next; }
		while (nextnode->num < pivotnode->num && left <= right) { right--; nextnode = nextnode->prev; }

		if (left < right) {
			prenode = memo->head; nextnode = memo->head;
			for (int i = 0; i < left; i++) { prenode = prenode->next; }
			for (int i = 0; i < right; i++) { nextnode = nextnode->next; }
			temp = prenode->num; prenode->num = nextnode->num; nextnode->num = temp;
		}
		else break;
	}
	prenode = memo->head;
	nextnode = memo->head;

	for (int i = 0; i < first; i++) { prenode = prenode->next; }
	for (int i = 0; i < right; i++) { nextnode = nextnode->next; }
	temp = prenode->num; prenode->num = nextnode->num; nextnode->num = temp;
	return right;
}
