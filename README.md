# Usage

Input via stdin one line with an interger, the number of words in the dictionary and a five letter word in all caps, the answer to the antiwordle. Then one line per word in the dictionart in all caps. The dictionary file includes the dictionart used on [Antiwordle](https://www.antiwordle.com/).

The program outputs a guess order which is optimal for the given answer. The program uses the hard mode rules.

The program uses a reduction to the maximum clique problem, which is NP-hard and therefore the program is sometimes very slow. I challenge you to show that the problem is in P or not.

