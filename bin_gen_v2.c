#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>



//PROTOTYPE
int strcmp (const char* str1, const char* str2);

struct bin
{
    int lo;
    int hi;
    int counter;
};

int generate_bins(int max, int number_of_bins, struct bin bins[])
{
    int i;
    int min = 0;
    int bins_size[number_of_bins];

    int even_length = (max-min+1)/number_of_bins;
    //max = 99, min = 0, number_of_bins = 5
    //ognuno lo faccio largo evel_length = 20
    for(i=0; i<number_of_bins; ++i)
        bins_size[i] = even_length;

    /* distribute surplus as evenly as possible across buckets */
    int surplus = (max-min+1)%number_of_bins;
    //surplus = 0
    for(i=0; surplus>0; --surplus, i=(i+1)%number_of_bins)
        bins_size[i] += 1; 

    int n=0, k=min;
    for(i=0; i<number_of_bins && k<=max; ++i, ++n){
        bins[i].lo=k;
        bins[i].hi=k+bins_size[i]-1;
        k += bins_size[i];
        bins[i].counter = 0;
    }
    return n;
}

int increment_bin(int number, int number_of_bins, struct bin bins[]) {
    int i;
    for(i=0; i<number_of_bins; ++i)
        if(number >= bins[i].lo && number <= bins[i].hi){
            bins[i].counter = bins[i].counter + 1;
            return bins[i].counter;
        }
    return number_of_bins;
}


#define MAX_NUMBER_OF_BINS 524288  

int main(int argc, char *argv[]) {
    int i;
    struct bin bins[MAX_NUMBER_OF_BINS];

    char *target_field = argv[1];
    
    int field_size = 0;
    if(strcmp(target_field, "FL") == 0){
        field_size = pow(2, 20);
    }
    else if(strcmp(target_field, "TC") == 0){
        field_size = pow(2, 8);
    }
    else if(strcmp(target_field, "HL") == 0){
        field_size = pow(2, 8);
    }


    int number_of_bins = atoi(argv[2]);
    int number = atoi(argv[3]);

    int n = generate_bins(field_size-1, number_of_bins, bins);
    for(i=0; i<number_of_bins; i++) {
        if(i<n)
            printf("%s[%d-%d]", i>0?",":"", bins[i].lo, bins[i].hi);
        else
            printf("%s[]", i>0?",":"");
    }
    printf("\n\n");

    int number_idx = increment_bin(number, n, bins);
    printf("%d\n", number_idx);
    //printf("method(%d)->[%d,%d]\n", number, ranges[number_idx].lo, ranges[number_idx].hi);

    return EXIT_SUCCESS;
}
