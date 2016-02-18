---
layout: post
title:  "Installing and Learning Jekyll"
date:   2015-07-10 18:08:00
categories: jekyll
---

I have been talking about making a blog for all of my hobbies and projects for a very long time and here we are; *I finally made the Thing!*

<!--more-->

So I thought for my first official post I'd post about actually creating the blog and getting up and running using GitHub Pages and Jekyll because I found it surprisingly difficult to find where to start - especially using windows.

# Creating the skeleton using GitHub Pages

Barry Clark provided me with a great starting point with his article [Build a Blog With Jekyll And GitHub Pages][bclark] where he outlines how to get up and running as quickly as possible using GitHub pages to do all of the 'hard stuff' for you.

I also used Anna Debenham's [Get Started With GitHub Pages (Plus Bonus Jekyll)][24ways]

Using a mix of the two links above and a small amount of Googling I finally had a skeleton "Hello World!" version of this blog. Next up was to allow for offline/local editing.

# Installing GitHub
I have only briefly used git and github previously in a very superficial sense (only downloading zips of other's projects) so I also needed to download, install and figure out [GitHub][github] to get my files locally.

# Installing Ruby and Jekyll
After installation I found this link to the official [GitHub Help Pages][githelp] who recommend installing jekyll using bundler to ensure the local version of Jekyll remains up-to-date (so the local build will exactly match that of GitHub Pages) however I did not actually use this method, I may need to re-visit this in future!

Julian Thilo has written a fantastic step-by-step guide to setting up [Jekyll on Windows][juthilo].

A few notes and hiccups I had while installing:

* I first installed the 64-bit version of Ruby and the DevKit simply because that matches my system however I encountered a few issues while installing and a quick Google revealed that the 64-bit version actually doesn't play nice with the other kids. So this was easily fixed - I uninstalled the 64-bit version and instead installed the 32-bit Ruby, I doubt a newbie like me would really be affected by the performance differences.
* I also for some reason attempted to install the DevKit in Program Files which is fine to unzip to but will not allow you to properly install. I then realised their recommendation was just for C:\RubyDevKit\
* I installed Python in the hopes of installing pygments but evidently that hasn't quite worked out, I'll put that on the to-fix list.
* Jekyll had a big list of errors when first trying `jekyll serve` so I used [this fix][stackoverflow] from Stack Overflow to re-install a working version of hitimes

# Editing and Previewing
1. Login to GitHub locally and ensure the appropriate repo is cloned to an appropriate local directory.
2. Open command prompt and navigate to the root directory `cd Twulz.github.io`
3. Run `jekyll serve --watch` and wait for the message `Server running...` The `--watch` flag ensures that when changes are made, the site will be updated automatically.
4. Open a browser and go to `http://localhost:4000/` to see the site.
5. Edit any required files.
6. Refresh the browser to see the changes.
7. When changes have been made, GitHub will show this so enter a summary and description.
8. Click `Commit to Master`
9. Click `Sync` in the top right hand corner
10. The changes will now show up on the site at `twulz.github.io`

# Useful Links
* Adam Pritchard has posted a great [Cheatsheet for Markdown][cheatsheet] to make pages look a little more interesting.
* Stack Overflow also has an [Markdown Help][markdownhelp] page showing many Markdown shortcuts which are also used with Jekyll.
* Tom Preston-Werner wrote an interesting article [Blogging Like a Hacker][bloghacker] concerning Jekyll which I think I will go back to after playing around a little more.

[juthilo]:			http://jekyll-windows.juthilo.com/
[cheatsheet]:		https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet
[bclark]:			http://www.smashingmagazine.com/2014/08/01/build-blog-jekyll-github-pages/
[24ways]:			http://24ways.org/2013/get-started-with-github-pages/
[github]:			https://windows.github.com/
[githelp]:			https://help.github.com/articles/using-jekyll-with-pages/
[bloghacker]:		http://tom.preston-werner.com/2008/11/17/blogging-like-a-hacker.html
[stackoverflow]:	http://stackoverflow.com/questions/28985481/hitimes-require-error-when-running-jekyll-serve-on-windows-8-1
[markdownhelp]:		http://stackoverflow.com/editing-help