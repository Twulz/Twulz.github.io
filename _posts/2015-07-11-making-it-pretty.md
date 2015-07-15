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