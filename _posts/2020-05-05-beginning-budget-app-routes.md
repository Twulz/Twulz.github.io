---
layout: post
title:  "Beginning the Budget App - Routes"
date:   2020-05-05
categories: Things Software Budget-App
tags: Node-App Server NodeJs REST API Javascript Budget-App
---

My server implements a RESTful API to be used with the budget app, but in order to do that I need to decide on the routes I will need to access. This post outlines the initial routes I've decided to implement.

<!--more-->

## Deciding on routes

I started designing the endpoints of what I thought would be needed initially. I included this in my readme and copied the contents here:

### General Endpoints

#### GET /

##### Response
```json
{
    "success": true,
    "response": "Hello World Success!"
}
```

### Auth Endpoints

#### POST /login

##### Body
```json
{
	"username": "user@email.com",
	"password": "some_string"
}
```

##### Response
```json
{
    "success": true,
    "response": "Authentication successful!",
    "token": "eyJhbG--redacted--U"
}
```

#### POST /register

##### Body
```json
{
	"username": "user@email.com",
	"password": "some_string"
}
```

##### Response
```json
{
    "success": true,
    "response": "User created!"
}
```

### Budget Endpoints

#### GET /api/budget/transactions/

##### Response
```json
{
    "success": true,
    "transactions": [
        {
            "date": "date",
            "amount": "decimal",
            "notes": "string",
            "cleared": "boolean",
            "category_id": "integer",
            "category_name": "string",
            "account_id": "integer",
            "account_name": "integer"
        }
    ]
}
```

#### POST /api/budget/transaction/

##### Body
```json
{
	"transaction": {
        "date": "date",
        "amount": "decimal",
        "notes": "string",
        "cleared": "boolean",
        "category_id": "integer",
        "account_id": "integer",
        "payee_id": "integer"
    }
}
```

##### Response
```json
{
    "success": true,
    "transaction_id": "integer"
}
```

#### GET /api/budget/accounts/

##### Response
```json
{
    "success": true,
    "accounts": [
        {
            "account_id": "integer",
            "account_name": "string",
            "active": "boolean"
        }
    ]
}
```

#### POST /api/budget/account/

##### Body
```json
{
    "account_name": "some_string"
}
```

##### Response
```json
{
    "success": true,
    "account_id": "integer"
}
```

#### GET /api/budget/categories/

##### Response
```json
{
    "success": true,
    "categories": [
        {
            "category_id": "integer",
            "category_name": "string"
        }
    ]
}
```

#### POST /api/budget/category/

##### Body
```json
{
    "category_name": "some_string"
}
```

##### Response
```json
{
    "success": true,
    "category_id": "integer"
}
```