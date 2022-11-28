To create branches from main that can be merged into main with a pr: 

(if you haven't init)

git init

git remote add name url
  
 <br/>

git pull (you should see a new branch called main be created in your local repo)
  
git checkout main
  
git checkout -b new-branch-name main
  
--do your stuff in the branch--
  
git add .
  
git commit -m "msg" 
  
git push name (may have to --set-upstream)
  
go into github web client and create pr OR from vscode gh extension
  
