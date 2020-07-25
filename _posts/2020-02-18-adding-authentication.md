---
layout: post
title:  "Adding Authentication to the Node App"
date:   2020-02-18
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript JWT Security Authentication Hash Middleware
---

After installing MySQL I realised that I needed a better solution than just storing plaintext usernames and passwords in an authentication table. So while I'm on my security-spree I've decided to implement the authentication middleware for the Node App including salting and hashing passwords using `bcrypt` and issuing JSON Web Tokens (JWT) to authenticate subsequent requests.

<!--more-->

## Installing JWT modules and environment variables

Users first send their login credentials to the `\login` route and are issued a JWT which is used in the Auth header (Bearer Token) for subsequent requests. During development I first got the authentication working for a single token before expanding to the login functionality.

```sh
npm install jsonwebtoken --save
npm install dotenv --save
```

JWT also requires the use of a 'secret' to create the tokens. I chose to save this file on the server as an environment variable, I tried a few methods before they were finally being recognised.

For my development machine I created a `.env` file in the root directory and defined the secret:
```env
# JSON Secret
SECRET=A_RANDOM_STRING
```

On linux I had to set the secret differently:

```sh
SECRET=A_RANDOM_STRING
export SECRET
printenv | grep SECRET
pm2 restart all --update-env
```

Finally I added it to the Jenkins build configuration:

![Build Environment](/images/server/12_jwt_secret_jenkins.JPG)

To import the libraries and environment variables is quite straight-forward:

```javascript
const jwt = require('jsonwebtoken');
require('dotenv').config({path: './.env'});

const secret = process.env['SECRET'];
```

To create the token, I put this in the `login` route:

```javascript
let token = jwt.sign(
    {username: req.body.username},
    secret,
    { expiresIn: '24h' }
);
```

To check the token, I've put this in its own `authHandler.js` middleware (full code is in my [next blog post]({% post_url 2020-02-25-adding-database %})!)

```javascript
jwt.verify(token, secret, (err, decoded) => {
    if (err) {
        res.statusCode = 401;
        return next('Authentication failed! Credentials are invalid');
    } else {
        req.decoded = decoded;
        next();
    }
});
```

## Adding bcrypt for salting & hashing

In addition to using JWT for authentication, when a user logs in I also don't want to store plaintext passwords in my database - so enter `bcrypt`! This adds salting and hashing to the passwords before being stored in the database (and gives the functions to compare given passwords to stored passwords).

I need to include the library and define the number of salt rounds:

```javascript
const bcrypt = require('bcrypt');

const saltRounds = a_numeral;
```

To register a user, simply use the hash function and store the hash in the callback function:

```javascript
bcrypt.hash(req.body.password, saltRounds, function(err, hash) {
    registerUser(req.body.username, hash);
});
```

To compare a password in the `login` route:

```javascript
bcrypt.compare(req.body.password, dbhash, function(err, result) {  
    if (result) {
        /* use result */ 
    } else {
        /* return error */
    }});
```

## Adding the authentication middleware

So to actually authenticate using the JWT I had to create authentication middleware, for reference, this has to go _after_ the authentication routes as the `login` and `register` API calls won't already have a token to send, so there's no need to go through the token authentication first. It does need to go _before_ any of the routes that I want to be protected such as my general routes.

```javascript
app.use(require('./routes/general/authentication.js'));
app.use(require('./handlers/authHandler.js'));
app.use(require('./routes/general/generalRoute.js'));
```

The contents of the `authHandler.js` file is below, it checks for the existence of the Bearer token and then the validity of the JWT.

```javascript
var jwt = require('jsonwebtoken');
require('dotenv').config({path: './.env'});
const secret = process.env['SECRET'];
const logging = process.env['LOGGING'];

/**
Checks whether the request has a valid JWT token, returns error if not
@param { OBJECT }
    { req.headers['x-access-token'] || req.headers['authorization'] }
@returns { OBJECT } 
{ 
    success: { true | false },
    response: { String },
    token: { String }
}
*/
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

module.exports = checkToken;
```
