# CHEATSHEET FOR GIT
Doc link : https://docs.google.com/document/d/1D59fzwRLq1DTPpcYgdn-EVpa_uCQtdYn3rj3zrN0__0

### Get repository in local 
```
git clone [doc link]
```

# ALWAYS DO BEFORE MAKING CHANGES
### Get latest changes of the repository or branch
```
git fetch
git status (check for updates)
git pull (if need to update)
```

### Committing changes
```
git add . (if there's new files, do this to add them into tracking)
git commit -am "Commit message, write your changes here"
git push origin (Push the changes online if online)
```

### Branches
```
git checkout -b branchName (Create branch and switch into it)

git switch branchName (switch branch !fetch and pull if it's a online branch)

git push --set-upstream origin <branch_name> (Make branch available online)

git status (check your current branch and commit status)
git branch (check branches in your local machine)

git fetch
git branch -a (check branchs including branch in the git repo)
```

### Merge branches
```
git switch main (branch you want to apply change to)
git merge changes (branch wtih change)
git commit -am "Commit merge with changes"
git push origin (push if the branch is online)
```