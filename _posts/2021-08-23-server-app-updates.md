---
layout: post
title:  "Server App Updates"
date:   2021-08-23
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript
---

In this post I return to my server app to make some much-needed maintenance updates and prepare it for changes I'll be making to the budget API.

<!--more-->

## Update My Environment

First I updated my environment, I downloaded the latest version of node and updated my npm version with `npm install -g npm` then updated all packages with `npm update`. I also ran `npm audit` and `npm audit fix` until I had 0 vulnerabilities showing. Because I updated to npm version 7 this updated my `package.lock` file too which needed to be committed.

## Remove Deprecated Code

Next up the `body-parser` library has been deprecated so I removed it and replaced this:
```js
const bodyParser = require('body-parser');
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
```

With the straight `express` equivalent:

```js
app.use(express.urlencoded({ extended: true }));
app.use(express.json());
```

## Fix error handling

In my current implementation I was catching errors and exiting the node process during the setup methods, but I was exiting without a code so Jenkins thought that creating or destroying tables in the database was successful even when they failed. To fix this was super easy to just pass in a non-zero value to the method, i.e. add exit code of 1 `process.exit(1);` instead of `process.exit();` when catching errors. 
```js
db.destroySensorDatabase()
    // ... 
    .catch((error) => {
        console.log(error);
        process.exit(1);
    });
```

This means the Jenkins build will fail when the database fails to create or destroy properly even before the tests are run.

## Release the Database Connection Back to Pool

Another problem I was having was Jenkins "hanging" after a few queries. I reailsed I wasn't releasing the connection after querying so I just added the `connection.release()` method to release the connection. Otherwise it was causing some kind of memory leak and I had to keep restarting Jenkins periodically.
```js
function runQuery(query) {
    return new Promise(function (resolve, reject) {
        pool.getConnection((error, connection) => {
            if (error) reject(error);
            connection.query(query, (error, result) => {
                connection.release();
                if (error) {
                    reject(error);
                } else {
                    resolve(result);
                }
            });
        });
    }); 
}
```









