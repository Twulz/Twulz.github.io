---
layout: post
title:  "Beginning the Budget App - First Route"
date:   2020-05-12
categories: Things Software Budget-App
tags: Node-App Server NodeJs REST API Javascript Budget-App
---

Instead of creating all those routes to create and update the accounts, categories and transactions, I decided for testing everything and getting it wired up I would just write the route to get all the transactions for a single user and then expand on the routes as required.

<!--more-->

## Creating the first route

For testing, I created a user/password combination and used Postman to register a user via the `POST /register` route. I then logged in to MySQL in the back end and ran the following SQL commands to allow app access for that user and to create a category, account and transaction.

```sql
UPDATE user SET app_access = true WHERE user_id = 1;

INSERT INTO category (user_id, category_name) VALUES (1, 'Food');

INSERT INTO account (account_name, user_id) VALUES ('Checking', 1);

INSERT INTO transaction (user_id, date, notes, amount, category_id, account_id) VALUES (1, '2020-04-24', 'Rent April', 500, 1, 1);
```

Next was to create the `getAllTransactions` function in `database/database.js` to retreive all transactions for the given user id.

```js
getAllTransactions(user_id) {
    return this.knex('transaction')
        .select('transaction.date', 'transaction.amount', 'transaction.notes', 'transaction.cleared', 'category.category_id', 'category.category_name', 'transaction.account_id', 'account.account_name', 'payee.account_name')
        .from('transaction')
        .where({ 'transaction.user_id': user_id })
        .innerJoin('category', 'transaction.category_id', 'category.category_id')
        .innerJoin('account', 'transaction.account_id', 'account.account_id')
        .leftJoin('account as payee', 'transaction.payee_id', 'payee.account_id')
        .catch((error) => { return new Error(error); });;
}
```

At this point I realised that I needed the `user_id` instead of the `username` in the jwt decoded data so next up I'll do just that.