---
layout: post
title:  "Jenkins Updates for the Server-App"
date:   2021-08-31
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript CICD Jenkins
---

In this post I finally revisit my server app and update Jenkins to the latest version and some other maintenance and improvement tasks.

<!--more-->

## Updating Jenkins and npm

I've been long dreading upgrading my environment because I didn't want to deal with breaking changes but it's time to bite the bullet and take advantage particularly of the security enhancements of the latest updates. So I did a standard update of all my packages (because I also installed Jenkins from the command line, this includes Jenkins).

```sh
sudo apt update
sudo apt upgrade
```

Logging into Jenkins I realised that it now required JDK 11 (I had JDK 8) so this is just another set of commands:

```sh
sudo apt-get install openjdk-11-jdk
systemctl restart jenkins
```

Now I needed to log into Jenkins and go to `Dashboard -> Manage Plugins` to update all the plugins, I had to do this a few times as I think some plugins had dependencies, etc.

Yay! Now Jenkins was all updated, I did a test build and surprisingly didn't break anything - I need to try harder!

I also updated npm itself:

```sh
sudo npm install -g npm
```

I had to do this in both my local environment and production. In my local environment I needed to commit the `package-lock.json` file as it was updated to the latest version.

## Moving Jenkins to use a separate database for testing

My initial setup for the project included automated testing for my deployments but as I was just focussed on getting it up and running I was running my tests on the same database as production while I was still setting it up. This is obviously bad and in great need of update.

I had setup the project using environment variables so this actually turned out to be quite an easy change; I logged in to phpmyadmin and created a new database imaginatively called `twulzservertest`. Then I just needed to update the environment variables for the Jenkins build to point to this database instead:

```sh
cd /var/lib/jenkins/workspace/Node-App
sudo nano .env
```

In this file I replaced my old database name `twulzserver` with `twulzservertest` and clicked `Build Now` in the Jenkins GUI. I could verify that all the tables and test data were created in the new database using the phpmyadmin interface - easy!

## Add the Server Homepage as a project in Jenkins

Finally I wanted to make sure any changes I made to the Server Homepage I made in a [previous blog post]({% post_url 2021-08-28-domain-security-updates%}) would be automatically deployed to the server, because who can be bothered with manual deployments!?

I added a new item to Jenkins and configured it to point to the new github repo; there's no building or testing required here so it just does a `git pull` after a new commit is detected on master.

![Git setup in Jenkins](/images/server/15_homepage_jenkins.png)

![Build setup in Jenkins](/images/server/16_homepage_jenkins.png)

And done! Now any changes I make to the homepage will be automatically deployed after pushing to the master branch.