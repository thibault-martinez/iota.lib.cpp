date > tmpfile
git remote rm origin && git remote add origin https://github.com/$TRAVIS_REPO_SLUG
git fetch origin
git checkout -b $TRAVIS_PULL_REQUEST_BRANCH origin/$TRAVIS_PULL_REQUEST_BRANCH
git add tmpfile
git commit -m 'performance report [CI SKIP]'
git push https://${GH_TOKEN}@github.com/$TRAVIS_REPO_SLUG $TRAVIS_PULL_REQUEST_BRANCH
curl -H "Authorization: token ${GH_TOKEN}" -X POST -d "{\"body\": \"Hello world\"}" "https://api.github.com/repos/${TRAVIS_REPO_SLUG}/issues/${TRAVIS_PULL_REQUEST}/comments"
  
