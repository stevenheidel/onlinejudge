prob=$1

set -x

for i in $(seq 0 9); do
    if [ -f ./data/$prob$prob/$prob.$i.in ]; then
        ./$prob/$prob < ./data/$prob$prob/$prob.$i.in | diff - ./data/$prob$prob/$prob.$i.ans
    fi
done
