---
layout: post
title:  "Refreshing this Blog - Post page layout"
date:   2020-07-21
categories: Things Software Blog
tags: Jekyll Blog Github-Pages Bootstrap
---

In this post I build the “Post page” layout for my new refreshed blog using Bootstrap 4, Jekyll and GitHub Pages.

<!--more-->

## Post Layout

For the post layout I could reuse many of the [components]({% post_url 2020-07-07-blog-refresh-cards %}) I had previously built [for the Homepage]({% post_url 2020-07-14-blog-refresh-home-page %}); header, footer, navbar and the asides (_About_, _Recent_ and _Archives_).

### Post Metadata

I reused the card component of bootstrap for the post metadata and related posts I have at the bottom of all the posts but again had to play with the margin and padding.

![Post Metadata](/images/blog/post_layout_meta.png)

###### post_meta.html

```html
{% raw %}{% assign post_meta = true %}{% endraw %}
	<div class="card my-2 flex-fill">
		<div class="card-body">
			<h5 class="card-title">
				<a href="#">
					<i class="far fa-file" aria-hidden="true"></i>
					Post Details
				</a>
			</h5>
			<p class="card-text">
				<ul class="list-unstyled">
					<li id="meta-user">
						<ul class="list-unstyled author-list">
							<li class="list-inline-item">
								<span class="meta">
									<i class="fa fa-user"></i> Author:
								</span>
							</li>
							<li class="list-inline-item">
								{% raw %}{{ site.author }}{% endraw %}
							</li>
						</ul>
					</li>
					{% raw %}{% if page.categories.first %}{% endraw %}
						<li id="meta-category">
							<ul class="list-unstyled tag-list">
								<li class="list-inline-item">
									<span class="meta">
										<i class="fa fa-user"></i> Categories:
									</span>
								</li>
								{% raw %}{% include libs/list_categories.html %}{% endraw %}
							</ul>
						</li>
					{% raw %}{% endif %}
					{% if page.categories.first %}{% endraw %}
						<li id="meta-tags">
							<ul class="list-unstyled tag-list">
								<li class="list-inline-item">
									<span class="meta">
										<i class="fas fa-tags"></i> Tags:
									</span>
								</li>
								{% raw %}{% include libs/list_tags.html %}{% endraw %}
							</ul>
						</li>
					{% raw %}{% endif %}{% endraw %}
				</ul>
			</p>
		</div>
	</div>
{% raw %}{% assign post_meta = nil %}{% endraw %}
```

### Post Pagination

Next up was new pagination buttons. The old website had simple links but I decided to make use of Bootstrap's button components instead this time.

![Post Pagination](/images/blog/post_pagination.png)

###### post_pagenation.html
```html
<section id="post_pagenation">
	<ul class="pagination justify-content-between">
		{% raw %}{% if page.previous.url %}{% endraw %}
			<li class="page-item">
				<a href="{% raw %}{{ site.baseurl }}{{ page.previous.url }}{% endraw %}" rel="previous" title="{% raw %}{{ page.previous.title }}{% endraw %}">&laquo;&nbsp;{% raw %}{{ page.previous.title | truncatewords: 15 }}{% endraw %}</a>
			</li>
		{% raw %}{% endif %}{% if page.next.url %}{% endraw %}
			<li class="page-item">
				<a href="{% raw %}{{ site.baseurl }}{{ page.next.url }}{% endraw %}" rel="next" title="{% raw %}{{ page.next.title }}{% endraw %}">{% raw %}{{ page.next.title | truncatewords: 15 }}{% endraw %}&nbsp;&raquo;</a>
			</li>
		{% raw %}{% endif %}{% endraw %}
	</ul>
</section>
```

### Breadcrumbs

The last remaining component for the Post layout was the breadcrumbs, but turns out this was a _huge_ undertaking that I redid a number of times so I've taken it out of this post and [moved it to the next.]({% post_url 2020-07-28-blog-refresh-project-layout %})

### Full Post Layout

I split the layout containing the breadcrumbs from the post layout so I could use it on other pages so below I've got `general.html` which uses the `default.html` layout, and then the `post.html` layout which uses the `general.html` layout.

###### general.html
```html
---
layout: default
group: Blog
---
<div class="col-xl-8 col-lg-9">

	{% raw %}{% include breadcrumbs.html %}{% endraw %}

	<article>

		<h1>
			{% raw %}{{ page.title }}{% endraw %}
		</h1>

		{% raw %}{{ content }}{% endraw %}

	</article>
</div>
```

###### post.html
```html
---
layout: general
group: Blog
---

<p class="h6">
	<time datetime="{% raw %}{{ page.date | date_to_xmlschema }}{% endraw %}">{% raw %}{{ page.date | date: site.date_format }}{% endraw %}</time>
</p>

<div class="post-image">
	<img src="{% raw %}{{ site.baseurl }}{{ page.related_image.path }}{% endraw %}" alt="{% raw %}{{ page.related_image.alt }}{% endraw %}" />
</div>

{% raw %}{{ content }}

{% include post/post_pagenation.html %}{% endraw %}

<hr />

<div class="row justify-content-center">
	<div class="col-md-6 d-flex align-items-stretch">
		{% raw %}{% include post/post_meta.html %}{% endraw %}
	</div>
	<div class="col-md-6 d-flex align-items-stretch">
		{% raw %}{% include post/related_posts.html %}{% endraw %}
	</div>
</div>
```

#### Other Post Fix-ups

All my images were not responsive in the old design (or indeed formatted properly _at all_) but I also didn't want to go back and update every single `img` tag on my site so I added another line to my `_bootstrap_customisation.scss` file to convert all my images to use the bootstrap `img-fluid` class using the `@extend` keyword. I might change this shortly, but for now this looks OK for the majority of my blog posts.

###### _bootstrap_customisation.scss

```scss
img {
  @extend .img-fluid;
  @extend .rounded; 
  @extend .mx-auto; 
  @extend .d-block
}
```

Then I manually updated `_syntax-highlighting.scss` to use my theme colours because I was really sick of all the red! It also looks much cleaner with a smaller tab size. I also updated the `_bootstrap_customisation.scss` with a few more things to make it look nice. I know I said I didn't want to do much CSS but here we are!

And all done! The new site is finally starting to look respectable again!

![Post Layout](/images/blog/post_layout.png)