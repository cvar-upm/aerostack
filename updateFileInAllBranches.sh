#!/bin/bash

FILE_TO_UPDATE=$1


branches=()
eval "$(git for-each-ref --shell --format='branches+=(%(refname))' refs/heads/)"
for branch in "${branches[@]}"; do
  if [[ "${branch}" != "master" ]]; then
    git checkout ${branch}
    git checkout master -- $FILE_TO_UPDATE        
  fi
done
