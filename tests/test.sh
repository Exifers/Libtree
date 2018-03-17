#/bin/sh

RED='\33[31m'
GREEN='\33[32m'
NC='\33[0m'

######################
# Looking for binary #
######################
bin=$(find . -name "tc")
if [ ! -z $bin ]; then
  printf "Found ./tc binary as $bin\n"
else
  printf "Cannot find tc binary"
  exit 1
fi

printf "Running testsuite ...\n"

rm -f error.log

##########################
# Looking for test suite #
##########################
srch_dir='.'
tests=$(find $srch_dir/tests/ -name "*.tig")
if [ -z "$tests" ]; then
  srch_dir='..'
  tests=$(find ../tests/ -name "*.tig")
  if [ -z "$tests" ] ; then
    printf "Cannot find tests to perform"
    exit 2
  fi
fi
nb_errors=0
nb_tests=$(find $srch_dir/tests/ -name "*.tig" | wc -l)


####################
# Performing tests #
####################
for file in $tests; do

  if [ $(wc -c < "$file") -eq "0" ]; then
    nb_tests=$((nb_tests - 1))
    continue
  fi

  if [[ "$file" =~ .*lexicon.* ]]; then
    error_st=2
  elif [[ "$file" =~ ".*grammar.*" ]]; then
    error_st=3
  elif [[ "$file" =~ ".*ast.*" ]]; then
    error_st="not zero"
  elif [[ "$file" =~ ".*binding.*" ]]; then
    error_st=4
  else
    error_st=-1
  fi

  if [[ "$file" =~ .*bad.* ]]; then
    typ="bad"
  else
    typ="good"
  fi

  ret=$($bin $file 2>> error.log 1>/dev/null ; printf $?)

  if [ $typ = "good" ]; then
    if [ "$ret" -le "$error_st" -a "$ret" -ne "0" ]; then
      printf "${RED}Test have failed : $file (return status: $ret)${NC}\n"
      printf "^ from test at : $file\n" >> error.log
      nb_errors=$((nb_errors + 1))
    fi
  else
    if [ "$ret" -gt "$error_st" -o "$ret" -eq "0" ]; then
      printf "${RED}Test have failed : $file (return status: $ret)${NC}\n"
      printf "^ from test at : $file\n" >> error.log
      nb_errors=$((nb_errors + 1))
    fi
  fi

done

######################
# Displaying results #
######################
if [ "$nb_errors" -ne 0 ]; then
  printf "${RED}$nb_errors${NC}/$nb_tests error(s) found\n"
  printf "See error.log for more information\n"
else
  printf "${GREEN}$nb_tests tests have been performed\n"
  printf "No error has been found${NC}\n"
fi
