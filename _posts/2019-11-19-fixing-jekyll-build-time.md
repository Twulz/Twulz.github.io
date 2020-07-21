---
layout: post
title:  "Fixing Jekyll Build Time"
date:   2019-11-19
categories: Things Software Blog
tags: Jekyll Blog Github-Pages
---

I had slightly neglected this blog for a while - I had a lot of drafts and random notes about the place because my local build for Jekyll was taking 12 to 40 *minutes* to build. I had a few hours to kill so it was finally time to give this a bit of time.

<!--more-->

A good way to analyze where the problems are are to run `jekyll serve --profile` which indicates the build time for each file. From the below, you can see that my problems were quite clearly in the `_layouts/post.html` and `_includes\post\related_posts.html`

```sh
C:\Users\twulz\Documents\GitHub\Twulz.github.io>jekyll serve --profile
Configuration file: C:/Users/twulz/Documents/GitHub/Twulz.github.io/_config.yml
            Source: .
       Destination: ./_site
 Incremental build: disabled. Enable with --incremental
      Generating...
  Populating LSI...
Rebuilding index...

    Liquid Warning: Liquid syntax error (line 12): Expected id but found number in "post in site.categories.3dprinter reversed" in engprojects/printer/index.html

Filename                                                   | Count |    Bytes |    Time
-----------------------------------------------------------+-------+----------+--------
_layouts/post.html                                         |    44 |  599.33K | 460.732
_includes/post/related_posts.html                          |    47 |   49.28K | 460.347
_layouts/default.html                                      |    70 | 2488.55K |   1.384
_includes/asides.html                                      |    70 | 1218.98K |   0.819
_includes/asides/archive_tabs.html                         |    70 |  927.09K |   0.406
_includes/libs/list_tags                                   |   115 |  626.27K |   0.340
_includes/asides/recent_posts.html                         |    70 |  223.95K |   0.224
_includes/post/post_meta.html                              |    47 |   62.29K |   0.204
_includes/libs/list_categories                             |   115 |  319.73K |   0.189
_includes/navbar.html                                      |    72 |  207.82K |   0.102
_includes/head.html                                        |    72 |  132.12K |   0.085
_includes/bottom.html                                      |    72 |   95.03K |   0.083
atom.xml                                                   |     1 |  467.32K |   0.077
_includes/libs/list_pages                                  |     3 |   63.25K |   0.076
blog/tags.html                                             |     1 |   53.31K |   0.064
assets/bootstrap-2.1.1/js/bootstrap.custom.js              |     1 |   18.45K |   0.055
index.html                                                 |     1 |    9.07K |   0.040
blog/categories.html                                       |     1 |   26.63K |   0.039
_includes/post/post_pagenation.html                        |    47 |   22.76K |   0.032
_includes/post/socials_large.html                          |    47 |   63.38K |   0.032
assets/js/script.js                                        |     1 |    4.50K |   0.029
assets/bootstrap-2.3.2/js/bootstrap.custom.js              |     1 |   27.96K |   0.028
_includes/asides/tweets.html                               |    70 |   38.62K |   0.024
_posts/2016-02-18-rediscovering-the-blog.md                |     1 |   18.79K |   0.020
blog/archives.html                                         |     1 |   11.14K |   0.019
page4/index.html                                           |     1 |    8.20K |   0.018
_includes/script.html                                      |    72 |   23.91K |   0.018
_includes/footer.html                                      |    72 |   13.08K |   0.017
page3/index.html                                           |     1 |    9.37K |   0.016
page2/index.html                                           |     1 |    8.91K |   0.015
_includes/header.html                                      |    72 |   12.16K |   0.014
sitemap.xml                                                |     1 |   10.50K |   0.014
assets/css/style.css                                       |     1 |    9.11K |   0.014
_layouts/single-no-sidebar.html                            |     2 |   20.15K |   0.013
page5/index.html                                           |     1 |    3.56K |   0.010
_layouts/single-with-sidebar.html                          |     3 |    9.23K |   0.010
_includes/libs/truncate_exec                               |     5 |    1.49K |   0.009
_includes/post/comment.html                                |    47 |    0.00K |   0.009
assets/bootstrap-2.3.2/css/bootstrap.custom.css            |     1 |  103.51K |   0.009
assets/bootstrap-2.3.2/css/bootstrap-responsive.custom.css |     1 |   16.57K |   0.006
_includes/asides/about.html                                |    70 |   13.95K |   0.005
home.html                                                  |     1 |    2.01K |   0.005
rss.xml                                                    |     1 |    7.53K |   0.004
engprojects/other/index.html                               |     1 |    1.58K |   0.002
_includes/asides/github.html                               |    70 |   13.81K |   0.002
_includes/libs/truncate_start                              |     5 |    0.00K |   0.002
_includes/pagenation.html                                  |     5 |    1.39K |   0.002
_includes/libs/thumbnail                                   |     5 |    0.00K |   0.002
engprojects/printer/index.html                             |     1 |    1.52K |   0.002
_includes/libs/truncate_end                                |     5 |    0.00K |   0.001


                    done in 471.247 seconds.
 Auto-regeneration: enabled for '.'
C:/Ruby25-x64/lib/ruby/2.5.0/fileutils.rb:90: warning: already initialized constant FileUtils::VERSION
C:/Ruby25-x64/lib/ruby/gems/2.5.0/gems/fileutils-1.2.0/lib/fileutils/version.rb:4: warning: previous definition of VERSION was here
C:/Ruby25-x64/lib/ruby/2.5.0/x64-mingw32/etc.so: warning: already initialized constant Struct::Passwd
C:/Ruby25-x64/lib/ruby/2.5.0/fileutils.rb:1188: warning: already initialized constant FileUtils::Entry_::S_IF_DOOR
C:/Ruby25-x64/lib/ruby/gems/2.5.0/gems/fileutils-1.2.0/lib/fileutils.rb:1267: warning: previous definition of S_IF_DOOR was here
C:/Ruby25-x64/lib/ruby/2.5.0/fileutils.rb:1444: warning: already initialized constant FileUtils::Entry_::DIRECTORY_TERM
C:/Ruby25-x64/lib/ruby/gems/2.5.0/gems/fileutils-1.2.0/lib/fileutils.rb:1545: warning: previous definition of DIRECTORY_TERM was here
C:/Ruby25-x64/lib/ruby/2.5.0/fileutils.rb:1448: warning: already initialized constant FileUtils::Entry_::SYSCASE
C:/Ruby25-x64/lib/ruby/gems/2.5.0/gems/fileutils-1.2.0/lib/fileutils.rb:1549: warning: previous definition of SYSCASE was here
C:/Ruby25-x64/lib/ruby/2.5.0/fileutils.rb:1501: warning: already initialized constant FileUtils::OPT_TABLE
C:/Ruby25-x64/lib/ruby/gems/2.5.0/gems/fileutils-1.2.0/lib/fileutils.rb:1602: warning: previous definition of OPT_TABLE was here
C:/Ruby25-x64/lib/ruby/2.5.0/fileutils.rb:1555: warning: already initialized constant FileUtils::LOW_METHODS
C:/Ruby25-x64/lib/ruby/gems/2.5.0/gems/fileutils-1.2.0/lib/fileutils.rb:1656: warning: previous definition of LOW_METHODS was here
C:/Ruby25-x64/lib/ruby/2.5.0/fileutils.rb:1562: warning: already initialized constant FileUtils::METHODS
C:/Ruby25-x64/lib/ruby/gems/2.5.0/gems/fileutils-1.2.0/lib/fileutils.rb:1663: warning: previous definition of METHODS was here
    Server address: http://127.0.0.1:4000
  Server running... press ctrl-c to stop.
  ```

The problem seemed to be the loop in the related_posts; when I set this to be 1 instead of 5 I got the build time down to 8 minutes and was only a few seconds with the loop completely removed so this was definitely the source of the problem.

```html
                    <nav id="related-posts" class="well">
                        <h3>You might also like</h3>
                        <ul>
{% for post in site.related_posts limit:5 %}
                            <li class="related-post">
                                <span>{{ post.date | date: site.date_format }}</span> - 
                                <a href="{{ site.baseurl }}{{ post.url }}">{{ post.title }}</a>
                            </li>
{% endfor %}
                        </ul>
                    </nav>
```

I posted all of this info on a [Stack Overflow Question][stack-overflow] as I was at my wits' end - I could have removed the related posts loop but I wanted a more long-term solution. A friendly user pointed out that as [GitHub Pages doesn't support lsi anyway][lsi], setting lsi:false in my _config.yml file was enough to allow my local builds to cut down to 15 seconds.

```yml
# Configuration for jekyll
# NOTICE: GitHub forces to set `safe: true` in order to prohibit using plugins.
safe: false
source: .
destination: ./_site
plugins_dir: ./_plugins
lsi: false
kramdown:
  input: GFM
  syntax_highlighter: rouge
excerpt_separator: <!--more-->
repository: Twulz/Twulz.github.io
```


[lsi]: https://help.github.com/en/github/working-with-github-pages/about-github-pages-and-jekyll#configuring-jekyll-in-your-github-pages-site
[stack-overflow]:https://stackoverflow.com/questions/58973423/jekyll-site-takes-12-40-minutes-to-build-locally-problem-with-posts-and-relate