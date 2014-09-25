#!/bin/bash

FILE_TO_UPDATE=$1
COMMIT_MSG=$2



branches=()
eval "$(git for-each-ref --shell --format='branches+=(%(refname))' refs/heads/)"

curr_branch=$(git symbolic-ref HEAD | sed -e 's,.*/\(.*\),\1,')


for branch in "${branches[@]}"; do
	branch_filt=${branch##"refs/heads/"}

	if [[ "${branch_filt}" != $curr_branch ]]; then
		echo "->Updating file $FILE_TO_UPDATE in branch $branch_filt, from branch $curr_branch"
		#echo $branch_filt
		#echo $FILE_TO_UPDATE
		#echo $COMMIT_MSG
	    	git checkout ${branch_filt}
	    	git checkout $curr_branch -- $FILE_TO_UPDATE 
		git add $FILE_TO_UPDATE
		git commit -m "$COMMIT_MSG"
		git push origin ${branch_filt}
	fi
done

#return to current branch
git checkout ${curr_branch}
