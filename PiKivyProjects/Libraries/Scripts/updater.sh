
DPEA_REPO_ROOT=~/git/

if test "$#" -ne 1; then
    echo "Usage: updater.sh 'Project Name'"
    echo ""
    echo "example: . updater.sh InfinityMirrorPie"
    echo ""
    return
fi

if [ -z "$DPEA_REPO_ROOT" ]; then
    echo ""
    echo "You must set the 'DPEA_REPO_ROOT' env variable to the root of the project"
    echo ""
    echo "example: export DPEA_REPO_ROOT=~/git/"
    return
fi

pushd `pwd`
echo  "Checking updates for $1"
cd $DPEA_REPO_ROOT/$1

git fetch
git diff --quiet origin/HEAD --
result=$?
if [ $result -ne 0 ]; then
    echo "Update needed"
    git pull https://<USERNAME>:<PASSWORD>@github.com/dpengineering/$1
fi

popd
