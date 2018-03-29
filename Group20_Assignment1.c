//Group No-20 Name:Rohit Verma(28) & Tarun Garg(45)
#include<stdio.h>
#include<stdlib.h>   //malloc
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>  //format of directory entries
#include<string.h>
#include<time.h>	//to be used with ctime otherwise only seconds would pe printed
#include<pwd.h>	//for printing user name along with user id
void lister(char *);

int main()
{
	char cwd[1024];
	/*getcwd implicitly passes the path name to the parameter buf i.e. 1st argument here cwd	*/
	if(getcwd(cwd,sizeof(cwd))!=NULL)
	printf("Current Working directory:%s\n",cwd);
	else
	printf("Unable to get Current Working Directory");
	
	lister(cwd);
	return 0;
}

void lister(char *str)
{
	printf("\nCurrent Iteration is Accessing:%s\n",str);
	printf("-----------------------------------------------------------");
	DIR *d;   //A type representing a directory stream
	char *str1;   //new string for concatenation of path
	struct dirent *file;//Dirent Structure Stores info about file
	struct stat st;//stat structure is used to store the status of the file
	d=opendir(str);   //return a pointer to the directory system
	while((file=readdir(d)))  /*readdir return a pointer to a dirent structure rep. next entry in directory system <-> dirent.h*/
	{
	
		str1=malloc(1024);   /*The malloc() function allocates size bytes and returns a pointer to the allocated memory.*/
		str1[0]='\0';
		strcat(str1,str);   //appending new path variable to old path
		strcat(str1,"/");
		strcat(str1,file->d_name);	
		lstat(str1,&st);//fetching the status of the file
		
		if((strcmp(file->d_name,".")!=0)&&(strcmp(file->d_name,"..")!=0))
		{
			printf("\nCurrent FILE/DIRECTORY :%s",file->d_name);	
			if(S_ISREG(st.st_mode)  || S_ISLNK(st.st_mode))
			{
				
				printf("\nOwner User id          :%d",st.st_uid);
				printf("\nOwner Name             :%s",getpwuid(st.st_uid)->pw_name);
				printf("\nFile Type              :");
				switch (st.st_mode & S_IFMT) //S_IFMT is bit mask for file type
				{ 
				   case S_IFBLK:  printf(" Block device\n");break; //fetching the file type
				   case S_IFCHR:  printf(" Character device\n");break; 
				   case S_IFDIR:  printf(" Directory\n");break; 
				   case S_IFIFO:  printf(" FIFO/pipe\n");break; 
				   case S_IFLNK:  printf(" Symlink\n");break; 
				   case S_IFREG:  printf(" Regular file\n");break; 
				   case S_IFSOCK: printf(" Socket\n");break; 
				   default:       printf(" Unknown?\n");break;
				} 
				printf("File Permissions       :");//Printing File Permissions
				printf((S_ISDIR(st.st_mode)) ? "d" : "-");  //man lstat
				printf((st.st_mode & S_IRUSR) ? "r" : "-");
				printf((st.st_mode & S_IWUSR) ? "w" : "-");
				printf((st.st_mode & S_IXUSR) ? "x" : "-");
				printf((st.st_mode & S_IRGRP) ? "r" : "-");
				printf((st.st_mode & S_IWGRP) ? "w" : "-");
				printf((st.st_mode & S_IXGRP) ? "x" : "-");
				printf((st.st_mode & S_IROTH) ? "r" : "-");
				printf((st.st_mode & S_IWOTH) ? "w" : "-");
				printf((st.st_mode & S_IXOTH) ? "x" : "-");				
				printf("\nLast Access Time       :%.24s",ctime(&st.st_atime));//ctime is used otherwise time would be printed in seconds which is not user readable
				printf("\nLast Modification Time :%.24s\n",ctime(&st.st_mtime));
				
				printf("************************************************\n");
		        
		       
			
			}
			else
			{
				switch (st.st_mode & S_IFMT) //S_IFMT is bit mask for file type
				{ 
				   case S_IFBLK:  printf(" Block device\n");break; 
				   case S_IFCHR:  printf(" Character device\n");break; 
				   case S_IFDIR:  printf(" Directory\n");break; 
				   case S_IFIFO:  printf(" FIFO/pipe\n");break; 
				   case S_IFLNK:  printf(" Symlink\n");break; 
				   case S_IFREG:  printf(" Regular file\n");break; 
				   case S_IFSOCK: printf(" Socket\n");break; 
				   default:       printf(" Unknown?\n");break;
				}
				if((st.st_mode & S_IFMT)==(S_IFDIR))
					printf("New Directory Encountered, Initiating Recursive Call...");
				lister(str1);  //Recursion in Case of Directory
			}
		}
	}
	closedir(d);  //closing the directory
}



