from functools import cache

@cache
def blink(s, remainingBlinks):
    if remainingBlinks == 0:
        return 1
    digits = len(str(s))
    if s == 0:
        return blink(1, remainingBlinks - 1)
    elif digits % 2 == 0:
        power = pow(10,int(digits/2))
        return blink(int(s / power), remainingBlinks - 1) + blink(int(s % power), remainingBlinks - 1)
    return blink(s * 2024, remainingBlinks - 1)

with open("input.txt") as file:
    stones = list(map(int,file.read().split()))
    sum = 0
    for s in stones:
        sum += blink(s, 75)
    print(sum)