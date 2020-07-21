---
layout: post
title:  "Configuring HTTPS for the Server"
date:   2020-02-04
categories: Things Software Server-App
tags: Node-App Server-App Server Security HTTPS Domain DNS Apache Reverse-Proxy
---

Today I'm adding HTTPS support to my new [All in One Server]({ % post_url 2020-01-21-all-in-one-server }) by registering a domain name and installing an SSL certificate from Lets Encrypt.

<!--more-->

## Registering and setting up the domain

I registered a new domain with Namecheap - $1 USD for a year? Done!

I used [this tutorial][DO-configureNameCheap] to configure the domain to work with my Digital Ocean Droplet. It was implemented quite quickly and now I could access my server at `http://imade-aserver.xyx`!

## Setting up virtual hosts for Apache

Next, I set up the virtual hosts as recommended by the [Apache tutorial][apache-tutorial] I was following.

```
sudo mkdir /var/www/imade-aserver.xyz
sudo chow -R $USER:$USER /var/www/imade-aserver.xyz
sudo chown -R $USER:$USER /var/www/imade-aserver.xyz
sudo chmod -R 755 /var/www/imade-aserver.xyz
nano /var/www/imade-aserver.xyz/index.html
sudo nano /etc/apache2/sites-available/imade-aserver.xyz.conf
sudo a2ensite imade-aserver.xyz.conf
sudo a2dissite 000-default.conf
sudo apache2ctl configtest
sudo systemctl restart apache2
```

## Registering an SSL certificate

Now that I have a domain name I can install the SSL certificate and configure https using [this tutorial][lets-encrypt]. 

```sh
sudo add-apt-repository ppa:certbot/certbot
sudo apt install python-certbot-apache
```

While configuring the firewall I discovered I still had port 3000 open so I deleted those rules:
```
sudo ufw status
sudo ufw delete 1
sudo ufw status
sudo ufw delete 4
sudo ufw status
```

In the end I already had Full Apache enabled so no need to reconfigure that:

```sh
$ sudo ufw status
Status: active

To                         Action      From
--                         ------      ----
OpenSSH                    ALLOW       Anywhere
8080                       ALLOW       Anywhere
Apache Full                ALLOW       Anywhere
OpenSSH (v6)               ALLOW       Anywhere (v6)
8080 (v6)                  ALLOW       Anywhere (v6)
Apache Full (v6)           ALLOW       Anywhere (v6)
```

Finally use certbot with an incredibly easy command to obtain and configure the certificate automatically and test the auto-renewal:

```sh
sudo certbot --apache -d imade-aserver.xyz -d www.imade-aserver.xyz
sudo certbot renew --dry-run
```

Success! Now I have the little padlock when I go to `https://imade-aserver.xyz` and `http://imade-aserver.xyz`!

Next steps is to remember what other projects I wanted to use this server for...


[DO-configureNameCheap]: https://www.digitalocean.com/community/tutorials/how-to-point-to-digitalocean-nameservers-from-common-domain-registrars
[dns-quickstart]: https://www.digitalocean.com/docs/networking/dns/quickstart/
[apache-tutorial]: https://www.digitalocean.com/community/tutorials/how-to-install-the-apache-web-server-on-ubuntu-18-04#step-5-%E2%80%94-setting-up-virtual-hosts-recommended
[lets-encrypt]: https://www.digitalocean.com/community/tutorials/how-to-secure-apache-with-let-s-encrypt-on-ubuntu-18-04