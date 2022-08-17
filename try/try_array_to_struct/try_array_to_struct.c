#include <stdio.h>

typedef struct
{
	int size;
	int id[];
} right_t;

typedef struct
{
	int size;
	int *id;
} wrong_t;

typedef struct{
	int id;
} wrong_1_t;

int main() {
	int data[6] = {5, 1, 2, 3, 4, 5};
	int* data_ptr = (int *)data;
	printf("data_ptr is %d\n", *data_ptr);
	right_t *data_hoslam = (right_t *)data;
	printf("id is %d\n", *((*data_hoslam).id));
	for (int i=0; i<5; i++)
		printf("size is %d, id[i] is %d\n", data_hoslam->size, (*data_hoslam).id[i]);

	wrong_t data_hoslam_wrong;
	wrong_t *data_hoslam_wrong_ptr = &data_hoslam_wrong;
	int data1[2] = {5, 1};
	data_hoslam_wrong_ptr = (wrong_t *)data1;
	wrong_1_t *data2 = (wrong_1_t *)data1;
	int *data3 = (int *)data1;
	printf("size is %d\n", data_hoslam_wrong_ptr->size);
	printf("id is %d\n", data2->id);
	printf("id is %d\n", *data3);
	// for (int i = 0; i < 5; i++)
	// 	printf("size is %d, id[i] is %d\n", data_hoslam_wrong_ptr->size, (*data_hoslam_wrong_ptr).id[i]);
}