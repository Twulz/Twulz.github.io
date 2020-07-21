---
layout: post
title:  "Configuring HTTPS for Jenkins on the All-in-One Server"
date:   2020-02-15
categories: Things Software Server-App
tags: Node-App Server-App Server Security HTTPS Apache Reverse-Proxy
---

In my [last blog post]({ % post_url 2020-02-04-configuring-https }) I registered a new domain name and installed a Let's Encrypt certificate to configure HTTPS, but now I reconfigured it so Jenkins would be secured too and could be reached on `https://imade-aserver.xyz/jenkins`.

<!--more-->

## Updating the config file for HTTP

I used the [Jenkins documentation][jenkins-apache] to configure Jenkins to work with HTTPS. The config file I created when installing Apache needs to be updated to redirect all traffic to https:

```sh
sudo nano /etc/apache2/sites-available/imade-aserver.xyz.conf
```

```conf
<VirtualHost *:80>
    ServerName imade-aserver.xyz
    Redirect permanent / https://imade-aserver.xyz/
</VirtualHost>
```

## Updating the config file for HTTPS

There is actually a separate config file for the https portion of the VirtualHost configuration:

```sh
sudo nano /etc/apache2/sites-available/imade-aserver.xyz-le-ssl.conf
```

```conf
<IfModule mod_ssl.c>
	<VirtualHost *:443>
	    ServerAdmin webmaster@localhost
	    ServerName imade-aserver.xyz
	    ServerAlias www.imade-aserver.xyz
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
	
	    ProxyPass / http://127.0.0.1:3000/
	    ProxyPassReverse / http://127.0.0.1:3000/
	    ErrorLog ${APACHE_LOG_DIR}/error.log
	    CustomLog ${APACHE_LOG_DIR}/access.log combined
	
	    Include /etc/letsencrypt/options-ssl-apache.conf
	    SSLCertificateFile /etc/letsencrypt/live/imade-aserver.xyz/fullchain.pem
	    SSLCertificateKeyFile /etc/letsencrypt/live/imade-aserver.xyz/privkey.pem
	</VirtualHost>
</IfModule>
```

After making changes to the Apache configuration I had to restart Apache:

```sh
sudo systemctl restart apache2
```

## Update the Jenkins arguments

The jenkins arguments needed to be updated to listen to requests from localhost and configure it to be located at the subdirectory /jenkins.

```sh
sudo nano /etc/default/jenkins
```

This is only the very last argument, I left the rest of the file as default:

```sh
JENKINS_ARGS="--webroot=/var/cache/$NAME/war --httpPort=$HTTP_PORT --httpListenAddress=127.0.0.1 --prefix=/jenkins
```

After making changes to the Jenkins configuration I also had to restart Jenkins:

```sh
sudo systemctl restart jenkins
```

## Configure Jenkins' location in its own settings

I went to `Jenkins > Manage Jenkins > Configure System` and updated the location to be the subdirectory:

![Jenkins Location](/images/server/10_jenkins_location.jpg)


## Delete the firewall rule for port 8080

Now that I'm accessing Jenkins from behind the apache firewall, I don't want the default jenkins port to be exposed anymore so I deleted the ufw rule.

```sh
sudo ufw delete allow 8080
sudo ufw status
			Status: active
			
			To                         Action      From
			--                         ------      ----
			OpenSSH                    ALLOW       Anywhere
			Apache Full                ALLOW       Anywhere
			OpenSSH (v6)               ALLOW       Anywhere (v6)
			Apache Full (v6)           ALLOW       Anywhere (v6)
```

## Accessing the Node-App and Jenkins

After the above configuration I can now access the Node App at: `https://imade-aserver.xyz` and jenkins at `https://imade-aserver.xyz/jenkins` and if I try accessing either of them through standard HTTP it will redirect to HTTPS. It also works at www.imade-aserver.xyz!

## Avoiding the Jenkins "Reverse Proxy is Broken" error

So after setting up the above I got an error message `It appears that your reverse proxy setup is broken`:

![Reverse Proxy is Broken](/images/server/11_jenkins_reverse_proxy_broken.jpg)

I found from [this link][reverseproxy] that I needed to add the `RequestHeader` parameters to the `/etc/apache2/sites-available/imade-aserver.xyz-le-ssl.conf` file, here is the completed file:

```conf
<IfModule mod_ssl.c>
	<VirtualHost *:443>
	    ServerAdmin webmaster@localhost
	    ServerName imade-aserver.xyz
	    ServerAlias www.imade-aserver.xyz
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

Now there are no errors in Jenkins and I can access both Jenkins _and_ the Node-App over HTTPS!
	    


[reverseproxy]: https://wiki.jenkins.io/display/JENKINS/Jenkins+says+my+reverse+proxy+setup+is+broken
[jenkins-apache]: https://wiki.jenkins.io/display/JENKINS/Running+Jenkins+behind+Apache