## How to Fix a Corrupted Git Repository
The virtual box sometimes has a network disconnect, which can cause a repository to become corrupted. There are a couple ways to fix this.

(1) Easy way. Reclone your repo from github (this will not be corrupt). Copy across the files that you'd changed on your local repo from the old corrupt repo to new clean one. Commit and push tags from the new local repo.

(2) Harder way, try to fix the corrupt repo. You can try to diagnose the repo with `git fsck` and see if you can spot what has happened. This could occur because of a missing local commit, your computer turning off mid-push, etc. There are lots of stack overflow posts you can try to follow for your specific case (e.g. https://stackoverflow.com/questions/11706215/how-to-fix-git-error-object-file-is-empty).