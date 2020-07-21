---
layout: post
title:  "Rediscovering the Blog"
date:   2016-02-18 16:30:00
categories: Things Software Blog
tags: Jekyll Blog
---
After setting up this blog and finally getting up to producing some content for it - I may have got super busy and abandoned the project for a while, however now I have decided to keep it up as I have a few projects in mind that I would like to log and here we are!

<!--more-->

That said, after all this time things have changed in the jekyll world apparently and my set up no longer worked (using the steps outlined in [Installing and Learning Jekyll][learning-jekyll] so these are the steps I used to get up and running again:
1. Run `gem update && gem cleanup` in the command line to update all Gems
2. Now after running `jekyll serve --watch` the following error is shown:
```
Configuration file: D:/Documents/GitHub/Twulz.github.io/_config.yml
       Deprecation: The 'plugins' configurationoption has been renamed to 'plugins_dir'. Please update your config file accordingly.
jekyll 3.1.1 | Error:  uninitialized constant Jekyll::Gist
```
So I changed my `_config.yml` file to reflect these changes.
4. Aaaaaand check out this huge error message, though it still has "server running..." at the end?
```
Configuration file: D:/Documents/GitHub/Twulz.github.io/_config.yml
       Deprecation: The 'plugins' configurationoption has been renamed to 'plugins_dir'. Please update your config file accordingly.
       Deprecation: You appear to have pagination turned on, but you haven't included the `jekyll-paginate` gem. Ensure you have `gems: [jekyll-paginate]` in yo
ur configuration file.
            Source: .
       Destination: ./_site
 Incremental build: disabled. Enable with --incremental
      Generating...

  Populating LSI...
Rebuilding index...
                      Liquid Exception: No such file or directory - python C:/Ruby22-x64/lib/ruby/gems/2.2.0/gems/pygments.rb-0.6.3/lib/pygments/mentos.py in D:
/Documents/GitHub/Twulz.github.io/_posts/2015-04-30-welcome-to-jekyll.markdown
                    done in 0.195 seconds.
       Deprecation: You appear to have pagination turned on, but you haven't included the `jekyll-paginate` gem. Ensure you have `gems: [jekyll-paginate]` in yo
ur configuration file.
  Please add the following to your Gemfile to avoid polling for changes:
    gem 'wdm', '>= 0.1.0' if Gem.win_platform?
 Auto-regeneration: enabled for '.'
Configuration file: D:/Documents/GitHub/Twulz.github.io/_config.yml
       Deprecation: The 'plugins' configurationoption has been renamed to 'plugins_dir'. Please update your config file accordingly.
    Server address: http://127.0.0.1:4000/
  Server running... press ctrl-c to stop.
```

Apparently with Jekyll 3.0 `jekyll-paginate` has been retired, use of [Octopress Paginate][octopress] is an alternative as shown in [this jekyll talk post][paginate].
I installed Octopress-Paginate using the instructions on their page: first manually using `gem install octopress-paginate`
and then adding the gem to the Jekyll configuration:
```
gems:
 - octopress-paginate
```

Now I just get the following error:
```
Configuration file: D:/Documents/GitHub/Twulz.github.io/_config.yml
jekyll 3.1.1 | Error:  uninitialized constant Jekyll::Gist
```

Another fix: uninstall all gems and reinstall everything using `gem uninstall --all` then `gem install github-pages`
The first time there was an error, after running `gem install github-pages` again everything seemed to install correctly.


Info from page: [https://rubygems.org/gems/jekyll-gist/versions/1.4.0]
gem install jekyll
gem install bundler
gem install rake
gem install rspec
gem install webmock

Now error:
```
C:/Ruby22/lib/ruby/gems/2.2.0/gems/bundler-1.11.2/lib/bundler/resolver.rb:354:in `block in verify_gemfile_dependencies_are_found!': Could not find gem 'rdiscoun
t x86-mingw32' in any of the gem sources listed in your Gemfile or available on this machine. (Bundler::GemNotFound)
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/bundler-1.11.2/lib/bundler/resolver.rb:330:in `each'
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/bundler-1.11.2/lib/bundler/resolver.rb:330:in `verify_gemfile_dependencies_are_found!'
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/bundler-1.11.2/lib/bundler/resolver.rb:199:in `start'
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/bundler-1.11.2/lib/bundler/resolver.rb:183:in `resolve'
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/bundler-1.11.2/lib/bundler/definition.rb:198:in `resolve'
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/bundler-1.11.2/lib/bundler/definition.rb:137:in `specs'
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/bundler-1.11.2/lib/bundler/definition.rb:182:in `specs_for'
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/bundler-1.11.2/lib/bundler/definition.rb:171:in `requested_specs'
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/bundler-1.11.2/lib/bundler/environment.rb:18:in `requested_specs'
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/bundler-1.11.2/lib/bundler/runtime.rb:13:in `setup'
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/bundler-1.11.2/lib/bundler.rb:92:in `setup'
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/jekyll-3.1.1/lib/jekyll/plugin_manager.rb:33:in `require_from_bundler'
        from C:/Ruby22/lib/ruby/gems/2.2.0/gems/jekyll-3.1.1/bin/jekyll:9:in `<top (required)>'
        from C:/Ruby22/bin/jekyll:23:in `load'
        from C:/Ruby22/bin/jekyll:23:in `<main>'

```

`gem install bundler`



So after getting myself up and running with a barebones blog yesterday I decided that I needed to make it a little more pretty. I've found many templates/themes online, there is a great list featured [on the Jekyll Repo][jekyllthemes].

The first step was cloning the appropriate repo and getting it up and running locally before making any changes. These themes come with a Gemfile which lets you install all the required gems using *bundler* (which I realised was the program mentioned in that first 'recommended install guide' from yesterday's post. This is very simply installed with `gem install bundler`
Then to install the required dependencies it's just a matter of navigating to that newly cloned directory and running `bundle install`
Again, I encountered a few issues with "cannot load such file", because of course these things can never be that straight forward!
A little more Googling gave me the idea to use `bundle update` to make sure all of the required gems are up to date, which brought me back to the small issue with hitimes which I had yesterday and fixed with [this method][stackoverflow].
Finally I had a very simple pretty blog with no content!

But of course I wasn't happy with just a "simple" pretty blog, I kept searching for more advanced options which opened a whole new can of worms. I attempted to create a blog using two different templates; [Jekyll Experiment][jekyll-experiment] and [Slim Pickins][slim-pickins] but both came back with errors such as below where `x is not a class` which prevented me from building the sites locally.

```
C:\Users\Alicia\Documents\GitHub\Twulz.github.io>jekyll serve --watch
Configuration file: C:/Users/Alicia/Documents/GitHub/Twulz.github.io/_config.yml
jekyll 2.5.3 | Error:  Gist is not a class
```

Slim Pickins did not even build on GitHub pages so I am assuming that is a version you must build yourself before pushing to github.

Eventually after much Googling, a little swearing and a few days of installing and re-installing I finally came to the realisation that this error is thrown in ruby when a name is reserved and after reading [this post][gist] I simply tried changing the name of `Gist` to `GistTag` in the following code in `_plugins/gist.rb`:

{% highlight ruby %}
module Jekyll
  class GistTag < Liquid::Tag
    def initialize(tag_name, args, tokens)
# etc etc
{% endhighlight %}

Et voila! The jekyll experiment website was finally working (albeit with warnings) locally. Phew! Now I just need to customise it.

Another small error that I encountered was the fact that the `--drafts` flag for `jekyll serve` would throw an error:

```
jekyll serve --drafts
...
jekyll 2.5.3 | Error: Numerical argument is out of domain - "sqrt"
```

However after renaming the drafts files to conform to the required final post format e.g. `2015-07-11-making-it-pretty.md` fixed this problem.




Just for my own records, this is the exact warnings that comes up for `jekyll serve` at this point in time:

```
C:\Users\Alicia\Documents\GitHub\Twulz.github.io>jekyll serve --watch
Configuration file: C:/Users/Alicia/Documents/GitHub/Twulz.github.io/_config.yml
            Source: .
       Destination: ./_site
      Generating...

  Populating LSI...
Rebuilding index...
                    C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Comparable#== will no more rescue exceptions of #<=> in the next release.
C:/Ruby22/lib/ruby/gems/2.2.0/gems/classifier-reborn-2.0.3/lib/classifier-reborn/lsi.rb:237: warning: Return nil in #<=> if the comparison is inappropriate or avoid such comparison.
     Build Warning: Layout 'nil' requested in atom.xml does not exist.
     Build Warning: Layout 'nil' requested in rss.xml does not exist.
     Build Warning: Layout 'nil' requested in sitemap.xml does not exist.
                    done.
  Please add the following to your Gemfile to avoid polling for changes:
    gem 'wdm', '>= 0.1.0' if Gem.win_platform?
 Auto-regeneration: enabled for '.'
Configuration file: C:/Users/Alicia/Documents/GitHub/Twulz.github.io/_config.yml
    Server address: http://127.0.0.1:4000
  Server running... press ctrl-c to stop.
```


[jekyllthemes]:		https://github.com/jekyll/jekyll/wiki/Themes
[jekyll-experiment]:https://github.com/tokkonopapa/jekyll-experiment
[slim-pickins]:		https://github.com/chrisanthropic/slim-pickins-jekyll-theme
[stackoverflow]:	http://stackoverflow.com/questions/28985481/hitimes-require-error-when-running-jekyll-serve-on-windows-8-1
[gist]:				http://brandontilley.com/2011/01/31/gist-tag-for-jekyll.html

[learning-jekyll]:	http://twulz.github.io/blog/2015/07/installing-and-learning-jekyll/
[paginate]:			https://talk.jekyllrb.com/t/build-problem-missing-post/1241/5
[octopress]:		https://github.com/octopress/paginate