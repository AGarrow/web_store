//NOT ENCRYPTION ONLY FILE ENCODING / DECODING

void decrypt (FILE *fp, char arr[50][50])
{

	char *line = NULL;
	size_t len = 0;
	int counter = 0;
	ssize_t read;
	
	//copy file contents, line by line, into array
	while( (read = getline(&line,&len,fp)) != -1  && counter < 20 )
	{
		strcpy(arr[counter],line);
		counter++;
	}
	
}

void encrypt (char arr[50][50],FILE *fp)
{
	  int i = 0;
 
	  //write contents of array to file		
    while(i < 15)
	  {
		  fprintf(fp,"%s\n",arr[i]);
		  i++;
	  }

}
