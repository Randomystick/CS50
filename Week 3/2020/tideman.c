#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

int source; //CS50

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new SINGLE vote
bool vote(int rank, string name, int ranks[])
{
    // CS50
    int namenumberMap = 0;
    bool nameMatches = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i], name)) // if name matches candidate (strcmp returns 0 if strings are identical
        {
            nameMatches = 1;
            namenumberMap = i;
        }
    }
    if (nameMatches)
    {
        ranks[rank] = namenumberMap;
//        for (int i = 0; i < candidate_count; i++)
//        {
//            printf("%i", ranks[i]);
//        }
        return true;
    }
    else return false;

}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // CS50
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i+1; j < candidate_count; j++)
        {
            preferences[ ranks[i] ][ ranks[j] ]++; // fix rank #1, update the matchup between it and everyone below (rank #1+1 and beyond)
            // preferences[x][y] = no of people preferring x over y
        }
    }
//    for (int i = 0; i < candidate_count; i++)
//    {
//        for (int j = 0; j < candidate_count; j++)
//        {
//            printf("%i", preferences[i][j]);
//        }
//    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // CS50
    //         j
    //   ======================    4 CANDIDATES
    //   | ⌀ | 0 | 1 | 2 | 3  |    6 PAIRS
    // i | 0 | ⌀ | 4 | 9 | 19 |    compare [i][j] vs [j][i]
    //   | 1 | 8 | ⌀ | 11| 25 |
    //   | 2 | 4 | 12| ⌀ | 21 |
    //   | 3 | 9 | 16| 17| ⌀  |
    //   ======================
    int currentPair = 0;
    pair_count = candidate_count * (candidate_count-1) / 2;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i+1; j < candidate_count; j++)
        {
            if ( preferences[i][j] > preferences[j][i] )
            {
                pairs[currentPair].winner = i;
                pairs[currentPair].loser = j;
                currentPair++;
            }
            else if ( preferences[i][j] == preferences[j][i] ) // "A pair of candidates who are tied (one is not preferred over the other) should not be added to the array."
            {

                pair_count--;
            }
            else
            {
                pairs[currentPair].winner = j;
                pairs[currentPair].loser = i;
                currentPair++;
            }
            //printf("winner is %i and loser is %i\n", pairs[i].winner, pairs[i].loser);
        }
        //for (int checc = 0; checc < pair_count; checc++)
        //{
        //    printf("OUTSIDE winner is %i and loser is %i\n", pairs[checc].winner, pairs[checc].loser);
        //}
    }
    
    //for (int checc = 0; checc < pair_count; checc++)
    //{
    //    printf("IMMEDIATE AFTER winner is %i and loser is %i\n", pairs[checc].winner, pairs[checc].loser);
    //}
    
    //printf("pair count %i\n", pair_count);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // CS50
    typedef struct
    {
        int winStrength;
        int posOrigin;
    }
    winStr;
    
    winStr winStrArray[pair_count];
    for (int i = 0; i < pair_count; i++) // for every winner loser pair in array 'pairs'
    {
        winStrArray[i].winStrength = preferences[ pairs[i].winner ][ pairs[i].loser ] - preferences[ pairs[i].loser ][ pairs[i].winner ];
        winStrArray[i].posOrigin = i; //winStrength at index i of winStrArray corresponds to the win strength of the pair located at i
    }
    //     PAIRS array:                                          winStrArray:
    // =========================                              =========================
    // | 0 | 0 | 3 | 1 | 3 | 3 | winner        ----------->   | 0 | 1 | 2 | 3 | 4 | 5 | posOrigin
    // | 1 | 2 | 0 | 2 | 1 | 2 | loser         |              | 3 | 6 | 4 | 7 | 12| 8 | winStrength(random numbers as e.g.)
    // =========================               |              =========================
    //  [0] [1] [2] [3] [4] [5]    -------------               [0] [1] [2] [3] [4] [5] //after sorting winStrArray, posOrigin != index
    //for (int i = 0; i < pair_count; i++)
    //{
    //    printf("winStrArray[%i] before is %i, %i\n", i, winStrArray[i].winStrength, winStrArray[i].posOrigin);
    //}

    //now to sort winStrArray
    //SELECTION SORT
    for (int j = 0; j < pair_count; j++)
    {
        winStr winStrCompare;
        winStrCompare.winStrength = -1;
        winStrCompare.posOrigin = -1;
        int winStrCompareINDEX = 0;
        for (int k = j+1; k < pair_count; k++)
        {
            if (winStrArray[k].winStrength > winStrCompare.winStrength)
            {
                winStrCompare = winStrArray[k]; //winStrCompare = stores a copy of the winStr object with highest wins
                winStrCompareINDEX = k;
            }
            //printf("for k = %i, winstrcompare is %i, %i\n", k, winStrCompare.winStrength, winStrCompare.posOrigin);
        }
        if (winStrCompare.winStrength > winStrArray[j].winStrength) //a swap should occur
        {
            winStrArray[winStrCompareINDEX] = winStrArray[j];
            winStrArray[j] = winStrCompare;
        }
        winStrCompare.winStrength = -1;
        winStrCompare.posOrigin = -1;
        winStrCompareINDEX = 0;
    }
                
    //for (int i = 0; i < pair_count; i++)
    //{
    //    printf("winStrArray[%i] after is %i, %i\n", i, winStrArray[i].winStrength, winStrArray[i].posOrigin);
    //}
    
    
    //    winStrArray:
    // =========================                                           =========================
    // | 0 | 1 | 2 | 3 | 4 | 5 | posOrigin                                 | 4 | 5 | 3 | 1 | 2 | 0 |
    // | 3 | 6 | 4 | 7 | 12| 8 | winStrength(random numbers as e.g.)       | 12| 8 | 7 | 6 | 4 | 3 |
    // =========================                                           =========================
    // [0] [1] [2] [3] [4] [5]                                              [0] [1] [2] [3] [4] [5]
    // pairs[ winStrArray[i].posOrigin ] must move to pairs[i]
    
    //can't do a simple buffer-and-swap, because the winStrArray[i].posOrigin reference positions get fked up
    //example:      winStrength, posOrigin
    //winStrArray[0] after is 5, 2 - okay, so you move the pair at index 2 to index 0...
    //winStrArray[1] after is 5, 4
    //winStrArray[2] after is 3, 0 - then now, this (pairs[winStrArray[i].posOrigin]) will reference that pair you just moved to index 0!
    //winStrArray[3] after is 3, 3
    //winStrArray[4] after is 3, 1
    //winStrArray[5] after is 3, 5
    
    pair pairsCOPY[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        pairsCOPY[i] = pairs[i];
    } // copy pairs[i] array into pairsCOPY
    
    //for (int i = 0; i < pair_count; i++)
    //{
    //    printf("pairscopy is %i and %i\n", pairsCOPY[i].winner, pairsCOPY[i].loser);
    //} 
    
    for (int j = 0; j < pair_count; j++)
    {
        pairs[j] = pairsCOPY[winStrArray[j].posOrigin];
        //for (int k = 0; k < pair_count; k++)
        //{
        //    printf("INTERMEDIARY winner is %i and loser is %i\n", pairs[k].winner, pairs[k].loser);
        //}
        //printf("\n\n");
    }
    //for (int checc = 0; checc < pair_count; checc++)
    //{
    //    printf("NOW winner is %i and loser is %i\n", pairs[checc].winner, pairs[checc].loser);
    //}
    
    return;
}



//functions cannot be declared in functions - these two below are for lock_pairs
    int drilldown_to_source(int winner)
    { 
        //                   (k)
        //    proposed loser  A -----------> B (j)
        //                                   |
        //                                   |
        //                                   |
        //                                   |
        //                                   |
        //                                   v
        //    proposed winner D <----------- C (i) <------------------- E
        // 
        // cannot: drilldown_to_source of proposed winner D returns A who is the proposed loser
        
        source = winner; // global variable because the sources within the recursive loops only have local scope - you will always return the original winner passed into function i.e the value with same scope as return statement.
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][source] == true)
            {
                drilldown_to_source(i);
            }
        }
        return source; // all the candidates have been looped; proposed winner is not loser in any pair
    }
    
    
    bool is_there_cycle(int winner, int loser) // only 2 scenarios where there is cycle
    {
        if (locked[loser][winner] == true) // scenario 1: there is already winner-loser going the other way of the proposed winner and proposed loser
        {
            return true; 
        }
        
        
        if (drilldown_to_source(winner) == loser) // scenario 2: proposed winner is loser in another pair, and those pairs ultimately link up to a winner who is the proposed loser
        {
            return true;
        }
        return false;
    }


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // CS50
    // locked[i][j] means i is locked in over j - all initialised as false
    
        for (int i = 0; i < pair_count; i++)
    {
        if ( !(is_there_cycle(pairs[i].winner, pairs[i].loser)) )
        {
            locked[pairs[i].winner][pairs[i].loser] = 1;
        }
    }
    return;
}


// Print the winner of the election
void print_winner(void)
{
    // CS50
    bool winner = 1;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                winner = 0;
            }
        }
        if (winner)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
