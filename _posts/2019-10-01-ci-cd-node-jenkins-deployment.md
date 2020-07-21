---
layout: post
title:  "CI/CD Pipeline using Node.js and Jenkins - 5: Deployment"
date:   2019-10-01
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript CICD Jenkins
---

Now that the Continuous Integration part of my pipeline was working, today I got the Continuous Delivery/Deployment part working to automatically deploy to the live server.

<!--more-->

## Deployment

I am still following [this tutorial][medium-tutorial] to get this pipeline working:

First, ssh into the jenkins server and switch to the jenkins user

```sh
su — jenkins
```

There was no password! This lets you set the new password and switch to the jenkins user again. 

```sh
sudo passwd jenkins
su - jenkins
```

Now need to generate a new public key:
```sh
ssh-keygen -t rsa
cat ~/.ssh/id_rsa.pub
```

Copy that to clipboard, then ssh into node server as twulz:

```sh
nano ~/.ssh/authorized_keys
```

Paste the copied ssh key into that file and change the permissions:
```sh
chmod 700 ~/.ssh
chmod 600 ~/.ssh/*
```

Then test the ssh setup by sshing into the node-app server from the jenkins server:
```sh
ssh twulz@157.245.55.163
```

YAY! Now that I've got the correct permissions, I can create the deployment file:

```sh
#!/bin/sh
ssh twulz@157.245.55.163 <<EOF
 cd ~/node-app
 git pull
 npm install —-production
 pm2 restart all
 exit
EOF
```

I need to make it executable:
```sh
chmod +x script/deploy
```

And back in the Jenkins console, I need to add the command to the `Execute Shell` script config:
```sh
whoami 
npm install
./script/test
./script/deploy
```

The build was failing because the service wasn't started:
```
[PM2][WARN] No process found
┌──────────┬────┬─────────┬──────┬─────┬────────┬─────────┬────────┬─────┬─────┬──────┬──────────┐
│ App name │ id │ version │ mode │ pid │ status │ restart │ uptime │ cpu │ mem │ user │ watching │
└──────────┴────┴─────────┴──────┴─────┴────────┴─────────┴────────┴─────┴─────┴──────┴──────────┘
 Use `pm2 show <id|name>` to get more details about an app
Build step 'Execute shell' marked build as failure
Finished: FAILURE
```
So I ran this, then success!
```
sudo pm2 start /home/twulz/node-app/index.js
```

## Add the dev-server configuration to the Node-App

This is a last step just for future development - currently, during development of the Node.js server I have to save the file, stop the server and re-start the server to see the updates. Using the Node-dev package, this detects any changes to the server and automatically restarts it to reflect the changes.

```
$ cd Documents\Github\node-app
$ git pull
$ npm install
$ node index.js
```

Then made some changes to the code, needed to add some dependencies:

`npm install morgan --save-prod` saves it to the dependencies in package.json. Also needed `npm install node-dev --save-dev` saves it to the devDependencies section in package.json

Then added scripts to package.json:
```
"scripts": {
    "dev-server": "./node_modules/.bin/node-dev ./index.js"
},
```

Now when I make changes it'll automatically restart the server

## Done!

Et voila! The CI/CD pipeline is up and running! Now whenever I commit code to GitHub:
1. GitHub notifies the Jenkins server 
1. Jenkins server then pulls the code into a local setup
1. It then runs the automated tests
1. If the tests pass, deploy to the Node-App live server.

Next steps will be doing something a little more exciting than printing some variation of "Hello World!"

[medium-tutorial]: https://medium.com/@mosheezderman/how-to-set-up-ci-cd-pipeline-for-a-node-js-app-with-jenkins-c51581cc783c