x = raw_input()
cnt = [0] * 5
for c in x:
    if c == 'Y':
        cnt[0] += 1
    elif c == 'E':
        cnt[1] += 1
    elif c == 'A':
        cnt[2] += 1
    elif c == 'H':
        cnt[3] += 1
    else:
        cnt[4] += 1
for x in cnt:
    print x,
