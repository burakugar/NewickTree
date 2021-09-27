#include <stdio.h>
int putshortline(int num,FILE *ptr){ //printing short lines
	if(num<=0)
			return 0;

	putc('-',ptr);
	num--;

	return putshortline(num,ptr);
}
void trim(char * str)		//after taking the node, we trim the spaces at the start and at the end of the node 
{
    int index, i;
    index = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }
    i = 0;
    while(str[i + index] != '\0')
    {
        str[i] = str[i + index];
        i++;
    }
    str[i] = '\0';
    i = 0;
    index = -1;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }
        i++;
    }
    str[index + 1] = '\0';
}
int isAlpha(char c){
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    else					//control if character is a letter or not
        return 0;
}
FILE *Newick2 (FILE *fp ,FILE *ptr,int parenthesis) //Building newick tree 
{	
	int i = 0,prvpt=0;
	char ch;
	char spacenode[30];
	ch=fgetc(fp);
	if(ch == EOF)
		return 0;
			
	while(ch != EOF && ch != ','){
		while(ch != ')' && ch != ','){
			if(ch=='('){ // taking parenthesis information
				parenthesis++;
			}
			else{
				spacenode[i] = ch;		//if character is a space or a letter load it to buffer
				i++;
			}
			ch=fgetc(fp);				
		}
		prvpt = parenthesis;	//we carry on until we see ")" 
		if(ch == ')'){		
			parenthesis--; // when we see ")" we assign the number of opened parenthesis to prvpt and then decrease the parantheysis amount
			ch=fgetc(fp);
		}
	}
		
	spacenode[i] = '\0';			//at the end of the spacenode we put null terminator
	putshortline(prvpt,ptr);		//print "-" as much as assigned parenthesis
	trim(spacenode);				// remove the spaces at the start and at the end of the node
	fputs(spacenode,ptr); 			//print the node
	putc('\n',ptr);					//pass the newline
	return Newick2(fp,ptr,parenthesis);		//recursion with number of parenthesis
	
}

int main(){
	FILE *fp=fopen("input.txt","r"); //open file for read
	FILE *ptr=fopen("output.txt","w");//open file for write
	Newick2(fp,ptr,0);//newick tree building and printing
	fclose(fp); //Close for reading file
	fclose(ptr);//Close for writing  file 	
}
