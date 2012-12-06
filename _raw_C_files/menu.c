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
  char c;
  int i = 0;
  char username[40];
  int j = 0;

  length++;

  fgets(inputString,length,stdin);

  input = inputString[7];

  while ( (c = inputString[i]) != '&')
    i++;

  while ( (c = inputString[i]) != '=')
    i++;

  i++;

  while ( (c = inputString[i]) != EOF && i < length){
    username[j] = c;
    j++;
    i++;
  }

  //Change password
  if (input == '0'){ 
    printf("<html><head><title>Change Password</title></head>\n"); 
    printf("<body><p>Change your password:</p>\n");
    printf("<form method=\"POST\" action=\"passchange.cgi\">\n");
    printf("<p>Please enter your username, old password, and new password.</p>\n");
    printf("<br>Note: please make sure you enter the correct info and that your account exists.<br>");
    printf("Username: <input type =\"text\" name=\"username\"><br>\n");
    printf("Old Password:<input type =\"password\" name=\"oldpass\"><br>\n");
    printf("New Password:<input type =\"password\" name=\"newpass\"><br>\n");
    printf("<input type =\"submit\" value=\"Submit!\"><br>\n");  
    printf("</body></html>");
  }

  //Open up log.csv and display
  else if (input == '1'){

    printf("<html><head><title>Purchase History</title></head>\n");
    printf("<body><p>Purchase History: (Log.csv) </p><br>\n");

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int counter = 0;
    ssize_t read;
    char logArray[20][50];
    char purchaseLine[50];
    char * junk;
    int purchaseSwitch = 0;
    char clearLine[50] = {0};

    fp = fopen("../databases/Log.csv", "r");

    //Print each line in file log.csv
    while ( (read = getline(&line,&len,fp)) != -1  && counter < 50){

      strcpy(logArray[counter],line);
      counter++;

    }

    fclose(fp);

    for (int i = 0; i < counter; i ++){

      if (strstr(logArray[i],username) && purchaseSwitch == 0){

        purchaseSwitch = 1;

        strcpy(purchaseLine,logArray[i]);
        junk = strtok(purchaseLine,",");
        junk = strtok(NULL,",");

        printf("Woah! You're a big spender, %s.<br><br>Damage done: %s$<br><br>",username,junk);

        printf("Here's what you splurged on: <br><br>");

        junk  = strtok(NULL,",");

        while( junk != NULL)
        {
          printf("%s: ", junk);
          junk = strtok(NULL,",");
          printf("you got %s of them.<br>",junk);
          junk = strtok(NULL,",");

        }

        strcpy(purchaseLine,clearLine);

        printf("<br><br>");
      }

      else if (strstr(logArray[i],username) && purchaseSwitch == 1){

        printf("Damn! You really went crazy up in herr, here's another one of your purchases:<br><br>");

        strcpy(purchaseLine,logArray[i]);
        junk = strtok(purchaseLine,",");
        junk = strtok(NULL,",");

        printf("Damage done: %s$<br><br>",junk);

        printf("Here's what you splurged on: <br><br>");

        junk  = strtok(NULL,",");

        while( junk != NULL)
        {
          printf("%s: ", junk);
          junk = strtok(NULL,",");
          printf("you got %s of them.<br>",junk);
          junk = strtok(NULL,",");

        }

        strcpy(purchaseLine,clearLine);
        printf("<br><br>");
      }

    } 

    if(purchaseSwitch == 1){

      printf("<a href=\"../home.html\">Home</a>   ");
      printf("<a href=\"javascript:history.back()\">Go back to menu.</a>");
      printf("</body></html>");

      return;
    }


    printf("What are you waiting for? Go buy something!<br>");
    printf("<br>");
    printf("<a href=\"../home.html\">Home</a>   ");
    printf("<a href=\"javascript:history.back()\">Go back to menu.</a>");
    printf("</body></html>");

  }


  //Access passweb.csv
  else if (input =='2'){

    printf("<html><head><title>PASSWEB.C ACCESS:</title></head>\n"); 
    printf("<body><p>Access all of passweb.c's functionality here:</p>\n");
    printf("<form method=\"POST\" action=\"passweb.cgi\">\n");
    printf("<pChoose a passweb.c function, then enter the required information in the fields below:</p>\n");
    printf("Verify (enter an existing username and password): <input type =\"radio\" name=\"option\" value=\"0\"><br>\n");
    printf("Add (enter a new username, password, type (USER or SYSTEM)): <input type =\"radio\" name=\"option\" value=\"1\"><br>\n");
    printf("Edit (enter an old username and password,type,then new u/n, pass and type): <input type =\"radio\" name=\"option\" value=\"2\"><br>\n");
    printf("Delete (enter username to delete): <input type =\"radio\" name=\"option\" value=\"3\"><br><br>\n");
    printf("Please fill in the required fields for the option you selected:<br><br>\n");
    printf("For delete: fill in first field.<br>verify:fill in first 2 fields.<br> add: first 3 fields <br><br>");
    printf("Username: <input type =\"text\" name=\"user1\"><br>\n");
    printf("Password:<input type =\"password\" name=\"oldpass\"><br>\n");
    printf("Type:<input type =\"text\" name=\"type1\"><br>\n");
    printf("New Username: <input type =\"text\" name=\"user2\"><br>\n");
    printf("New Password:<input type =\"password\" name=\"newpass\"><br>\n");
    printf("New Type:<input type =\"text\" name=\"type2\"><br>\n");
    printf("<input type =\"submit\" value=\"Submit!\"><br>\n");  
    printf("<br>"); 
    printf("<a href=\"../Home.html\">Home</a>   ");
    printf("<a href=\"javascript:history.back()\">Go back to menu.</a>");
    printf("</body></html>");
  }

  //Access Inventory
  else {

    printf("<html><head><title>Inventory</title></head>\n");
    printf("<body><p>Store Inventory: (Inventory.csv) </p>\n");

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int counter = 0;
    ssize_t read;

    fp = fopen("../databases/Inventory.csv", "r");

    //Print each line in file inventory.csv
    while ( (read = getline(&line,&len,fp)) != -1  && counter < 50){

      printf("%s<br>",line);
      counter++;

    }

    fclose(fp);

    printf("<a href=\"../Home.html\">Home</a>   ");
    printf("<a href=\"javascript:history.back()\">Go back to menu.</a>");
    printf("</body></html>");


  }


}



