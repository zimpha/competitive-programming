def valid(s):
    if len(s) != 9: return False
    if s[0] not in "1234567" or s[4] != ' ': return False
    if s[1:4] not in ["TAX", "TEX", "TBX"]: return False
    if s[0] != '7' and s[1:4] == "TEX": return False
    for c in s[5:]:
        if c not in "0123456789": return False
    if int(s[5:]) == 0: return False
    return True

n = int(input())
ret = 0
for i in range(n):
    s = input()
    ret += valid(s)
print(ret)
