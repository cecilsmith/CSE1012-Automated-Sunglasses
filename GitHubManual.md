# Git Help

For this quick guide, the assumption will be made that the user will have Git installed. To install Git, refer to [this](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) link.



## Initial Git Install

To get this repo in your local filesystem, first navigate to your folder of choice in terminal.

Then, run the following:

` git clone https://github.com/cecilsmith/EE1301-Cloud-Lock.git `

This will download the repository into the folder.



## Updating your local repository

Before you work on the repository, it is best practice to make sure you have the most up-to-date version. To do this, navigate to your repository and run:

` git pull origin `

Now, your local version will be up-to-date with the online version.



## Check your repo for changes/status updates

Before you push changes, it is often in your best interest to check what you have changed. This is especially useful if you have been making meaningless changes to files. To do this simply enter:

` git status `

Untracked filed will be highlighted in red. Tracked files (ones that will be pushed to the repo) are highlighted in green.

NOTE: Always add your files you wish to commit before pushing to the repo.


## Pushing your changes to GitHub

When you are satisfied with your changes, and have "`git add`ed" all the files you wish to update, you can push your changes to GitHub using the following commands in Terminal:

`git commit -a -m "TYPE YOUR COMMIT MESSAGE HERE"`

`git push`

## Alternatives

If this seems too complicated, you can also access this all quite easily via the VSCode application. You must download the repo through `git clone`, but once it has been downloaded, you can manage and push the files through the `Source Control` sidebar.  
