// menu.c - implements menu program, essentially takes input from user/system
// menu scripts and performs selected action. 
//
// Inputs: 
// 0 -> change password (from USER menu)
// 1 -> see purchase history (from USER menu)
// 2 -> access password (from SYSTEM menu)
// 3 -> see inventory (from SYSTEM menu)

    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

int main() {

  printf("Content-type: text/html\n\n");


  //The following block of code gets the input option from stdin and stores it in the
  //input variable. 

  char inputString[200];
  char input;
  int length = atoi(getenv("CONTENT_LENGTH"));
  
  length++;

  fgets(inputString,length,stdin);

  input = inputString[length - 2];

  
  //Change password
  if (input == '0'){ 
    printf("<html><head><title>Change Password</title></head>\n");
    printf("<body>change password code here</body></html>");
  
  }

  //Open up log.csv and display
  else if (input == '1'){

    printf("<html><head><title>Purchase History</title></head>\n");
    printf("<body><p>Purchase History: (log.csv) </p>\n");
    
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int counter = 0;
    ssize_t read;

    fp = fopen("log.csv", "r");

    //Print each line in file log.csv
    while ( (read = getline(&line,&len,fp)) != -1  && counter < 50){

      printf("%s<br>",line);
      counter++;
    
    }

   fclose(fp);

   printf("<a href=\"index.html\">Home</a>   ");
   printf("<a href=\"javascript:history.back()\">Go back to menu.</a>");
   printf("</body></html>");
  }

  //Access passweb.csv
  else if (input =='2'){
  }

  //Access Inventory
  else {
    
    printf("<html><head><title>Inventory</title></head>\n");
    printf("<body><p>Store Inventory: (log.csv) </p>\n");
    
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int counter = 0;
    ssize_t read;

    fp = fopen("inventory.csv", "r");

    //Print each line in file inventory.csv
    while ( (read = getline(&line,&len,fp)) != -1  && counter < 50){
      
      printf("%s<br>",line);
      counter++;
    
    }

   fclose(fp);

   printf("<a href=\"index.html\">Home</a>   ");
   printf("<a href=\"javascript:history.back()\">Go back to menu.</a>");
   printf("</body></html>");
  
  
  }



}



