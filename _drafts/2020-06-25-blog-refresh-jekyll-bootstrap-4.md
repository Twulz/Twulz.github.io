---
layout: post
title:  "Refreshing this blog with Jekyll and Bootstrap 4"
date:   2020-06-25
categories: blog
tags: blog
---

After playing with bootstrap a bit for the budget app, and with all of the web development I'm now doing at work I was really dragging my feet in updating this blog. 

<!--more-->

I made it in 2014 when the extent of my web development knowledge was what I learned on [Lissa Explains it All][lissa] (to my absolute delight it's still around, and still looks the same!) This was back in the late 90's and used on absolute bangers of websites as [Neopets][neopets], Geocities and of course my [MySpace][myspace] page. I basically knew enough not to plaster my shiny new blog with [amazing animations, javascript jokes and music that you can't turn off][nineties] (warning: I'm not joking about the music!)- but not quite enough to make a blog using best practices.

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

As I mentioned in the intro, a huge source of embarrassment with my blog had to do with how it wasn't really responsive and was absolutely horrible on mobile.

![Imade-athing.com on mobile](/images/blog/01_horrible_mobile.jpg)

...Gross... So that definitely needed to change!

The old blog did in fact use Bootstrap - version 2, so there was _some_ responsiveness where the menu moved to the newline, images became smaller, etc. I was planning to review the whole thing anyway though so I thought I should bring it up to the latest version of Bootstrap and learn how to create a layout properly.

### Installation & Theming

I downloaded the [source files][get-bootstrap] as I'm using Jekyll which can build the sass files. I unzipped the files and created a `_sass` folder with a `bootstrap-4-5-0` folder inside. I then copied the contents of the `sass` folder in the source files to that bootstrap folder.

I'm not particularly artistic (or masochistic?) enough to create my own theme so I downloaded and installed the [free `Pulse` theme from Bootswatch][bootswatch] to make everything pretty! To install this I just needed to download their `_variables.scss` and `_bootswatch.scss` files into my `_sass` folder. To further customise I also created `_bootstrap_customisation.scss` where I could put anything I wrote myself so if I was to update bootstrap I could adapt my customisations too without having to sift through the old bootstrap.

Finally, I created a `main.scss` file inside the `assets` folder and imported all of the above files like this:

```scss
---
# Only the main Sass file needs front matter 
---

@import "variables";
@import "bootstrap-4-5-0/bootstrap";
@import "bootswatch";
@import "bootstrap_customisation";
```

### Layout & Customisation

I had to update the Gemfile and run bundle install to install the latest version of jekyll and get rid of some of the extra crap I had in here.

then clear it with `bundle clean` and update `bundle update`

now I can run `jekyll serve` without `bundle exec jekyll serve`

Then I manually updated `_syntax-highlighting.scss` to use my theme colours because I was really sick of all the red! I also updated the `_bootstrap_customisation.scss` with a few more things to make it look nice.



All my images were not responsive in the old design (or indeed formatted properly _at all_) but I also didn't want to go back and update every single `img` tag on my site so I added another line to my `_bootstrap_customisation.scss` file to convert all my images to use the bootstrap `img-fluid` class using the `@extend` keyword:

```scss
img {
  @extend .img-fluid;
  @extend .rounded; 
  @extend .mx-auto; 
  @extend .d-block
}
```





![The Dark Souls Board Game](/images/darksouls/15_enemies_painted.jpg)

https://medium.com/better-programming/an-introduction-to-using-jekyll-with-bootstrap-4-6f2433afeda9

[lissa]: http://www.lissaexplains.com/
[neopets]: https://www.neopets.com
[myspace]: https://www.myspace.com
[nineties]: https://www.cameronsworld.net/
[get-bootstrap]: https://getbootstrap.com/docs/4.5/getting-started/download/
[bootswatch]: https://bootswatch.com/pulse/