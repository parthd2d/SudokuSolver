#include <bits/stdc++.h>
#define endl "\n"
using namespace std;

bool is_safe(int mat[][9],int i,int j,int no,int n)
{
    //check for row and col
    for(int rc=0;rc<n;rc++)
    {
        if(mat[rc][j]==no||mat[i][rc]==no)
        {
            return false;
        }
    }

    //check for subgrid
    int sx=(i/3)*3,sy=(j/3)*3;
    for(int x=sx;x<sx+3;x++)
    {
        for(int y=sy;y<sy+3;y++)
        {
            if(mat[x][y]==no)
            {
                return false;
            }
        }
    }

    return true;
}

bool solve_sudoku(int mat[][9],int i,int j,int n)
{
    //base case
    if(i==9)
    {
        //print solution
        for(int r=0;r<n;r++)
        {
            for(int c=0;c<n;c++)
            {
                cout<<mat[r][c]<<" ";
            }
            cout<<endl;
        }
        return true;
    }

    //recursive case
    if(j==n)
    {
        return solve_sudoku(mat,i+1,0,n);
    }

    //skip the prefilled cell
    if(mat[i][j]!=0)
    {
        return solve_sudoku(mat,i,j+1,n);
    }

    //cell to be filled
    //try out all possiblities
    for(int no=1;no<=n;no++)
    {
        //check if we can place no at i,j in matrix
        if(is_safe(mat,i,j,no,n))
        {
            mat[i][j]=no;
            bool solve_subproblem=solve_sudoku(mat,i,j+1,n);
            if(solve_subproblem==true)
            {
                return true;
            }

        }
    }
    //if no option works
    mat[i][j]=0;
    return false;

}

int no_of_sol(int mat[][9],int i,int j,int n)
{
    //base case
    if(i==9)
    {
        //print solution
        // for(int r=0;r<n;r++)
        // {
        //     for(int c=0;c<n;c++)
        //     {
        //         cout<<mat[r][c]<<" ";
        //     }
        //     cout<<endl;
        // }
        return 1;
    }

    //recursive case
    if(j==n)
    {
        return solve_sudoku(mat,i+1,0,n);
    }

    //skip the prefilled cell
    if(mat[i][j]!=0)
    {
        return solve_sudoku(mat,i,j+1,n);
    }

    //cell to be filled
    //try out all possiblities
    int ways=0;
    for(int no=1;no<=n;no++)
    {
        //check if we can place no at i,j in matrix
        if(is_safe(mat,i,j,no,n))
        {
            mat[i][j]=no;
            ways+=no_of_sol(mat,i,j+1,n);
        }
    }
    //if no option works
    mat[i][j]=0;
    return 0;

}

int main()
{
    int n = 9;
    int mat[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    if(!solve_sudoku(mat,0,0,9))
    {
        cout<<"No solution exists"<<endl;
    }

    cout<<no_of_sol(mat,0,0,n)<<endl;


    return 0;
}