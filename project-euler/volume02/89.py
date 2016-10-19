def sub(roman):
    result = roman
    replacements = [
        ("VIIII", "IX"),
        ("IIII", "IV"),
        ("LXXXX", "XC"),
        ("XXXX", "XL"),
        ("DCCCC", "CM"),
        ("CCCC", "CD"),
    ]
    for old, new in replacements:
        result = result.replace(old, new)
    return result

f = open('roman.txt', 'r')
ret = 0
tot = 0
for l in f:
    tot += len(l)
    s = sub(l)
    ret += len(s)
print tot - ret
