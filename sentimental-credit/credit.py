import cs50 as cs50
import math
# TODO

card = cs50.get_string("Number:")

dummy = card
mastercardset = "12345"
amexset = "47"


def luhncheck(cardnumber):
    # sums of the seconds which are multiplied by 2
    sumsec = 0
    # sums of the first which arr not multiplied
    sumfir = 0
    for i in range(int((len(cardnumber)+1)/2)):
        # find summation of the firsts
        fir = int((cardnumber[len(cardnumber)-1-i*2]))
        sumfir += fir

    for i in range(int((len(cardnumber))/2)):
        # find summation of seconds
        secint = str(int((cardnumber[len(cardnumber)-2-i*2]))*2)

        for i in range(len(secint)):
            sumsec += int(secint[i-1])

    modulo = sumsec+sumfir

    if str(modulo)[-1:] == "0":
        return True
    else:
        return False


# main checking function
while True:
    # check if luhn's algorithim is satisfied
    if (luhncheck(dummy)):
        # determine what type of card based on lenth and starting digits
        if dummy[0] == "4":
            if len(dummy) == 13 or len(dummy) == 16:
                print("VISA")
                break

        if dummy[0] == "3" and dummy[1] in amexset:
            if len(dummy) == 15:
                print("AMEX")
                break

        if dummy[0] == "5" and dummy[1] in mastercardset:
            if len(dummy) == 16:
                print("MASTERCARD")
                break
    # if luhns algorithim is not satisfied or if it is but a card type cannot be determined
    else:
        print("INVALID")
        break
