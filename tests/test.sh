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
  printf "Cannot find tc binary\n"
  exit 1
fi

printf "Running testsuite ...\n\n"

rm -f error.log

##########################
# Looking for test suite #
##########################
srch_dir='.'
tests=$(find "$srch_dir/tests/" -name "*.tig" | sort)
if [ -z "$tests" ]; then
  srch_dir='..'
  tests=$(find ../tests/ -name "*.tig" | sort)
  if [ -z "$tests" ] ; then
    printf "Cannot find tests to perform\n"
    exit 2
  fi
fi
nb_errors=0
nb_tests=$(find $srch_dir/tests/ -name "*.tig" | wc -l)

print_results ()
{
  printf "$2 preformed\n"
  printf "$3 empty\n"
  nb_success=$(($2 - $1))
  printf "${GREEN}$nb_success${NC}/$2 passed\n"
  printf "${RED}$1${NC}/$2 error(s) found\n"
  printf "\n"
}

cur_errors=0
cur_nb_tests=0
skipped=0


####################
# Performing tests #
####################
last_error_st=0
for file in $tests; do

  if [ $(wc -c < "$file") -eq "0" ]; then
    nb_tests=$((nb_tests - 1))
    skipped=$((skipped + 1))
    continue
  fi

  cur_nb_tests=$((cur_nb_tests + 1))

  if [[ "$file" =~ .*lexicon.* ]]; then
    error_st=2
    if [ "$error_st" -ne "$last_error_st" ]; then
      if [ "$last_error_st" -ne "0" ];then
        print_results $cur_errors $cur_nb_tests $skipped
        cur_errors=0
        cur_nb_tests=0
        skipped=0
      fi
      printf "=== LEXICON ===\n"
      last_error_st=$error_st
    fi
  elif [[ "$file" =~ .*grammar.* ]]; then
    error_st=3
    if [ "$error_st" -ne "$last_error_st" ]; then
      if [ "$last_error_st" -ne "0" ];then
        print_results $cur_errors $cur_nb_tests $skipped
        cur_errors=0
        cur_nb_tests=0
        skipped=0
      fi
      printf "=== GRAMMAR ===\n"
      last_error_st=$error_st
    fi
  elif [[ "$file" =~ .*ast.* ]]; then
    error_st="not zero"
    if [ "$error_st" -ne "$last_error_st" ]; then
      if [ "$last_error_st" -ne "0" ];then
        print_results $cur_errors $cur_nb_tests $skipped
        cur_errors=0
        cur_nb_tests=0
        skipped=0
      fi
      printf "=== PRETTY PRINTER ===\n"
      last_error_st=$error_st
    fi
  elif [[ "$file" =~ .*binding.* ]]; then
    error_st=4
    if [ "$error_st" -ne "$last_error_st" ]; then
      if [ "$last_error_st" -ne "0" ];then
        print_results $cur_errors $cur_nb_tests $skipped
        cur_errors=0
        cur_nb_tests=0
        skipped=0
      fi
      printf "=== BINDING ===\n"
      last_error_st=$error_st
    fi
  else
    error_st=-1
    if [ "$error_st" -ne "$last_error_st" ]; then
      if [ "$last_error_st" -ne "0" ];then
        print_results $cur_errors $cur_nb_tests $skipped
        cur_errors=0
        cur_nb_tests=0
        skipped=0
      fi
      printf "=== ADDITIONAL ===\n"
      last_error_st=$error_st
    fi
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
      cur_errors=$((cur_errors + 1))
    fi
  else
    if [ "$ret" -gt "$error_st" -o "$ret" -eq "0" ]; then
      printf "${RED}Test have failed : $file (return status: $ret)${NC}\n"
      printf "^ from test at : $file\n" >> error.log
      nb_errors=$((nb_errors + 1))
      cur_errors=$((cur_errors + 1))
    fi
  fi

done

print_results $cur_errors $cur_nb_tests $skipped

######################
# Displaying results #
######################
printf "\nTOTAL ---\n"
if [ "$nb_errors" -ne 0 ]; then
  success=$((nb_tests - nb_errors))
  printf "${GREEN}$success${NC}/$nb_tests tests passed\n"
  printf "${RED}$nb_errors${NC}/$nb_tests error(s) found\n"
  printf "See error.log for more information\n"
else
  printf "${GREEN}$nb_tests tests have been performed\n"
  printf "No error has been found${NC}\n"
fi


cat $srch_dir/tests/tiger.ascii
