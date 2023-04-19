import csv
import sys


def main():

    # TODO: Check for command-line usage
    if (len(sys.argv) != 3):
        return print("Usage: python dna.py data.csv sequence.txt")

    arg_csv = sys.argv[1]
    arg_txt = sys.argv[2]

    # TODO: Read database file into a variable

    # READ CSV FILE
    csv_list = []
    with open(f"{arg_csv}", newline='') as csvfile:
        csv_reader = csv.DictReader(csvfile)
        for item in csv_reader:
            csv_list.append(dict(item))

    # TODO: Read DNA sequence file into a variable

    txt_sequence = open(f"{arg_txt}", 'r').read()

    # print(csv_list)
    # print("text->", txt_sequence)

    # TODO: Find longest match of each STR in DNA sequence

    keys = csv_list[0].keys()
    result = {}
    for key in keys:
        if key != 'name':
            result[key] = longest_match(txt_sequence, key)

    # print(keys)
    # print(result)
    # print(search_results)

    # TODO: Check database for matching profiles

    dna_match = 0
    for person in csv_list:

        correct_count = 0
        for key in keys:
            if key != 'name':
                if int(person[key]) == int(result[key]):
                    correct_count += 1
        if correct_count == len(keys) - 1:
            print(f"{person['name']}")
            dna_match = 1
    if dna_match == 0:
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
