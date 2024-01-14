#include <merge.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h> //floor(double) function
#include "chunk.h"
#include "record.h"
#include "bf.h"
#include "hp_file.h"



void Init_Record_Iterators(int size,CHUNK_Iterator iterator,int current_loop)
{
    CHUNK chunk;

    //we must go in the number of chunk so we initilize right
    

}

CHUNK_RecordIterator *Create_Record_Iterators(int bWay,int number_of_chunk_in_file,int loop_number,int loops_to_merge,int *size)
{
    CHUNK_RecordIterator *record_iterator;

    //if we are in the last loop we must make less record iterator /else we use the defoult
    int iterators_to_create = (loop_number == loops_to_merge-1) ? number_of_chunk_in_file - (bWay * loops_to_merge) : bWay;
    *size = iterators_to_create;

    record_iterator = malloc(sizeof(CHUNK_RecordIterator) * iterators_to_create);

    return record_iterator;
}


void merge(int file_desc, int chunkSize, int bWay, int output_fd) {
    
    //we create a chunk iterator so we make the chunks with the data
    CHUNK_Iterator iterator = CHUNK_CreateIterator(file_desc,chunkSize);
    CHUNK inputChunk;

    //find out how many loops we must do to merge using at most bWay chunks per time
    double estimate_loops =  Arraysize() / (double)bWay;
    int loops_to_merge = (int)(floor(estimate_loops) == estimate_loops) ? estimate_loops : estimate_loops + 1;
    int size;

    //we use a array of record itaratos (one for every chunk)
    CHUNK_RecordIterator *record_iterator = NULL;
    
    //here we start the merge algorith based on the loops we calculate earlyer
    for(int i = 0; i < loops_to_merge; i++)
    {
        free(record_iterator);
        record_iterator = NULL;
        record_iterator = Create_Record_Iterators(bWay,Arraysize(),i,loops_to_merge,&size);

        //we initilize the records iterators with the right data
        Init_Record_Iterators(size,iterator,i+1);


    }

    if(record_iterator != NULL)
        free(record_iterator);

}


