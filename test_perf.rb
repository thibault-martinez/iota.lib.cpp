# Check we have the required environment variables
if not ENV['TRAVIS_PULL_REQUEST'] or not ENV['TRAVIS_REPO_SLUG'] or not ENV['GH_TOKEN'] or not ENV['TRAVIS_PULL_REQUEST_BRANCH']
  puts "Environment misconfiguration"
  exit
end

# Basic init
result      = ""
decrease    = ""
improvement = ""
notif       = ""

# Get report from master branch
`git checkout master -- test_perf_result`

# For each test
#  > get execution time
#  > check if there is major regression or improvement
#  > update the performance report
Dir['build/bin/*_test'].each do |f|
  start_time  = Time.now
  `$(#{f} 1> /dev/null 2> /dev/null)`
  end_time    = Time.now
  total_time  = end_time - start_time

  prev_perf    = `cat test_perf_result | grep #{f} | cut -d ' ' -f 2`.to_f
  higher_bound = prev_perf + (total_time * 25 / 100)
  lower_bound  = prev_perf - (total_time * 25 / 100)
  diff         = (total_time - prev_perf) * 100 / prev_perf

  if total_time > higher_bound
    decrease += "#{f}: was #{prev_perf}, now #{total_time} (+#{'%0.02f' % diff}%)\n"
  elsif total_time < lower_bound
    improvement += "#{f}: was #{prev_perf}, now #{total_time} (#{'%0.02f' % diff}%)\n"
  end

  result += "#{f} #{total_time}\n"
end

# Update the performance report
`echo '#{result}' > test_perf_result`

# Setup regression report
if not decrease.empty?
  notif += "# Performance degradation report\n"
  notif += decrease
end

# Setup improvement report
if not improvement.empty?
  notif += "# Performance improvement report\n"
  notif += improvement
end

# Setup no change report
if notif.empty?
  notif += 'No major performance regression or improvement\n'
end

# Notify
`curl -H "Authorization: token ${GH_TOKEN}" -X POST -d '{"body": "#{notif}"}' "https://api.github.com/repos/${TRAVIS_REPO_SLUG}/issues/${TRAVIS_PULL_REQUEST}/comments"`
exit
# Push the updated perf report
`git remote rm origin && git remote add origin https://github.com/$TRAVIS_REPO_SLUG`
`git fetch origin`
`git checkout -b $TRAVIS_PULL_REQUEST_BRANCH origin/$TRAVIS_PULL_REQUEST_BRANCH`
`git add test_perf_result`
`git commit -m 'performance report [CI SKIP]'`
`git push https://${GH_TOKEN}@github.com/$TRAVIS_REPO_SLUG $TRAVIS_PULL_REQUEST_BRANCH`
