---
layout: post
title:  "Testing the Authentication Routes in Mocha"
date:   2020-03-17
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript Authentication Knex Mocha
---

With all the changes made in [the last]({% post_url 2020-02-25-adding-database %}) [few posts]({% post_url 2020-02-18-adding-authentication %}), obviously my Hello World tests would now fail and I needed to write new ones to verify the authentication was working correctly.

<!--more-->

## Tests

I created a `testData.js` file to house all of the dummy data to be used during testing:

###### testData/test
```javascript
module.exports = {
    authentication: [
        {username: 'testuser@email.com', password: 'a_string', app_access: true}
    ]
}
```

Before each test run, I needed to first destroy any database schema that already exists, so I can be sure that the test environment is set up in a known state. So I always destroy the existing setup and then initialise including the above test data.

###### database/initTest.js
```javascript
const Database = require('./database');
const testData = require('./testData');
require('dotenv').config({path: './.env'});
const dbURL = process.env['DB_URL'];

const db = new Database(dbURL);

/**
 * Destroy any existing instance of the tables required for the node-app
 * @returns { Promise } of string | Error
 */
const destroy = async() => {
  await db.destroySchema();
  process.exit;
}

/**
 * Initialises the database with all of the tables required for the node-app
 * @returns { Promise } of string | Error
 */
const initialise = async () => {
  await db.initDatabase(testData);
  process.exit();
}

/**
 * To remove the test authentication user after testing
 * @returns { Promise } of string | Error
 */
const cleanup = async () => {
  await db.deleteUser('testuser@email.com');
  process.exit();
}

destroy();
initialise();
```

I updated the `package.json` file to include the init and test commands:

###### package.json
```json
    "scripts": {
        "initDB": "node ./database/init.js",
        "cleanTest": "node ./database/cleanTest.js",
        "initTestDB": "node ./database/initTest.js",
        "test": "mocha --recursive --timeout 100000 --exit",
        "dev-server": "./node_modules/.bin/node-dev ./index.js"
    }
```

Now to actually write the testcases for the new authentication routes. First I needed to send a `POST` request with the login credentials to ensure that a token is issued. Then I use this token in a header to send a GET request and recieve a positive response. I also did negative testing to ensure that the correct codes are returned on the various failure cases.

###### test/authtest.js
```javascript
const request = require('supertest');
const app = require('../index.js');
const chai = require('chai');
const chaiHttp = require('chai-http');

const { expect } = chai;
chai.use(chaiHttp);

describe('GET / SUCCESS', function() {

    var token = null;

    before(function(done) {
        request(app)
            .post('/login')
            // TODO: need to properly implement knex to create more valid test data!
            .send({ username: "admin", password: "password" })
            .end(function(err, res) {
                token = res.body.token; // Or something
                done();
            });
      });

    it('Respond with success', function(done) {
        request(app)
            .get('/')
            .set("Authorization", "Bearer " + token) 
            .set({'Accept': 'application/json'})
            .end(function(err, res) {
                expect(res).to.exist;
                expect(res.statusCode).to.equal(200);
                expect(res.body.response).to.include('Success');
                done();
            })
    });
});

describe('GET / FAILURE: missing Token', function() {
    it('Respond with 400: check the request', function(done) {
        request(app)
            .get('/')
            .set({'Accept': 'application/json'})
            .end(function(err, res) {
                expect(res).to.exist;
                expect(res.statusCode).to.equal(400);
                expect(res.body.error).to.include('check the request');
                done();
            })
    });
});

describe('GET / FAILURE: invalid Token', function() {
    it('Respond with 401: unorthorized', function(done) {
        request(app)
            .get('/')
            .set("Authorization", "Bearer totally_legit_token") 
            .set({'Accept': 'application/json'})
            .end(function(err, res) {
                expect(res).to.exist;
                expect(res.statusCode).to.equal(401);
                expect(res.body.error).to.include('invalid');
                done();
            })
    });
});

describe('POST /login SUCCESS', function() {
    it('Respond with login token', function(done) {
        request(app)
            .post('/login')
            // TODO: need to properly implement knex to create more valid test data!
            .send({ username: "admin", password: "password" })
            .end(function(err, res) {
                expect(res).to.exist;
                expect(res.statusCode).to.equal(200);
                expect(res.body.token).to.exist;
                done();
            });
    })
});
```

I also had to update the general routes tests to just fail with the correct error codes:

```javascript
const request = require('supertest');
const app = require('../index.js');
const chai = require('chai');
const chaiHttp = require('chai-http');

const { expect } = chai;
chai.use(chaiHttp);

describe('GET /', function() {
    it('Respond with fail', function(done) {
        request(app)
            .get('/')
            .set('Accept', 'application/json')
            .end(function(err, res) {
                expect(res.statusCode).to.equal(400);
                done();
            })
    });
});

describe('POST /', function() {
    it('Respond with fail', function(done) {
        request(app)
            .post('/')
            .set('Accept', 'application/json')
            .end(function(err, res) {
                expect(res.statusCode).to.equal(400);
                done();
            })
    });
});
```

All that's left is to run the tests using first `npm run initTestDB` then `npm run test`.

```sh
>npm run test

> node-app@0.0.3 test C:\Users\twulz\Documents\GitHub\node-app
> mocha --recursive --timeout 100000 --exit



  GET / SUCCESS
POST /login 200 170.380 ms - 238
GET / 200 1.606 ms - 50
    √ Respond with success

  GET / FAILURE: missing Token
GET / 400 0.418 ms - 88
    √ Respond with 400: check the request

  GET / FAILURE: invalid Token
GET / 401 0.355 ms - 87
    √ Respond with 401: unorthorized

  POST /login SUCCESS
POST /login 200 78.885 ms - 238
    √ Respond with login token (73ms)

  GET /
GET / 400 0.156 ms - 88
    √ Respond with fail

  POST /
POST / 400 0.130 ms - 88
    √ Respond with fail


  6 passing (326ms)
```

And finally add the tests to the Build in Jenkins:

![Jenkins build](/images/server/13_build_new_tests.PNG)

And done! with the Mocha tests passing in Jenkins my builds could finally be deployed to my production server! Now what did I want to do with my server again...?

[mysql8]: https://stackoverflow.com/questions/50093144/mysql-8-0-client-does-not-support-authentication-protocol-requested-by-server
