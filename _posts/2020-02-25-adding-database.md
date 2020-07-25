---
layout: post
title:  "Connecting the Database to the Node App"
date:   2020-02-25
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript Authentication Knex MySQL SQL
---

I'd [previously installed mysql]({% post_url 2020-02-16-installing-mysql-phpmyadmin %}) but the authentication I added in my [last blog post]({% post_url 2020-02-16-installing-mysql-phpmyadmin %}) just kept everything in memory so far so in this post I'll be using the MySQL database connected to Node using Knex to construct queries.

<!--more-->

## Add database in phpmyadmin

I added the `twulzserver` database and `authentication` table manually using SQL commands and set up my users on my local dev machine:

```sql
DROP TABLE IF EXISTS authentication;
DROP SCHEMA IF EXISTS `twulzserver`;
CREATE SCHEMA IF NOT EXISTS `twulzserver`;
USE `twulzserver`;
```

I had an issue on my Windows machine while trying to connect to my database when I wrote the code included below, so I've snuck back up here to document [the extra steps][mysql8] I need to do on Windows using MySQL 8 to avoid this authentication error:

```sh
UnhandledPromiseRejectionWarning: Error: ER_NOT_SUPPORTED_AUTH_MODE: Client does not support authentication protocol requested by server;
```

I needed to set the authentication method to `mysql_native_password` instead of the MySQL 8 default as the library used by node doesn't support the default MySQL 8 authentication.

```sql
ALTER USER 'Twulz'@'localhost' IDENTIFIED WITH mysql_native_password BY 'my_password';
flush privileges;
```

I initially created the authentication table manually too before I implemented it in Knex in the next section.

```sql
CREATE TABLE `authentication` (
	`id` INT(10) NOT NULL AUTO_INCREMENT,
    `username` VARCHAR(255) NOT NULL,
    `password` CHAR(60) NOT NULL,
    `app_access` BOOLEAN NOT NULL DEFAULT FALSE,
    PRIMARY KEY (`id`)
);
```

I also manually added my first authenticated user. As I'm just doing development at the moment and don't want random people/bots creating accounts and being able to authenticate with my app; as an extra security layer I'm only allowing accounts that have the `app_access` field set to `true` which you can't do through the API in the current design. I'll log in to phpmyadmin and enable the app access for any legitimate users I create for now.

```sql
INSERT INTO authentication (`username`, `password`, `app_access`) VALUES ('an_email@somedomain.com', 'hashed_password_string', true);
```

## Add database code

I'll be using the `Knex` javascript library to interface with the SQL database. This library lets me build SQL queries without dealing with concatenating a bunch of strings. I've just included the full database code here which handles the authentication table functions that can be used by the other routes.

I decided to set the database URL (which includes the username and password) as another environment variable. So I added this to the `.env` file on my development machine and added it to the Jenkins environment variables described above.

The database URL string resembles this:
```sh
DB_URL=mysql:Username:password@localhost:port/database_name
```

I added the initDB script to the package.json file so I can easily create the database using `npm run initDB`:

###### package.json
```json
    "scripts": {
        "initDB": "node ./database/init.js",
        "dev-server": "./node_modules/.bin/node-dev ./index.js"
    }
```

This init file simply calls the `initDatabase()` function, but in the future I might need to add more.

###### database/init.js
```javascript
const Database = require('./database');
require('dotenv').config({path: './.env'});
const dbURL = process.env['DB_URL'];

const db = new Database(dbURL);

/**
Initialises the database with all of the tables required for the node-app
@returns { Promise } of string | Error
*/
const initialise = async () => {
  await db.initDatabase();
  process.exit();
}

initialise();
```

Here is the current database code:

###### database/database.js

```javascript
const knex = require('knex');

const formatDate = (d) => moment(d).format('YYYY-MM-DD');

class Database {

    /**
    Constructor of Database Object
    @param { Object } config: Knex database configuration 
    */
    constructor(config) {
      this.knex = knex({
        client: 'mysql',
        connection: config
      })
    }

    /**
    Creates all tables required for the Node-App
    @returns { Promise } of string | Error
    @example 'Success' | Error
    */
    createSchema() {
        return this.knex.schema
            .dropTableIfExists('authentication')
            .createTable('authentication', tb => {
                tb.increments('auth_id')
                tb.string('username').notNullable()
                tb.specificType('password', 'CHAR(60)').notNullable()
                tb.boolean('app_access').notNullable().defaultTo('false')
            })
            .then(() => 'Success')
    }

    /**
    Destroys all tables used in the Node-App
    @returns { Promise } of 'Success' | Error
    @example 'Success' | Error
    */
    destroySchema() {
        return this.knex.schema
          .dropTableIfExists('authentication')
          .then(() => 'Success')
    }

    /**
    Creates database schema - TODO: enables insert of sample data for development
    @returns { Promise } of 'Success' | Error
    @example 'Success' | Error
    */
    initDatabase() {
        return this.createSchema()
            .then(() => 'Success')
    }

    /**
    Registers a new user with the given username and password
    @param { string } username: The username (email address) of the user
    @param { CHAR(60) } password: A salted hash generated from the user's inputted password
    @returns { Promise } of 'Success' | Error
    */
    registerUser(username, password) {
        return this.knex('authentication')
            .insert({ 
                'username': username,
                'password': password })
            .then(() => 'Success')
    }

    /**
    Gets the salted hash representing the given username's password
    @param { string } username: The username (email address) of the user
    @returns { CHAR(60) } password: A salted hash generated from the user's inputted password
    */
    getUserAuthData(username) {
        return this.knex
            .select('password')
            .from('authentication')
            .where('username', username)
            .first()
            .then((result) => {return result.password})
    }
}

module.exports = Database;
```

## Full authentication route code

Finally I've put it all together and here is the login/register code in its current state. I added some error handling with the appropriate HTTP response codes and error messages.

###### routes/general/authentication.js
```javascript
const express = require('express');
const router = express.Router();
const jwt = require('jsonwebtoken');
const bcrypt = require('bcrypt');
const Database = require('../../database/database');

require('dotenv').config({path: './.env'});

const secret = process.env['SECRET'];
const logging = process.env['LOGGING'];
const dbURL = process.env['DB_URL'];

const db = new Database(dbURL);
const saltRounds = a_numeral;

/**
Allows a user to log in to the system - is issued a JWT token
@body 
{
    username: { string },
    password: { string }
}
@returns 
{ 
    success: { true | false },
    response: { String },
    token: { String }
}
*/
router.post('/login', async(req, res, next) => {
    try {
        res.setHeader('content-type', 'application/json');

        if (req.body.username && req.body.password) {
            var dbhash = await db.getUserAuthData(req.body.username);
            bcrypt.compare(req.body.password, dbhash, function(err, result) {
                if (result) {
                    let token = jwt.sign(
                        {username: req.body.username},
                        secret,
                        { expiresIn: '24h' }
                    );
                    // return the JWT token for the future API calls
                    res.statusCode = 200;
                    res.json({
                        success: true,
                        response: 'Authentication successful!',
                        token: token
                    });
                } else {
                    res.statusCode = 401;
                    err = 'Incorrect username or password';
                    return next(err);
                }
            });
        } else {
            res.statusCode = 400;
            return next('Authentication failed! Please check the request');
        }
    } catch (err) {
        return next(err);
    }
});

/**
Allows a user to register a username and password into the system.
@body 
{
    username: { string },
    password: { string }
}
@returns 
{ 
    success: { true | false },
    response: { String }
}
*/
router.post('/register', async(req, res, next) => {
    try {
        if (req.body.username && req.body.password) {
            bcrypt.hash(req.body.password, saltRounds, function(err, hash) {
                db.registerUser(req.body.username, hash);
                res.statusCode = 201;
                res.json({
                    success: true,
                    response: 'User created!'
                });
            });
        } else {
            res.statusCode = 400;
            return next('Registration failed! Please check the request');
        }
    } catch (err) {
        return next(err);
    }

});
  
module.exports = router;
```


[mysql8]: https://stackoverflow.com/questions/50093144/mysql-8-0-client-does-not-support-authentication-protocol-requested-by-server
