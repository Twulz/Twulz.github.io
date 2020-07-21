---
layout: post
title:  "CI/CD Pipeline using Node.js and Jenkins - 4: Jenkins Issues"
date:   2019-09-17
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript CICD Git
---

Last time I did the initial configuration of Jenkins but I'm having a few issues. Today I'll be troubleshooting these issues and making sure GitHub and Jenkins are hooked up correctly, and that all the automated tests run and pass successfully.

<!--more-->

## Problem: NPM not found

Last time when I clicked the "Build now" link in Jenkins to test the new setup, and got an error: `Error: npm: not found`

```sh
Started by user Alicia
Running as SYSTEM
Building in workspace /var/lib/jenkins/workspace/node-app
No credentials specified
 > git rev-parse --is-inside-work-tree # timeout=10
Fetching changes from the remote Git repository
 > git config remote.origin.url https://github.com/Twulz/node-app.git # timeout=10
Fetching upstream changes from https://github.com/Twulz/node-app.git
 > git --version # timeout=10
 > git fetch --tags --progress -- https://github.com/Twulz/node-app.git +refs/heads/*:refs/remotes/origin/*
 > git rev-parse refs/remotes/origin/master^{commit} # timeout=10
 > git rev-parse refs/remotes/origin/origin/master^{commit} # timeout=10
Checking out Revision 81d9f909cfd34cd5eb65a123dd9f2a1e67686512 (refs/remotes/origin/master)
 > git config core.sparsecheckout # timeout=10
 > git checkout -f 81d9f909cfd34cd5eb65a123dd9f2a1e67686512
Commit message: "Solve vulnerabilities"
 > git rev-list --no-walk 81d9f909cfd34cd5eb65a123dd9f2a1e67686512 # timeout=10
[node-app] $ /bin/sh -xe /tmp/jenkins7265834994987103977.sh
+ npm install
/tmp/jenkins7265834994987103977.sh: 2: /tmp/jenkins7265834994987103977.sh: npm: not found
Build step 'Execute shell' marked build as failure
Finished: FAILURE
```

I checked the Build environment in Jenkins:

![No NodeJS installation?](/images/server/03_add_npm_to_path.JPG)

**Solution:** I hadn't configured NodeJS plugin for Jenkins!
So I followed [these instructions][install-node] to install Node within Jenkins.


![Add NodeJS installation to jenkins](/images/server/04_add_NodeJS_installer.JPG)

This then meant that there was a Node.js installation to choose in the Build Environment page again:

![Now add npm to path](/images/server/05_add_npm_to_path.JPG)

## Problem: Permission denied

With Node installed and configured correctly I tried building again - now there is a `Permission denied` error on the `./script/test` shell script.

```sh
Started by user Alicia
Running as SYSTEM
Building in workspace /var/lib/jenkins/workspace/node-app
No credentials specified
 > git rev-parse --is-inside-work-tree # timeout=10
Fetching changes from the remote Git repository
 > git config remote.origin.url https://github.com/Twulz/node-app.git # timeout=10
Fetching upstream changes from https://github.com/Twulz/node-app.git
 > git --version # timeout=10
 > git fetch --tags --progress -- https://github.com/Twulz/node-app.git +refs/heads/*:refs/remotes/origin/*
 > git rev-parse refs/remotes/origin/master^{commit} # timeout=10
 > git rev-parse refs/remotes/origin/origin/master^{commit} # timeout=10
Checking out Revision 81d9f909cfd34cd5eb65a123dd9f2a1e67686512 (refs/remotes/origin/master)
 > git config core.sparsecheckout # timeout=10
 > git checkout -f 81d9f909cfd34cd5eb65a123dd9f2a1e67686512
Commit message: "Solve vulnerabilities"
 > git rev-list --no-walk 81d9f909cfd34cd5eb65a123dd9f2a1e67686512 # timeout=10
Unpacking https://nodejs.org/dist/v12.10.0/node-v12.10.0-linux-x64.tar.gz to /var/lib/jenkins/tools/jenkins.plugins.nodejs.tools.NodeJSInstallation/NodeJS on Jenkins
[node-app] $ /bin/sh -xe /tmp/jenkins6895391044336724061.sh
+ npm install
added 621 packages from 1298 contributors and audited 12356 packages in 16.274s
found 0 vulnerabilities

+ ./script/test
/tmp/jenkins6895391044336724061.sh: 3: /tmp/jenkins6895391044336724061.sh: ./script/test: Permission denied
Build step 'Execute shell' marked build as failure
Finished: FAILURE
```

Tried to change the permissions for the whole node-app folder (using PuTTY):

```sh
sudo chmod -R 757 /var/lib/jenkins/workspace/node-app
sudo systemctl restart jenkins
```

**Solution:** Each time I'd change the permissions I could run the shell script ok, but when I'd rebuild I'd get the `permission denied` error again.

Turns out that the execute permissions are saved by git, so each time when jenkins pulled the git repo, it overwrote the execute permissions. I'd intially created the repo on Windows so I just cloned it to a temp directory elsewhere on my jenkins droplet, reset the permissions, commit and push back to github. 

I spent ages on this, and because this was over a few weeks I didn't realise I'd written a note to myself about these permissions in a [previous post]({% post_url 2019-08-06-ci-cd-node-jenkins-helloworld-node-app %})! I should really keep up with these blog posts more frequently...

Here is how I fixed this permanently:

```sh
cd /tmp/
ls
git clone https://github.com/Twulz/node-app.git
cd node-app/
ls -la
cd script/
ls -la
cd ..
sudo chmod -R 757 node-app
cd node-app/script/
ls -la
cd node-app/
git commit -m "Update execute permissions"
git config --global user.email "myuser@thisisarealemail.com"
git config --global user.name "Twulz"
git add .
git status
git commit -m "Update execute permissions"
git push
git status
```

## Problem: Mocha tests hang

Then I found that mocha tests all ran and passed, but it "hangs" afterwards:
I found [this link][mocha_hangs] that mocha can hang after running all tests if you don't garbage collect properly (apparently my hello world test doesn't! Add it to the TODO list!).
So I added the --exit flag to the test script and the test finally PASSES!

```sh
#!/bin/sh

./node_modules/.bin/mocha ./test/test.js --exit
```

## Changing the jenkins success colour

Finally, this isn't very important functionality-wise, but it was driving me crazy! The colour of a successful build in Jenkind defaults to blue, so I downloaded a simple `Green Balls` add-on which changes this to green.

![Green balls](/images/server/06_green_balls.JPG)



[medium-tutorial]: https://medium.com/@mosheezderman/how-to-set-up-ci-cd-pipeline-for-a-node-js-app-with-jenkins-c51581cc783c
[install java]: https://www.digitalocean.com/community/tutorials/how-to-install-java-with-apt-on-ubuntu-18-04#installing-specific-versions-of-openjdk
[jenkins-docs]: https://wiki.jenkins.io/display/JENKINS/Installing+Jenkins+on+Ubuntu
[install-node]: https://wiki.jenkins.io/display/JENKINS/NodeJS+Plugin