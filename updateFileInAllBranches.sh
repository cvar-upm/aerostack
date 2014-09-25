#!/bin/bash

FILE_TO_UPDATE=$1
COMMIT_MSG=$2


branches=()
eval "$(git for-each-ref --shell --format='branches+=(%(refname))' refs/heads/)"



for branch in "${branches[@]}"; do
	branch_filt=${branch##"refs/heads/"}

	if [[ "${branch_filt}" != "master" ]]; then
		echo $branch_filt
	    	git checkout ${branch_filt}
	    	git checkout master -- $FILE_TO_UPDATE 
#		git commit -m $COMMIT_MSG
	fi
done
