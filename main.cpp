/*
Author: Morgan Purcell
Date: 02/15/2022
*/
 

//import the iostream library
#include<iostream>
//import the fstream library
#include<fstream>
//import the string library
#include <string>
 
//declare the use of the standard  namespace
using namespace std;
 
//fixed constant to make it easier to change the maze array sizes
#define MAXSIZE 200
//initialize a global 2D array to store the maze
char maze[MAXSIZE][MAXSIZE];

//declare two global variables for the number of rows and columns in the maze
int rown, coln;
//declare two more global variables as place holders for when rown and coln are reached
int gotThereRow, gotThereCol;

//declare global variables for the maze entrance and exit coordinates as integers
int rowStart, colStart, rowEnd, colEnd;

//declare a global variable to evaluate if the maze has been solved or not
bool solved;
 

//define the solveMaze function
bool solveMaze(int currentRow, int currentCol, int rowEnd, int colEnd)
{
    //base case checks if the exit of the maze has been reached
    if (currentRow == rowEnd && currentCol == colEnd)
    {
        //assign the exit '*'
        maze[currentRow][currentCol] = '*';
        //initialize global variables to hold the values of the exit
        gotThereRow = rowEnd;
        gotThereCol = colEnd;
        //return true if the base case is implemented 
        return true;
    }
 
 
     //check if the current row and column are on an invalid location
    if(maze[currentRow][currentCol] == '#' || currentRow < 0 || currentRow > rown || currentCol < 0 || currentCol > coln)
    {
        //leave this attempt if so
        return true;
    }

    //check if the curren row and column have already been visited
    if(maze[currentRow][currentCol] == '*')
    {
        //mark the location as potentially part of the solution
        maze[currentRow][currentCol] = '*';
        //leave this attempt
        return true;
    }


    //recursive call to check north for a valid space, if the maze has not already been solved
    if (maze[currentRow - 1][currentCol] == '+' && solved == false)
    {
        //assign the current space to '*'
        maze[currentRow][currentCol] = '*';
        //solve the maze from the valid space
        solveMaze(currentRow - 1, currentCol, rowEnd, colEnd);
    }

    //recursive call to check east for a valid space, if the maze has not already been solved
    if (maze[currentRow][currentCol + 1] == '+' && solved == false)
    {
        //assign the current space to '*'
        maze[currentRow][currentCol] = '*';
        //solve the maze from the valid space
        solveMaze(currentRow, currentCol + 1, rowEnd, colEnd);
    }
    
    //recursive call to check south for a valid space, if the maze has not already been solved
    if (maze[currentRow + 1][currentCol] == '+' && solved == false)
    {
        //assign the current space to '*'
        maze[currentRow][currentCol] = '*';
        //solve the maze from the valid space
        solveMaze(currentRow + 1, currentCol, rowEnd, colEnd);
    }
    
    //recursive call to check west for a valid space, if the maze has not already been solved
    if (maze[currentRow][currentCol - 1] == '+' && solved == false)
    {
        //assign the current space to '*'
        maze[currentRow][currentCol] = '*';
        //solve the maze from the valid space
        solveMaze(currentRow, currentCol - 1, rowEnd, colEnd);
    }
    
    //if and else block to evaluate if the maze has been solved to make sure no 'B's are placed after the maze has already been solved
    //check if the maze has been solved
    if(gotThereRow == rowEnd && gotThereCol == colEnd)
    {
        //if it has, solved = true
        solved = true;
        //if it has return true
        return true;
    }
    //if the maze has not been solved and no path can be taken
    else
    {
        //mark the current spot as bad
        maze[currentRow][currentCol] = 'B';
    }
 
    //if we reach here, there is no solution to the maze and flase should be returned to answerFound
    return false;
}


//define the solveMaze function
void solveMaze()
{
    //initalize a bool variable to store the result of the second solveMaze overloaded function
	bool answerFound = solveMaze(rowStart, colStart, rowEnd, colEnd);
    //if solveMaze returns false, there is no solution
	if (!answerFound)
		cout << "NO SOLUTION FOUND." << "\n\n";
}
 
 
//define the main method
int main(int argc, char* argv[])
{
    //promt the user for a file name and store it in a string variable
    string filename;
    cout << "Give a file name: ";
    cin >> filename;
    //read in the file
    ifstream mazefile(filename);
    cout << "\n\n";
 
    //check if the file did not open succesfully
    if (!mazefile)
    {
        //if so, exit th program
        cout << "Could not open the file";
        return 0;
    }
 
    //initialize global variables using integers from the input file 
    mazefile >> rown >> coln >> rowStart >> colStart >> rowEnd >> colEnd;
 
    //initialize the maze array with elements from the file using a nested for loop
    for (int i = 0; i < rown; i++)
    {
        for(int j = 0; j < coln; j++)
        {
            mazefile >> maze[i][j];
        }
    }
 
    //print the original maze using a nested for loop
    cout << "The Original Maze:" << endl;
    for (int i = 0; i < rown; i++)
    {
        for (int j = 0; j < coln; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
    cout << "\n\n";
 
    //call solveMaze function to solve the maze
    solveMaze();
 
    //if the exit was reached
    if(solved == true)
    {
        //print the solved maze using a nested for loop
        cout << "The Solved Maze:" << endl;
        for (int i = 0; i < rown; i++)
        {
            for (int j = 0; j < coln; j++)
            {
                cout << maze[i][j];
            }
            cout << endl;
        }
    }

    //if the exit was not reached
    if(solved != true)
    {
        //print the unsolved maze using a nested for loop
        cout << "The Attempted Maze:" << endl;
        for (int i = 0; i < rown; i++)
        {
            for (int j = 0; j < coln; j++)
            {
                cout << maze[i][j];
            }
            cout << endl;
        }
    }
 
    //return 0 to indicate a successful program
    return 0;
}