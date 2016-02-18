---
layout: post
title:  "Reviving the blog"
date:   2016-02-16
categories: jekyll
tags: markdown
---
So I went through all of the trial and error to set up this blog - just to abandon it. I am now back and ready to jump back in and finally Make some Things!

<!--more-->

### Picking up the pieces
I must have finished my last blog without recording the changes I'd made; I eventually got the [Slim Pickins][slim-pickins] layout working however attempting to rebuild this on my local machine proved very difficult. 

I tried updating to the current version which implements changes using octopress, etc. however this created more problems than it solved. After much trial and error, I finally could re-build the site on my computer and push it to GitHub.

#### Steps to fix it:
1. Rename `plugins` to `plugins_dir` in _config.yml
2. Add the following to _config.yml

    ```
    gems:
     - jekyll-paginate
    ```

3. Rename `GistTag` to `Gist` in _plugins/gist.rb
4. Remove the first blog post which made use of pygments/syntax highlighting.
4. Rename `layout: nil` to 'layout: null` in atom.xml, rss.xml and sitemap.xml
5. Add `gem 'wdm', '>= 0.1.0' if Gem.win_platform?` to Gemfile

Now my code blocks won't have any syntax highlighting, but I can add that in later when I figure out how to *not* break it.

### Formatting Discovery:
To do the indented code block above, indent your fenced block by (4 * bullet_indent_level) spaces and have a newline above and below the fenced block. E.g. above I used 4*1= 4 spaces above.

[slim-pickins]:		https://github.com/chrisanthropic/slim-pickins-jekyll-theme