/***********************************************
 * 
 *  markdown codeblock saver
 * 
 ***********************************************/
    // read in file from argv[1]
    // check if directory by same name already exists
    // create directory and name it for MD file
    // foreach codeblock in MD, create a file named file1, file2, etc.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    // Check if the filename was specified
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get the extension of the filename
    char *extension = strrchr(argv[1], '.');

    // Check if the extension is md
    // if (extension == NULL || strcmp(extension, ".md") != 0) {
    //     printf("The file %s is not of type md.\n", argv[1]);
    //     return 1;
    // }

  // Check if the extension is md or MD
  if (strcmp(extension, ".md") != 0 && strcmp(extension, ".MD") != 0) {
    printf("The filename must have an md or MD extension.\n");
    exit(1);
  }





    // open MD file
    FILE *mdfp;
    mdfp = fopen(argv[1], "r");
    if (mdfp == NULL) {
        perror("Unable to open file!");
        exit(1);
    }



//   if (mkdir(dirname, 0777) != 0) {
//     perror("mkdir");
//     exit(1);
//   }

    // create output directory named for MD file
    // Create a directory with the same name as the basename of the specified md file
    char *dirname = strtok(argv[1], ".");
    // char *dirname = basename(argv[1]);


    //strcpy(dirname,argv[1]);
    //sprintf(dirname,"%s_TEST",argv[1]);
    struct stat st = {0};
    if (stat(dirname, &st) == -1) {
        mkdir(dirname, 0700);
        chdir(dirname);
    }

    // create a file for each codeblock
    FILE *fp;
    char filename[128] = "";
    int i=0;
    bool in_codeblock = false;

    char *textRead = malloc(st.st_size);
    while (fscanf(mdfp, "%[^\n] ", textRead) != EOF) {
        // printf("scanning %s\n",textRead);
        if (textRead[0]=='`' && textRead[1]=='`' && textRead[2]=='`') {
            if (in_codeblock == true) {
                in_codeblock = false;
                i++;
                fclose(fp);
            } else {
                in_codeblock = true;
                sprintf(filename,"file_%2.2i",i);
                fp = fopen(filename, "w");
                continue;
            }
        }
        if (in_codeblock == true) {
            fprintf(fp, "%s\n", textRead);
        }
    }
    
    // fclose(mdfp);



    return 0;
}

