# TODO

import cs50 as cs50

# ask user for input until the answer is acceptable
while True:
    h = cs50.get_int("Height:")
    if h > 0 and h < 9:
        break

# build pyramid
for i in range(h):
    print(" "*(h-i-1), end="")
    print("#"*(i+1), "", "#"*(i+1))
