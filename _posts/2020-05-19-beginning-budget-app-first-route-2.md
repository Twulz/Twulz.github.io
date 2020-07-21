---
layout: post
title:  "Beginning the Budget App - Finishing the First Route"
date:   2020-05-19
categories: Things Software Budget-App
tags: Node-App Server NodeJs Database Knex Javascript Budget-App
---

I realised that returning the username with the JWT is not useful to the rest of the app - I must return the `user_id` instead. This can then be used in future requests.

<!--more-->

## Changing JWT

So first I updated getUserAuthData to also retrieve the user_id:
##### database/database.js
```js
getUserAuthData(username) {
    return this.knex
        .select('user_id', 'app_access')
        .from('user')
        .where('username', username)
        .first()
        .then((result) => {
            if (result) {
                return result;
            } else {
                return null;
            }})
        .catch((error) => { console.error(error) })
}
```

Then ensure that the jwt is signed with the user_id instead of username:
##### routes/general/authentication.js
```js
if (result) {
    let userData = await db.getUserAuthData(req.body.username);
    if (userData.app_access) {
        let token = jwt.sign(
            { user_id: userData.user_id },
            secret,
            { expiresIn: '24h' }
        );
        ...
    }
    ...
}
```

With that change, when the authHandler verifies the jwt, the user_id can be found in the `req.decoded.user_id` variable in the subsequent routes.

##### handlers/authHandler.js
```js
var checkToken = function(req, res, next) {
    let token = req.headers['x-access-token'] || req.headers['authorization'];
    if (token) {
        if (token.startsWith('Bearer ')) {
            // Remove Bearer from string
            token = token.slice(7, token.length);
        }
        jwt.verify(token, secret, (err, decoded) => {
            if (err) {
                res.statusCode = 401;
                return next('Authentication failed! Credentials are invalid');
            } else {
                req.decoded = decoded;
                next();
            }
        });
    } else {
        res.statusCode = 400;
        return next('Authentication failed! Please check the request');
    }
};
```

### Creating the first Budget route

With these changes I could go ahead and create the first budget route at `/api/budget/transactions/`

##### routes/budget/budget.js
```js
const express = require('express');
const router = express.Router();
const Database = require('../../database/database');

require('dotenv').config({path: './.env'});

const dbURL = process.env['DB_URL'];

const db = new Database(dbURL);

router.get('/api/budget/transactions/', async (req, res, next) => {
    try {
        res.setHeader('content-type', 'application/json');
        let transactions = await db.getAllTransactions(req.decoded.user_id);
        res.statusCode = 200;
        res.json({
            success: true,
            transactions: transactions
        });
    } catch (error) {
        return next(error);
    }
});

module.exports = router;
```

Now after logging in I can send a get request with the appropriate auth header to recieve all of the transactions on the account (for now just one):

```json
{
    "success": true,
    "transactions": [
        {
            "date": "2020-04-23T14:00:00.000Z",
            "amount": 500,
            "notes": "Rent April",
            "cleared": 0,
            "category_id": 1,
            "category_name": "Food",
            "account_id": 1,
            "account_name": null
        }
    ]
}
```

#### Route test

Finally I created the test for this route - success! Now 7 passing tests!

```js
const request = require('supertest');
const app = require('../index.js');
const chai = require('chai');
const chaiHttp = require('chai-http');

const { expect } = chai;
chai.use(chaiHttp);

describe('GET /api/budget/transactions/ SUCCESS', function() {

    var token = null;

    before(function(done) {
        request(app)
            .post('/login')
            .send({ username: 'testuser@email.com', password: 'password' })
            .end(function(err, res) {
                token = res.body.token;
                done();
            });
      });

    it('Respond with success', function(done) {
        request(app)
            .get('/api/budget/transactions/')
            .set("Authorization", "Bearer " + token) 
            .set({'Accept': 'application/json'})
            .end(function(err, res) {
                expect(res).to.exist;
                expect(res.statusCode).to.equal(200);
                expect(res.body.success).to.equal(true);
                expect(res.body.transactions).to.exist;
                done();
            })
    });
});
```

The next step is to look at creating a front-end for this budget app to display it nicely instead of JSON objects!
