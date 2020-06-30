
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' 
REGEX CAPTURING GRPS & FINDALL

 re.findall returns only captured groups, i.e. search terms enclosed in brackets.
 re.findall on (AGATC)+ will hence only return (AGATC), the captured group, even if the matched search term is more than that.
 SOLN: Wrap (AGATC) as a non-capturing group ?:. Where there are no captured groups, re.findall will return all.
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' 
OBTAINING v CALLING

 txtFile.read = obtains the read method = <built-in method read of _io.TextIOWrapper object at 0xDEADBEEF>
 txtFile.read() = call the read method on txtFile = actually read the file as we want
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' 
RANGE LEN 

 for i in range(len(list)):     print(f"{a[i]}")  
 IS THE SAME AS
 for i in list:                 print(f"{i}")
 
 for i in range(len(a)):    a[i] = a[i] * 2
 IS THE SAME AS
 for i, e in enumerate(a):  a[i] = e * 2
 IS THE SAME AS
 a = [e * 2 for e in a]
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

#python dna.py databases/small.csv sequences/1.txt
import sys # argv, exit
import csv
import re


# first command-line arg: name of an assumed valid CSV file containing STR counts for a list of individuals
# secnd command-line arg: name of an assumed valid text file containing DNA sequence to identify. 
# IF INCORRECT NO OF CLA -> exit with error msg + error code 2 (command line syntax error)
if len(sys.argv) != 3:
    print(f"{len(sys.argv)}")
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit(2)
# DEBUG #print(f"csv is {sys.argv[1]} and txt is {sys.argv[2]}")


# OPEN CSV FILE, READ CONTENTS INTO MEMORY
## name ATGC TAGC CAGT
##  A    4    5    6
##  B    8    2    3
csvFile = open(sys.argv[1], 'r')
csvReader = csv.reader(csvFile) # this is an iterator
# STORE STRs in a list
STRs = next(csvReader)
STRs.pop(0)


# OPEN DNA SEQUENCE FILE, READ CONTENTS INTO MEMORY
with open(sys.argv[2], 'r') as txtFile:
    DNAsequence = txtFile.read()
# DEBUG # print(f"{DNAsequence}")


# List to count consecutive repeats
STRsCOUNT = []
# FOR EACH STR...
for i in STRs:
    # ...COMPUTE LONGEST RUN OF CONSECUTIVE REPEATS.
    regex = '(?:'+ i + ')+'
    searches = re.findall(regex, DNAsequence)
    # If no repeats found, straightaway print "No match" and exit.
    if not searches:
        print("No match")
        sys.exit(0)
    longest = max(searches, key=len)
    STRCOUNT = str(longest.count(i))
    ''' DESIGN CHOICE: It's less computationally intensive to add the single quotes here, than to remove it from all csv entries.'''
    STRsCOUNT.append( f'{STRCOUNT}' )
    # DEBUG #    print(f"running for {i}, regex is {regex}, search text is {searches}, longest is {longest}, count is {STRCOUNT}\n")

#print(STRsCOUNT)
matchFound = False
for lines in csvReader:
    # IF STR counts match exactly w an individual...
    if STRsCOUNT == lines[1:]:
        # ...print their name. Specification: STR counts will not match more than one individual.
        print(lines[0])
        matchFound = True
        
if not matchFound:
    print("No match")


csvFile.close()