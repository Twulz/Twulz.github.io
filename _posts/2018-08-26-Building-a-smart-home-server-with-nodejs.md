---
layout: post
title:  "Building the Smart Home Server with NodeJS"
date:   2018-08-26
categories: Things Mechatronics FYP
tags: SmartHome ESP32 NodeMCU NodeJs MySQL SQL Database
related_image: 
  path: /images/mechatronicsFYP/01_overview_diagram.png
  alt: Node.js
---

For my Mechatronics Engineering _Final Year Project_ I was part of a 3-person team that developed a modular _Smart Home_ system that used a raspberry pi as the main server with various modules developed using ESP32 (NodeMCUs) that send and recieve data from the main server. This post is an overview of the server but keep an eye out for my next post on the package box system.

<!--more-->

# Introduction
For this project we were basically given free reign to scope and design the Smart Home system. In the end we decided to use a Node.js server run on a Raspberry Pi to be the brain of the smart home which hosted the database and the server that communicates over WiFi using the HTTP protocol providing a RESTful API that could then be used by many modules.

## Database Schema

The database needed for this Smart Home system is outlined below, note that many of the modules required the use of the sensors which were all controlled from the sensors table. Also note that there are two lighting tables; _inside_light_ dealt with the light levels required to determine if the internal house lights in a room should be turned on/off and the _outside_light_ table dealt with the outside light levels to raise or lower the blinds on the outside of a room.

![Database Schema](/images/mechatronicsFYP/02_database_schema.png)

![Database Schema](/images/mechatronicsFYP/03_database_schema.png)

# Code

## Routes
Here are the routes available for the smart home system:
* POST /access/
* POST /packageCode/
* GET /room/:id/heatingcooling
* POST /sensors/:id/temperature
* GET /room/:id/blind
* POST /sensors/:id/outside_light
* GET /garden_section/:id
* POST /sensors/:id/moisture
* GET /room/:id/light
* POST /sensors/:id/inside_light

## Server.js
The overall server code was really quite simple; each module has its own route file defining the routes used by each module and also a custom error handler for when things go wrong.

```javascript
const express = require('express');
const logger = require('morgan');
const bodyParser = require('body-parser');
var db = require('./models/dbconnection');
//const routes = require('./routes');

let store = {};
store.temperature = [];

const logging = true;

let app = express();
app.use(bodyParser.json());
app.use(logger('dev'));

app.use(require('./routes/packageBox.js'));
app.use(require('./routes/climateControl.js'));
app.use(require('./routes/lighting.js'));
app.use(require('./routes/garden.js'));

// Error handler, needs to be defined AFTER everything else
app.use(function (err, req, res, next) {
    // If status code hasn't changed, default to 500 server error
    if (res.statusCode === 200) {
        res.statusCode = 500;
        console.error(err);
	}
	// Return an error code
    res.json({
		status: res.statusCode,
        error: new String(err),
    })
});

// Start the server
app.listen(3000);
console.log("Server Running...");
```

## packageBox.js
This file has all the routes defined for the package box (see my next post for the actual build!)

```javascript
var express = require('express');
var router = express.Router();
var db = require('../models/dbconnection');
var Database = require('../models/database');

const database = new Database(db);
const logging = true;

// Post an access code to check if the code is allowable in the database.
// Make sure you specify the json (e.g. "{ "fobCardCode": "DE44156F" }") in the "body" field of Postman
// Also ensure it's specified as JSON
router.post('/access/', async (req, res, next) => {
    try {
        if (logging) { console.log("FobCardCode = " + req.body.fobCardCode); }
        if (req.body.fobCardCode) {
            var results = await database.isAllowedFobAccess(req.body.fobCardCode);
            if(logging) { console.log(results); }
            res.setHeader('content-type', 'application/json');
            if (results.length > 0)
            {
                res.statusCode = 200;
                res.send(JSON.stringify({"status": 200, "error": null, "response": "Access Granted"}));
            }
            else
            {
                res.statusCode = 200;
                res.send(JSON.stringify({"status": 200, "error": null, "response": "Access Denied"}));
            }
        } else {
            res.statusCode = 400;
            throw new Error("Code not sent");
        }
    } catch (err) {
        return next(err);
    }
});

router.post('/packageCode/', async (req, res, next) => {
    try {
        if (logging) { console.log("packageCode = " + req.body.keyCode); }
        if (req.body.keyCode) {
            //await db.query("SELECT * FROM package WHERE (keypadCode = ?) AND (packageInBox = 1)", [req.body.keyCode], function (err, results, fields) {
            var results = await database.isAllowedKeypadAccess(req.body.keyCode);
            res.setHeader('content-type', 'application/json');
            if (results.length > 0)
            {
                res.send(JSON.stringify({"status": 200, "error": null, "response": "Access Granted"}));
            }
            else
            {
                res.send(JSON.stringify({"status": 200, "error": null, "response": "Access Denied"}));
            }
        } else {
            res.statusCode = 400;
            throw new Error("Code not sent");
        }
    } catch(err) {
        return next(err);
    }
});

module.exports = router;
```

## database.js
This file contains all of the database functions including creating/destroying the initial data to enable automated testing using Mocha and Chai.

```javascript
const knex = require('knex');

class Database {

    constructor(config) {
        this.knex = knex({
          client: 'mysql',
          connection: config
        })
      }

    createSchema() {
        return this.knex.schema
            // Drop tables if they weren't destroyed - so can start again
            .dropTableIfExists('access_link')
            .dropTableIfExists('package')
            .dropTableIfExists('access_fob_card')
            .dropTableIfExists('temperature')
            .dropTableIfExists('outside_light')
            .dropTableIfExists('inside_light')
            .dropTableIfExists('lights')
            .dropTableIfExists('humidity')
            .dropTableIfExists('moisture')
            .dropTableIfExists('sensors')
            .dropTableIfExists('sensor_types')
            .dropTableIfExists('garden_sections')
            .dropTableIfExists('room')

            // Create tables for package box
            .createTable('package', table => {
                table.increments('packageId').unsigned().notNullable().primary()
                table.string('packageDesc', 45)
                table.string('keypadCode', 6).notNullable().unique()
                table.integer('packageInBox').notNullable().defaultTo(1)
                table.string('pickedUpBy').defaultTo(null)
                table.date('pickedUpDate')
            })
            .createTable('access_fob_card', table => {
                table.increments('accessFobCardId').unsigned().notNullable().primary()
                table.string('fobCardCode').notNullable()
            })
            .createTable('access_link', table => {
                table.integer('packageId').unsigned().notNullable()
                table.integer('fobCardId').unsigned().notNullable()
                table.foreign('packageId').references('package.packageId')
                table.foreign('fobCardId').references('access_fob_card.accessFobCardId')
                table.primary(['packageId', 'fobCardId'])
            })
            
            .createTable('room', table => {
                table.increments('room_id').unsigned().notNullable().primary()
                table.string('description').notNullable()
                table.float('preset_temp').notNullable().defaultTo(0.0)
                table.integer('heater_state').notNullable().defaultTo(0)
                table.integer('cooling_state').notNullable().defaultTo(0)
                table.integer('blind_state').notNullable().defaultTo(0)
            })

            .createTable('garden_sections', table => {
                table.increments('section_id').unsigned().notNullable().primary()
                table.string('description').notNullable()
                table.integer('minMoisture').unsigned().defaultTo(null)
                table.integer('criticalMoisture').unsigned().defaultTo(null)
                table.integer('lightSensitivity').unsigned().defaultTo(null)
                table.float('current_sun').notNullable().defaultTo(50.0)
                table.integer('valve_state').notNullable().defaultTo(0)
            })

            .createTable('sensor_types', table => {
                table.increments('sensor_type_id').unsigned().notNullable().primary()
                table.string('sensor_name').notNullable()
            })

            .createTable('sensors', table => {
                table.increments('sensor_id').unsigned().notNullable().primary()
                table.integer('sensor_type').unsigned().notNullable()
                table.integer('room_id').unsigned().defaultTo(null)
                table.integer('garden_section_id').unsigned().defaultTo(null)
                table.dateTime('last_replaced').notNullable().defaultTo(this.knex.raw('NOW()'))
                table.foreign('sensor_type').references('sensor_types.sensor_type_id')
                table.foreign('room_id').references('room.room_id')
                table.foreign('garden_section_id').references('garden_sections.section_id')
            })

            .createTable('humidity', table => {
                table.timestamp('timestamp').notNullable().defaultTo(this.knex.raw('NOW()'))
                table.integer('sensor_id').unsigned().notNullable()
                table.integer('humidityValue').notNullable()
                table.foreign('sensor_id').references('sensors.sensor_id')
                table.primary(['timestamp', 'sensor_id'])
            })

            .createTable('moisture', table => {
                table.timestamp('timestamp').notNullable().defaultTo(this.knex.raw('NOW()'))
                table.integer('sensor_id').unsigned().notNullable()
                table.integer('moistureLevel').notNullable()
                table.foreign('sensor_id').references('sensors.sensor_id')
                table.primary(['timestamp', 'sensor_id'])
            })

            .createTable('temperature', table => {
                table.timestamp('timestamp').notNullable().defaultTo(this.knex.raw('NOW()'))
                table.integer('sensor_id').unsigned().notNullable()
                table.float('temperature').notNullable()
                table.foreign('sensor_id').references('sensors.sensor_id')
                table.primary(['timestamp', 'sensor_id'])
            })

            .createTable('outside_light', table => {
                table.timestamp('timestamp').notNullable().defaultTo(this.knex.raw('NOW()'))
                table.integer('sensor_id').unsigned().notNullable()
                table.float('sun_percent').notNullable()
                table.foreign('sensor_id').references('sensors.sensor_id')
                table.primary(['timestamp', 'sensor_id'])
            })

            .createTable('inside_light', table => {
                table.timestamp('timestamp').notNullable().defaultTo(this.knex.raw('NOW()'))
                table.integer('sensor_id').unsigned().notNullable()
                table.integer('brightnessValue').notNullable()
                table.foreign('sensor_id').references('sensors.sensor_id')
                table.primary(['timestamp', 'sensor_id'])
            })

            .createTable('lights', table => {
                table.increments('light_id').unsigned().notNullable().primary()
                table.integer('room_id').unsigned().notNullable()
                table.integer('state').notNullable().defaultTo(0)
                table.foreign('room_id').references('room.room_id')
            })

            // Done!
            .then(() => 'Success')
    }

    destroySchema() {
        return this.knex.schema
            .dropTableIfExists('access_link')
            .dropTableIfExists('package')
            .dropTableIfExists('access_fob_card')
            .dropTableIfExists('temperature')
            .dropTableIfExists('outside_light')
            .dropTableIfExists('inside_light')
            .dropTableIfExists('lights')
            .dropTableIfExists('humidity')
            .dropTableIfExists('moisture')
            .dropTableIfExists('sensors')
            .dropTableIfExists('sensor_types')
            .dropTableIfExists('garden_sections')
            .dropTableIfExists('room')
            .then(() => 'Success')
    }

    initDatabase(data) {
        // You need to manually create the database before calling this.

        // Populate database
        return this.createSchema()
            .then(() => this.knex.insert(data.package).into('package'))
            .then(() => this.knex.insert(data.access_fob_card).into('access_fob_card'))
            .then(() => this.knex.insert(data.access_link).into('access_link'))
            .then(() => this.knex.insert(data.room).into('room'))
            .then(() => this.knex.insert(data.garden_sections).into('garden_sections'))
            .then(() => this.knex.insert(data.sensor_types).into('sensor_types'))
            .then(() => this.knex.insert(data.sensors).into('sensors'))
            .then(() => this.knex.insert(data.temperature).into('temperature'))
            .then(() => this.knex.insert(data.outside_light).into('outside_light'))
            .then(() => this.knex.insert(data.lights).into('lights'))
            .then(() => 'Success')
    }

    isAllowedFobAccess(fobCardCode) {
        return this.knex
            .select('*')
            .from('access_fob_card')
            .where('fobCardCode', fobCardCode);
    }

    isAllowedKeypadAccess(keyCode) {
        return this.knex
            .select('*')
            .from('package')
            .where('keypadCode', keyCode)
            .andWhere('packageInBox', 1)
    }

    getHeatingCooling(room_id) {
        return this.knex
            .select('*')
            .from('room')
            .where('room_id', room_id )
            .then((result) => {return result})
    }

    insertTemperature(sensor_id, temp) {
        return this.knex('temperature')
            .insert({'sensor_id': sensor_id, 'temperature': temp})
            .then(() => 'Success')
    }

    getSensorRoom(sensor_id) {
        return this.knex
            .select('room_id')
            .from('sensors')
            .where('sensor_id', sensor_id)
            .then((room_id) => {return room_id[0]})
    }

    getSensorGardenSection(sensor_id) {
        return this.knex
            .select('garden_section_id')
            .from('sensors')
            .where('sensor_id', sensor_id)
            .then((garden_section_id) => {return garden_section_id[0]})
    }

    updateHeaterCoolerState(heater_state, cooling_state, room_id) {
        return this.knex('room')
            .update({
                'heater_state': heater_state,
                'cooling_state': cooling_state
            })
            .where('room_id', room_id)
            .then(() => 'Success')
    }

    insertOutsideLight(sensor_id, sun_percent) {
        return this.knex('outside_light')
            .insert({'sensor_id': sensor_id, 'sun_percent': sun_percent})
            .then(() => 'Success')
    }

    deleteOldOutsideLightData() {
        return this.knex('outside_light')
            .where(this.knex.raw('timestamp < (NOW() - INTERVAL 15 MINUTE)'))
            .del()
            .then(() => 'Success')
    }

    updateBlindState(blind_state, room_id) {
        return this.knex('room')
            .update({ 'blind_state': blind_state })
            .where('room_id', room_id)
            .then(() => 'Success')
    }

    getRoomLightValues(room_id) {
        return this.knex
            .select('light_id', 'state')
            .from('lights')
            .where('room_id', room_id)
            .then((result) => {return result})
    }

    insertInsideLight(sensor_id, brightnessValue) {
        return this.knex('inside_light')
            .insert({'sensor_id': sensor_id, 'brightnessValue': brightnessValue})
            .then(() => 'Success')
    }

    updateRoomLightState(light_state, room_id) {
        return this.knex('lights')
            .update({ 'state': light_state })
            .where('room_id', room_id)
            .then(() => 'Success')
    }

    getGardenSectionData(section_id) {
        return this.knex
            .select('*')
            .from('garden_sections')
            .where('section_id', section_id)
            .then((result) => {return result[0]})
    }

    insertMoistureLevel(sensor_id, moistureLevel) {
        return this.knex('moisture')
            .insert({'sensor_id': sensor_id, 'moistureLevel': moistureLevel})
            .then(() => 'Success')
    }

    updateGardenWaterState(water_state, section_id) {
        return this.knex('garden_sections')
            .update({'valve_state': water_state})
            .where('section_id', section_id)
            .then(() => 'Success')
    }

    updateGardenSunState(sun_percent, section_id) {
        return this.knex('garden_sections')
            .update({'current_sun': sun_percent})
            .where('section_id', section_id)
            .then(() => 'Success')
    }
    
};

module.exports = Database;
```


## Automated Testing using Mocha

In this project we used test-driven development to ensure that bugs in other parts of the code were minimised when code was changed. The tests were run using Mocha and the test environment was created and destroyed using Knex before/after each set of tests to ensure correct functionality.

```dos
C:\Users\twulz\Documents\GitHub\SmartHomeFYP\Server>npm run test

> rest-api@1.0.0 test C:\Users\twulz\Documents\GitHub\SmartHomeFYP\Server
> mocha --recursive --exit

superagent: Enable experimental feature http2


(node:16224) ExperimentalWarning: The http2 module is an experimental API.
  HeatingCooling
    updateTemperature
      √ should update the temperature of the given sensor in the database (145ms)
    getHeatingCooling
      √ should return the heating/cooling state of the given room
    turnHeaterOn
      √ should turn on the heater (79ms)
    turnCoolingOn
      √ should turn on the cooler (75ms)
    turnHVACoff
      √ should turn off heater and cooler (113ms)

  Blinds
    updateOutsideLight
      √ should update the light outside read by the given sensor in the database (80ms)
    getBlind state
      √ should return the blind state of the given room
    openBlinds
      √ should open the blinds (75ms)
    closeBlinds
      √ should close the blinds (105ms)

  Garden
    getGardenState
      √ should return the threshold values for garden section 1 (77ms)
    postGardenTemperature
      √ should insert the temperature from the garden into the database (53ms)
    postGardenMoisture
      √ should insert the moisture from the garden into the database (97ms)
    turnWateringOnCritical
      √ should turn on the watering system in garden section 1 (below critical level) (121ms)
    turnWateringOnMinimum
      √ should turn on the watering system in garden section 1 (above critical, below min, low light) (161ms)
    turnWateringOffOverSun
      √ should turn on the watering system in garden section 1 (above critical, below min, high light) (154ms)

  grantAccessFobCard
    accessGranted
      √ should grant access to correct code (44ms)
    accessDenied
      √ should deny access to incorrect code
    badRequest_spelling
      √ should return an error for no provided code (spelling error)
    badRequest_noBody
      √ should return an error for no provided code (no POST body)

  grantAccessKeypad
    accessGranted
      √ should grant access to correct code
    accessDenied
      √ should deny access to incorrect code
    badRequest_spelling
      √ should return an error for no provided code (spelling error)
    badRequest_noBody
      √ should return an error for no provided code (no POST body)

  Lights
    getRoomLights
      √ should return the required light states of the given room (45ms)
    updateRoomBrightness
      √ should update the brightness of the given sensor in the database (77ms)
    turnLightsOn
      √ should turn on the lights in a given room (114ms)
    turnLightsOff
      √ should turn off the lights in a given room (107ms)


  27 passing (3m)
```