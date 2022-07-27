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
} candidate;

// Array of candidates
candidate candidates[MAX];
candidate winners[MAX];

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
    // TODO
    int i;
    for (i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
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
    // TODO
    int i;
    int j;
    int swap = 1;
    int winnersQTY = 0;
    int sortedlength = candidate_count;

    // implement a bubble sort
    while (swap != 0)
    {
        swap = 0;
        for (i = 0; i < sortedlength - 1; i++)
        {
            if (candidates[i].votes > candidates[i + 1].votes)
            {
                string temp_name = candidates[i].name;
                int temp_vote = candidates[i].votes;
                candidates[i].votes = candidates[i + 1].votes;
                candidates[i].name = candidates[i + 1].name;
                candidates[i + 1].votes = temp_vote;
                candidates[i + 1].name = temp_name;
                swap++;
            }
        }
        sortedlength--;
    }

    for (i = candidate_count - 1; i >= 0; i--)
    {
        if (candidates[candidate_count - 1].votes <= candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}
