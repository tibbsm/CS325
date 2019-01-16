#include <stdio.h>
#include <stdlib.h>

int main() {

	FILE *infile;
	int size;

	infile =fopen("tsp_example_3.txt","r");
	if (!infile)
		return 1;

    while(!feof(infile)) {
        fscanf(infile,"%d%*[^\n]", &size);
    } 
    fclose(infile);
    size++;

    int tmp;
    int ncity[size];
    int x[size];
    int y[size]; 

    infile =fopen("tsp_example_3.txt","r");
    for (int i = 0; i < size; i++) {
    	fscanf(infile,"%d", &tmp);
    	ncity[i] = tmp;
    	
    	fscanf(infile,"%d", &tmp);
    	x[i] = tmp;

    	fscanf(infile,"%d", &tmp);
    	y[i] = tmp;
    } 
    fclose(infile);
 
    for (int i = 0; i < size; i++) {
    	printf("%d ", ncity[i]);
    	printf("%d ", x[i]);
    	printf("%d \n", y[i]);
    } 


	fclose(infile);
	return 0;
}
