#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main (int argc, char* argv[])
{
  //using defaults from Lab 4.pdf and quiz_grades.txt
  //first two columns is chapter 1 (HW1 and HW2 respectively)
  //second two columns is chapter 2 (HW1 and HW2 respectively)
  int student = 10;
  int manager_stat = 0;
  int worker_stat = 0;
  int current; //for the current hw in the array

  //for working with child processes
  int row = 0;
  int column = 0;
  int total = 0;
  int max = 0;

  //example: ./Part 2 quiz_grades.txt 2 2
  if (argc < 4)
  {
    printf("Enter filename, # of chapters, and # of homeworks per chapter\n");
    return 1;
  }


  char filename[strlen(argv[1])];
  strcpy(filename,argv[1]); //copy filename into argv[1]
  int chapter = atoi(argv[2]); //# of chapters is second argument.  atoi -> convert string to int
  int hw = atoi(argv[3]); // # of hw per chapter is third argument


  //at least 2 chapters and at least 1 hw per chapter
  if (chapter < 2 || hw < 1)
  {
    printf("# of Chapters and # of hw per chapter should be at least 1\n");
    return 1;
  }

  int hw_total = chapter * hw;

  //Memory
  int *grades[student];
  for (int i = 0; i<student;i++)
  {
    grades[i] = (int *) malloc(hw_total * sizeof(int));
  }



  // reading data from filename
  FILE *input_file = fopen(filename, "r"); //read file
  for (int i = 0; i < student; i++)
  {
    for (int j = 0; (j < hw_total) && ( (fscanf(input_file, "%d", &current)) ) > 0 ; j++)
    {
      grades[i][j] = current;
    }
  }
  fclose(input_file);




  //calculate averages
  for (int i = 0; i < chapter; i++)
  {
    manager_stat = fork(); //create manager process for each chapter
    if (manager_stat < 0) //if error
    {
      perror ("Fork Failed\n");
      return 1;
    }

    else if (manager_stat == 0)
    {
      for (int j = 0; j < hw; j++)
      {
        worker_stat = fork(); //create worker process for each hw
        if (worker_stat < 0) //if error
        {
          perror("Fork Failed\n");
          return 1;
        }

        else if (worker_stat == 0)
        {
          column = column + j;

          for (row = 0; row < student; row++)
          {
            total = total + grades[row][column];
            if (grades[row][column] > max)
            {
              max = grades[row][column];
            }

          }

          //print the averages and maxes for each hw
          printf("\nChapter %d / HW %d: \n\tAverage: %f\n \tMax: %d\n", (i+1), (j+1), total/10.0, max);
          return 1;
        }
      }
      return 1;
    }
    column = column + hw;
  }

  return 0;

}