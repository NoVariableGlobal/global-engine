# Set up the submodule so dependencies are properly included in the project:
git submodule init
git submodule update

# Define the hooks patch as $root/hooks over $root/.git/hooks so we can run our own hooks:
git config core.hooksPath hooks
