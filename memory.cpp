#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <iostream>
using namespace std;

void directoryOp(char[]);
void createStat(char *);
void insertArray(char *,struct stat *);

const int maxNums = 100;
long memArray[maxNums];
//EZ: SHould not use a fixed size array...

int main(int argc,char *argv[]) {

        if(argc == 1)
                directoryOp(".");
        else
                while(--argc) {
                        printf("%s:\n",*++argv);
                        directoryOp(*argv);
                }

        double bin1count=0, bin2count=0, bin3count=0, bin4count=0, bin5count=0;
        int bin1[maxNums];
        int bin2[maxNums];
        int bin3[maxNums];
        int bin4[maxNums];
        int bin5[maxNums];
        double total;

        for(int i=0; i<maxNums; i++){
                if(memArray[i] >= 0 && memArray[i] <= 256){
                        bin1[i] = memArray[i];
                //      cout << "bin1" << endl;
                        bin1count++;
                }else
                if(memArray[i] > 256 && memArray[i] <= 1024){
                        bin2[i] = memArray[i];
                //      cout << "bin2" << endl;
                        bin2count++;
                }else
                if(memArray[i] > 1024 && memArray[i] <= 4096){
                        bin3[i] = memArray[i];
                //      cout << "bin3" << endl;
                        bin3count++;
                }else
                 if(memArray[i] > 4096 && memArray[i] <= 8192){
                        bin4[i] = memArray[i];
                //      cout << "bin4" << endl;
                        bin4count++;
                }else
                if(memArray[i] > 8192){
                        bin5[i] = memArray[i];
                //      cout << "bin5" << endl;
                        bin5count++;
                }

        }

        total = bin1count + bin2count + bin3count + bin4count + bin5count;

        cout << "\n\nRange(kb)  num_of_files    percentage(%)" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "   0-256           "      <<  bin1count <<  "              " << bin1count/total << "            " << endl;
        cout << "  256-1024          "      <<  bin2count <<  "               " << bin2count/total << "            " << endl;
        cout << " 1024-4096         "      <<  bin3count <<  "              " << bin3count/total << "            " << endl;
        cout << "4096-8192          "      <<  bin4count <<  "               " << bin4count/total << "            " << endl;
        cout << "  8192+            "      <<  bin5count <<  "               " << bin5count/total << "            " << endl;
        return 0;

}

void directoryOp(char dirname[]) {

        DIR * directoryPtr;
        struct dirent *entry;

        directoryPtr = opendir(dirname);
        while((entry = readdir(directoryPtr)) != NULL)
                        createStat(entry -> d_name);
                closedir(directoryPtr);
}

void createStat(char *filename) {

        struct stat info;
        if(stat(filename,&info)==-1)
                perror(filename);
        else
                insertArray(filename,&info);
}


void insertArray(char *filename,struct stat * info_p) {

        static int count = 0;
        int number = info_p->st_size;
        memArray[count] = number;
        printf("%8ld",(long)info_p -> st_size);
        count++;

}
