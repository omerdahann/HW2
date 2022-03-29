#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Worker
{
	long unsigned ID;
	char* name;
	long unsigned salary;
	long unsigned year;

}Worker;

Worker* CreateWorker()
{
	Worker* Ptr = (Worker*)malloc(sizeof(Worker));
	if (!Ptr) { printf("Fail\n"); exit(0); };
	printf("Enter ID:");
	scanf("%u", &(Ptr->ID));
	Ptr->name = (char*)malloc(20);
	if (!Ptr->name) { printf("Fail\n"); exit(0); };
	printf("Enter Name:");
	scanf("%19s", Ptr->name);
	Ptr->name = realloc(Ptr->name, strlen(Ptr->name) + 1);
	printf("Enter Salary:");
	scanf("%ul", &(Ptr->salary));
	printf("Enter Year:");
	scanf("%u", &(Ptr->year));
	return Ptr;
}

void PrintWorker(Worker* Worker) {
	if (Worker == NULL) {
		printf("Fail\n");
		return;
	}
	printf("ID:%d\n Name:%s\n Salary:%lu\n Years:%d\n", Worker->ID, Worker->name, Worker->salary, Worker->year);
}

typedef struct WorkerList {
	Worker* data;
	struct WorkerList* next;
}WorkerList;

WorkerList* addWorker(WorkerList* head, Worker* w)
{
	if (w == NULL) {
		printf("Fail\n");
		exit(1);
	}

	WorkerList* Ptr = (WorkerList*)malloc(sizeof(WorkerList));
	if (Ptr == NULL) { printf("Fail"); exit(1); };
	Ptr->data = w;
	Ptr->next = NULL;

	if (head == NULL) {
		return Ptr;
	}

	if (head->next == NULL) {
		if (head->data->salary <= w->salary) {
			Ptr->next = head;
			return Ptr;
		}
		else {
			head->next = Ptr;
			return head;
		}
	}

	WorkerList* temp = head;

	while (temp->next != NULL) {
		temp = temp->next;
	}
	if (head->data->salary > temp->data->salary) {
		temp = head;
		if (temp->data->salary <= w->salary) {
			Ptr->next = temp;
			return Ptr;
		}
		while (temp->next != NULL) {
			if (temp->next->data->salary <= w->salary) {
				Ptr->next = temp->next;
				temp->next = Ptr;
				return head;
			}
			else {
				temp->next = Ptr;
				return head;
			}
			temp = temp->next;
		}
		temp->next = w;
		return head;
	}
	else {
		temp = head;
		if (temp->data->salary >= w->salary) {
			Ptr->next = temp;
			return Ptr;
		}

		while (temp->next != NULL) {
			if (temp->next->data->salary >= w->salary) {
				Ptr->next = temp->next;
				temp->next = Ptr;
				return head;
			}
			else {
				temp->next = Ptr;
				return head;
			}
			temp = temp->next;
		}
		temp->next = w;
		return head;
	}
}

int index(WorkerList* head, long unsigned ID) {
	int counter = 0;
	while (head != NULL) {
		counter++;
		if (head->data->ID == ID) {
			return counter;
		}
		head = head->next;
	}
	return -1;
}

WorkerList* deleteWorstWorker(WorkerList* head) {
	WorkerList* temp = head;
	if (head == NULL)
		return NULL;

	if (head->next == NULL) {
		free(head);
		return NULL;
	}

	if (head->data->salary > head->next->data->salary) {
		while (temp->next->next != NULL) {
			temp = temp->next;
		}
		free(temp->next->data);
		temp->next = NULL;
	}
	else {
		head = head->next;
		free(temp->data);
	}
	return head;
}

void update_worker(WorkerList* head, float precent) {
	while (head != NULL) {
		head->data->salary += (head->data->salary) * precent;
		head = head->next;
	}
}

WorkerList* reverse(WorkerList* head) {
	if (head == NULL)
		return NULL;

	if (head->next == NULL)
		return head;

	WorkerList* Top = head;
	WorkerList* Mid = head->next;
	if (head->next->next == NULL) {
		Mid->next = Top;
		Top->next = NULL;
		head = Mid;
		return head;
	}

	WorkerList* bottom = head->next->next;
	while (bottom != NULL)
	{
		Mid->next = Top;
		Top = Mid;
		Mid = bottom;
		bottom = bottom->next;
	}
	Mid->next = Top;
	head->next = NULL;
	head = Mid;
	return head;
}

void freeWorkers(WorkerList* head) {
	if (head == NULL) {
		return;
	}

	if (head->next == NULL) {
		free(head->data);
		free(head);
	}

	WorkerList* temp = head->next;
	while (temp != NULL) {
		free(head->data);
		free(head);
		head = temp;
		temp = temp->next;
	}
	free(head->data);
	free(head);
}

void printListWorkers(WorkerList* head) {
	while (head != NULL) {
		PrintWorker(head->data);
		head = head->next;
	}
}

void main()
{
	printf("Check CreateWorker and PrintWorker:\n ");
	Worker* Worker1 = CreateWorker();
	Worker* Worker2 = CreateWorker();
	Worker* Worker3 = CreateWorker();
	Worker* Worker4 = CreateWorker();
	Worker* Worker5 = CreateWorker();
	PrintWorker(Worker1);
	PrintWorker(Worker2);
	PrintWorker(Worker3);
	PrintWorker(Worker4);
	PrintWorker(Worker5);
	printf("Check addWorker:\n ");
	WorkerList* Ptr = NULL;
	Ptr = addWorker(Ptr, Worker1);
	Ptr = addWorker(Ptr, Worker2);
	Ptr = addWorker(Ptr, Worker3);
	Ptr = addWorker(Ptr, Worker4);
	Ptr = addWorker(Ptr, Worker5);
	printListWorkers(Ptr);
	printf("Check index\n ");
	printf("The result:%d\n", index(Ptr, 208911958));
	printf("Check deleteWorstWorker\n ");
	Ptr = deleteWorstWorker(Ptr);
	printListWorkers(Ptr);
	printf("Check update_worker\n ");
	update_worker(Ptr, 0.5);
	printListWorkers(Ptr);
	printf("Check reverse\n ");
	Ptr = reverse(Ptr);
	printListWorkers(Ptr);
	printf("Check freeWorker\n ");
	freeWorkers(Ptr);
}