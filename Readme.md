install and run
sudo apt-get install freeglut3-dev
make clean && make
./op

git checkout master (go to master branch for dev)
git pull (get up to date with remote changes from other contributors)

--when ready--

git add <file changed>
git commit -m "prefix message" where prefix is [fix] if you fixed something or [feat] if you created a feature
git push

this will create a PR (pull request) for me to review