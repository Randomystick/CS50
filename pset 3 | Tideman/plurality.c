  #include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // CS50: check if name keyed in is valid (one of the names of the candidates)
    // If name matches: update candidate’s vote total to account for the new vote. return true
    // If name does not match: no vote totals should change. return false
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i].name)) //if name matches (strcmp returns 0 if strings are identical)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // CS50: print out the name of the candidate who received the most votes in the election, and then print a newline.
    // Tie: output the names of each of the winning candidates, each on a separate line.
    int highestVote = 0;
    int winnerID = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > highestVote)
        {
            highestVote = candidates[i].votes;
            winnerID = i;
        }
    }
    printf("%s\n", candidates[winnerID].name);
    for (int i=0; i < candidate_count; i++)
    {
        if (candidates[i].votes == highestVote && i !=winnerID)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
