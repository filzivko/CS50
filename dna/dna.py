import csv
import sys


def main():

    dbread = []
    seq = []

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Incorrect number of inputs")

    # TODO: Read database file into a variable
    with open(sys.argv[1], 'r') as f:
        database = csv.DictReader(f, delimiter=',')
        for row in database:
            dbread.append(row)
        f.close()

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as s:
        sequence = s.read()
        seq = sequence
        s.close()

    keylist = list(dbread[0].keys())
    matchseq = ["name"]

    # TODO: Find longest match of each STR in DNA sequence
    for i in range(1, len(keylist)):
        matchseq.append(longest_match(seq, keylist[i]))

    rowcount = 0
    # TODO: Check database for matching profiles
    for row in dbread:
        rowcount += 1
        correct = 0
        for i in range(1, len(keylist)):
            if int(row[keylist[i]]) != matchseq[i]:
                correct = 0
                break
            else:
                correct = 1
        if correct == 1:
            print(row[keylist[0]])
            break
        if rowcount == len(dbread):
            print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
