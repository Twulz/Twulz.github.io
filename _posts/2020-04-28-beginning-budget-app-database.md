---
layout: post
title:  "Beginning the Budget App - Database"
date:   2020-04-28
categories: Things Software Budget-App
tags: Server NodeJs Database Knex Javascript Budget-App
---

Now that my Node server is up and running (and secure), it's finally time to actually _do_ something with it! My first project will be purely software; a budgeting app that can be used to record transactions and define a monthly limit on each category to keep track of finances using a variation on the 'envelope' strategy.

<!--more-->

## Adding the Database for the Budget App

### Database Design

I used [diagrams.net](https://app.diagrams.net/) to draw up an ERD for the initial design of the database.

Users will be able to add: 
* Accounts which represent all of their bank accounts and other 'containers' for money (bank accounts, credit cards, loan accounts, cash).
* Categories which have a monthly limit assigned to them (e.g. rent, groceries, dining out, 'fun' money)
* Transactions which can be paid from one account to another (payee account), with the money assigned to one of the categories on a particular date. Cleared or uncleared transactions may be added (as they still show in bank accounts).
* The budget table took a bit of thought - each category is defined in its own table but each month the category amount may change so another table was needed to track this. I may revise this design in future as the "date" field should only have one category per month.

![Budget App ERD](/images/budget/01_budget_erd.PNG)

### Implementation in Knex

The next step was to implement the Schema in Knex.

```js
createSchema() {
    return this.knex.schema
        .dropTableIfExists('budget')
        .dropTableIfExists('transaction')
        .dropTableIfExists('category')
        .dropTableIfExists('account')
        .dropTableIfExists('user')
        .createTable('user', tb => {
            tb.increments('user_id').primary()
            tb.string('username').notNullable().unique()
            tb.specificType('password', 'CHAR(60)').notNullable()
            tb.boolean('app_access').notNullable().defaultTo('false')
        })
        .createTable('account', tb => {
            tb.increments('account_id').primary()
            tb.string('account_name').notNullable()
            tb.boolean('active').notNullable().defaultTo('true')
            tb.integer('user_id').unsigned().notNullable()
            tb.foreign('user_id').references('user.user_id')
        })
        .createTable('category', tb => {
            tb.increments('category_id').primary()
            tb.string('category_name').notNullable()
            tb.integer('user_id').unsigned().notNullable()
            tb.foreign('user_id').references('user.user_id')
        })
        .createTable('transaction', tb => {
            tb.increments('transaction_id').primary()
            tb.date('date').notNullable()
            tb.string('notes')
            tb.decimal('amount',14,2).notNullable()
            tb.boolean('cleared').notNullable().defaultTo('false')
            tb.integer('user_id').unsigned().notNullable()
            tb.integer('payee_id').unsigned()
            tb.integer('category_id').unsigned().notNullable()
            tb.integer('account_id').unsigned().notNullable()
            tb.foreign('user_id').references('user.user_id')
            tb.foreign('payee_id').references('account.account_id')
            tb.foreign('category_id').references('category.category_id')
            tb.foreign('account_id').references('account.account_id')
        })
        .createTable('budget', tb => {
            tb.increments('budget_id').primary()
            tb.decimal('amount',14,2).notNullable().defaultTo(0)
            tb.date('date').notNullable()
            tb.integer('category_id').unsigned().notNullable()
            tb.foreign('category_id').references('category.category_id')
        })
        .then(() => 'Success')
        .catch((error) => { return new Error(error); });
}
```

With that I have the first iteration of my database designed. Now to design the routes I'll need to create and the helper functions to allow for CRUD (Create, Read, Update, Delete) of the database.