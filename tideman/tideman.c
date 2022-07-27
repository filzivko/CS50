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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// int lock_array[15];

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int start, int loser);

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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // DONE?
    int i;
    for (i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // printf("valid entry: RANK:%d I:%d\n", rank, i);
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // in preferences here, the
    int i;
    int j;
    int newstart = 0;
    for (i = 0; i < candidate_count; i++)
    {
        // printf("i is: %d and ranks[i] is %d\n", i, ranks[i]);
        // printf("ranks[i] is %d when i is%d\n", ranks[i], i);
        for (j = newstart; j < candidate_count; j++)
        {
            // printf("j is %d and rank[j] is %d\n", j, ranks[j]);
            if (i != j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
            // printf("fil (1) compared to john (0) is %d\n", preferences[1][0]);
            // printf("%s ", candidates[ranks[i]]);
            // printf("%s beats %s : %d times\n", candidates[ranks[i]], candidates[ranks[j]], preferences[i][j]);
        }
        newstart++;
        // printf("newline\n");
    }

    // this is for debugging, can be deleted once complete
    for (i = 0; i < candidate_count; i++)
    {
        for (j = 0; j < candidate_count; j++)
        {
            // printf("%s compared to %s is %d\n", candidates[i], candidates[j], preferences[i][j]);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int i;
    int j;
    for (i = 0; i < candidate_count; i++)
    {
        for (j = 0; j < candidate_count; j++)
        {
            // printf("i:%d  j:%d\n", i, j);
            if (preferences[i][j] > preferences[j][i])
            {
                // printf("imbalance of %d to %d of %d-%d\n", i, j, preferences[i][j], preferences[j][i]);
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int i;
    int j;
    // implement a bubble sort
    int swap = 1;

    // this can be deleted
    for (i = 0; i < 3; i++)
    {
        // printf("pre sort %d winner and %d loser\n", pairs[i].winner, pairs[i].loser);
    }

    while (swap != 0)
    {
        swap = 0;
        int sort_length = pair_count;
        for (i = 0; i < sort_length; i++)
        {
            // printf("checking %s with %d compared to %s with %d\n", candidates[pairs[i].winner], preferences[pairs[i].winner][pairs[i].loser], candidates[pairs[i].loser], preferences[pairs[i + 1].winner][pairs[i + 1].loser]);
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                // printf("looking at %s with %d compared to %s with %d\n", candidates[pairs[i].winner], preferences[pairs[i].winner][pairs[i].loser], candidates[pairs[i].loser], preferences[pairs[i + 1].winner][pairs[i + 1].loser]);
                int tempwinner = pairs[i].winner;
                int temploser = pairs[i].loser;
                pairs[i].winner = pairs[i + 1].winner;
                pairs[i].loser = pairs[i + 1].loser;
                pairs[i + 1].winner = tempwinner;
                pairs[i + 1].loser = temploser;
                // printf("This works\n");

                swap++;
            }
        }
        sort_length--;
    }

    for (i = 0; i < pair_count; i++)
    {
        // printf("post sort winner:%s no%d loser:%s no%d\n", candidates[pairs[i].winner], pairs[i].winner, candidates[pairs[i].loser], pairs[i].loser);
        // printf("%d to %d\n", preferences[pairs[i].winner][pairs[i].loser], preferences[pairs[i].loser][pairs[i].winner]);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int i;

    for (i = 0; i < pair_count; i++)
    {
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int i;
    int j;
    int k;
    int winner;
    int winpoint;

    for (i = 0; i < candidate_count; i++)
    {
        winpoint = 1;
        // printf("start winpoint 1 - i:%d\n", i);
        for (j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                winpoint = 0;
                // printf("winpoint 0 - j is:%d i is:%d\n", j, i);
            }
        }

        if (winpoint == 1)
        {
            winner = i;
            // printf("winner is set to i : %d\n", i);
        }
    }

    printf("%s\n", candidates[winner]);
    return;
}

bool check_cycle(int start, int loser)
{
    int i;
    if (loser == start)
    {
        return true;
    }
    for (i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (check_cycle(start, i))
            {
                return true;
            }
        }
    }
    return false;
}
