---
layout: post
title:  "Beginning the Budget App - Bootstrap"
date:   2020-05-26
categories: Things Software Budget-App
tags: Node-App Server NodeJs Database Knex Javascript Budget-App Bootstrap JQuery AJAX
---

Now that I have at least one working route for my budget app I'm turning my attention to the front end. I'd like to get the full stack wired up end-to-end with displaying one table of data so I can make sure I haven't missed anything major! For this I've decided to use Bootstrap in the form of a premade layout as I don't fancy myself much of a CSS designer!

<!--more-->

## Enter Bootstrap

I've decided to use Bootstrap to provide the design components in the front end. [This great layout](https://startbootstrap.com/themes/sb-admin-2/) seemed perfect for my needs - an open sourced (MIT Licensed) layout with a cohesive design with a responsive layout, Chart.js and Font Awesome already ready to go. I can spend less time on the design of individual components and more on the app as a whole.

So I downloaded the layout and installed it using `npm install` and `npm start` to get started on my local machine. I spent some time playing around with some of the menu items and icons, played with some of the charts and tables - this really looks like a good solution for me!

![Initial Layout](/images/budget/02_budget_initial_layout.PNG)

## Adding JQuery to Talk to the Server

Playing around with the HTML, CSS and JavaScript already in the layout is all well and good but I'll really be able to start making cool stuff when I can get stuff from the database. For this I decided to go with JQuery and AJAX to send and recieve the HTTP requests.

To get started there was very little overhead, I just added these two lines to my `index.html` file:

```html
<script src="node_modules/jquery/dist/jquery.min.js"></script>
<script src="index.js"></script>
```

Inside `index.js` was the following:

```js
$(function(){

    $.ajax('http://localhost:3000/', {
      type: 'get',
      dataType: 'json',
      contentType: 'application/json'
    })
    .done(function(response) {
      if (response.success === true) {
        console.log(response.response);
      }
    });
  
});
```

I also rearranged the routes in my Node-App Server's `index.js` so that the general `/` route comes _before_ the authentication routes so this means on my local machine I don't need to send a token just yet - I'm only testing the connectivity.

```js
app.use(require('./routes/general/generalRoute.js'));
app.use(require('./routes/general/authentication.js'));
app.use(require('./handlers/authHandler.js'));
//app.use(require('./routes/general/generalRoute.js'));
app.use(require('./routes/budget/budget.js'));
```

### Adding CORS

So running this code I got the following error:

```
index.html:1 Access to XMLHttpRequest at 'http://localhost:3000/' from origin 'null' has been blocked by CORS policy: Response to preflight request doesn't pass access control check: No 'Access-Control-Allow-Origin' header is present on the requested resource.
```

Which according to [this stackoverflow link](https://stackoverflow.com/questions/43871637/no-access-control-allow-origin-header-is-present-on-the-requested-resource-whe) is due to my server not sending the correct headers in the `OPTIONS` response. Sure enough, on my server it shows the `OPTIONS` request:

```
OPTIONS / 200 1.557 ms - 8
```

The solution is to implement `CORS` middleware which is just installing the `npm install cors --save` and adding these lines into my server `index.js` file before the rest of the routes:

```js
const cors = require('cors');

...

app.use(cors());
```

Refreshing my `index.html` page and I get my `Hello World Success!` message in the browser console!

### Adding the Authentication back

Next up is trying out a real token that I was previously using in Postman to see if I need anything else for the authorisation - but this is working just fine:

```js
$(function(){

    $.ajax('http://localhost:3000/api/budget/transactions', {
      type: 'get',
      dataType: 'json',
      contentType: 'application/json',
      headers: { 
        "Authorization": "Bearer eyJh_this_real_token_IWSGI" }
    })
    .done(function(response) {
        if (response.success === true) {
            console.log(response);
        }
    });
  
});
```

Yay I can get data from the database!

### Putting the Transactions into a Table

#### Updating the transaction data

I discovered that both the 'from' account_id/account_name were being overwritten by the 'payee' data as the default output of Knex is to leave off the table name for the object, i.e. the output was:

```json
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
```

So I updated the `getAllTransactions()` method to use the `as` keyword to specify the `fromaccount_id`, `fromaccount_name` and `payee_name`:

```js
getAllTransactions(user_id) {
    let result = this.knex('transaction')
        .select(
            'transaction.date', 
            'transaction.amount', 
            'transaction.notes', 
            'transaction.cleared', 
            'category.category_id', 
            'category.category_name', 
            'transaction.account_id as fromaccount_id', 
            'fromaccount.account_name as fromaccount_name', 
            'transaction.payee_id', 
            'payee.account_name as payee_name' )
        .from('transaction')
        .where({ 'transaction.user_id': user_id })
        .innerJoin('category', 'transaction.category_id', 'category.category_id')
        .innerJoin('account as fromaccount', 'transaction.account_id', 'fromaccount.account_id')
        .leftJoin('account as payee', 'transaction.payee_id', 'payee.account_id')
        .catch((error) => { return new Error(error); });
    return result;
}
```

Which makes the output now:

```json
"transactions": [
    {
        "date": "2020-04-23T14:00:00.000Z",
        "amount": 500,
        "notes": "Rent April",
        "cleared": 0,
        "category_id": 1,
        "category_name": "Food",
        "fromaccount_id": 1,
        "fromaccount_name": "Checking",
        "payee_id": null,
        "payee_name": null
    }
]
```

### Using JQuery to add to the table

I added id tags to the `tables.html` file: `<tbody id="transaction-data">` and removed all of the contents. Back in my `tables.js` file I added two foreach loops to first iterate over all transactions and then each of the data items within the transaction to build the table (code is further below). I got the data showing up with all the right profiling however half of my table seems to not know about the other half:

![No Data in Table](/images/budget/03_No_data_in_table.PNG)

I was getting a "No data available in table" row added to my table - turns out this is due to instantiating the table _before_ inserting the data using the jQuery callback. To solve this I just added the `$('#dataTable').DataTable();` line after the table elements.

```js
$(function(){

    $.ajax('http://localhost:3000/api/budget/transactions', {
      type: 'get',
      dataType: 'json',
      contentType: 'application/json',
      headers: { 
        "Authorization": "Bearer eyJh--redacted--gvYIWSGI" }
    })
    .done(function(response) {
      if (response.success === true) {
        let tableContent = "";
        console.log(response);
        $.each(response.transactions, function(index, element) {
          console.log(element);
          tableContent += '<tr>';
          $.each(element, (transindex, transelement) => {
            tableContent += "<td class=\"" + transindex + '\">' + transelement + '</td>';
          });
          tableContent += '</tr>';
        });
        $('#transaction-data').append(tableContent);
      }
      $('#dataTable').DataTable();
    });
});
```

And if you're wondering how I hid the `cleared`, `category_id`, `fromaccount_id` and `payee_id` - I added the key as the class name and the following CSS to not display these columns:

```html
<style>
.cleared, .category_id, .fromaccount_id, .payee_id {
    display:none;
}
</style>
```

The full HTML code for the table is this:

```html
<table class="table table-bordered" id="dataTable" width="100%" cellspacing="0">
    <thead>
    <tr>
        <th class="date">Date</th>
        <th class="amount">Amount</th>
        <th class="notes">Notes</th>
        <th class="cleared">Cleared</th>
        <th class="category_id">Category ID</th>
        <th class="category_name">Category</th>
        <th class="fromaccount_id">Account ID</th>
        <th class="fromaccount_name">Account</th>
        <th class="payee_id">Payee ID</th>
        <th class="payee_name">Payee</th>
    </tr>
    </thead>
    <tfoot>
    <tr>
        <th class="date">Date</th>
        <th class="amount">Amount</th>
        <th class="notes">Notes</th>
        <th class="cleared">Cleared</th>
        <th class="category_id">Category ID</th>
        <th class="category_name">Category</th>
        <th class="fromaccount_id">Account ID</th>
        <th class="fromaccount_name">Account</th>
        <th class="payee_id">Payee ID</th>
        <th class="payee_name">Payee</th>
    </tr>
    </thead>
    <tbody id="transaction-data">
    </tbody>
</table>
```

And here's a screenshot of my first real page! ...still need to look at the header nav bar but I've got some data showing up now! Please ignore that apparently I've paid my fake Rent from my fake Food category...

![Transaction Table](/images/budget/04_table.PNG)