---
layout: post
title:  "Reviving the blog"
date:   2016-02-17
categories: jekyll, markdown
---

### Steps to fix the blog:
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

Now my code blocks won't have any syntax highlighting, but I can add that in later when I figure out how to -not- break it.

### Formatting Discovery:
To do the indented code block above, indent your fenced block by (4 * bullet_indent_level) spaces and have a newline above and below the fenced block. E.g. above I used 4*1= 4 spaces above.