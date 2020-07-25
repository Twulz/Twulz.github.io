---
layout: post
title:  "CI/CD Pipeline using Node.js and Jenkins - 3: Configure Jenkins"
date:   2019-09-03
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript CICD Jenkins Git
---

Today I'm carrying on with my CI/CD pipeline by creating the Jenkins server that will do the automated testing and deployment of the Node-App.

<!--more-->

## Create Droplet and Configure User Permissions from Scratch

Select "Ubuntu" from the "distributions" menu - version 18.04.

Log in as root user using my ssh key/password

```sh
adduser --system --group twulz
mkdir /home/twulz/.ssh
chmod 0700 /home/twulz/.ssh/
cp -Rfv /root/.ssh /home/twulz/
chown -Rfv twulz.twulz /home/twulz/.ssh
chown -R twulz:twulz /home/twulz/
gpasswd -a twulz sudo
echo "twulz ALL=(ALL) NOPASSWD: ALL" | (EDITOR="tee -a" visudo)
service ssh restart
usermod -s /bin/bash twulz
exit
```

Then re-connect using PuTTY and login as twulz (using the ssh passkey).

## Java 8 install
Jenkins still uses Java 8 instead of the default of Java 9 (Ubuntu 18.04) so I had to install Java 8 as default first, but I need to add the 'universe' repo to do so:

```sh
sudo add-apt-repository universe
sudo apt install openjdk-8-jdk
java -version
```

This had the correct output according to [these instructions][install java].

## Jenkins install

The [Jenkins docs][jenkins-docs] provide the instructions of installing Jenkins using `apt-get`.

```sh
wget -q -O - https://pkg.jenkins.io/debian/jenkins.io.key | sudo apt-key add -
sudo sh -c 'echo deb http://pkg.jenkins.io/debian-stable binary/ > /etc/apt/sources.list.d/jenkins.list'
sudo apt update
sudo apt install jenkins
sudo systemctl start jenkins
sudo systemctl status jenkins
```

Then I needed to activate OpenSSH and activate the firewall:

```sh
sudo ufw allow OpenSSH
sudo ufw enable
```

Finally - open port 8080 which is the one used for jenkins:

```sh
sudo ufw allow 8080
sudo ufw status
```

I then took a snapshot here just in case!

## Configure Jenkins

Jenkins is installed, so to configure I went to `http://IP_ADDRESS:8080`. To log in, you need to view the file at
`/var/lib/jenkins/secrets/initialAdminPassword`:

```sh
sudo cat /var/lib/jenkins/secrets/initialAdminPassword
```

In classic hacker style - *I'm IN*, so next I had to set it up with a user and password and all of the following settings:

![Jenkins configuration](/images/server/01_jenkins_setup.JPG)

Note the Repo URL, GitHub hook trigger and the script in the Build section:
```sh
npm install
./script/test
```

Next I had to configure the webhook so GitHub would tell Jenkins every time there was a new commit, so within the GitHub repo settings, add the `https://IP-ADDRESS/github-webhook/` Payload URL.

![Github webhook lookup](/images/server/02_webhook_setup.JPG)

## Testing

So after all of this setup, I tried selecting `Build Now` to test what I've done so far... aaaand there's an error: `npm: not found`. I'll be tackling that next time!

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

[medium-tutorial]: https://medium.com/@mosheezderman/how-to-set-up-ci-cd-pipeline-for-a-node-js-app-with-jenkins-c51581cc783c
[install java]: https://www.digitalocean.com/community/tutorials/how-to-install-java-with-apt-on-ubuntu-18-04#installing-specific-versions-of-openjdk
[jenkins-docs]: https://wiki.jenkins.io/display/JENKINS/Installing+Jenkins+on+Ubuntu
[install-node]: https://wiki.jenkins.io/display/JENKINS/NodeJS+Plugin