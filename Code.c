#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

candidate candidates[MAX_CANDIDATES];
int voter_count;
int candidate_count;


// Functions
int get_index(string name);
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    candidate_count = argc - 1;
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
    }
    voter_count = get_int("Max Voters: ");
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 1; j < candidate_count + 1; j++)
        {
            string mm = get_string("Rank %i: ", j);
            vote(i, j - 1, mm);
        }
    }
    tabulate();
    while (!print_winner())
    {
        int minn = find_min();
        eliminate(minn);
        tabulate();
    }
    print_winner();
}

int get_index(string nam)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, nam) == 0)
        {
            return i;
        }
    }
    return -1;
}
    
bool vote(int voter, int rank, string name)
{
    int index = get_index(name);
    if (index == -1)
    {
        return false;
    }
    else
    {
        preferences[voter][rank] = index;
        return true;
    }
}

void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int current_index = preferences[i][j];
            if (!candidates[current_index].eliminated)
            {
                candidates[current_index].votes++;
                break;
            }
        }
        
    }
}

bool print_winner(void)
{
    int maj;
    if (voter_count % 2 == 0)
    {
        maj = (voter_count / 2) + 1;
    }
    else
    {
        maj = (voter_count + 1) / 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= maj)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

int find_min(void)
{
    int current = 0;
    for (int i = 0; i < candidate_count; i++) 
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[current].votes > candidates[i].votes)
            {
                current = i;
            }
        }   
    }
    return candidates[current].votes;
    
}

bool is_tie(int min)
{
    int count = 0;
    int cc = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        if (!candidates[j].eliminated)
        {
            cc++;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes == min)
            {
                count++;
            }
        }
    }
    return count == cc ? true : false;
}

void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && !candidates[i].eliminated)
        {
            candidates[i].eliminated = true;
        }
    }
}
