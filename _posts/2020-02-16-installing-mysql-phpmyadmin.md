---
layout: post
title:  "Installing MySQL and phpMyAdmin on the Server"
date:   2020-02-16
categories: Things Software Server-App
tags: Node-App Server-App Server NodeJs Database MySQL SQL DigitalOcean PhpMyAdmin
---

With my server now secured I'm installing MySQL and phpMyAdmin for the database and to view and configure it via a GUI.

<!--more-->

## Installing MySQL

I followed [yet another great DigitalOcean tutorial][mysql-tut] to install MySQL on the All-in-One Server. 

```sh
sudo apt update
sudp apt install mysql-server
sudo mysql_secure_installation
```

I selected `Yes` for each of the prompts except the Validate Password Plugin as I'll be the only user it's not as difficult to enforce password policies.

I then configured a new user (obviously with a different password!) and ensured that mysql was up and running:

```sh
sudo mysql
mysql> SELECT user,authentication_string,plugin,host FROM mysql.user;
mysql> ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';
mysql> FLUSH PRIVILEGES;
mysql> SELECT user,authentication_string,plugin,host FROM mysql.user;
mysql> CREATE USER 'Twulz'@'localhost' IDENTIFIED BY 'password';
mysql> GRANT ALL PRIVILEGES ON *.* TO 'Twulz'@'localhost' WITH GRANT OPTION;
mysql> exit
systemctl status mysql.service
```

## Installing Php - finishing out the LAMP stack

I found [this tutorial][lamp-stack] after all of my other configurations, I really should have jumped straight in with the LAMP stack from the beginning!

I skipped straight to Step 3 to install PHP

```sh
sudo apt install php libapache2-mod-php php-mysql
```

I made sure that Apache looks for php files before static html files:

```sh
sudo nano /etc/apache2/mods-enabled-dir.conf
```

```conf
<IfModule mod_dir.c>
    DirectoryIndex index.php index.html index.cgi index.pl index.xhtml index.htm
</IfModule>
```

```sh
sudo systemctl restart apache2
```

### Testing php on the server

I added another few lines to my Apache config file to serve php web pages at https://imade-aserver.xyz/php:

```sh
sudo nano /etc/apache2/sites-available/imade-aserver.xyz-le-ssl.conf
```

```conf
DocumentRoot /var/www/imade-aserver.xyz
ProxyPass /php !
```

This tells the server that the root directory is at `/var/www/imade-aserver.xyz` but only to access it if the sub-directory is `https://imade-aserver.xyz/php`. All other directories are routed to the Node-App server. Here is the complete file for reference:

```conf
<IfModule mod_ssl.c>
<VirtualHost *:443>
    ServerAdmin webmaster@localhost
    ServerName imade-aserver.xyz
    ServerAlias www.imade-aserver.xyz
    DocumentRoot /var/www/imade-aserver.xyz
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

    ProxyPass /php !
    ProxyPass / http://127.0.0.1:3000/
    ProxyPassReverse / http://127.0.0.1:3000/
    ErrorLog ${APACHE_LOG_DIR}/error.log
    CustomLog ${APACHE_LOG_DIR}/access.log combined

    Include /etc/letsencrypt/options-ssl-apache.conf
    SSLCertificateFile /etc/letsencrypt/live/imade-aserver.xyz/fullchain.pem
    SSLCertificateKeyFile /etc/letsencrypt/live/imade-aserver.xyz/privkey.pem

    RequestHeader set X-Forwarded-Proto "https"
    RequestHeader set X-Forwarded-Port "443"
</VirtualHost>
</IfModule>
```

Then restart the apache server:
```sh
sudo systemctl restart apache2
```

I also had to make a test file, located at `/var/www/imade-aserver.xyz/php/index.php`

```sh
cd /var/www/imade-aserver.xyz
mkdir php
cd php
sudo nano index.php
```

```php
<?php
echo "<h1>TwulzServer PHP Test Page</h1>";
echo "<p>Php site working correctly</p>";
?>
```

Now I can access my php site at: `https://imade-aserver.xyz/php` while still maintaining access to Jenkins and my Node-App.

## Installing phpMyAdmin

I followed [yet another DigitalOcean tutorial][php-tut] to install and configure phpMyAdmin.

```sh
sudo apt update
sudo apt install phpmyadmin php-mbstring php-gettext
```

I made sure to select the apache2 configuration for phpmyadmin during the installation process and to use the `dbconfig-common` database.

```sh
sudo phpenmod mbstring
sudo systemctl restart apache2
```

I already had the root user setup to use a password and had configured an alternate user for normal access to the database. 

I had to add `/phpmyadmin` as an exception to my Apache2 configuration so it wouldn't try to `GET /phpmyadmin` from my Node App:

```sh
sudo nano /etc/apache2/sites-available/imade-aserver.xyz-le-ssl.conf
```

In the same location as the `ProxyPass /php !` line above, I also added it for `/phpmyadmin`:

```conf
ProxyPass /phpmyadmin !
```

And restart apache2 to apply the changes:

```sh
sudo systemctl restart apache2
```

Now I could go straight to `https://imade-aserver.xyz/phpmyadmin` to log into the database!

## Adding additional security to phpMyAdmin directory

I followed step 3 of the DigitalOcean tutorial to further secure my phpmyadmin instance. First I added the `AllowOverride All` directive to the configuration file:

```sh
sudo nano /etc/apache2/conf-available/phpmyadmin.conf
```

```conf
<Directory /usr/share/phpmyadmin>
    Options FollowSymLinks
    DirectoryIndex index.php
    AllowOverride All
    ...
```

```sh
sudo systemctl restart apache2
```

Also create `.htaccess` for phpmyadmin:

```sh
sudo nano /usr/share/phpmyadmin/.htaccess
```

```sh
AuthType Basic
AuthName "Restricted Files"
AuthUserFile /etc/phpmyadmin/.htpasswd
Require valid-user
```

And create a username password pair to use with the authentication:

```sh
sudo htpasswd -c /etc/phpmyadmin/.htpasswd username
```

Then I was prompted to enter a password.

It's noted on the tutorial that if I was to create _another_ user, I'd run the same command without the `-c` flag.

Now when I go to `https://imade-aserver.xyz/phpmyadmin` I'm prompted first for the .htaccess password and then presented with the normal phpmyadmin login page.





[mysql-tut]: https://www.digitalocean.com/community/tutorials/how-to-install-mysql-on-ubuntu-18-04
[lamp-stack]: https://www.digitalocean.com/community/tutorials/how-to-install-linux-apache-mysql-php-lamp-stack-ubuntu-18-04
[php-tut]: https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-phpmyadmin-on-ubuntu-18-04