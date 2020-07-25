---
layout: post
title:  "CI/CD Pipeline using Node.js and Jenkins - 1: Hello World Server App"
date:   2019-08-06
categories: Things Software Server-App
tags: Server-App Server NodeJs Javascript CICD DigitalOcean
related_image: 
  path: /images/server/jenkins_logo.png
  alt: Jenkins
---

Jenkins is an open source automation server that can be used to set up a Continuous Integration/Continuous Delivery (CI/CD) pipeline to streamline the deployment process. I wanted to set it up for my next project; a Node.js server that I could use for a lot of my future projects - I want to create a RESTful API that I can use for any of my projects that need to communicate with a central server. 

<!--more-->

I thought this would be a good opportunity to learn how to set up a server, keep it secure and not have to do it for each project! I know there are web services which can be used as API endpoints but that wouldn't be as interesting a project now would it?

If you've read some of my other blog posts you'd know that I've actually already set up a Node.js server for my Final Year Projects at Uni, so where's the challenge with this one? Well one major thing I learned from those and my recent work in testing is that automated testing is fantastic and saves _so many_ headaches and that deploying stuff sucks. Enter - CI/CD!

The goal here is to set up a CI/CD pipeline using Jenkins so when I push code to my GitHub repo, it automatically runs the Mocha tests I've set up in the project and (if the tests pass) deploys the code to another server running my Node Server App.

I mostly followed [this medium tutorial][medium-tutorial] to set up this pipeline.

## Create Node.js App

Now let's jump in - I created a [new repo on GitHub named node-app][github-node-app], automatically added a .gitignore (Node) and README (but no license).

Clone to local computer
```sh
cd D:\Documents\Github
git clone git@github.com:twulz/node-app.git
cd node-app
```

### Create Node.js Hello World App

At this stage, I'm going for the "Hello World" for my Node.js server while I work out the CI/CD part.

###### package.json file:
```js
{
 “name”: “node-app”,
 “description”: “hello jenkins test app”,
 “version”: “0.0.1”,
 “private”: true,
 “dependencies”: {
    “express”: “3.12.0”
 },
 “devDependencies”: {
    “mocha”: “1.20.1”,
    “supertest”: “0.13.0”
 }
}
```

Install using:
```sh
npm install
```

###### index.js file:
```js
// Importing node framework
var express = require('express');

var app = express();

// Respond with "hello world" for requests to root "/"
app.get('/', function(req, res) {
    res.send('Hello world!');
});

// Listen to port 3000 by default
app.listen(process.env.PORT || 3000);

module.exports = app;
```

Run the app:
```sh
node index.js
```

View app on browser using `http://localhost:3000`

Woohoo it works!

### Write tests

Automated testing is a big part of CI/CD pipelines because what happens if your changes break something? You definitely don't want that code going live!

###### /test/test.js file:
```js
var request = require('supertest');
var app = require('../index.js');

describe('GET /', function() {
    it('respond with hello world', function(done) {
        // navigate to root and check the response is "hello world"
        request(app).get('/').expect('Hello world!', done);
    });
});
```

When I was running this all on windows, this way of running tests doesn't work:
```
./node_modules/.bin/mocha ./test/test.js
```

I had to navigate to the folder containing mocha and run it that way:
```
cd node_modules/.bin
mocha ../../test/test.js
```
Then everything passed.

###### /script/test file:
```sh
#!/bin/sh
./node_modules/.bin/mocha ./test/test.js
```

**I didn't change the permissionss of it yet!!**
I also need linux to use this command, so need to run this later: 
```sh
chmod +x script/test
```
_NB: When going back over this draft, I found this comment again - this would have saved so much time! These permissions caused errors in the coming posts...stay tuned..._

Then run the script: `./script/test`. 

```sh
git add .
git commit -m "simple node app with test'
git push origin master
```

## Create Node-App Droplet on DigitalOcean

I decided to use Digital Ocean (DO) to host my servers - one for Jenkins and the other for the Node App. DO is a pretty popular alternative to the behemoth that is Amazon Web Services (AWS) at a pretty reasonable price point. Servers are called "Droplets" and it's best practice to set them up with SSH keys for the machine/s you'll be accessing from.

### Generate new SSH private key

I went to create a new SSH private key and of course I've already done this - on windows Public keys default to: `C:\Users\Twulz\.ssh\id_rsa.pub`

### Create the new Droplet:

Follow the prompts to create a new droplet:
1. Select `Node.js default application`
1. I chose the `1GB` (cheapest!) option, I had to scroll back to the left to see this option.
1. Selected a datacentre in Singapore.
1. Add SSH public key from above.
1. Name nodejs-app
1. CREATE

### Use PuTTy to ssh in:
I could use the console in the Digital Ocean console, but I prefer to use PuTTy - I used the standard settings (port 22, IP given on DigitalOcean).

First things first: log in as root, create another user and switch to that user.

```sh
adduser twulz
```

Follow prompts

```sh
usermod -a -G sudo twulz
su - twulz
```

### Deploy the node-app

This is the first deployment of the node-app just to make sure I've configured everything correctly.

```sh
sudo apt-get install git
git clone https://github.com/twulz/node-app.git
cd node-app
npm install --production
sudo ufw allow 3000
node index.js
```

Then I went to `http://IP-ADDRESS:3000` to see that sweet sweet Hello World goodness!

### Run forever
I don't want to have to keep starting the server every time so I installed pm2 and started the server as a process:
```sh
sudo npm install pm2@latest -g
pm2 start index.js
```

### Save on server time
I'm only working on this project for a few hours a week, so I don't need the servers live all the time so I can save on costs by taking a snapshot of the droplet then destroying it. I can then recreate the droplet from the snapshot when I'm ready to work on it again.

1. Turn off the droplet
1. `Options -> Snapshot -> Take Snapshot`
1. Delete the droplet.



[medium-tutorial]: https://medium.com/@mosheezderman/how-to-set-up-ci-cd-pipeline-for-a-node-js-app-with-jenkins-c51581cc783c
[github-node-app]: https://github.com/Twulz/node-app