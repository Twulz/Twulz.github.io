
# HelloWorld CI/CD Pipeline using Node.js and Jenkins

## Create new GitHub Repo

Named node-app, automatically added .gitignore (Node) and README (but no license).

Clone to local computer
```
cd D:\Documents\Github
git clone git@github.com:twulz/node-app.git
cd node-app
```

## Create Node.js App

### package.json file:
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
```
npm install
```

### index.js file:
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
```
node index.js
```

View app on browser using `http://localhost:3000`

## Write tests

### /test/test.js file:
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

From the [medium-tutorial], but this doesn't work on windows: `./node_modules/.bin/mocha ./test/test.js`
I had to navigate to the folder containing mocha and run it that way:
```
cd node_modules/.bin
mocha ../../test/test.js
```
Then everything passed.

### /script/test file:
```sh
#!/bin/sh
./node_modules/.bin/mocha ./test/test.js
```

**I didn't change the permissionss of it yet!!**
Need linux to use this command, so need to run this later: `chmod +x script/test`
Then run the script: `./script/test`

```
git add .
git commit -m "simple node app with test'
git push origin master
```

## Generate new SSH private key

Public keys already existed: `C:\Users\Twulz\.ssh\id_rsa.pub`

### Use Puttygen to generate new private key:
"Load an existing private key file" - C:\Users\Twulz\.ssh\id_rsa.pub
Saved to D

## Create Droplet on DigitalOcean

Follow the prompts to create a new droplet:
* Node.js default application
* 1GB cheapest option (had to scroll back across!)
* Datacentre in Singapore
* Add SSH public key
* Name nodejs-app
* CREATE

## Use PuTTy to ssh in:
Use the standard settings (port 22, IP given on DigitalOcean)

Add new private key to the SSH -> Auth section.

```
Login as: root
adduser twulz
```

Follow prompts

```
usermod -a -G sudo twulz
su - twulz
```

## Deploy the node-app

```
sudo apt-get install git
git clone https://github.com/twulz/node-app.git
cd node-app
npm install -production
sudo ufw allow 3000
node index.js
```

### Run forever
```
sudo npm install pm2@latest -g
pm2 start index.js
```

## Save on server time
Create a snapshot of the droplet then destroy it.

Turn off the droplet
Options -> Snapshot -> Take Snapshot

Then delete the droplet.

# Create a new SSH key for my laptop

Use puttygen to create another key-value pair.
Copy this to security section of DigitalOcean.

When I re-created the app from the snapshot - I could select "All SSH pairs" to enable wheatley on it.

Couldn't log in as non-root user (...good...):

Logged in as root

Checked if my twulz user still existed: `getent passwd | grep twulz`
yep it exists!




## I couldn't log in as anything but root

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

## Now to reset the auto-starting app on a new dropplet (after taking a snapshot and destroying):

1. Create the droplet from the snapshot
1. Sign in to twulz user
1. Move to the `/node-app/` folder `cd node-app`
1. Start pm2: `pm2 start index.js`
1. Go to http://IP-ADDRESS:3000







# Jenkins server

## Configure user permissions from scratch

Select "Ubuntu" from the "distributions" menu - 18.04

Log in as root user using my ssh key/password

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

Install git `sudo apt-get install git`

### Install jenkins:

Jenkins still uses Java 8 instead of the default of Java 9 (Ubuntu 18.04) so I had to install Java 8 as default first:

```sh
sudo add-apt-repository ppa:webupd8team/java

sudo apt install oracle-java8-installer
wget -q -O - https://pkg.jenkins.io/debian-stable/jenkins.io.key | sudo apt-key add -
sudo apt-add-repository "deb https://pkg.jenkins.io/debian-stable binary/"
sudo apt-get update
sudo apt install jenkins



wget -q -O - https://pkg.jenkins.io/debian/jenkins.io.key | sudo apt-key add -

sudo sh -c 'echo deb http://pkg.jenkins.io/debian-stable binary/ > /etc/apt/sources.list.d/jenkins.list'

sudo apt-get update

sudo apt-get install jenkins

sudo systemctl status jenkins

sudo ufw allow 8080
```

NOTHING WORKS, SCRAP THE WHOLE JENKINS SECTION
















# Jenkins server

## Configure user permissions from scratch

Select "Ubuntu" from the "distributions" menu - 18.04

Log in as root user using my ssh key/password

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
exit
```

Then re-connect using PuTTY and login as twulz (using the ssh passkey).

### Java 8 install

Installing Java sdk 8 didn't work so needed to add the 'universe' repo:

```
sudo add-apt-repository universe
sudo apt install openjdk-8-jdk
java -version
```

This had the correct output according to [install java].

### Jenkins install

```
wget -q -O - https://pkg.jenkins.io/debian/jenkins.io.key | sudo apt-key add -
sudo sh -c 'echo deb http://pkg.jenkins.io/debian-stable binary/ > /etc/apt/sources.list.d/jenkins.list'
sudo apt update
sudo apt install jenkins
sudo systemctl start jenkins
sudo systemctl status jenkins
```

Need to activate OpenSSH and activate the firewall:

```
sudo ufw allow OpenSSH
sudo ufw enable
```

Open port 8080 which is the one used for jenkins:

```
sudo ufw allow 8080
sudo ufw status
```

I took a snapshot here just in case!

### Configure Jenkins

Go to http://IP_ADDRESS:8080

Need to unlock it viewing the file at:
`/var/lib/jenkins/secrets/initialAdminPassword`
```
sudo cat /var/lib/jenkins/secrets/initialAdminPassword
```

Set it up with a user and password.

![Jenkins configuration](/images/nodeApp/01_jenkins_setup.JPG)


![Github webhook lookup](/images/nodeApp/02_webhook_setup.JPG)

`Error: npm: not found`

```
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

![No NodeJS installation?](/images/nodeApp/03_add_npm_to_path.JPG)

Solution: I hadn't configured NodeJS plugin for jenkins!
Followed these instructions: https://wiki.jenkins.io/display/JENKINS/NodeJS+Plugin

![Add NodeJS installation to jenkins](/images/nodeApp/04_add_NodeJS_installer.JPG)

![Now add npm to path](/images/nodeApp/05_add_npm_to_path.JPG)

```
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

```
sudo chmod -R 757 /var/lib/jenkins/workspace/node-app
sudo systemctl restart jenkins
```

still not working, added whoami to the pipeline:


[medium-tutorial]: https://medium.com/@mosheezderman/how-to-set-up-ci-cd-pipeline-for-a-node-js-app-with-jenkins-c51581cc783c
[install java]: https://www.digitalocean.com/community/tutorials/how-to-install-java-with-apt-on-ubuntu-18-04#installing-specific-versions-of-openjdk