read n m

declare -A graph

declare -a cnt
for ((i=0; i<n; ++i)) do
  cnt[$i]=0
done
for i in `seq ${m}`; do
  read a b
  graph[$a,${cnt[$a]}]=$b
  graph[$b,${cnt[$b]}]=$a
  cnt[$a]=$((${cnt[$a]}+1))
  cnt[$b]=$((${cnt[$b]}+1))
done

declare -a mark

for ((i=0; i<n; ++i)) do
  mark[$i]=0
done

declare -a queue
ret=0
for ((i=0; i<n; ++i)) do
  if [ ${mark[$i]} -eq 0 ]; then
    ret=$[$ret+1]
    h=0
    t=1
    queue[0]=$i
    while [ $h -lt $t ]; do
      u=${queue[$h]}
      h=$[$h+1]
      m=${cnt[$u]}
      for ((j=0; j<$m; ++j)) do
        v=${graph[$u,$j]}
        if [ ${mark[$v]} -eq 0 ]; then
          mark[$v]=1
          queue[$t]=$v
          t=$[$t+1]
        fi
      done
    done
  fi
done
echo $ret
