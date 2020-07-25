---
layout: post
title:  "Building a Smart Parking Server"
date:   2018-09-18
categories: Things Mechatronics FYP
tags: SmartParking ESP32 NodeMCU NodeJs MySQL SQL Database
related_image: 
  path: /images/parking/nodejs.png
  alt: Node.js
---

A summary of developing the server using Node.js for my _Smart Parking for Smart Cities_ project I was a part of for my Computer Science final year project that we presented at the Capstone Expo (CapEx) at Swinburne.

<!--more-->

For my Computer Science _Final Year Project_ I was part of a 10-person team tasked with creating a _Smart Cities_ solution to solve problems that people with disabilities experience with finding appropriate parking.

After some research we found that the main issues that people with disabilities experience with parking is first finding parks that are nearby to their destination and that aren't already taken (either by other permit-holders or by non-permit holders).

So the design for the project was to be implemented in four stages; as you can't just go from a non-smart city to completely smart overnight. The scope for the current app was to be fully functional for stages 1 and 2 (so users can search for and book a space) and to be workable, but not necessarily scalable for a real-world application.

1.	**Stage 1 - Searching for a space: Ready for real-world.**
All three spaces included in the hardware demo are searchable in the Android app, and available to be enabled/disabled using the admin interface. The addresses used for this purpose was the ATC building at Swinburne university where CapEx took place.
2.	**Stage 2 – Booking a space: Ready for real-world.**
Spaces 1 and 2 are able to be booked in the app (if they are “enabled” by the admin interface) and the identity of the cars parked can be verified by the back-end, given their credentials. This is shown by the green and red LEDs on the hardware display panel signalling correctly parked and incorrectly parked, respectively.
3.	**Stage 3 – Blocking unauthorised access:**
In this stage, bollards are introduced to block unauthorised access to the spaces until the user with the booking is nearby. This model detects the car nearby using the fourth RFID sensor and lowers the bollard, which is a 9g servo motor, allowing the Lego car to park in the space and verify using the LEDs in stage 2. The bollard is then raised again when the car leaves the space.
4.	**Stage 4 – Dynamically allocated spaces:**
Stage 4 introduces space number 3 to the hardware demo that becomes available when spaces 1 and 2 are booked to allow for another user to potentially book a space for that time. This availability is indicated by the disability symbol on Space 3’s control panel lighting up and the bollard for this space to be raised. The space then becomes available to be searched for as in stage 1, booked like stage 2 and the bollard to be lowered when the car arrives as in stage 3.

We split into subteams to create the three components for the system:
* The back-end/server including the database and Node.js server to handle HTTP requests for the other two components.
* The user interface in the form of an Android App.
* The admin interface in the form of an Angular website.

I was part of the server team so here is my short write-up on my contributions there.

# Node.js Server

## Libraries

* Knex is a npm module which can be used to construct chainable meaningful SQL query for popular relational databases such as MySQL and PostgreSQL. The module provides several interfaces including Promise and data type conversion between the database and JavaScript.
* Mocha is a popular unit testing framework in JavaScript which is designed for both Behavioural-Driven Development (BDD) and Test-Driven Development (TDD).
* Chai is a npm module which provide chainable and readable assertion libraries for unit testing 

## Database

We used a MySQL server that was accessed through Knex to also enable the test environment for the automated testing using Mocha and Chai.

![Database](/images/parking/06_database_schema.jpg)

## Routes

### User Routes
Used by the Android app.
* GET /api/availabilities/v3
* GET /api/bookings/v3
* POST /api/bookings/v3
* DELETE /api/booking/:receiptID/v3
* GET /api/lots/v3
* POST /api/authentication/register/v0
* POST /api/authentication/login/v0

### Admin Routes
Used by the admin web interface.
* GET /api/admin/statistics/v0
* GET /api/admin/permits/v0
* PATCH /api/admin/permits/:userID/v0
* GET /api/admin/users

### Hardware Routes
Used by the hardware demo.
* POST /verify_park/v0
* GET /booking_status/:id/v0
* POST /booked_space/v0
* GET /third_park/v0
* GET /space_bookable/:id/v0

## Node.js Server

Here are some of the main files I contributed to the project. As you can see; the server was implemented with authentication (using Bearer tokens, this part was covered by another student), each route category was separated for some level of abstraction and finally there is a custom error handler for when anything goes wrong.


### Server.js
````javascript
const express = require('express');
const logger = require('morgan');
const errorhandler = require('errorhandler');
const bodyParser = require('body-parser');

let app = express();

// tell CORS to allow traffic from all origins
app.use(function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Headers", "Authorization, Origin, X-Requested-With, Content-Type, Accept");
  res.header("Access-Control-Allow-Methods", "GET, POST, DELETE, PATCH");
  next();
});

// Middleware
app.use(bodyParser.json());
app.use(logger('dev'));
//app.use(errorhandler());

app.use("/api/authentication", require("./routes/authentication_routes.js"));
app.use("/api/admin", require("./routes/admin_routes.js"));
app.use(require("./routes/temp_auth.js"));
// Routes used only for testing (early routes)
app.use(require('./routes/test_routes.js'));
// Routes used only for user app
app.use(require('./routes/user_routes.js'));
// Routes used only for the hardware demo
app.use(require('./routes/hardware_demo_routes.js'));


// Error handler, needs to be defined after everything else
app.use(function (err, req, res, next) {
    // If status code hasn't changed, default to 500
    if (res.statusCode === 200) {
        res.statusCode = 500;
        console.error(err);
    }
    // Intentionally not using output object to prevent other fields leaking
    res.json({
        ok: false,
        // new String() to force it to be a string in json
        error: new String(err),
    })
});
// Start Server
console.log("Server Running...");
app.listen(3000);
````



### user_routes.js
The user route data was verified against the schema I wrote and used the knex interfaces to read/write to the database.

```javascript
var express = require('express');
var router = express.Router();
var Ajv = require('ajv');
const config = require('../models/config');
const Database = require('../models/database');

const db = new Database(config);

var auth = require("../src/authentication");

var availabilitiesInputSchema = require('../routes/schemas/get_availabilities_input.json');
var bookingsInputSchema = require('../routes/schemas/post_bookings_input.json');
var lotsInputSchema = require('../routes/schemas/get_lots_input.json');
var ajv = Ajv({allErrors: true});

// Set to true for console outputs
var logging = false;

router.get('/api/availabilities/v3', async (req, res, next) => {
	try {
		if (logging) { console.log(req.query); }

		// Parse string -> required type
		var valid = false;
		if (parseAvailabilities(req.query))
		{
			// Validate JSON against schema
			valid = ajv.validate(availabilitiesInputSchema, req.query);
		}

		// Respond
		if (valid)
		{
			if (logging) { console.log("\nINPUT VALID\n"); }

			let availabilities = await db.getAvailabilities(req.query.minLat, req.query.minLong, req.query.maxLat, req.query.maxLong, req.query.date, req.query.time, req.query.duration);
			if (logging) { console.log(availabilities); }
			return res.json({ "ok": true, "lots": availabilities });
		}
		else
		{
			if (logging) { console.log("\nINPUT INVALID\n"); }
			res.statusCode = 400;
			throw new Error("JSON does not match schema");
		}
	} catch (err) {
		return next(err);
	}
});

router.get('/api/bookings/v3', auth.userAuth, async (req, res, next) => {
	try {
		if (req.user.userId) {
			if (logging) { console.log("User Id is " + req.user.userId); }
			let bookings = await db.getBookings(req.user.userId);
			if (logging) { console.log(bookings); }
			return res.json({ "ok": true, "bookings": bookings });
		} else {
			throw new Error("UserId not defined");
		}
	} catch (err) {
		return next(err);
	}
});

router.post('/api/bookings/v3', auth.userAuth, async (req, res, next) => {
	try {
		if (logging) { console.log("Body is:"); console.log(req.body); }
		if (logging) { console.log("userId is: " + req.user.userId); }

		// Parse string -> required type
		var valid = false;
		// Validate JSON against schema
		var ajv = Ajv({allErrors: true});
		valid = ajv.validate(bookingsInputSchema, req.body);

		// Respond
		if (valid && req.user.userId)
		{
			if (logging) { console.log("\nINPUT VALID\n"); }

			// Insert into database
			let receiptID = await db.insertBooking(req.user.userId, req.body.spaceID, req.body.date, req.body.time, req.body.duration);

			if (!((receiptID.isFulfilled == false) && (receiptID.isRejected == false))) {
				if (logging) { console.log("Receipt ID is " + receiptID); }
				res.status(201);
				return res.json({ "ok": true, "receiptID": receiptID });
			} else {
				throw new Error("Booking could not be confirmed");
			}
		}
		else
		{
			if (logging) { console.log("\nINPUT INVALID\n"); }
			res.statusCode = 400;
			throw new Error("JSON does not match schema");
		}
	} catch (err) {
		switch (err.code) {
			case 'ERR006': 
				res.statusCode = 400;
				next(new Error("Booking for this time already exists"));
				break;
			case 'ERR004': 
				res.statusCode = 400;
				next(new Error("User ID for this booking request is invalid"));
				break;
			default:
				res.statusCode = 500;
				return next(err);
		}
	}
});

router.delete('/api/booking/:receiptID/v3', auth.userAuth, async (req, res, next) => {
	try {
		if (logging) { console.log(req.params.receiptID); }
		if (logging) { console.log("userId is: " + req.user.userId); }

		// Respond if receiptID is an Int
		if (parseInt(req.params.receiptID) && req.user.userId)
		{
			if (logging) { console.log("\nINPUT VALID\n"); }

			let returned = await db.deleteBooking(req.params.receiptID);
			if (logging) { console.log(JSON.stringify(returned)); }

			if (!((returned.isFulfilled == false) && (returned.isRejected == false))) {
				res.status(202);
				return res.json({"ok": true});
			} else {
				res.statusCode = 500;
				throw new Error("Booking could not be deleted");
			}
		}
		else
		{
			if (logging) { console.log("\nINPUT INVALID\n"); }
			res.statusCode = 400;
			throw new Error("Invalid input");
		}
	} catch (err) {
		return next(err);
	}
});

router.get('/api/lots/v3', async (req, res, next) => {
	try {
		if (logging) { console.log(req.query); }

		// Parse string -> required type
		var valid = false;
		if (parseLots(req.query))
		{
			// Validate JSON against schema
			valid = ajv.validate(lotsInputSchema, req.query);
		}

		// Respond
		if (valid)
		{
			if (logging) { console.log("\nINPUT VALID\n"); }

			let lots = await db.getLots(req.query.minLat, req.query.minLong, req.query.maxLat, req.query.maxLong);

			if (logging) { console.log(lots); }

			// Create response
			return res.json({ "ok": true, "lots": lots });
		}
		else
		{
			if (logging) { console.log("\nINPUT INVALID\n"); }
			res.statusCode = 400;
			throw new Error("JSON does not match schema");
		}
	} catch (err) {
		return next(err);
	}
});

module.exports = router;

/********************************************************/
// Helper Functions
/********************************************************/

/*
* Checks the type of each given query parameter and return true if parsing OK
*/
function parseAvailabilities(query) {
	if ((query.maxLat = parseFloat(query.maxLat)) && (query.minLat = parseFloat(query.minLat))
		&& (query.maxLong = parseFloat(query.maxLong)) && (query.minLong = parseFloat(query.minLong))
		&& (query.time = parseInt(query.time)) && (query.duration = parseInt(query.duration)) && query.date)
	{
		return true;
	}
	return false;
}

/*
* Checks the type of each given query parameter and return true if parsing OK
*/
function parseLots(query) {
	if ((query.maxLat = parseFloat(query.maxLat)) && (query.minLat = parseFloat(query.minLat)) && 
		(query.maxLong = parseFloat(query.maxLong)) && (query.minLong = parseFloat(query.minLong)))
	{
		return true;
	}
	return false;
}
```

### Database.js

Here is the main database code - I removed some parts that I didn't contribute to at all.

```javascript

const DBError = require('./dberror')
const Transformer = require('./transformer')

const knex = require('knex')
const moment = require('moment')
const _ = require('lodash')
const randToken = require('random-token')
const tf = new Transformer()

const formatDate = (d) => moment(d).format('YYYY-MM-DD')
const parseBool = (b) => (b === null) ? b : (b === 1)

class Database {

  constructor(config) {
    this.knex = knex({
      client: 'mysql2',
      connection: config
    })
  }

  createSchema() {
    return this.knex.schema
      .dropTableIfExists('parking_schedules')
      .dropTableIfExists('parking_receipts')
      .dropTableIfExists('parking_spaces')
      .dropTableIfExists('parking_lots')
      .dropTableIfExists('tokens')
      .dropTableIfExists('users')
      .createTable('users', tb => {
        tb.increments('user_id')
        tb.date('reg_date').notNullable()
        tb.string('first_name').notNullable()
        tb.string('last_name').notNullable()
        tb.string('email').notNullable().unique()
        tb.string('password').notNullable()
        tb.boolean('admin').notNullable()
        tb.string('vehicle_reg').notNullable().unique()
        tb.string('permit_no').notNullable().unique()
        tb.date('permit_exp').notNullable()
        tb.string('rfid_tag').unique().defaultTo(null)
        tb.boolean('permit_approved')
      })
      .createTable('tokens', tb => {
        tb.increments('token_id')
        tb.text('token').notNullable()
        tb.integer('user_id').unsigned().notNullable()
        tb.foreign('user_id').references('users.user_id')
      })
      .createTable('parking_lots', tb => {
        tb.increments('lot_id')
        tb.float('latitude', 8, 5).notNullable()
        tb.float('longitude', 8, 5).notNullable()
        tb.string('name').notNullable()
        tb.string('address').notNullable()
      })
      .createTable('parking_spaces', tb => {
        tb.increments('space_id')
        tb.boolean('active').notNullable()
        tb.string('name').notNullable()
        tb.float('latitude', 8, 5).notNullable()
        tb.float('longitude', 8, 5).notNullable()
        tb.integer('lot_id').unsigned().notNullable()
        tb.integer('rfid_reader').unsigned().defaultTo(null)
        tb.foreign('lot_id').references('parking_lots.lot_id')
      })
      .createTable('parking_receipts', tb => {
        tb.increments('receipt_id')
        tb.integer('user_id').unsigned().notNullable()
        tb.foreign('user_id').references('users.user_id')
      })
      .createTable('parking_schedules', tb => {
        tb.integer('space_id').unsigned().notNullable()
        tb.date('date').notNullable()
        tb.integer('time_slot').unsigned().notNullable()
        tb.integer('receipt_id').unsigned()
        tb.primary(['space_id', 'date', 'time_slot'])
        tb.foreign('space_id').references('parking_spaces.space_id')
        tb.foreign('receipt_id').references('parking_receipts.receipt_id')
      })
      .then(() => 'Success')
  }

  destroySchema() {
    return this.knex.schema
      .dropTableIfExists('parking_schedules')
      .dropTableIfExists('parking_receipts')
      .dropTableIfExists('parking_spaces')
      .dropTableIfExists('parking_lots')
      .dropTableIfExists('tokens')
      .dropTableIfExists('users')
      .then(() => 'Success')
  }

  initDatabase(data) {
    return this.createSchema()
      .then(() => this.knex.insert(data.users).into('users'))
      .then(() => this.knex.insert(data.tokens).into('tokens'))
      .then(() => this.knex.insert(data.parking_lots).into('parking_lots'))
      .then(() => this.knex.insert(data.parking_spaces).into('parking_spaces'))
      .then(() => this.knex.insert(data.parking_receipts).into('parking_receipts'))
      .then(() => this.knex.insert(data.parking_schedules).into('parking_schedules'))
      .then(() => 'Success')
  }

  insertBooking(userID, spaceID, date, startTime, duration) {
    return this.knex
      .select()
      .from('parking_spaces')
      .where('space_id', spaceID)
      .then((spaces) => {
        if (spaces[0].active == 1) {
          return this.knex.transaction((trx) => {
            return trx
              .insert({ user_id: userID })
              .into('parking_receipts')
              .then((ids) => {
                let transform = (i) => ({
                  space_id: spaceID,
                  date: date,
                  time_slot: i + startTime,
                  receipt_id: ids[0]
                })
                let timeSlots = [...Array(duration).keys()]
                let schedules = timeSlots.map(transform)
                return trx
                  .insert(schedules)
                  .into('parking_schedules')
                  .then(() => ids[0])
              })
          }).catch(err => { throw DBError.mysql('insertBooking', err) })
        } else {
          throw new Error('Inactive space')
        }
      }
    )
  }

  verifyPark(tag, spaceID) {
    let today = new Date()
    let timeSlot = today.getHours() * 2 + Number(today.getMinutes() >= 30)
    return this.knex
      .from('users')
      .innerJoin('parking_receipts', 'users.user_id', 'parking_receipts.user_id')
      .innerJoin('parking_schedules', 'parking_receipts.receipt_id', 'parking_schedules.receipt_id')
      .select('parking_schedules.date', 'parking_schedules.time_slot')
      .where({
        'parking_schedules.date': formatDate(today),
        'parking_schedules.time_slot': timeSlot,
        'parking_schedules.space_id': spaceID,
        'users.rfid_tag': tag
      })
      .then(rows => rows.length === 1)
  }

  getBookingStatus(spaceID) {
    let today = new Date()
    let timeSlot = today.getHours() * 2 + Number(today.getMinutes() >= 30)
    return this.knex
      .select('receipt_id')
      .from('parking_schedules')
      .where({
        'parking_schedules.date': formatDate(today),
        'parking_schedules.time_slot': timeSlot,
        'parking_schedules.space_id': spaceID
      })
      .then(rows => rows.length === 1)
  }

  getBookedSpace(tag) {
    let today = new Date()
    let timeSlot = today.getHours() * 2 + Number(today.getMinutes() >= 30)
    return this.knex
      .from('users')
      .innerJoin('parking_receipts', 'users.user_id', 'parking_receipts.user_id')
      .innerJoin('parking_schedules', 'parking_receipts.receipt_id', 'parking_schedules.receipt_id')
      .select('parking_schedules.space_id')
      .where({
        'parking_schedules.date': formatDate(today),
        'parking_schedules.time_slot': timeSlot,
        'users.rfid_tag': tag
      })
      .then(rows => (rows.length === 1 ? rows[0].space_id : null ))
  }

  getSpaceActiveState(spaceID) {
    return this.knex
      .select('active')
      .from('parking_spaces')
      .where({ 'space_id': spaceID })
      .then((activeState) => {return activeState[0].active});
  }

  updateSpaceActiveState(space_id, activeState) {
    try {
      return this.knex('parking_spaces')
        .update({ 'active': activeState })
        .where('space_id', space_id)
        .then(() => 'Success')
    } catch (err) {
      throw DBError.mysql('Could not update activeState', err);
    }
  }
}

module.exports = Database
```

This all ended up being a bit of a code-dump but there's no good pictures to put for a server!

Be sure to check out my [next blog post]({{ site.baseurl }}{% post_url 2018-10-10-Building-a-smart-parking-demo %}) for the hardware demo I built for this project too.