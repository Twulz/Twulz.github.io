---
layout: post
title:  "How to use posts"
date:   
categories: jekyll
tags: markdown
---

Notes to myself

<!--more-->

- Posts won't show up until the date(/time) has passed. This is possibly based on US time.
- Use `jekyll serve --watch` to build and display the site in `localhost:4000`. Use `jekyll serve --watch --drafts` to show posts in the `_drafts` folder too.

### Useful tools:
[Markdown Syntax Highlighting for Notepad++][highlight] Basically add this `userDefineLang.xml` file to `%APPDATA%\Notepad++\userDefineLang.xml`to enable Markdown syntax highlighting in Notepad++.

### How to Install (tested on Wheatley):
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

[highlight]:		https://github.com/Edditoria/markdown_npp_zenburn
[rubyDownload]:		http://rubyinstaller.org/downloads/