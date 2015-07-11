---
layout: post
title:  "Making it Pretty!"
date:   2015-07-11 14:15:00
---

# **I'm Making a Pretty Thing!**

So after getting myself up and running with a barebones blog yesterday I decided that I needed to make it a little more pretty. I've found many templates/themes online, there is a great list featured [on the Jekyll Repo][jekyllthemes].

The first step was cloning the appropriate repo and getting it up and running locally before making any changes. These themes come with a Gemfile which lets you install all the required gems using *bundler* (which I realised was the program mentioned in that first 'recommended install guide' from yesterday's post. This is very simply installed with `gem install bundler`
Then to install the required dependencies it's just a matter of navigating to that newly cloned directory and running `bundle install`
Again, I encountered a few issues with "cannot load such file", because of course these things can never be that straight forward!
A little more Googling gave me the idea to use `bundle update` to make sure all of the required gems are up to date, which brought me back to the small issue with hitimes which I had yesterday and fixed with [this method][stackoverflow].
Finally I had a pretty blog with no content!

[jekyllthemes]:		https://github.com/jekyll/jekyll/wiki/Themes
[stackoverflow]:	http://stackoverflow.com/questions/28985481/hitimes-require-error-when-running-jekyll-serve-on-windows-8-1