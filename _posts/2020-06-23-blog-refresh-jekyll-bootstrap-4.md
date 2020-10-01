---
layout: post
title:  "Refreshing this Blog with Jekyll and Bootstrap 4"
date:   2020-06-23
categories: Things Software Blog
tags: Jekyll Blog Github-Pages Bootstrap
---

After playing with bootstrap a bit for the budget app, and with all of the web development I'm now doing at work I was really dragging my feet in updating this blog. 

<!--more-->

I made this blog in 2014 when the extent of my web development knowledge was what I learned on [Lissa Explains it All][lissa] (to my absolute delight it's still around, and still looks the same!) This was back in the late 90's and used on absolute bangers of websites as [Neopets][neopets], Geocities and of course my [MySpace][myspace] page. I basically knew enough not to plaster my shiny new blog with [amazing animations, javascript jokes and music that you can't turn off][nineties] (warning: I'm not joking about the music!)- but not quite enough to make a blog using best practices.

I'm older and somewhat wiser and tring to access my blog on mobile was hurting my soul, so definitely time for a refresh!

## All the Sins I wanted to fix

It may not be a great idea to lay out all the ways I've failed and/or just been lazy with not fixing these problems as they came up but it's oh-so-satisfying to see how far I've come, so bad ideas be damned, here's what needed fixin'!

### Domain name

My domain name was expiring so I'd have to renew (at exorbitant prices) or change. This one isn't really a "sin" but still needs attention!

### Responsiveness

As I mentioned in the intro, a huge source of embarrassment with my blog had to do with how it wasn't really responsive and was absolutely horrible on mobile.

![Imade-athing.com on mobile](/images/blog/oh_no_mobile.png)

...Gross... So that definitely needed to change!

![Imade-athing.com on mobile](/images/blog/non_responsive_images.png)

#nailedit, that's how images are meant to show on mobile yeah?

### Other weird mobile behaviour

The navigation menu also came apart on mobile:

![Imade-athing.com on mobile](/images/blog/weird_menu_mobile.png)

### Broken Links

One or two of my links would lead to my 404 not found page. Definitely need to fix that.

![Imade-athing.com on mobile](/images/blog/broken_links.png)

### Formatting issues

The project pages had major alignment issues, I think one of the original referenced fonts no longer existed.

![Imade-athing.com on mobile](/images/blog/project_page_alignment_issue.png)

The text on the drop-down menu of the navbar had lost its coloured formatting and was only visible on hover. Not great for usability!

![Imade-athing.com on mobile](/images/blog/Weird_Menu.png)

### Related posts

The _related posts_ were just the five latest posts, regardless of which post you were viewing. Not as grating as the other problems but still needed to fix.

![Imade-athing.com on mobile](/images/blog/related_posts.png)

## Fix: Domain name

I use [Namecheap](https://namecheap.com) as my domain registrar and my blog domain was coming up for renewal. This is when I discovered that even though I got my initial domain for maybe a dollar, for every year after this the price increases dramatically. It was actually cheaper to move to the `.com` version instead!

It's often not recommended to move your domain due to branding, search engine standing and losing absolute links etc. but as I haven't been actively promoting my blog I saw it as no great loss!

I went ahead and purchased the `imade-athing.com` domain, this time picking a much longer time frame to lock in the yearly price of roughly $10.

I then needed to update the `Advanced DNS Settings` in the Namecheap console with the CNAME record for my site (hosted on GitHub Pages) and the A records for GitHub.

![Advanced DNS Settings](/images/blog/dns_settings_namecheap.png)

I also updated the `custom domain` in `Settings` on GitHub with the new domain and after 24 hours my SSL certificate was enabled so I could check `Enforce HTTPS` so all traffic would be routed through HTTPS. 

Done!

## Fixing Responsiveness - Upgrade to Bootstrap 4

So now that I've outlined how badly I did in the past (or how badly things broke over time...) I should probably get to the fixing.

Lots of these problems were weird CSS issues so I decided to update to Bootstrap 4. The old blog did in fact use Bootstrap - version 2, so there was _some_ responsiveness where the menu moved to the newline, images became smaller sometimes, etc. I was planning to review the whole thing anyway though so I thought I should bring it up to the latest version of Bootstrap and learn how to create a layout properly.

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

I had to update the Gemfile and run `bundle install` to install the latest version of jekyll and get rid of all the extra crap I had in there. I ended up just with the github pages version of jekyll. 

```Gemfile
source "https://rubygems.org"

gem "github-pages", group: :jekyll_plugins
```

Then I had to clean my environment with `bundle clean` and update `bundle update`. Now I can run `jekyll serve` again without the `bundle exec` prefix.

I also got rid of all the crap from my `_config.yml` file, I'm going to add back in the config as I use it. Here's the cleaned version at this stage:

```yml
# Configuration for Jekyll
safe: false
source: .
destination: ./_site
lsi: false
kramdown:
  input: GFM
  syntax_highlighter: rouge
excerpt_separator: <!--more-->

# Configuration for site
title: I Made a Thing!
description: A personal log of the Things I've Made
author: Twulz
url: https://twulz.github.com
baseurl: ""
repository: "Twulz/Twulz.github.io"
lang: EN-AU

# Configuration for blog
lang: en
paginate: 10
columns: 3
date_format: "%B %d, %Y"
truncate_len: 200
recent_posts: 10

# Configuration for navbar
navbar_list:
- name: Home
  link: /
- name: Blog
  link: /blog/
  dropdown: &dropdown
  - name: Archives
    link: /blog/archives
  - name: Categories
    link: /blog/categories
  - name: Tags
    link: /blog/tags
- name: Things
  dropdown: &dropdown
  - name: Engineering Things
    link: /engprojects/
  - name: Miniature Things
    link: /mini/
  - name: Gardening Things
    link: /garden/
- name: About
  link: /about.html

exclude:
  - Gemfile
  - Gemfile.lock
  - Rakefile
  - README.md
```

With all of this installed my site finally builds but has no CSS because all of the class names from Bootstrap 2 have changed in Bootstrap 4 - next time I'll start making it pretty again!









https://medium.com/better-programming/an-introduction-to-using-jekyll-with-bootstrap-4-6f2433afeda9

[lissa]: http://www.lissaexplains.com/
[neopets]: https://www.neopets.com
[myspace]: https://www.myspace.com
[nineties]: https://www.cameronsworld.net/
[get-bootstrap]: https://getbootstrap.com/docs/4.5/getting-started/download/
[bootswatch]: https://bootswatch.com/pulse/