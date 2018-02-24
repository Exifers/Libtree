#! /bin/sh

for file in $(find . -name "*.tig"); do
  content=$(cat $file)
  if [ -z "$content" ]; then
    echo $file
  fi
done
