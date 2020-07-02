---
layout: post
title:  "Refreshing this blog with Jekyll and Bootstrap 4"
date:   2020-06-25
categories: blog
tags: blog
---

After playing with bootstrap a bit for the budget app, and with all of the web development I'm now doing at work I was really dragging my feet in updating this blog. 

I made it in 2014 when the extent of my web development knowledge was what I learned on [Lissa Explains it All][http://www.lissaexplains.com/] (to my absolute delight it's still around, and still looks the same!) This was back in the late 90's and used on absolute bangers of websites as [Neopets][https://www.neopets.com], Geocities and of course my [MySpace][https://www.myspace.com] page. I basically knew enough not to plaster my shiny new blog with [amazing animations, javascript jokes and music that you can't turn off][https://www.cameronsworld.net/] (warning: I'm not joking about the music!)- but not quite enough to make a blog using best practices.

I'm older and somewhat wiser and tring to access my blog on mobile was hurting my soul, so definitely time for a refresh!

The goals for the project were:
* Update the domain name which was expiring anyway
* Make the layout responsive (update to Bootstrap 4!)
* Refresh some disused plugins and links
* Fix as many "sins" as I could find.

## Domain name

I use [Namecheap][https://namecheap.com] as my domain registrar and my blog domain was coming up for renewal. This is when I discovered that even though I got my initial domain for maybe a dollar, for every year after this the price increases dramatically. It was actually cheaper to move to the `.com` version instead!

It's often not recommended to move your domain due to branding, search engine standing and losing absolute links etc. but as I haven't been actively promoting my blog I saw it as no great loss!

I went ahead and purchased the `imade-athing.com` domain, this time picking a much longer time frame to lock in the yearly price of roughly $10.

I then needed to update the `Advanced DNS Settings` in the Namecheap console with the CNAME record for my site (hosted on GitHub Pages) and the A records for GitHub.

![Advanced DNS Settings](/images/blog/dns_settings_namecheap.png)

I also updated the `custom domain` in `Settings` on GitHub with the new domain and after 24 hours my SSL certificate was enabled so I could check `Enforce HTTPS` so all traffic would be routed through HTTPS. Done!

## Update to Bootstrap 4

### Installation & Theming

As I mentioned in the intro, a huge source of embarrassment with my blog had to do with how it wasn't really responsive and was absolutely horrible on mobile.

![Imade-athing.com on mobile](/images/blog/01_horrible_mobile.jpg)

...Gross... So that definitely needed to change!

The old blog did in fact use Bootstrap - version 2, so there was _some_ responsiveness where the menu moved to the newline, images became smaller, etc. I was planning to review the whole thing anyway though so I thought I should bring it up to the latest version of Bootstrap and learn how to create a layout properly.

I'm not particularly artistic (or masochistic?) enough to create my own theme so I downloaded and installed the [free `Pulse` theme from Bootswatch][https://bootswatch.com/pulse/] to make everything pretty!

To install this I just downloaded the sass `_variables.scss` and `_bootswatch.scss` to my `_sass` directory, making sure to import them in my `assets\main.scss` file.

```scss
---
# Only the main Sass file needs front matter 
---

@import "variables";
@import "bootstrap/bootstrap";
@import "syntax-highlighting";
@import "bootstrap-4-jekyll/bootstrap-4-jekyll";
@import "bootswatch";
@import "bootstrap_customisation";
```

### Layout & Customisation



![The Dark Souls Board Game](/images/darksouls/15_enemies_painted.jpg){: .rounded .mx-auto .d-block }

https://medium.com/better-programming/an-introduction-to-using-jekyll-with-bootstrap-4-6f2433afeda9
