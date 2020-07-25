---
layout: post
title:  "Configuring the All-in-One Server"
date:   2020-01-21
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript CICD Jenkins DigitalOcean Apache
---

In this post I'm basically starting the CI/CD pipeline from scratch on a new server - this time I'll keep it running 24/7 so I can get moving on the projects that will interact with it. This involves setting up Jenkins and the CI/CD pipeline again, configuring Apache as a reverse proxy and finally adding an SSL certificate to implement HTTPS for added security.

<!--more-->

I've been playing around with the CI/CD pipeline and my Hello World Node-App for quite some time, each time I'd get a chance to work on it I'd re-create the snapshots in new droplets, reconfigure and continue on. Now I'm looking at finalising the security and having the server run 24/7 to get moving on some of these other projects I want to get communicating with the server. To save on costs, I've decided to combine the Jenkins and Node-App server so I don't need to recreate and reconfigure the Jenkins one anymore.

## Recreating the Jenkins CI/CD Pipeline

I first created a new Ubuntu 18.04 droplet on Digital Ocean, set up a new admin user and [followed my previous blog post]({% post_url 2019-09-03-ci-cd-node-jenkins-jenkins-setup %}) to set up Jenkins on this new server.

```sh
adduser --system --group twulz
mkdir /home/twulz/.ssh
chmod 0700 /home/twulz/.ssh/
cp -Rfv /root/.ssh /home/twulz/
sudo cp -Rfv /root/.ssh /home/twulz/
```

To minimise issues and to isolate them step-by-step I decided to first set it up without the deploy script in the pipeline so my Jenkins `Execute Shell` script looked like this:

```sh
npm install
./script/test
#./script/deploy
```

Success! The build and test steps worked without a problem. Then I updated the deploy script to account for local deployment and added deploy back in to the build step... Fail:

```sh
cd ~/node-app
git pull
npm install -—production
pm2 restart all
exit
```

Error message:
```
+ ./script/deploy
./script/deploy: 2: cd: can't cd to /var/lib/jenkins/node-app
```

Whoops, I had created the directory as the Twulz user and the jenkins user couldn't access it. I'd also forgotten to start the process in order to "restart" it:

```sh
cd /var/lib/jenkins
sudo chown jenkins:jenkins -R ./node-app
git pull
pm2 status
pm2 start index.js
```

To ensure the process manager `pm2` starts when the Node-App server boots, I followed [this tutorial][pm2-tutorial]. `pm2` comes with an in-built command that gives you the command you need to run as admin to start pm2 on boot:

```sh
pm2 startup
sudo env PATH=$PATH:/usr/bin /usr/local/lib/node_modules/pm2/bin/pm2 startup systemd -u twulz --hp /home/twulz
cd node-app/
pm2 start index.js
pm2 save
```

I then thought that the script should be able to deal with either starting _or_ restarting the process, so I updated the deploy script:

```
#!/bin/sh
cd ~/node-app
git pull
npm install -—production
(pm2 restart node-app) || (pm2 start index.js --name "node-app")
exit
```

Success! CI/CD Pipeline was all set up again - this time on the same server.

## Reconfiguring the Apache reverse proxy

I [followed another of my blog posts]({ % post_url 2019-12-10-apache-reverse-proxy-for-node-app-server}) to install and configure Apache web server to handle the requests so I could once again only accept local requests to my node-server and have everything else handled by Apache. Here are the commands I used:

```
sudo apt-get update
sudo apt-get install
sudo apt-get install apache2
sudo apache2ctl TwulzServer
sudo apache2ctl configtest
sudo nano /etc/apache2/apache2.conf
sudo apache2ctl configtest
sudo systemctl restart apache2
sudo ufw app list
sudo ufw app info "Apache Full"
sudo ufw allow in "Apache Full"
sudo a2enmod proxy
sudo a2enmod proxy_http
sudo a2enmod proxy_balancer
sudo a2enmod lbmethod_byrequests
sudo systemctl restart apache2
sudo nano /etc/apache2/sites-available/000-default.conf
sudo systemctl restart apache2
```

Success! When I navigated to http://IP_ADDRESS/ I got my server output:
```json
{"status":200,"error":null,"response":"Hello World! Server Success!"}
```

The last step to get back to where I was before was I also had to re-instate the change to index.js to only accept requests from localhost:

```js
// Start the server
if(!module.parent){
    var server = app.listen(process.env.PORT || 3000, 'localhost', function() {
        console.log('Server started on port 3000...');
    });
}
```

Done! Now I can finally register a domain name and add HTTPS support to finish off the setup.

[pm2-tutorial]: https://futurestud.io/tutorials/pm2-restart-processes-after-system-reboot