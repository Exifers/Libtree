#/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

bin=$(find . -name "tc")

if [ "./tc" = "$bin" ] ; then
  echo "Found ./tc binary"
else
  echo "tc binary not found, compiling ..."
  make
fi

echo "Running testsuite ..."

rm -f error.log

tests=$(find tests/grammar -name "*.tig")
nb_errors=0
nb_tests=$(find tests/grammar -name "*.tig" | wc -l)

for file in $tests; do
  ret=$(./tc < $file 2>>error.log ; echo $?)
  if [ "$ret" -ne "0" ]; then
    echo "${RED}Test have failed : $file (return status: $ret)${NC}"
    echo "^ from test at : $file" >> error.log
    nb_errors=$((nb_errors + 1))
  fi
done

if [ "$nb_errors" -ne 0 ]; then
  echo "${RED}$nb_errors${NC}/$nb_tests error(s) found"
  echo "See error.log for more information"
else
  echo "${GREEN}$nb_tests tests have been performed"
  echo "No error has been found${NC}"
fi
