---
layout: post
title:  "CI/CD Pipeline using Node.js and Jenkins - 6: Creating and Destroying Droplets"
date:   2019-10-15
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript CICD Jenkins DigitalOcean
---

After getting my CI/CD pipeline up and running, I needed an easier way to create droplets from snapshots so that process wasn't so time-consuming.

<!--more-->

## Parameterising the Node-App IP Address:

With my current setup, if I take a snapshot and destroy the Node-App server, when I re-create the server from the snapshot in another droplet it will have a different IP address. The IP address is hard-coded into the deploy script so each time I create it, I would need to commit new code to be able to deploy.

To get over this hurdle, I parameterised the deploy script to accept the IP address as a command line argument, so the IP address could be configured in the Jenkins config, instead of within the code itself.

```sh
#!/bin/sh
ssh twulz@$1 <<EOF
 cd ~/node-app
 git pull
 npm install -—production
 pm2 restart all
 exit
EOF
```

So now the Build `Execute Shell` script reads:

```sh
whoami
npm install
./script/test
./script/deploy 157.245.55.163 #IP address of node-app server.
```

So each time the Node-App server address changes, just need to update that parameter to the new IP on the Jenkins server, without needing a new commit to git.

### To spin up a new Jenkins droplet:
1. Use the previous droplet snapshot.
2. Wait for it to be live, then copy the new IP address
3. Update the webhook in [Github](https://developer.github.com/webhooks/)
4. Done! Any new commits will automatically deploy to the Node-App server.

### To spin up a new Node-App droplet:
1. Create the droplet from the snapshot
1. Wait for it to be live, then copy the new IP address
1. Update the IP address in the jenkins config: http://jenkins-ip-address:8080/job/node-app/configure 
1. ssh into the jenkins droplet (may need to login as root or twulz then `su - jenkins`)
1. ssh from jenkins droplet into node-app droplet once `ssh twulz@node-ip-address`, answer "yes", this adds it to a known hosts file.
1. in the node-app server, start pm2: `pm2 start index.js`
1. Now if you hit "Build now" in Jenkins, it should build and deploy: http://jenkins-ip-address:8080/