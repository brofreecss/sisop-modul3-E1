#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

char nama_file [1000];

void* periksa(void* arg){
	char* needle;
	needle = (char*) arg;

	char buffer[10000];
	strcpy(buffer,"cat ");
	strcat(buffer,nama_file);		//tambah nama file
	strcat(buffer," | grep -o ");
	strcat(buffer, needle);			//tambah string yang mau dicari
	strcat(buffer, " | wc -l");

	printf("%s :" ,needle);
	system(buffer);
}

int main(int argc, char const *argv[])
{
	int i;

	// jangan lupa input nama file
	strcpy(nama_file,"novel.txt");

	pthread_t tid[10];
	int tid_stat[10];
	for(i=0;i<argc-1;++i){
		tid_stat[i] = pthread_create(&tid[i],NULL,periksa,(void*)argv[i+1]);
		if(tid_stat[i]){ // jika gagal
			//kasi error
			fprintf(stderr,"gagal wtf %d\n",tid_stat[i]);
			exit(EXIT_FAILURE);
		}
		pthread_join(tid[i],NULL);
	}
	return 0;
}