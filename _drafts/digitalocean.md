
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



[medium-tutorial]: https://medium.com/@mosheezderman/how-to-set-up-ci-cd-pipeline-for-a-node-js-app-with-jenkins-c51581cc783c