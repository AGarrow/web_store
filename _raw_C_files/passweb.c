// passweb.cgi: this script essentially parses the selected option in menu.c
// and calls the corresponding function of passweb_store using system()
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

int main() {

  printf("Content-type: text/html\n\n");

  //The following block of code gets the input option from stdin and stores it in the
  //input variable. 

  char input[200];
  char option;
  int length = atoi(getenv("CONTENT_LENGTH"));
  
  length++;

  fgets(input,length,stdin);

  option = input[7];

  //Most of this code just stores the username, old password, new password entered in html form
  //in variables username, oldpass, newpass
  
  char c;
  int i = 0;
  int j = 0;
  char olduser[40] = {0};
  char oldpass[40] = {0};
  char oldtype[40] = {0};
  char newuser[40] = {0};
  char newpass[40] = {0};
  char newtype[40] = {0};
  char systemString[150] = {0};  

  while ((c = input[i]) != '='){
    i++;
  }

  i++;

  while ((c = input[i]) != '&'){
      i++;
  }

  while ((c = input[i]) != '='){
    i++;
  }

  i++;

  while ((c = input[i]) != '&'){
      olduser[j] = c;
      i++;
      j++;
  }

  olduser[j] = '\0';

  j = 0;

  while ((c = input[i]) != '='){
    i++;
  }

  i++;

  while ((c = input[i]) != '&'){
      oldpass[j] = c;
      i++;
      j++;
  }

  oldpass[j] = '\0';

  j = 0;

while ((c = input[i]) != '='){
    i++;
  }

  i++;

  while ((c = input[i]) != '&'){
      oldtype[j] = c;
      i++;
      j++;
  }

  oldtype[j] = '\0';

  j = 0;

while ((c = input[i]) != '='){
    i++;
  }

  i++;

  while ((c = input[i]) != '&'){
      newuser[j] = c;
      i++;
      j++;
  }

  newuser[j] = '\0';

  j = 0;

while ((c = input[i]) != '='){
    i++;
  }

  i++;

  while ((c = input[i]) != '&'){
      newpass[j] = c;
      i++;
      j++;
  }

  newpass[j] = '\0';

  j = 0;

while ((c = input[i]) != '='){
    i++;
  }

  i++;

  while ((c = input[i]) != EOF && i < length){
      newtype[j] = c;
      i++;
      j++;
  }

  newtype[j] = '\0'; 



//Create the specified system() systemString and submit, depending on option selected:


//user chose verify
if (option == '0'){

  strcat(systemString, "./passweb_store -verify ");
  strcat(systemString, olduser);
  strcat(systemString," ");
  strcat(systemString, oldpass);
  
   int log = system(systemString);
  
   printf("<head><title>Success</title></head><body>");
   printf("<a href=\"../home.html\">Home</a>   ");
   printf("<a href=\"javascript: window.history.go(-2)\">Go back to menu.</a>");
   printf("</body></html>");

}

//user chose add
else if (option == '1'){

  strcat(systemString, "./passweb_store -add ");
  strcat(systemString, olduser);
  strcat(systemString," ");
  strcat(systemString, oldpass);
  strcat(systemString," ");
  strcat(systemString, oldtype);
  
  int log = system(systemString);
  
   printf("<head><title>Success</title></head><body>");
   printf("<a href=\"../home.html\">Home</a>   ");
   printf("<a href=\"javascript: window.history.go(-2)\">Go back to menu.</a>");
   printf("</body></html>");

}

//user chose edit
else if (option == '2'){

  strcat(systemString, "./passweb_store -edit ");
  strcat(systemString, olduser);
  strcat(systemString," ");
  strcat(systemString, oldpass);
  strcat(systemString," ");
  strcat(systemString, oldtype);
  strcat(systemString," ");
  strcat(systemString, newuser);
  strcat(systemString," ");
  strcat(systemString, newpass);
  strcat(systemString," ");
  strcat(systemString, newtype);
 
 
 int log = system(systemString);
  
   printf("<head><title>Success</title></head><body>");
   printf("<a href=\"../home.html\">Home</a>   ");
   printf("<a href=\"javascript: window.history.go(-2)\">Go back to menu.</a>");
   printf("</body></html>");


}

//user chose delete
else{

  strcat(systemString, "./passweb_store -del ");
  strcat(systemString, olduser);
  
   int log = system(systemString);
  
   printf("<head><title>Success</title></head><body>");
   printf("<a href=\"../home.html\">Home</a>   ");
   printf("<a href=\"javascript: window.history.go(-2)\">Go back to menu.</a>");
   printf("</body></html>");

}


}
