#######################################################################
# FYI: math power function: pow(y, x), not y^x
#######################################################################

import sys # for sys.exit

while True:
    try:
        ccNumber = int(input("Type a credit card number: "))
    except ValueError:
        sys.exit("INVALID")
    if not (13 <= len(str(ccNumber)) <= 16):
        sys.exit("INVALID")
    else:
        #int typed
        break

# counting from the end of the number... 
oddNumber = [] 
evenNumber = []
# note: ints are stored as strings in these 2 arrays ('lists' in Python)

ccNumber = str(ccNumber)
ccLength = len(ccNumber)
for num in range (ccLength): # num = 0 to ccLength-1
    if ((num % 2) == 0): # if num is 0,2,4,6,etc....
        oddNumber.append(ccNumber[ccLength-num-1]) 
        # append the last number in the list; the +1 is because len(ccNumber) counts from 1, but index of list counts from 0.
    else:
        evenNumber.append(ccNumber[ccLength-num-1])


# IMPLEMENTING LUHN'S ALGORITHM:

# STEP1: multiply each of the even digits by 2. E.g. 1x2 + 0x2 + 0x2 + 0x2 + 0x2 + 6x2 + 0x2 + 4x2 = 2 + 0 + 0 + 0 + 0 + 12 + 0 + 8
for y in range(len(evenNumber)):
    evenNumber[y] = str(int(evenNumber[y])*2)
#    print(f"{evenNumber[y]}")


# STEP2: add those products’ digits (i.e., not the products themselves) together. E.g. 2 + 0 + 0 + 0 + 0 + 1 + 2 + 0 + 8 = 13
evenSum = 0
for y in range(len(evenNumber)):
    if (int(evenNumber[y]) < 10):
        evenSum += int(evenNumber[y])
    else:
        evenSum += (int(evenNumber[y]) % 10) + 1
#print(f"{evenSum}")


# STEP3: Now let’s add that sum (13) to the sum of the odd digits. E.g. 13 + 4 + 0 + 0 + 0 + 0 + 0 + 3 + 0 = 20
oddSum = 0
for x in range(len(oddNumber)):
    oddSum += int(oddNumber[x])
SUM = oddSum + evenSum


# STEP4: if sum % 10 = 0, is legit
if ((SUM % 10) != 0):
    print("INVALID")
else:
    ccStart = int(ccNumber[:2])
    if (ccStart == 34) or (ccStart == 37):
        print("AMEX")
    if (51 <= ccStart <= 55):
        print("MASTERCARD")
    if (40 <= ccStart <= 49):
        print("VISA")