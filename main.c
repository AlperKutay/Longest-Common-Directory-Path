//In this project we get inputs with arguments
//Therefore you should run the program with arguments 
//Firstly compile with 'gcc -o main main.c'
//then run with './main  /bob/john/betty/clark /bob/harry/../john/./betty/david /bob/john/betty/../betty/tom/mark /bob///john///betty///brad///martin
//DO NOT Forget the enter the directory of the project firstly 
#include <stdio.h>
#include <string.h>
#define MAX_NUM_PATHS 1024
#define MAX_NUM_INPUTS 10
#define MAX_LENGHT_DIRECTORY_NAME 10
//#define Windows
//if you cannot enter arguments just delete the slash before Windows
void print_paths(char paths[][MAX_NUM_PATHS], int num_paths) {//prints each path in the begining path array 
    for (int i = 0; i < num_paths; i++) {
        printf("%s\n", paths[i]);
    }
}
void free_current(char current_paths[][MAX_LENGHT_DIRECTORY_NAME],int count_free)//replace bits with '\0' which means it deletes everything in the array
{
    for (int i = 0; i < count_free; i++)
    {
        memcpy(current_paths[i],"\0\0\0\0\0\0\0\0\0\0",MAX_LENGHT_DIRECTORY_NAME);
    }
    
}
void print_current_paths(char paths[][MAX_LENGHT_DIRECTORY_NAME], int num_paths) {//prints paths that are splited by '/'
    for (int i = 0; i < num_paths; i++) {
        /*if (paths[i][0]=='\0')
        {
            continue;
        }*/
        
        printf("%s", paths[i]);
    }
}
void remove_multiple_slashes(char paths[][MAX_NUM_PATHS], int num_paths )//removes multiple slash and it reduces the number of slashes to only one EX: '/aaaa////bb//c' ==> '/aaaa/bb/c'
{
    for (int count_paths = 0; count_paths < num_paths; count_paths++) {
        int path_index = 0, count = 0;
        while (paths[count_paths][path_index] != '\0') {
            if (path_index > 0 && paths[count_paths][path_index] == '/' && paths[count_paths][path_index-1] == '/') {//it detects multiple slashes one after another
                path_index++;//skip it and increse the index
                continue;
            }
            paths[count_paths][count] = paths[count_paths][path_index];
            count++;
            path_index++;
        }
        paths[count_paths][count] = '\0';
    }
}
int control_starting(char paths[MAX_NUM_PATHS])//control whether path is starting '/' or not 
{
    if (paths[0]=='/')
    {
        return 1;
    }
    return 0;
}
void parse_directory(char input_path[MAX_NUM_PATHS],char output[][MAX_LENGHT_DIRECTORY_NAME])//parse the directory that is given begining '/aaa/bbb/cccc/d/e' ==> '/aaa','/bbb','/cccc','/d','/e'
{
    int path_index = 1;
    int count_directories = 0;
    int count_current_direc = 1;
    //we assummed path begins with '/',since we check begging of path in the beginning 
    output[0][0]='/';
    while (input_path[path_index] != '\0')//it continues until the end
    {
        if (input_path[path_index] == '/')//we assumed there is no multiple slashes because we remove them before
        {//if slash appeared, we can assume it is begging of the parsed path 
            output[count_directories][count_current_direc]='\0';
            count_current_direc =0;
            count_directories ++;
            output[count_directories][count_current_direc]=input_path[path_index];
        }
        else
        {
            output[count_directories][count_current_direc]=input_path[path_index];
        }
        count_current_direc++;
        path_index++;
    }
      
}
void compare(char paths[][MAX_NUM_PATHS], int num_paths,char comparison_result[MAX_NUM_PATHS])//main algorithm the find longest common directory
{//in this funciton we are going to compare paths with each other
//Firstly we compare the first both path and then we get comparison result
//After that we will do same thing with each paths and comparison_result and get new comparison_result
    int count = 0;
    char temp1 [MAX_NUM_PATHS][MAX_LENGHT_DIRECTORY_NAME];
    char temp2 [MAX_NUM_PATHS][MAX_LENGHT_DIRECTORY_NAME];
    int lenght = 0;
    int count_paths=0;
    while (count_paths<num_paths)
    {//since I have done this funciton before destination function, I had to add copying newpath part to the destination part
        free_current(temp1,MAX_NUM_PATHS);
        free_current(temp2,MAX_NUM_PATHS);
        if (count_paths==0)//it is the part of comparing of the first two paths
        {
            if(control_starting(paths[0]) && control_starting(paths[1]))//check they are starting with slash
            {
                parse_directory(paths[0],temp1);//Firstly parse the paths to temp arrays
                parse_directory(paths[1],temp2);
                while (strcmp(temp1[count],temp2[count])==0)//get the lenght of same paths 
                {
                    lenght = lenght + strlen(temp1[count]);
                    count++;
                }
                if(lenght != 0)//if lenght is not zero then copy of paths. It does not matter whether paths[0] or paths[1] because they are same at some lenght 
                {
                    memcpy(comparison_result,paths[0],lenght);
                    comparison_result[lenght]='\0';
                }
                else// if lenght is 0 then add just slash
                {
                    comparison_result[0] = '/';
                    comparison_result[1] = '\0';
                }                      
            }
            else// if they are not starting with slash then write only slash
            {
                comparison_result[0] = '/';
                comparison_result[1] = '\0';
            }
            count_paths = count_paths+2;//if there is no more than directory kill the function
        }
        else// do same things another path and comparison_result then update the comparison_result 
        {
            count = 0;
            lenght = 0;
            if(control_starting(paths[count_paths]) && control_starting(comparison_result))
            {
                parse_directory(paths[count_paths],temp1);
                parse_directory(comparison_result,temp2);
                while (strcmp(temp1[count],temp2[count])==0)
                {
                    lenght = lenght + strlen(temp1[count]);
                    count++;
                }
                if(lenght != 0)
                {
                    memcpy(comparison_result,paths[count_paths],lenght);
                    comparison_result[lenght]='\0';
                }
                else
                {
                    comparison_result[0] = '/';
                    comparison_result[1] = '\0';
                }                      
            }
            else
            {
                comparison_result[0] = '/';
                comparison_result[1] = '\0';
            }
            count_paths = count_paths+2;
        }
                 
    }  
    printf("%s \n",comparison_result);
    
    
}
void destination_path(char paths[][MAX_NUM_PATHS], int num_paths,char current_paths[][MAX_LENGHT_DIRECTORY_NAME])//this function detects '..' and '.'
{
    // in this function, we are going to take path and parse it. 
    //After that, we check '..' and '.', then we copy the new parsed path without '.' and '..'. 
    //Lastly we copy the parsed path to the new path structure which is have same size with input path array.
    int count_paths =0;
    int lenght = 0;
    int index_of_current_path;
    int count_path_in_temppath=0;
    int count_current_parsed_path=0;
    int index_of_new_unparsed_path;
    char paths2[MAX_NUM_INPUTS][MAX_NUM_PATHS];//it takes new path that is unparsed
    while(count_paths < num_paths)
    {
        count_path_in_temppath=0;
        count_current_parsed_path=0;
        char temp_path [MAX_NUM_PATHS][MAX_LENGHT_DIRECTORY_NAME];
        parse_directory(paths[count_paths],temp_path);//Firstly parse the directory and it is shown at function
        while (temp_path[count_path_in_temppath][0] != '\0')
        {
            if (!strcmp(temp_path[count_path_in_temppath],"/.."))//if array that we are checking it is '..', it deletes previous parsed path
            {
                memcpy(current_paths[count_current_parsed_path-1],"\0\0\0\0\0\0\0\0\0\0",MAX_LENGHT_DIRECTORY_NAME);
                count_current_parsed_path--;
            }
            else if (!strcmp(temp_path[count_path_in_temppath],"/."))//it just continues
            {
                count_path_in_temppath++;
                continue;
            }
            else//it adds parsed path to current path
            {
                memcpy(current_paths[count_current_parsed_path],temp_path[count_path_in_temppath],strlen(temp_path[count_path_in_temppath]));
                count_current_parsed_path++;
            }
            count_path_in_temppath++;
        }
        free_current(temp_path,count_path_in_temppath);//it deletes content of temp_path
        index_of_current_path=0;
        index_of_new_unparsed_path=0;
        for(int path_number=0;path_number<count_current_parsed_path;path_number++)//in this part we are going to copy parsed path to output path unparsedly ex: '/aaa','/b,'/cd' ==> '/aaa/b/cd' 
        {
            while (current_paths[path_number][index_of_current_path]!='\0')
            {
                paths2[count_paths][index_of_new_unparsed_path]=current_paths[path_number][index_of_current_path];
                index_of_current_path++;
                index_of_new_unparsed_path++;
            }
            index_of_current_path=0;
        }
        memcpy(paths[count_paths],paths2[count_paths],MAX_NUM_PATHS);//copy the paths
        free_current(current_paths,count_path_in_temppath);//deletes content of current path
        count_paths++;
    } 
}
int main(int argc, char** argv) 
{

    char current_paths[MAX_NUM_PATHS][MAX_LENGHT_DIRECTORY_NAME];
    char comparison_result[MAX_NUM_PATHS];
    char output_path [MAX_NUM_PATHS][MAX_LENGHT_DIRECTORY_NAME];

#ifdef Windows
    char paths[MAX_NUM_INPUTS][MAX_NUM_PATHS] = {"/a/b/c/s","/a/b/c/f/e","/a/b/c/f/e/g"};//Enter The inputs
    int num_paths = argc-1;
    
#else
    char paths[MAX_NUM_INPUTS][MAX_NUM_PATHS] ;
    int num_paths = argc-1;
    // Copy command line arguments to paths array
    for (int i = 1; i <= num_paths; i++) {

        strcpy(paths[i-1], argv[i]);

    }
#endif


    // Remove multiple slashes from paths
    remove_multiple_slashes(paths,num_paths);
    //adjust the new paths and copy the paths array according to existance of '..' and '.'
    destination_path(paths,num_paths,current_paths);
    //compare and prints the final result
    compare(paths,num_paths,comparison_result);
    return 0;
}
