---
layout: post
title:  "Refactoring the Server App to Remove Knex"
date:   2020-09-08
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript SQL
---

In this post I replaced the Knex library I was using to construct queries with straight SQL queries using the normal mysql library using pooled connections and promises.

<!--more-->

As I began making changes to my node-app to add the budget functionality I found myself having to convert the Knex code into a SQL query (and print to the console) to properly troubleshoot while I was developing. This seems kind of backwards as using Knex is meant to avoid needing to construct a query properly, and I figure brushing up my raw SQL skills would be much more applicable to future projects than a particular javascript implementation of it.

So refactor time, yay!

I moved all the database connection code back into the `database.js` file and made use of connection pooling to handle concurrent requests.

I added this to a new `runQuery` function which handles the connection and returns a promise so my queries could become "then-able".

```js
/* Converts the mysql pool query function into a Promise function */
function runQuery(query) {
    return new Promise(function (resolve, reject) {
        pool.getConnection((error, connection) => {
            if (error) reject(error);
            connection.query(query, (error, result) => {
                if (error) reject(error);
                else resolve(result);
            });
        });
    });
}
```

Then I could replace the functions that used the Knex query with one that calls the `runQuery` function instead, e.g:

```js
destroyUserDatabase: () => {
    let q_dropTableUser = `DROP TABLE IF EXISTS user;`;
    return runQuery(q_dropTableUser)
        .then(() => '---destroyUserDatabase Drop Success')
        .catch((error) => new Error(error));
}
```

I also needed another helper class to convert JSON objects into a string of the format `("value1", "value2", ...)`, I added a few of these functions for the objects I needed but I'll replace these with a better solution after this first refactor phase.

```js
function user_JSONtoValueString(data) {
    let values = '';
    for (let i=0; i< data.length; i++) {
        if (i!=0) values += ",";
        values += "(\"";
        values += data[i].username + "\",\"";
        values += data[i].password + "\"";
        if (data[i].app_access) values += "," + data[i].app_access
        values += ")";
    }
    return values;
}
```

I could then replace the initialisation functions with straight SQL queries e.g. `CREATE TABLE` and insert values using `INSERT INTO` and the helper function.

```js
initUserDatabase: (data) => {

    let q_createTableUser = `
    CREATE TABLE user (
        id INT NOT NULL AUTO_INCREMENT,
        username VARCHAR(255) NOT NULL UNIQUE,
        password VARCHAR(60) NOT NULL,
        app_access BOOLEAN NOT NULL DEFAULT 0,
        PRIMARY KEY (id)
    );`;
    let q_insertUser_full = '';
    if (data && data.user) q_insertUser_full = `INSERT INTO user (username, password, app_access) VALUES ` + user_JSONtoValueString(data.user);

    return runQuery(q_createTableUser)
        .then((result) => {
            console.log('---initUserDatabase Create Success');
            // Insert given data
            if (data && data.user) return runQuery(q_insertUser_full);
        })
        .then(() => '---initUserDatabase Insert Success')
        .catch((error) => new Error(error));

}
```

I think I'm violating a bunch of javascript style guides with this but this is much more straight-forward and easily troubleshooted (troubleshot?), I consider it a great success!

```js
initBudgetDatabase: () => {
    let q_createTableAccount = `
    CREATE TABLE account (
        id INT NOT NULL AUTO_INCREMENT,
        name VARCHAR(255) NOT NULL,
        active BOOLEAN NOT NULL DEFAULT 1,
        user_id INT NOT NULL,
        PRIMARY KEY (id),
        FOREIGN KEY (user_id) REFERENCES user(id)
    );`
    let q_createTableCategory = `
    CREATE TABLE category (
        id INT NOT NULL AUTO_INCREMENT,
        name VARCHAR(255) NOT NULL,
        user_id INT NOT NULL,
        PRIMARY KEY (id),
        FOREIGN KEY (user_id) REFERENCES user(id)
    );`
    let q_createTableTransaction = `
    CREATE TABLE transaction (
        id INT NOT NULL AUTO_INCREMENT,
        date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
        notes VARCHAR(255),
        amount DECIMAL(19,2) NOT NULL,
        cleared BOOLEAN NOT NULL DEFAULT 0,
        user_id INT NOT NULL,
        payee_id INT NOT NULL,
        category_id INT NOT NULL,
        account_id INT NOT NULL,
        PRIMARY KEY (id),
        FOREIGN KEY (user_id) REFERENCES user(id),
        FOREIGN KEY (payee_id) REFERENCES account(id),
        FOREIGN KEY (category_id) REFERENCES category(id),
        FOREIGN KEY (account_id) REFERENCES account(id)
    );`
    let q_createTableBudget = `
    CREATE TABLE budget (
        id INT NOT NULL AUTO_INCREMENT,
        amount DECIMAL(19,2) NOT NULL DEFAULT 0,
        date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
        category_id INT NOT NULL,
        PRIMARY KEY (id),
        FOREIGN KEY (category_id) REFERENCES category(id)
    );`
    let createQuery = 
        q_createTableAccount +
        q_createTableCategory + 
        q_createTableTransaction +
        q_createTableBudget;
    return runQuery(createQuery)
        .then(() => '---initBudgetDatabase Create Success')
        .catch((error) => new Error(error));
}
```

Then I could simplfy my init scripts to chain the "then"s to end up with this masterpiece:

```js
cleanInit: (data) => {
    db.destroySensorDatabase()
        .then((result) => {
            console.log(result);
            return db.destroyBudgetDatabase()
        })
        .then((result) => {
            console.log(result);
            return db.destroyUserDatabase();
        })
        .then ((result) => {
            console.log(result);
            return db.initUserDatabase(data);
        })
        .then((result) => {
            console.log(result);
            return db.initBudgetDatabase()
        })
        .then((result) => {
            console.log(result);
            return db.initSensorDatabase(data);
        })
        .then((result) => {
            console.log(result);
            process.exit();
        })
        .catch((error) => {
            console.log(error);
            process.exit(1);
        });
```

Beautiful, now I can get on with the rest of these projects...