---
layout: post
title:  "Changing the domain and Jenkins reconfiguration"
date:   2021-08-28
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Javascript CICD Jenkins
---

I changed the domain used for my server and reconfigured Apache2 to have a homepage to link to all the services now running on it - phpmyadmin, jenkins, the node-app and now the homepage.

<!--more-->

## Changing the Domain

With my domain renewal coming up I decided I didn't want to renew the imade-aserver.xyz domain and instead use my twulz.com domain that I've purchased instead. First up I needed to update the config files corresponding to the new domain:

```sh
sudo cp imade-aserver.xyz-le-ssl.conf twulz.com-le-ssl.conf
sudo nano twulz.com-le-ssl.conf
sudo nano /etc/apache2/sites-available/twulz.com.conf
```

#### /etc/apache2/sites-available/twulz.com-le-ssl.conf
```conf
<IfModule mod_ssl.c>
    <VirtualHost *:443>
        ServerAdmin webmaster@localhost
        ServerName twulz.com
        ServerAlias www.twulz.com
        DocumentRoot /var/www/twulz.com
        ProxyPreserveHost On
        ProxyRequests Off
        AllowEncodedSlashes NoDecode

        <Proxy *>
        Order deny,allow
        Allow from all
        </Proxy>

        ProxyPass /jenkins http://127.0.0.1:8080/jenkins nocanon
        ProxyPassReverse /jenkins http://127.0.0.1:8080/jenkins
        ProxyPassReverse /jenkins http://imade-aserver.xyz/jenkins

        Redirect 301 /blog https://imade-athing.com/

        ProxyPass /php !
        ProxyPass /phpmyadmin !
        ProxyPass /api http://127.0.0.1:4000
        ProxyPassReverse /api http://127.0.0.1:4000
        ErrorLog ${APACHE_LOG_DIR}/error.log
        CustomLog ${APACHE_LOG_DIR}/access.log combined

        Include /etc/letsencrypt/options-ssl-apache.conf

        RequestHeader set X-Forwarded-Proto "https"
        RequestHeader set X-Forwarded-Port "443"
        SSLCertificateFile --redacted--
        SSLCertificateKeyFile --redacted--
    </VirtualHost>
</IfModule>
```

So this will mean that the node-app server will instead be accessible from the /api/ path with a normal website to more easily navigate everything I'm using the domain for.

#### /etc/apache2/sites-available/twulz.com.conf
```
<VirtualHost *:80>
    ServerName twulz.com
    Redirect permanent / https://twulz.com/
    RewriteEngine on
    RewriteCond %{SERVER_NAME} =www.twulz.com [OR]
    RewriteCond %{SERVER_NAME} =twulz.com
    RewriteRule ^ https://%{SERVER_NAME}%{REQUEST_URI} [END,NE,R=permanent]
</VirtualHost>
```

I then created a new `index.html` file with a "Hello World!" just to check the normal server functionality in case I break phpmyadmin, the node-app or jenkins separately.

```sh
sudo mkdir /var/www/twulz.com
sudo chown -R $USER:$USER /var/www/twulz.com
sudo chmod -R 755 /var/www/twulz.com
sudo nano /var/www/twulz.com/index.html
```

To tell apache2 to use the new server there's a few commands I needed to run:

```sh
sudo a2ensite twulz.com.conf
sudo a2dissite imade-aserver.xyz.conf
sudo apache2ctl configtest
sudo systemctl restart apache2
```

Success! 

## Adding a homepage for navigation

I created a simple homepage using Bootstrap 4 (the same as I use for this blog) to be served at the root directory to allow for navigating to all the services on the server. The code can be found over on [Github](https://github.com/Twulz/TwulzServerHome/blob/master/index.html).

I simply removed the placeholder `index.html` and cloned the repo into `/var/www/twulz.com` which was already being served by apache2 and now I could easily navigate between all my services!

![Server Homepage](/images/server/14_server_homepage.png)

## Security Test and Updates

I used the [Mozilla Observatory](https://observatory.mozilla.org/) to test my website for security issues. I couldn't resolve _all_ of the recommendations they have because of some dependencies for using phpmyadmin.

I did add this section to `/etc/apache2/sites-available/twulz.com-le-ssl.conf` below SSLCertificateKeyFile which brought up my score to a B which is the best I could do without disabling features of phpmyadmin.
```
<IfModule headers_module>
    RequestHeader set X-HTTPS 1
    Header set Content-Security-Policy "font-src 'self' https://fonts.gstatic.com https://fonts.googleapis.com; img-src 'self'; object-src 'none'; frame-ancestors 'self';"
    Header set X-Content-Type-Options nosniff
    Header set X-Frame-Options "SAMEORIGIN;"
    Header set Strict-Transport-Security "max-age=63072000; includeSubdomains;"
</IfModule>
```
