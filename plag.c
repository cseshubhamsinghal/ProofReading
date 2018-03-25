#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <ctype.h>



void calc_hash(char input[],char output[],char output2[]);
void remove_punct_and_make_lower_case(char *p);

int main(){
char file[50];
int i,j,k,doc,doc_match;
int s[]={0,0,0,0};
char line[10000];
double sum,total_hash;

double hashno[]={0,0,0,0};
double wordno[]={0,0,0,0};
double percent;
char input[50];
char output[50];
char output2[50];
double hash[4][10000];
char *word[3][10000];

for(i=1;i<4;i++){

sprintf(input,"input%d.txt",i);
sprintf(output,"output%d.txt",i);
sprintf(output2,"output%d%d.txt",i,i);

calc_hash(input,output,output2);
}



	printf("\nFetching documents and hash values:\n");
	
	
for(j=1;j<4;j++){
	
	
	FILE *fptr;
	sprintf(file,"output%d.txt",j);
    fptr = fopen(file, "r");
	i=0;
	while(fgets(line, sizeof(line), fptr)!=NULL) {
		hash[j][i]=atoi(line);
		i++;
		hashno[j]++;
	}
	fclose(fptr);


	
	
	sprintf(file,"output%d%d.txt",j,j);
    fptr = fopen(file, "r");
	i=0;
	while(fgets(line, sizeof(line), fptr)!=NULL) {
		word[j][i]=(line);
		i++;
		wordno[j]++;
	}
	fclose(fptr);
}
	
	
printf("Enter the document number for which you want to check plagiarsim: ");
scanf("%d",&doc);
	
	
	printf("\nComparison started:\n");
	
	
	
   for(k=1;k<4;k++){
	if(doc!=k){

    for(i=0;i<hashno[doc];i++){
	 for(j=0;j<hashno[k];j++){
		if(hash[doc][i]==hash[k][j]){
			if(strcmp(word[doc][i],word[k][j])==0){
			s[k]++;
			break;
			}}} 
			}
	}
}
	
	for(k=1;k<4;k++){
		if(doc!=k){	
			printf("Total words matched with document%d: %d\n\n",k,s[k]);
			
			if(sum<s[k]){
				sum=s[k];
				total_hash=hashno[doc]+hashno[k];
				doc_match=k;
			}
		}
	}
	

	percent=(2*sum*100)/total_hash;	
	printf("\nPlagiarism detected with document%d: %0.2lf percent\n",doc_match,percent);

return 0;
}








void calc_hash(char input[],char output[],char output2[]){


	char *isnull;
	

    char file[15];
	int i=0;
	char line[5000];
	char* string[5000];         //extracting lines
	char* words[5000];         //extracting words
	char* word[5000];         //extracting tokens
	char str[50];
	int nolines=0;     //number of lines in a document
	int nowords=0;    //total number of words in the document
	int noword=0;      ////number of words in the document after removing stopwords
	int j=0;                    //counter for words
	int m,k,q,z;
	int p;
	double hash[2000];           //for storing hash values

  char* stopword[]= {"a"," ","\t\t","\0","\r", "about", "above", "above", "across", "after", "afterwards", "again", "against", "all", "almost", "alone", "along", "already", "also","although","always","am","among", "amongst", "amoungst", "amount", "an", "and", "another", "any","anyhow","anyone","anything","anyway", "anywhere", "are", "around", "as", "at", "back","be","became", "because","become","becomes", "becoming", "been", "before", "beforehand", "behind", "being", "below", "beside", "besides", "between", "beyond", "bill", "both", "bottom","but", "by", "call", "can", "cannot", "cant", "co", "con", "could", "couldnt", "cry", "de", "describe", "detail", "do", "done", "down", "due", "during", "each", "eg", "eight", "either", "eleven","else", "elsewhere", "empty", "enough", "etc", "even", "ever", "every", "everyone", "everything", "everywhere", "except", "few", "fifteen", "fify", "fill", "find", "fire", "first", "five", "for",
		              "former", "formerly", "forty", "found", "four", "from", "front", "full", "further", "get", "give", "go", "had", "has", "hasnt", "have", "he", "hence", "her", "here", "hereafter", "hereby", "herein", "hereupon", "hers", "herself", "him", "himself", "his", "how", "however", "hundred", "ie", "if", "in", "inc", "indeed", "interest", "into", "is", "it", "its", "itself", "keep", "last", "latter", "latterly", "least", "less", "ltd", "made", "many", "may", "me", "meanwhile", "might", "mill", "mine", "more", "moreover", "most", "mostly", "move", "much", "must", "my", "myself", "name", "namely", "neither", "never", "nevertheless", "next", "nine", "no", "nobody", "none", "noone", "nor", "not", "nothing", "now", "nowhere", "of", "off", "often", "on", "once", "one", "only", "onto", "or", "other", "others", "otherwise", "our", "ours", "ourselves", "out", "over", "own","part", "per", "perhaps",
					  "please", "put", "rather", "re", "same", "see", "seem", "seemed", "seeming", "seems", "serious", "several", "she", "should", "show", "side", "since", "sincere", "six", "sixty", "so", "some", "somehow", "someone", "something", "sometime", "sometimes", "somewhere", "still", "such", "system", "take", "ten", "than", "that", "the", "their", "them", "themselves", "then", "thence", "there", "thereafter", "thereby", "therefore", "therein", "thereupon", "these", "they", "thickv", "thin", "third", "this", "those", "though", "three", "through", "throughout", "thru", "thus", "to", "together", "too", "top", "toward", "towards", "twelve", "twenty", "two", "un", "under", "until", "up", "upon", "us", "very", "via", "was", "we", "well", "were", "what", "whatever", "when", "whence", "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "whereupon", "wherever", "whether", "which", "while",
					  "whither", "who", "whoever", "whole", "whom", "whose", "why", "will", "with", "within", "without", "would", "yet", "you", "your", "yours", "yourself", "yourselves", "the"};
					  
	FILE *fptr;
    fptr=fopen(input,"r");

    if (fptr == NULL)
    {
	printf("Cannot open file \n");
	exit(0);
    }


   while(fgets(line, sizeof(line), fptr)!=NULL){									 //extracting line by line
		if ((isnull=strchr(line, '\n')) != NULL)
		  { *isnull='\0'; }

		string[i]=strdup(line);
		i++;
		nolines++;
		}
	fclose(fptr);

	 for (i=0 ; i<nolines; i++) {												 //extracting word by word

		char *p= strtok(string[i]," ");
		while(p!=NULL){
		       words[j++]=p;
		       nowords++;
		       p=strtok(NULL," ");
	       }
	    }

		 for(i=0;i<nowords;i++) {
		remove_punct_and_make_lower_case(words[i]);												//conversion to lower case
				      }
				      
       printf("\n\nTotal number of words in the document %s:%d\n",input,nowords);
        
	 for(i=0;i<nowords;i++) {														//removal of stopwords
	   for(k=0;k<322;k++){
		     if(strcmp(words[i],stopword[k])==0){
			 words[i]="0";
			 break; }
			 }
			}
			
		 z=0;
		 for(i=0;i<nowords;i++) {
		
		     if(strcmp(words[i],"0")!=0){
		     word[z]=words[i];
			z++;
			noword++;}
			}
			
			printf("Number of words remaining after removal of stopwords:%d\n",noword);

	       for(i=0;i<2000;i++)
	       {hash[i]=0;}


	  p=17;
	  for(i=0;i<noword;i++)											//calculating hash values
	  { 
		strcpy(str,word[i]);
		m=strlen(str);

	      for(k=1;k<=m;k++)
		  {
	   		q=(int)str[k-1];
			hash[i]=hash[i]+(q*pow(p,m-k));
			}
		
		}


		
			FILE *f;	
	       f = fopen(output,"w");
	   	   for(k = 0; k < noword; k++ )											//writing to file
			{
			fprintf(f, "%0.2lf\n", hash[k]);  
			}
			fclose(f);
		
			f = fopen(output2,"w");
	   	   for(k = 0; k < noword; k++ )											//writing to file
			{
			fprintf(f, "%s\n", word[k]);  
			}
			
			printf("Saved hash values in %s\n",output);
	       fclose(f);
		
		
}

void remove_punct_and_make_lower_case(char *p)
{
    char *src = p, *dst = p;

    while (*src)
    {
       if (ispunct(*src))
       {
          /* Skip this character */
          src++;
       }
       else if (isupper(*src))
       {
          /* Make it lowercase */
          *dst++ = tolower(*src);
          src++;
       }
       else if (src == dst)
       {
          /* Increment both pointers without copying */
          src++;
          dst++;
       }
       else
       {
          /* Copy character */
          *dst++ = *src++;
       }
    }

    *dst = 0;
}
