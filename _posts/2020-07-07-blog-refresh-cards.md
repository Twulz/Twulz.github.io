---
layout: post
title:  "Refreshing this Blog - Cards and Asides"
date:   2020-07-07
categories: Things Software Blog
tags: Jekyll Blog Github-Pages Bootstrap
---

In this post I add more content modules to eventually build the home page layout for my new refreshed blog using Bootstrap 4, Jekyll and GitHub Pages.

<!--more-->

## Container Layout

In Bootstrap 4 the `container-fluid` class is used to set up the responsive grid I'll be using for all of the asides. I chose to add this to the `default.html` code so everything included would be containerised and the asides don't need to be added to each page individually.

###### default.html
```html
<!DOCTYPE html>
<html lang="{% raw %}{{ site.lang | default: "en-AU" }}{% endraw %}">

  {% raw %}{% include head.html %}{% endraw %}

  <body>
    
    {% raw %}{% include header.html %}{% endraw %}

    {% raw %}{% include navbar.html %}{% endraw %}


    <div class="container-fluid my-2">
      <div class="row justify-content-center">

        {% raw %}{{ content }}{% endraw %}

        {% raw %}{% include asides.html %}{% endraw %}
        
      </div>
    </div>

    {% raw %}{% include footer.html %}{% endraw %}

    {% raw %}{% include scripts.html %}{% endraw %}

  </body>
</html>
```

Now I had to set up the `asides.html` file. I did some testing with the layout after implementing the cards in the next section so I've skipped ahead and just put the finalised code here. The Bootstrap 4 library uses a grid system where the container is divided into 12 sections so each div has a number representing how many of those 12-units that this section takes up for each viewport.

E.g. `col-sm-12 col-md-8 col-lg-12` means that for mobile (small) screens this div takes up 12, or the whole container above it. On medium screens it takes up 8/12 or (or 2/3) of the screen and finally when you get to large (and extra-large) screens it takes up the full width again.

###### asides.html

```html
<div class="col-lg-3 col-md-12 col-sm-12">
    <div class="row justify-content-center">
        <div class="col-sm-12 col-md-8 col-lg-12">
            {% raw %}{% include asides/about.html %}{% endraw %}
        </div>
        <div class="col-sm-6 col-lg-12">
            {% raw %}{% include asides/recent_posts.html %}{% endraw %}
        </div>
        <div class="col-sm-6 col-lg-12 d-flex align-items-stretch">
            {% raw %}{% include asides/archives.html %}{% endraw %}
        </div>
    </div>
</div>
```

### Aside modules

All of the "asides" are just cards so they're fairly straight-forward modules: About Me, Recent Posts and Archives. I also had to look up the [Font Awesome](https://fontawesome.com/icons?d=gallery) icons that would be relevant too. 

Cards simply take up the width of the container and the height of the contents so the actual layout parameters are defined above in `asides.html`.

###### about.html

```html
<div class="card my-2">
    <div class="card-body">
        <h5 class="card-title">
            <a href="{% raw %}{{ site.baseurl }}{% endraw %}/about/">
                <i class="fa fa-user" aria-hidden="true"></i>
                About Me
            </a>
        </h5>
        <p class="card-text">Engineer, maker, do-er...
            <br>I basically just like to make things.</p>
    </div>
</div>
```

###### archives.html

```html
<div class="card my-2">
    <div class="card-body">
        <h5 class="card-title">
            <a href="{% raw %}{{ site.baseurl }}{% endraw %}/blog/archives/">
                <i class="fas fa-book" aria-hidden="true"></i>
                Archives
            </a>
        </h5>
        <p class="card-text">
            <ul class="nav nav-tabs">
                <li class="nav-item">
                    <a class="nav-link active" id="categories-tab" data-toggle="tab" href="#categories" role="tab" aria-controls="categories" aria-selected="true">
                        Categories
                    </a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" id="tags-tab" data-toggle="tab" href="#tags" role="tab" aria-controls="tags" aria-selected="false">
                        Tags
                    </a>
                </li>
            </ul>

            <div class="tab-content" id="categories-tags">
                <div class="tab-pane fade show active" id="categories" role="tabpanel" aria-labelledby="categories-tab">
                    <ul class="list-inline">
                        {% raw %}{% include libs/list_categories.html %}{% endraw %}
                    </ul>
                </div>
                <div class="tab-pane fade" id="tags" role="tabpanel" aria-labelledby="tags-tab">
                    <ul class="list-inline">
                        {% raw %}{% include libs/list_tags.html %}{% endraw %}
                    </ul>
                </div>
            </div>
        </p>
    </div>
</div>
```

###### recent_posts.html

```html
<div class="card my-2">
    <div class="card-body">
        <h5 class="card-title">
            <a href="{% raw %}{{ site.baseurl }}{% endraw %}/blog/archives/">
                <i class="far fa-file-alt" aria-hidden="true"></i>
                Recent Posts
            </a>
        </h5>
        <p class="card-text">
            <ul class="list-unstyled">
                {% raw %}{% for post in site.posts limit: site.recent_posts %}{% endraw %}
                    <li>
                        <p>
                            {% raw %}{{ post.date | date: "%d-%m-%Y" }}{% endraw %}: <a href="{% raw %}{{ site.baseurl }}{{ post.url }}{% endraw %}">{% raw %}{{ post.title }}{% endraw %}</a>
                        </p>
                    </li>
                    {% raw %}{% unless forloop.last %}{% endraw %}
                        <li class="divider"></li>
                    {% raw %}{% endunless %}{% endraw %}
                {% raw %}{% endfor %}{% endraw %}
            </ul>
        </p>
    </div>
</div>
```
Here is a screenshot of all the completed cards (on a medium screen):
![Completed Asides](/images/blog/cards_asides.png)
