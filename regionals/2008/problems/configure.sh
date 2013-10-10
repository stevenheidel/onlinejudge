#!/bin/sh

export ACM_CONTEST_HOME=/usr/local/acm/rmrc2007

export ID_gpa=Q
export ID_account=R

export ID_graft=A
export ID_lookandsay=B
export ID_server=C
export ID_cointoss=D
export ID_vacation=E
export ID_baseball=F
export ID_teamwork=G
export ID_wavelet=H
export ID_addition=I

for problem_set in practice real
do
  . howard/$problem_set/probs
  for problem in $PROBS
  do
    ID=$(eval echo '$'ID_$problem)
    echo Problem $ID: $problem "("$problem_set/$problem")"
    /bin/rm -rf $problem
    mkdir $problem
    mkdir $problem/cases
    sed s/'$'ID/$ID/g < howard/$problem_set/html/$problem.html > $problem/$problem.html
    for i in `"$ACM_CONTEST_HOME/bin/img.pl" howard/$problem_set/html/$problem.html`
    do
      echo "howard/$problem_set/html/$i  -> $problem/$i"
      cp "howard/$problem_set/html/$i" "$problem/$i"
    done
    (cd $problem; /usr/local/acm/htmldoc/bin/htmldoc --quiet --webpage -t pdf -f $problem.pdf $problem.html)

    if [ -f howard/$problem_set/solns/${problem}.c ] ; then 
      cp howard/$problem_set/solns/${problem}.c $problem/$problem.c
    else
      cp howard/$problem_set/solns/${problem}.cc $problem/$problem.cpp
    fi
    (cd $problem; make -f "$ACM_CONTEST_HOME/config/Makefile" $problem.exe)

    for vext_in in c cc cpp
    do
      if [ -f "howard/$problem_set/verifiers/${problem}-verifier.$vext_in" ]
      then
        echo "found verifier for $problem."
        vext_out=$vext_in
        if [ "$vext_in" = "cc" ]
        then
          vext_out="cpp"
        fi
        cp howard/$problem_set/verifiers/${problem}-verifier.$vext_in $problem/${problem}-verifier.$vext_out
        (cd $problem; make -f "$ACM_CONTEST_HOME/config/Makefile" $problem-verifier.exe)
      fi
    done
       
    c=1
    while [ -f howard/$problem_set/data/$problem.in.$c ] 
    do
      src=howard/$problem_set/data
      b=$(($c-1))
      if [ -f $src/$problem.in.$c ] ; then
        if [ $c = 1 ] ; then
          dst=$problem/cases/"example"
        else
          dst=$problem/cases/"test"$b
        fi
	mkdir $dst
        "$ACM_CONTEST_HOME/bin/trim" <$src/$problem.in.$c >$dst/$problem.in
	if [ -f $src/$problem.out.$c ] ; then
          "$ACM_CONTEST_HOME/bin/trim" <$src/$problem.out.$c >$dst/$problem.out
        fi
      fi
      c=$(($c+1))
    done
  done
done