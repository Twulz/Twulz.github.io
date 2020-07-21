---
layout: post
title:  "Installing and Learning Jekyll and GitHub Pages"
date:   2016-02-17
categories: Things Software Blog
tags: Blog Jekyll Git Github-Pages
---

I have been talking about making a blog for all of my hobbies and projects for a very long time and here we are; *I finally made the Thing!*

<!--more-->

So I thought for my first official post I'd post about actually creating the blog and getting up and running using GitHub Pages and Jekyll because I found it surprisingly difficult to find where to start - especially using windows.

### Creating the skeleton using GitHub Pages

Barry Clark provided me with a great starting point with his article [Build a Blog With Jekyll And GitHub Pages][bclark] where he outlines how to get up and running as quickly as possible using GitHub pages to do all of the 'hard stuff' for you.

Using a mix of the two links above and a small amount of Googling I finally had a skeleton "Hello World!" version of this blog up on github pages. After some time of experimenting with the next few steps, I went ahead and made it a bit more pretty by implementing a theme I found on [on the Jekyll Repo][jekyllthemes] called [Slim Pickins][slim-pickins]. Next up was to allow for offline/local editing.

### Install a good editor
I'm currently using Notepad++ with a syntax highlighter called [Markdown Syntax Highlighting for Notepad++](highlight) to edit my files. I have included the modified file that I actually used [here](https://github.com/Twulz/Twulz.github.io/tree/master/projects/jekyll-blog/userDefineLang.xml)

### Installing GitHub
I have only briefly used git and github previously in a very superficial sense (only downloading zips of other's projects) so I also needed to download, install and figure out GitHub to get my files locally. This just involved installing the program, logging in and cloning the repo containing the site to my local machine.

### Installing Ruby and Jekyll
Julian Thilo has written a fantastic step-by-step guide to setting up [Jekyll on Windows][juthilo]. Basically; Jekyll relies on the Ruby language to operate so the next step was installing [Ruby][rubyDownload] and the Ruby Development Kit on my local machine. 

A few notes and hiccups I had while installing:

* I first installed the 64-bit version of Ruby and the DevKit simply because that matches my system however I encountered a few issues while installing and a quick Google revealed that the 64-bit version actually doesn't play nice with the other kids. So this was easily fixed - I uninstalled the 64-bit version and instead installed the 32-bit Ruby, I doubt a newbie like me would really be affected by the performance differences.
* I also for some reason attempted to install the DevKit in Program Files which is fine to unzip to but will not allow you to properly install. I then realised their recommendation was just for C:\RubyDevKit\
* I installed Python in the hopes of installing pygments but evidently that hasn't quite worked out, I'll put that on the to-fix list.
* Jekyll had a big list of errors when first trying `jekyll serve` so I used [this fix][stackoverflow] from Stack Overflow to re-install a working version of hitimes

## tl/dr: Quick and dirty 'How to Install':
1. Install Notepad++
2. Install [Markdown Syntax Highlighting for Notepad++][highlight] by adding the given `userDefineLang.xml` to `%APPDATA%\Notepad++\userDefineLang.xml` to enable Markdown syntax highlighting in Notepad++.
3. Install GitHub and clone the website directory to the local machine.
4. [Get Ruby for Windows][rubyDownload], 32-bit works better with everything and ensure you select "Add Ruby executables to your PATH".
5. [Get Ruby Development Kit for Windows][rubyDownload] (scroll down) - extract to `C:\RubyDevKit\`
    1. Open command prompt.
	2. `cd C:\RubyDevKit\`
	3. `ruby dk.rb init`
	4. `ruby dk.rb install`
6. Install Bundler: `gem install bundler`
7. Go to the GitHub website directory (where the Gemfile is) and run `bundle install` and possibly `bundle update`
8. Build the server with `jekyll serve --watch`, use `bundle exec jekyll serve` if errors show up and also set the `--drafts` flag if you want to include drafts.

## Editing and Previewing
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

### Other useful notes:
- Posts won't show up until the date(/time) has passed. This is possibly based on US time.
- Use `jekyll serve --watch` to build and display the site in `localhost:4000`. Use `jekyll serve --watch --drafts` to show posts in the `_drafts` folder too.

[rubyDownload]:		http://rubyinstaller.org/downloads/
[juthilo]:			http://jekyll-windows.juthilo.com/
[highlight]:		https://github.com/Edditoria/markdown_npp_zenburn
[jekyllthemes]:		https://github.com/jekyll/jekyll/wiki/Themes
[slim-pickins]:		https://github.com/chrisanthropic/slim-pickins-jekyll-theme
[bclark]:			https://www.smashingmagazine.com/2014/08/build-blog-jekyll-github-pages/
[stackoverflow]:	http://stackoverflow.com/questions/28985481/hitimes-require-error-when-running-jekyll-serve-on-windows-8-1