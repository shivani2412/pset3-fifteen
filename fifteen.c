/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int dim;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    dim = atoi(argv[1]);
    if (dim < DIM_MIN || dim > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < dim - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int temp;
    int k = dim * dim - 1;
    for(int i=0;i < dim;i++)
    {
        for(int j=0;j < dim;j++)
        {
            board[i][j] = k;
            k--;
            if (k == 0)
            { 
                break;
            }     
        }
    }
    if (dim % 2 == 0)
    {
        temp = board[dim - 1][dim - 2];
        board[dim - 1][dim - 2] = board[dim - 1][dim - 3];
        board[dim - 1][dim - 3] = temp;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i=0;i < dim;i++)
    {
        for(int j=0; j < dim;j++)
        {
            
            if (board[i][j] == 0)
            { 
                printf(" _");
            }    
                 else
                printf("%2i ",board[i][j]);
            
            
           
            
        }
        printf("\n");
    }
}


/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{       
    int temp=0;
        
    for(int i=0;i < dim;i++)
    {
        int k_1;
        int l_1;
        int m_1;
        int n_1;
        for(int j=0;j < dim;j++)
        { 
        
            if (board[i][j] == 0)
            {
                k_1 = i;
                l_1 = j;
                    
            }
                
            if (board[i][j] == tile)
            {
                m_1 = i;
                n_1 = j;
            }
            if ((k_1 == m_1 - 1) && (l_1 == n_1))
            {
                temp = board[k_1][l_1];
                board[k_1][l_1] = board[m_1][n_1];
                board[m_1][n_1] = temp;
                return true;
                }
            if ((k_1 == m_1) && (l_1 == n_1 + 1))
            {
                temp = board[k_1][l_1];
                board[k_1][l_1] = board[m_1][n_1];
                board[m_1][n_1] = temp;
                return true;
                    
            }
            if ((k_1 == m_1 + 1) && (l_1 == n_1))
            {
                temp = board[k_1][l_1];
                board[k_1][l_1] = board[m_1][n_1];
                board[m_1][n_1] = temp;
                return true;
            }
            if ((k_1 == m_1) && (l_1 == n_1 - 1))
            {
                temp = board[k_1][l_1];
                board[k_1][l_1] = board[m_1][n_1];
                board[m_1][n_1] = temp;
                return true;
            }
            
        }
    }
    return false;
}


/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{  
    int count = 1;
    for(int i=0;i < dim;i++)
    { 
         
        for(int j=0;j < dim;j++)
        { 
        
            if (board[i][j] == count)
            {
                count++;
                if (count == dim * dim)
                {
                    return true;
                }    
        }
         else  
                return false;  
           
           
        }
        
    }
    return false; 
    
}



