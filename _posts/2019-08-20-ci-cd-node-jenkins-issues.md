---
layout: post
title:  "CI/CD Pipeline using Node.js and Jenkins - 2: Security Issues"
date:   2019-08-20
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript CICD Jenkins
---

In my last blog post I set up the HelloWorld Node.js app on a Digital Ocean droplet. Today, I had a few security and access issues when re-creating the server using the snapshot I took previously.

<!--more-->

## Create a new SSH key for my laptop

I initially created the project using my desktop so now to connect to my droplets I needed to create a new key-value pair to use with my laptop.

I used puttygen to create another key-value pair and copied this to security section of DigitalOcean.

To add this to the droplet I created last time, I re-created the droplet from the snapshot I'd taken and selected `All SSH pairs` under the security section. This means that I can log in from either my laptop or desktop.

## Problem: I couldn't log in as non-root

After setting all that up - there was another problem. I couldn't log in as a non-root user. So I logged in as the root user.

First, I checked if my `twulz` user still existed using `getent passwd | grep twulz`
yep it exists!

After some googling, the problem was that the .ssh directory was for the root user, but wasn't copied to the twulz user, so to fix I did the following commands:

```
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
```

## Problem: Node-app wasn't auto-starting on a new droplet:

After taking a snapshot, destroying the droplet and re-creating the Node-app server, I had to restart pm2:

1. Create the droplet from the snapshot
1. Sign in to twulz user
1. Move to the `/node-app/` folder `cd node-app`
1. Start pm2: `pm2 start index.js`
1. Go to `http://IP-ADDRESS:3000`

This post is short and sweet because I spent way too much time on the ssh problem!