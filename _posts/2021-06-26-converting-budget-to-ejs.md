---
layout: post
title:  "Converting the Budget App to use EJS Templates"
date:   2021-06-26
categories: Things Software Budget-App
tags: Node-App Server NodeJs Database Knex Javascript Budget-App Bootstrap EJS Express
---

Last time I [visited the budget app]({% post_url 2020-05-26-beginning-budget-app %}) I used Ajax and JQuery to communicate back to the server but I've since decided to go with more modern tools and frameworks installed using node.js. Here I'll be converting the app to use EJS templating.

<!--more-->

## Installation

This means using express and for templating I'm going to use [EJS - Embedded JavaScript templating][ejs] to convert the bootstrap layout into templates so I could reuse components across the app and not have to change things in multiple places. They can be installed using npm:

```sh
npm install express ejs
```

I created a new folder in root called `views` and moved `home.html` into it, at the same time renaming it to `home.ejs` - I don't actually need to make any other changes here to get it working with ejs, keeping it all as HTML works just fine to get things going.

The root _file_ for the app is now `index.js` (instead of `index.html`) and to start using the packages they can be `require`d or ejs can be specified as the view engine with the views folder (this line isn't required, but including it for explicitness). I also need to provide another folder for all the static resources for the project which I called `resources` and moved all the other folders into it (`css`, `img`, `js`, `scss`, `vendor`) so that express knows where to find the resources I've already referenced locally.

The barebones file is now:

```js
const express = require('express');
const app = express();

app.use(express.static('resources'));

app.set('view engine', 'ejs');
app.set('views', 'views');

app.get('/', (req, res) => {
    res.render('home');
});

app.listen(3000, () => {
    console.log("LISTENING ON PORT 3000");
});
```

The app can now be run using `node index.js` and navigating to `localhost:3000` in the browser - all looking good so far!

## Templating

Next it was time to take advantage of the templating capabilities of ejs - currently I've got common components just copied/pasted into all of the other files which is a nightmare to try to maintain. I created a folder in the `views` folder called `includes` to hold these components. I started the process by identifying the components that are shared across different pages and moving them into their own `.ejs` files in this folder.

A good candidate was a file I named `foot.ejs` which had the scroll button, logout modal and all the extra javascript needed - I added a `fundit.js` file to include the custom javascript I'd add to the page.

```html
<!-- Scroll to Top Button-->
<a class="scroll-to-top rounded" href="#page-top">
  <i class="fas fa-angle-up"></i>
</a>

<!-- Logout Modal-->
<div class="modal fade" id="logoutModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
  <div class="modal-dialog" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="exampleModalLabel">Ready to Leave?</h5>
        <button class="close" type="button" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">×</span>
        </button>
      </div>
      <div class="modal-body">Select "Logout" below if you are ready to end your current session.</div>
      <div class="modal-footer">
        <button class="btn btn-secondary" type="button" data-dismiss="modal">Cancel</button>
        <a class="btn btn-primary" href="login">Logout</a>
      </div>
    </div>
  </div>
</div>

<!-- Bootstrap core JavaScript-->
<script src="/vendor/jquery/jquery.min.js"></script>
<script src="/vendor/bootstrap/js/bootstrap.bundle.min.js"></script>

<!-- Core plugin JavaScript-->
<script src="/vendor/jquery-easing/jquery.easing.min.js"></script>

<!-- Custom scripts for all pages-->
<script src="/js/sb-admin-2.min.js"></script>

<!-- Page level plugins -->
<script src="/vendor/chart.js/Chart.min.js"></script>

<!-- Page level custom scripts -->
<script src="/js/demo/chart-area-demo.js"></script>
<script src="/js/demo/chart-pie-demo.js"></script>

<script src="/js/fundit.js"></script>
```

So I cut the above code from the `home.ejs` file and replaced it with a simple `include` tag in it's place, just above the `</body>` tag.
```js
  <%- include('includes/foot') -%>
```

I continued on like this, replacing any code that was repeated across the pages and moved them into their own files: `foot.ejs`, `footer.ejs`, `sidebar.ejs`, `topbar.ejs` and `head.ejs` all into their own files. `head.ejs` needed some extra customisation as each page would have it's own title. I could add this in as an ejs variable passed in through the renderer.
```html
<title>FundIt! - <%= title %></title>
```

In `index.js` I added the variable as a second argument passed into the render:

```js
app.get('/', (req, res) => {
    res.render('home', { title: 'Dashboard' });
});
```

The components can actually be further combined to have an includes within an includes but for now I'll settle for the bulk of the code being in components so I only have to change them in one location.

The `home.ejs` file now looked like so:

```html
<!DOCTYPE html>
<html lang="en">

<%- include('includes/head') -%>

<body id="page-top">

  <!-- Page Wrapper -->
  <div id="wrapper">

    <%- include('includes/sidebar') -%>

    <!-- Content Wrapper -->
    <div id="content-wrapper" class="d-flex flex-column">

      <!-- Main Content -->
      <div id="content">

        <%- include('includes/topbar') -%>

        <!-- Begin Page Content -->
        <div class="container-fluid">

          <!-- ... -->

        </div>
        <!-- /.container-fluid -->

      </div>
      <!-- End of Main Content -->

      <%- include('includes/footer') -%>

    </div>
    <!-- End of Content Wrapper -->

  </div>
  <!-- End of Page Wrapper -->

  <%- include('includes/foot') -%>

</body>

</html>
```

So this is all well and good for the homepage but none of the links work anymore because they're not rendered. Time to fix that!

## Adding Other Pages

I renamed all of the files that I had already started on from `.html` to `.ejs`: `404.ejs`, `account.ejs`, `budget.ejs`, `reports.ejs`, `settings.ejs` and `transactions.ejs`. I then replaced the components that I'd taken out into templates with the relevant `<%- include('...') -%>` tag so they all resembled the `home.ejs` snippet above.

Now to set the renderer to find these files - I could add them all individually and hard-code their routes into the app but this wouldn't be very extensible so I added a dynamic route. This route takes any other route (apart from `/`) and searches a config file for matching data in the config file - if it's found it will render the correct page and if not will return the 404 Not Found page.

```js
const config = require('./config.json');

app.get('/:page', (req, res) => {
    const { page } = req.params;
    let data = config.pages[page];
    if (data) {
        res.render(page, { name : page, ...data });
    } else {
        res.render('404', { title : "404 Not Found" });
    }
});
```

This means I can add other parameters and other pages by adding them to this file, or even hide ones that aren't ready to be rendered yet. Here is the corresponding `config.json` file:

```json
{
    "pages" : {
        "account" : {
            "title" : "Account"
        },
        "budget" : {
            "title" : "Budget"
        },
        "reports" : {
            "title" : "Reports"
        },
        "settings" : {
            "title" : "Settings"
        },
        "transactions" : {
            "title" : "All Transactions"
        }
    }
}
```

Finally I wanted to preserve the other sb-admin-2 bootstrap theme examples both to refer back to and also to have some more practise at converting to templates. I added all these files to the `views/examples` folder, including another `views/examples/includes` folder to maintain components exclusive to the examples. I also needed to add another route to the `index.js` app for this - added before the previous one so that the `/examples/` page isn't caught in the previously defined route.

```js
const express = require('express');
const app = express();
const config = require('./config.json');

app.use(express.static('resources'));

app.set('view engine', 'ejs');
app.set('views', 'views');

app.get('/', (req, res) => {
    res.render('home', { title: 'Dashboard' });
});

app.get('/examples/:page', (req, res) => {
    const { page } = req.params;
    let data = config.examplePages[page];
    if (data) {
        res.render('examples/'page, { name : page, ...data });
    } else {
        res.render('404', { title : "404 Not Found" });
    }
});

app.get('/:page', (req, res) => {
    const { page } = req.params;
    let data = config.pages[page];
    if (data) {
        res.render(page, { name : page, ...data });
    } else {
        res.render('404', { title : "404 Not Found" });
    }
});

app.listen(3000, () => {
    console.log("LISTENING ON PORT 3000");
});
```

Lastly I added the titles to the config file underneath the pages:

```json
{
    "pages" : {
        "account" : {
            "title" : "Account"
        },
        "budget" : {
            "title" : "Budget"
        },
        "reports" : {
            "title" : "Reports"
        },
        "settings" : {
            "title" : "Settings"
        },
        "transactions" : {
            "title" : "All Transactions"
        }
    },

    "examplePages" : {
        "blank" : {
            "title" : "Blank"
        },
        "buttons" : {
            "title" : "Buttons"
        },
        "cards" : {
            "title" : "Cards"
        },
        "charts" : {
            "title" : "Chart"
        },
        "forgot-password" : {
            "title" : "Forgot Password"
        },
        "home" : {
            "title" : "Dashboard"
        },
        "login" : {
            "title" : "Login"
        },
        "register" : {
            "title" : "Register"
        },
        "tables" : {
            "title" : "Tables"
        },
        "utilities-animation" : {
            "title" : "Animation Utilities"
        },
        "utilities-border" : {
            "title" : "Border Utilities"
        },
        "utilities-colour" : {
            "title" : "Colour Utilities"
        },
        "utilities-other" : {
            "title" : "Other Utilities"
        }
    }
}
```

[ejs]: https://ejs.co/
[sb-admin-2]: https://startbootstrap.com/themes/sb-admin-2/ 