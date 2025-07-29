#include "includes/cub3d.h"
// we have first to parse the input and read the file and 
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
//make rules for the input 
bool valid_path_input(char *path)
{
  // normalement maps/*.cub
  // but what if he just make it in 
  //let's start with quick parse is to check if the file containts ( dir and file) -> meaning (dir/file.cub)
  // first part has to match the maps
  // check just direcotry
  int i = 0;
  while (path[i] != '/')
    i++;
  if(path[i] && path[i] == '/')
    i++;
  while(path[i] != '.')
    i++;
  if (path[i] == '.')
    i++;
  if(strcmp(path + i  , "cub") != 0)
  {
    printf("messing with the input!!why?.\n");
    return false;
  }
  return true;
}
int main(int ac, char **av)
{
  if(ac == 2)
  {
    // process the input first make it valid first
    // ur dealing with a string, so we must just manipulate the string with the funciton 
    if(!valid_path_input(av[1]))
      return 1;
    int fd = open(av[1], O_RDONLY );
    if(fd < 0)
    {
      printf("file not exist.\n");
      return 1;
    
    }
    /// i have no idea if this good practice or not
    char **buffer = NULL;
    buffer = malloc(sizeof(char *));
    int size = 0;
    while((buffer[size] = get_next_line(fd)) != NULL)
      size++;
    printf("rak ghadi blan \n");
  }
  else 
  {
    printf("example of input : map/smthng.cub\n");
  }
}

