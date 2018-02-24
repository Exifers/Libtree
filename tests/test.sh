#/bin/sh

RED='\33[31m'
GREEN='\33[32m'
NC='\33[0m'

bin=$(find . -name "tc")

if [ ! -z $bin ]; then
  printf "Found ./tc binary as $bin\n"
else
  printf "Cannot find tc binary"
  exit 1
fi

printf "Running testsuite ...\n"

rm -f error.log

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

for file in $tests; do
  ret=$($bin $file 2>> error.log 1>/dev/null ; printf $?)
  if [ "$ret" -ne "0" ]; then
    printf "${RED}Test have failed : $file (return status: $ret)${NC}\n"
    printf "^ from test at : $file\n" >> error.log
    nb_errors=$((nb_errors + 1))
  fi
done

if [ "$nb_errors" -ne 0 ]; then
  printf "${RED}$nb_errors${NC}/$nb_tests error(s) found\n"
  printf "See error.log for more information\n"
else
  printf "${GREEN}$nb_tests tests have been performed\n"
  printf "No error has been found${NC}\n"
fi
