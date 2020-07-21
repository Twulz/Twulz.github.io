---
layout: project
group: Software
title: All-In-One Server
posts_title: "Here are the posts I have made so far about the Server and Node App:"
category: Server-App
breadcrumbs: 
- Things
- Software
---

I created a CI/CD pipeline using Jenkins to handle the integration and deployment of my Node-App project. This project will be a central HTTP server which will be used for some of my future projects.

The Node-App interfaces with a MySQL database using Knex to execute queries. As part of the CI/CD pipeline I utilised Mocha to handle automated testing.</p>

I used an Apache reverse proxy to forward traffic to the Jenkins web interface (\jenkins), the PhpMyAdmin interface (for MySQL) (\phpmyadmin), a general php webpage (\php) or to the Node-App routes (\\).