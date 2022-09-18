
import csv
import sys


def main():

    # TODO: Check for command-line usage
    if (len(sys.argv) != 3):
        print("Wrong number of arguments")
        exit(1)

    # TODO: Read database file into a variable
    db_list = []

    with open('{}'.format(sys.argv[1])) as f:
        small_db = csv.DictReader(f)
        for item in small_db:
            db_list.append(item)

    # TODO: Read DNA sequence file into a variable
    with open('{}'.format(sys.argv[2])) as f:
        seq1 = f.readline()

    # TODO: Find longest match of each STR in DNA sequence

    seq_AGATC = longest_match(seq1,'AGATC')
    seq_AATG = longest_match(seq1,'AATG')
    seq_TATC = longest_match(seq1,'TATC')

    # TODO: Check database for matching profiles
    match = 'nf'

    for i in db_list:
        if(int(i["AGATC"]) == seq_AGATC and int(i["AATG"]) == seq_AATG and int(i["TATC"]) == seq_TATC):
            print(i["name"])
            match = i["name"]
            break

    if match == 'nf':
        print("not found")


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
