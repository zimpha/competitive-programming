from dlxsudoku import Sudoku

f = open('sudoku.txt', 'r')

ret = 0
for l in f:
    s = Sudoku(l)
    s.solve()
    s = s.to_oneliner()
    ret += int(s[0:3])
print ret
