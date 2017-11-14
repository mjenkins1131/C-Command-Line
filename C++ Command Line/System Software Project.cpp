#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <istream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/stat.h>
#include <dirent.h>
using namespace std;


int ms_mkfile(char *args)
{

	const char *filename = (const char *)args;
	
	//checks to see if file alrady exists
	if (ifstream(filename)) {
		cout << "The file already exists" << endl;
		return 0;
	}
	
	//creates needed file. Returns error message if it already exists
	ofstream file(filename);
	file.flush();
	file.close();

	if (!filename) {
		cout << "There was an error. Please make sure the file doesnt already exist and try again." << endl;
	}

	else {
		cout << "Okay, created file: " << filename << endl;
	}
}

//remove file command
int ms_rmfile(char *arg) {

	if (remove(arg) != 0)
		perror("There was an error deleting the file");
	else
		cout << "File deleted" << endl;

}

//make directory command
int ms_mkdir(char *args)
{
	const char *dirNam = (const char *)args;
	mkdir(dirNam, S_IRUSR | S_IWUSR | S_IXUSR);
	if (!dirNam) {
		cout << "There was an error. Please make sure the directory doesnt already exist and try again." << endl;
	}
	else {
		cout << "Okay, created directory: " << dirNam << endl;
	}
}

//change directory command
int ms_cd(char *arg) {
	const char *dirNam = (const char *)arg;
	chdir(dirNam);
	if (!dirNam) {
		cout << "There was an error. Please make sure the directory exist and is spelled correctly and try again." << endl;
		return 0;
	}
	else {
		cout << "Done, you are now in " << dirNam << endl;
	}
}

//remove directory command
int ms_rmdir(char *arg) {
	const char *dirNam = (const char *)arg;
	rmdir(dirNam);
	if (!dirNam) {
		cout << "There was an error. Please make sure the directory exist and try again." << endl;
	}
	else if (rmdir(dirNam) == -1) {
		cout << "The directory you are trying to remove isnt empty. Please make sure it is empty before deleting." << endl;
	}
	else {
		cout << dirNam << " removed" << endl;
	}
}

//shows the stats of a file
int ms_stat(char *arg) {
	struct stat info;
	char buffer[800];
	if (stat(arg, &info) == -1) {
		perror("There was an error");
	}

	cout << "File last accessed " << ctime(&info.st_atime) << endl;
	cout << "File last modified " << ctime(&info.st_mtime) << endl;

}

//lists the files in a directory
int ms_ls(char *arg) {
	char *path;
	size_t size;
	DIR *dir;
	struct dirent *ent;
	path = getcwd(path, size);
	if ((dir = opendir(path)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			cout << ent->d_name << endl;
		}
		closedir(dir);
	}
	else {
		perror("");
		return EXIT_FAILURE;
	}

}

void ms_mkfs() {
	
	//creates a file system
	//needs to be implemented in memory
	mkdir("Documents", S_IRUSR | S_IWUSR | S_IXUSR);
	mkdir("Downloads", S_IRUSR | S_IWUSR | S_IXUSR);
	mkdir("Pictures", S_IRUSR | S_IWUSR | S_IXUSR);
	mkdir("Desktop", S_IRUSR | S_IWUSR | S_IXUSR);
	cout << "System created" << endl;

}

//executes the requested command
int execute(char **cmd) {
	
	//switch case may be used
	if (strcmp(cmd[0], "exit") == 0) {
		cout << "Have a good day" << endl;
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(cmd[0], "help") == 0) {
		cout << "List of commands: rmfile <filename>, mkfile <filename>, cd <directory name>, ls, stat, mkfs" << endl;
	}
	else if (strcmp(cmd[0], "mkfs") == 0) {
		ms_mkfs();
	}
	else if (strcmp(cmd[0], "cd") == 0) {
		ms_cd(cmd[1]);
	}
	else if (strcmp(cmd[0], "mkdir") == 0)
	{
		ms_mkdir(cmd[1]);
	}
	else if (strcmp(cmd[0], "rmdir") == 0) {

		ms_rmdir(cmd[1]);
	}
	else if (strcmp(cmd[0], "stat") == 0)
	{
		ms_stat(cmd[1]);
	}
	else  if (strcmp(cmd[0], "ls") == 0) {

		ms_ls(cmd[1]);
	}
	else if (strcmp(cmd[0], "mkfile") == 0) {

		ms_mkfile(cmd[1]);
	}
	else if (strcmp(cmd[0], "rmfile") == 0) {

		ms_rmfile(cmd[1]);
	}

	else {
		cout << "Invalid command, type help for a list of commands" << endl;
	}
}

//splits the command line into tokens
char* tokens[400];
char** ms_split_line(char *cmd) {
	int position = 0;
	char* token;

	token = strtok(cmd, " ");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		token = strtok(NULL, " ");
	}

	return tokens;

}

//buffer for read line
char buffer[400];

//read line method for reading the command line
char* ms_read_line(void)
{
	int position = 0;
	int c;

	while (1) {

		c = getchar();

		if (c == EOF || c == '\n') {

			buffer[position] = '\0';
			return buffer;
		}
		else {
			buffer[position] = (char)c;
		}
		position++;
	}
}

int main()
{
	char** args;
	int status;
	char* cmd;
	cout << "Welcome to my shell " << endl;
	do {
		printf("Marvins Shell> ");
		cmd = ms_read_line();
		args = ms_split_line(cmd);
		execute(args);
	} while (true);
	return EXIT_SUCCESS;
}



