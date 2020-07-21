---
layout: post
title:  "Adding an Apache Reverse Proxy for the Node App Server"
date:   2019-12-10
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript Apache Reverse-Proxy
---

I want to add HTTPS support to the node-app server so today I configured an Apache Reverse Proxy to redirect traffic from port 80 and 443 (HTTP and HTTPS) to my node-app which runs on port 3000.

<!--more-->

I followed [these instructions][DO-LAMP] to install apache2 on my Ubuntu 16.04 Digital Ocean Droplet which contains my Node-App server and then followed [some more instructions][DO-instructions] to configure the reverse proxy itself.

First, install apache2:

```sh
sudo apt-get update
sudo apt-get install apache2
```

Then supress the warnings by configuring the `ServerName IP_address` in the `apache2.conf` file.

```sh
sudo nano /etc/apache2/apache2.conf
sudo apache2ctl configtest
sudo systemctl restart apache2
```

Allow Apache through the firewall:

```sh
sudo ufw app list
sudo ufw app info "Apache Full"
sudo ufw allow in "Apache Full"
```

Insall the Apache modules needed for the reverse proxy:

```sh
sudo a2enmod proxy
sudo a2enmod proxy_http
sudo a2enmod proxy_balancer
sudo a2enmod lbmethod_byrequests
sudo systemctl restart apache2
```

Configure the redirect in the default config:

```sh
sudo nano /etc/apache2/sites-available/000-default.conf
sudo systemctl restart apache2
```

This config file now looks like this:
```conf
<VirtualHost *:80>
        ProxyPreserveHost On

        ProxyPass / http://127.0.0.1:3000/
        ProxyPassReverse / http://127.0.0.1:3000/

        # The ServerName directive sets the request scheme, hostname and port that
        # the server uses to identify itself. This is used when creating
        # redirection URLs. In the context of virtual hosts, the ServerName
        # specifies what hostname must appear in the request's Host: header to
        # match this virtual host. For the default virtual host (this file) this
        # value is not decisive as it is used as a last resort host regardless.
        # However, you must set it for any further virtual host explicitly.
        #ServerName www.example.com

        #ServerAdmin webmaster@localhost
        #DocumentRoot /var/www/html

        # Available loglevels: trace8, ..., trace1, debug, info, notice, warn,
        # error, crit, alert, emerg.
        # It is also possible to configure the loglevel for particular
        # modules, e.g.
        #LogLevel info ssl:warn

        #ErrorLog ${APACHE_LOG_DIR}/error.log
        #CustomLog ${APACHE_LOG_DIR}/access.log combined

        # For most configuration files from conf-available/, which are
        # enabled or disabled at a global level, it is possible to
        # include a line for only one particular virtual host. For example the
        # following line enables the CGI configuration for this host only
        # after it has been globally disabled with "a2disconf".
        #Include conf-available/serve-cgi-bin.conf
</VirtualHost>
```

I tested the redirect and realised I hadn't actually started the server:

```sh
cd node-app/
pm2 start index.js
```

Now when I access the server's IP address through a browser without specifying the Port, it defaults to port 80 (HTTP) and I get the `Hello World` message from my Node-App.

Now to only allow direct access to the Node-App from localhost (add as the second argument in the index.js file):

```
// Start the server
var server = app.listen(process.env.PORT || 3000, 'localhost', function() {
    console.log('Server started on port 3000...');
});
```

This caused an error due to my automated tests which currently check for a 404 error when trying to send a POST request. A solution was to add `ProxyErrorOverride off` to the above file as found in [this post](https://stackoverflow.com/questions/55313408/apache-not-passing-through-404-error-from-api-behind-reverse-proxy).

```conf
<VirtualHost *:80>
        ProxyPreserveHost On
        ProxyErrorOverride off
        ProxyPass / http://127.0.0.1:3000/
        ProxyPassReverse / http://127.0.0.1:3000/
</VirtualHost>
```

[DO-instructions]: https://www.digitalocean.com/community/tutorials/how-to-use-apache-as-a-reverse-proxy-with-mod_proxy-on-ubuntu-16-04
[DO-LAMP]: https://www.digitalocean.com/community/tutorials/how-to-install-linux-apache-mysql-php-lamp-stack-on-ubuntu-16-04